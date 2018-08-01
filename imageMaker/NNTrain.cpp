#include "NNTrain.h"

namespace imgmaker
{
	CNNTrain::CNNTrain(const char* _filefold, const char* _modelFilePath)
	{
		this->filefold = _filefold;
		this->modelFilePath = _modelFilePath;
	}

	CNNTrain::~CNNTrain()
	{
	}

	bool CNNTrain::loadModel(const char * trainname)
	{
		bool success = false;

		imgmaker::setLogLevel(imgmaker::IMGMAKER_LOG_LEVEL_CRITICAL);
		imgmaker::logCritical("construct network begin...");
		success = mNetWork.loadModel(modelFilePath, trainname,classes,mCategory);
		if (!success)
		{
			success = train(trainname);
			assert(success);
			mCategory.clear();
			success = mNetWork.loadModel(modelFilePath, trainname, classes, mCategory);
			assert(success);
		}
		imgmaker::logCritical("construct network done.");

		return success;
	}

	bool CNNTrain::train(const char *_trainname)
	{
		bool success = false;

		imgmaker::setLogLevel(imgmaker::IMGMAKER_LOG_LEVEL_CRITICAL);

		//load train images  train labels
		imgmaker::logCritical("loading training data...");
		std::vector<std::string> filenames;
		std::vector<label_t> filelabels;
		success = getFiles(filefold, filenames, filelabels, mCategory);
		this->classes = mCategory.size();
		assert(success);
		std::vector<IplImage*> images;
		success=load_batch_images(filenames, images,0);
		assert(success && images.size() > 0);
		assert(images.size()==filelabels.size());
		//shuffle images and labels
		shuffle_data(images, filelabels);
		//set train data & validate data
		std::vector<IplImage*> train_images;
		std::vector<label_t> train_labels;
		std::vector<IplImage*> validate_images;
		std::vector<label_t>validate_labels;
		to_trainset_validateset(images, filelabels, train_images, train_labels, validate_images, validate_labels);
		
		imgmaker::logCritical("load training data done. train set's size is %d,validate set's size is %d", train_images.size(), validate_images.size());

		float learningRate = 0.1f;
		const float decayRate = 0.8f;
		const float minLearningRate = 0.001f;
		const size_t testAfterBatches = 50;
		const size_t maxBatches = 10000;
		const size_t max_epoch = 5;
		const size_t batch = 128;//batch size
		const size_t channels = images[0]->nChannels;
		const size_t width = images[0]->width;
		const size_t height = images[0]->height;
		imgmaker::logCritical("max_epoch:%d,testAfterBatches:%d", max_epoch, testAfterBatches);
		imgmaker::logCritical("learningRate:%f ,decayRate:%f , minLearningRate:%f", learningRate, decayRate, minLearningRate);
		imgmaker::logCritical("channels:%d , width:%d , height:%d", channels, width, height);

		imgmaker::logCritical("construct network begin...");
		imgmaker::NetWork network(buildConvNet(batch, channels, width, height, classes));
		//network = buildConvNet(batch, channels, width, height);
		network.setLossFunctor(std::make_shared<imgmaker::crossEntropyFunctor>());
		network.setOptimizer(std::make_shared<imgmaker::SGD>(learningRate));
		network.setLearningRate(learningRate);
		imgmaker::logCritical("construct network done.");

		float val_accuracy = 0.0f;
		float train_loss = 0.0f;
		int train_batches = 0;
		float val_loss = 0.0f;

		//train
		imgmaker::logCritical("begin training...");
		std::shared_ptr<imgmaker::DataBucket> inputDataBucket = std::make_shared<imgmaker::DataBucket>(imgmaker::DataSize(batch, channels, width, height));
		std::shared_ptr<imgmaker::DataBucket> labelDataBucket = std::make_shared<imgmaker::DataBucket>(imgmaker::DataSize(batch, classes, 1, 1));
		size_t epochIdx = 0;
		while (epochIdx < max_epoch)
		{
			//before epoch start, shuffle all train data first
			shuffle_data(train_images, train_labels);
			size_t batchIdx = 0;
			while (true)
			{
				if (!fetch_data(train_images, inputDataBucket, train_labels, labelDataBucket, batchIdx*batch, batch))
				{
					break;
				}
				const float batch_loss = network.trainBatch(inputDataBucket, labelDataBucket);
				train_loss = imgmaker::moving_average(train_loss, train_batches + 1, batch_loss);
				train_batches++;
				if (batchIdx > 0 && batchIdx % testAfterBatches == 0)
				{
					std::tie(val_accuracy, val_loss) = test(network, 128, validate_images, validate_labels);
					imgmaker::logCritical("sample : %d/%d , learningRate : %f , train_loss : %f , val_loss : %f , val_accuracy : %.4f%%",
						batchIdx*batch, train_images.size(), learningRate, train_loss, val_loss, val_accuracy*100.0f);
					train_loss = 0.0f;
					train_batches = 0;
				}
				if (batchIdx >= maxBatches)
				{
					break;
				}
				batchIdx++;
			}
			if (batchIdx >= maxBatches)
			{
				break;
			}

			std::tie(val_accuracy, val_loss) = test(network, 128, validate_images, validate_labels);
			//update learning rate
			learningRate = max(learningRate*decayRate, minLearningRate);
			network.setLearningRate(learningRate);
			imgmaker::logCritical("epoch[%d] val_loss : %f , val_accuracy : %.4f%%", epochIdx++, val_loss, val_accuracy*100.0f);
			if (val_accuracy > 0.98)
				break;
		}
		
		std::tie(val_accuracy, val_loss) = test(network, 128, validate_images, validate_labels);
		imgmaker::logCritical("final val_loss : %f , final val_accuracy : %.4f%%", val_loss, val_accuracy*100.0f);
		success = network.saveModel(modelFilePath, _trainname, classes, mCategory);
		assert(success);
		imgmaker::logCritical("finished training.");
		return success;
	}

	std::pair<float, float>CNNTrain::test(imgmaker::NetWork& network, const size_t batch,
		const std::vector<IplImage*>& test_images, const std::vector<label_t>& test_labels)
	{
		assert(test_images.size() == test_labels.size() && test_images.size()>0);
		int correctCount = 0;
		float loss = 0.0f;
		int batchs = 0;
		for (size_t i = 0; i < test_labels.size(); i += batch, batchs++)
		{
			const size_t start = i;
			const size_t len = min(test_labels.size() - start, batch);
			const std::shared_ptr<imgmaker::DataBucket> inputDataBucket = convertVectorToDataBucket(test_images, start, len);
			const std::shared_ptr<imgmaker::DataBucket> labelDataBucket = convertLabelToDataBucket(test_labels, start, len,classes);
			const std::shared_ptr<imgmaker::DataBucket> probDataBucket = network.testBatch(inputDataBucket);

			//get loss
			const float batch_loss = network.getLoss(labelDataBucket, probDataBucket);
			loss = imgmaker::moving_average(loss, batchs + 1, batch_loss);

			const size_t labelSize = probDataBucket->getSize()._3DSize();
			const float* probData = probDataBucket->getData().get();
			for (size_t j = 0; j < len; j++)
			{
				const uint8_t stdProb = test_labels[i + j].data;
				const uint8_t testProb = getMaxIdxInArray(probData + j*labelSize, probData + (j + 1) * labelSize);
				if (stdProb == testProb)
				{
					correctCount++;
				}
			}
		}
		const float accuracy = (float)correctCount / (float)test_labels.size();
		return std::pair<float, float>(accuracy, loss);
	}

	void CNNTrain::Predict_Img(const char* filepath)
	{
		bool success = false;

		imgmaker::setLogLevel(imgmaker::IMGMAKER_LOG_LEVEL_CRITICAL);
		//train
		imgmaker::logCritical("begin test...");

		IplImage* PreImg = cvLoadImage(filepath);

		const std::shared_ptr<imgmaker::DataBucket> inputDataBucket = LoadPredictImage(PreImg);
		const std::shared_ptr<imgmaker::DataBucket> probDataBucket = mNetWork.testBatch(inputDataBucket);
		const size_t labelSize = probDataBucket->getSize()._3DSize();
		const float* probData = probDataBucket->getData().get();
		
		const uint8_t testProb = getMaxIdxInArray(probData + labelSize, probData + (1 + 1) * labelSize);
		imgmaker::logCritical("label : %d", testProb);

		//const cv::Mat srcGrayImg = samples[i].second;
		//cv::destroyAllWindows();
		//cvShowImage("src", PreImg);
		//cvWaitKey();
		
		imgmaker::logCritical("finished test.");
	}

	std::string  CNNTrain::Predict_Img(IplImage* PreImg)
	{
		bool success = false;

		imgmaker::setLogLevel(imgmaker::IMGMAKER_LOG_LEVEL_CRITICAL);
		//train
		imgmaker::logCritical("begin test...");

		const std::shared_ptr<imgmaker::DataBucket> inputDataBucket = LoadPredictImage(PreImg);
		const std::shared_ptr<imgmaker::DataBucket> probDataBucket = mNetWork.testBatch(inputDataBucket);
		const size_t labelSize = probDataBucket->getSize()._3DSize();
		const float* probData = probDataBucket->getData().get();

		const uint8_t testProb = getMaxIdxInArray(probData , probData + labelSize);
		std::string out = mCategory[testProb];
		imgmaker::logCritical("label : %d", testProb);

		imgmaker::logCritical("finished test.");
		return out;
	}

	std::shared_ptr<imgmaker::DataBucket> CNNTrain::LoadPredictImage(IplImage* &PreImg)
	{
		const int number = 1;
		const int channel = mNetWork.mSize.channels;
		const int width = mNetWork.mSize.width;
		const int height = mNetWork.mSize.height;
		std::shared_ptr<imgmaker::DataBucket> result(new imgmaker::DataBucket(imgmaker::DataSize(number, channel, width, height)));
		const size_t sizePerImage = channel*width*height;
		const float scaleRate = 1.0f / 255.0f;

		/*double seedx = width / PreImg->width;
		double seedy = height / PreImg->height;
		PreImg = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, channel);
		resizeImgage(inImg, PreImg,  seedx,  seedy);*/
		//----
		for (size_t i = 0; i < (size_t)number; i++)
		{
			//image data
			float* inputData = result->getData().get() + i*sizePerImage;
			const uint8_t* mdata = (uchar *)PreImg->imageData;//const uint8_t* imageData = &test_images[i].data[0];
			for (size_t j = 0; j < sizePerImage; j++)
			{
				inputData[j] = (float)mdata[j] * scaleRate;
			}
		}
		//image data
		/*float* inputData = result->getData().get() + sizePerImage;
		const uint8_t* mdata = (uchar *)PreImg->imageData;//const uint8_t* imageData = &test_images[i].data[0];
		for (size_t j = 0; j < sizePerImage; j++)
		{
			inputData[j] = (float)mdata[j] * scaleRate;
		}*/
		return result;
	}
}

