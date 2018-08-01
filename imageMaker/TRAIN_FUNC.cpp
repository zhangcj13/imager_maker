#include "TRAIN_FUNC.h"
namespace imgmaker
{
	//根据不同文件夹名字为分类，获取文件名字并取得器标签
	bool getFiles(const std::string foldname, std::vector<std::string> &filenames, std::vector<label_t> &filelabels, std::vector<std::string> &mCategory,
		std::string filecategory, uint8_t labeln)
	{
#ifdef WIN32  
		_finddata_t file;
		struct _finddata_t fileinfo;    //_finddata_t是一个结构体，要用到#include <io.h>头文件；
		long ld;
		if ((ld = _findfirst((foldname + "\\*").c_str(), &fileinfo)) != -1l){
			do{
				if ((fileinfo.attrib&_A_SUBDIR)) //如果是文件夹；
				{
					if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)  //如果文件名不是.或者,,,则递归获取子文件中的文件；
					{
						//getFiles(foldname + "\\" + fileinfo.name, filenames, filelabels, fileinfo.name, labeln);  
						getFiles(foldname + "\\" + fileinfo.name, filenames, filelabels, mCategory,
							fileinfo.name, labeln);//递归子文件夹
						//mLabel _mLabel;
						//_mLabel.first = fileinfo.name;
						//_mLabel.second = labeln;
						mCategory.push_back(fileinfo.name);
						labeln++;
					}
				}
				else   //如果是文件；
				{
					filenames.push_back(foldname + "\\" + fileinfo.name);
					label_t _label_t;
					_label_t.data = labeln;
					filelabels.push_back(_label_t);
				}
			} while (_findnext(ld, &fileinfo) == 0);

			_findclose(ld);

		}
#endif  
#ifdef linux  
		DIR *dir;
		struct dirent *ptr;
		char base[1000];

		if ((dir = opendir(cate_dir.c_str())) == NULL)
		{
			perror("Open dir error...");
			exit(1);
		}

		while ((ptr = readdir(dir)) != NULL)
		{
			if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)    ///current dir OR parrent dir  
				continue;
			else if (ptr->d_type == 8)    ///file  
				//printf("d_name:%s/%s\n",basePath,ptr->d_name);  
				files.push_back(ptr->d_name);
			else if (ptr->d_type == 10)    ///link file  
				//printf("d_name:%s/%s\n",basePath,ptr->d_name);  
				continue;
			else if (ptr->d_type == 4)    ///dir  
			{
				files.push_back(ptr->d_name);
				/*
				memset(base,'\0',sizeof(base));
				strcpy(base,basePath);
				strcat(base,"/");
				strcat(base,ptr->d_nSame);
				readFileList(base);
				*/
			}
		}
		closedir(dir);
#endif  
		//排序，按从小到大排序  	
		//filenames.sort(files.begin(), files.end());
		return true;
	}
	//根据文件夹名字采用opencv导入iplimage图片
	//bool load_batch_images(const std::string& file_path, std::vector<image_t>& images);//bool load_batch_images(const std::vector<std::string> &filenames, std::vector<image_t>& images)
	bool load_batch_images(const std::vector<std::string> &filenames, std::vector<IplImage*>& images, int ltype)
	{
		images.clear();//clear all data 清空容器存储
		std::vector<std::string>::const_iterator iter;
		iter = filenames.begin();
#pragma omp parallel for
		for (iter = filenames.begin(); iter != filenames.end(); iter++)
		{

			IplImage* img = cvLoadImage(iter->c_str(), ltype);

			IplImage*Plate_threshold = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
			double ret = cvThreshold(img, Plate_threshold, 0, 255, CV_THRESH_OTSU + CV_THRESH_BINARY);

			/*image_t image;
			image.channels = img->nChannels;
			image.width = img->width;
			image.height = img->height;
			image.Tsize = image.width*image.height*image.channels;
			image.data.resize(image.Tsize);*/

			//memccpy(img->imageData, image.data, image.Tsize);*/

			images.push_back(Plate_threshold);
		}
		return true;
	}
	//洗牌,随机打乱导入的数据
	//static void shuffle_data(std::vector<image_t>& images, std::vector<label_t>& labels)
	void shuffle_data(std::vector<IplImage*>& images, std::vector<label_t>& labels)
	{
		assert(images.size() == labels.size());
		std::vector<size_t> indexArray;
		for (size_t i = 0; i < images.size(); i++)
		{
			indexArray.push_back(i);
		}
		std::random_shuffle(indexArray.begin(), indexArray.end());

		std::vector<IplImage*> tmpImages(images.size());
		std::vector<label_t> tmpLabels(labels.size());
		for (size_t i = 0; i < images.size(); i++)
		{
			const size_t srcIndex = i;
			const size_t dstIndex = indexArray[i];
			tmpImages[srcIndex] = images[dstIndex];
			tmpLabels[srcIndex] = labels[dstIndex];
		}
		images = tmpImages;
		labels = tmpLabels;
	}
	//将数据分成训练集与测试几何
	void to_trainset_validateset(const std::vector<IplImage*> images, const std::vector<label_t> labels,
		std::vector<IplImage*> &train_images, std::vector<label_t> &train_labels,
		std::vector<IplImage*> &validate_images, std::vector<label_t> &validate_labels, float rate)
	{
		size_t sizeT = static_cast<size_t>(images.size()*rate);
		//train
		train_images.reserve(sizeT);
		train_labels.reserve(sizeT);
		train_images.insert(train_images.begin(), images.begin(), images.begin() + sizeT);
		train_labels.insert(train_labels.begin(), labels.begin(), labels.begin() + sizeT);
		//validate
		validate_images.reserve(images.size() - train_images.size());
		validate_labels.reserve(labels.size() - train_labels.size());
		validate_images.insert(validate_images.begin(), images.begin() + sizeT, images.end());
		validate_labels.insert(validate_labels.begin(), labels.begin() + sizeT, labels.end());

	}
	//在网络中添加层
	void add_input_layer(imgmaker::NetWork& network)
	{
		std::shared_ptr<imgmaker::layerInput> inputLayer(std::make_shared<imgmaker::layerInput>());
		network.addayer(inputLayer);
	}
	void add_active_layer(imgmaker::NetWork& network)
	{
		network.addayer(std::make_shared<imgmaker::layerRelu>());
	}
	void add_conv_layer(imgmaker::NetWork& network, const int number, const int input_channel)
	{
		std::shared_ptr<imgmaker::layerConvolution> convLayer(std::make_shared<imgmaker::layerConvolution>());
		convLayer->setParamaters(imgmaker::ParamSize(number, input_channel, 3, 3), 1, 1, true, imgmaker::layerConvolution::SAME);
		network.addayer(convLayer);
	}
	void add_pool_layer(imgmaker::NetWork& network, const int number)
	{
		std::shared_ptr<imgmaker::layerPooling> poolingLayer(std::make_shared<imgmaker::layerPooling>());
		poolingLayer->setParamaters(imgmaker::layerPooling::PoolingType::MaxPooling, imgmaker::ParamSize(1, number, 2, 2), 2, 2, imgmaker::layerPooling::SAME);
		network.addayer(poolingLayer);
	}
	void add_fc_layer(imgmaker::NetWork& network, const int output_count)
	{
		std::shared_ptr<imgmaker::layerFullconnect> fullconnectLayer(std::make_shared<imgmaker::layerFullconnect>());
		fullconnectLayer->setParamaters(imgmaker::ParamSize(1, output_count, 1, 1), true);
		network.addayer(fullconnectLayer);
	}
	void add_softmax_layer(imgmaker::NetWork& network)
	{
		std::shared_ptr<imgmaker::layerSoftmax> softmaxLayer(std::make_shared<imgmaker::layerSoftmax>());
		network.addayer(softmaxLayer);
	}
	//建立卷积网络
	imgmaker::NetWork buildConvNet(const size_t batch, const size_t channels, const size_t width, const size_t height, const size_t classes)
	{
		imgmaker::NetWork network;
		imgmaker::DataSize  dSize(batch, channels, width, height);
		network.mSize = dSize;

		//network.setInputSize(imgmaker::DataSize(batch, channels, width, height));
		network.setInputSize(dSize);

		//input data layer
		add_input_layer(network);

		//convolution layer
		add_conv_layer(network, 6, 1);
		add_active_layer(network);
		//pooling layer
		add_pool_layer(network, 6);

		//convolution layer
		add_conv_layer(network, 12, 6);
		add_active_layer(network);
		//pooling layer
		add_pool_layer(network, 12);

		//full connect layer
		add_fc_layer(network, 512);
		add_active_layer(network);

		//network.addayer(std::make_shared<imgmaker::DropoutLayer>(0.5f));

		//full connect layer
		add_fc_layer(network, classes);

		//soft max layer
		add_softmax_layer(network);

		return network;
	}
	//喂数据
	bool fetch_data(const std::vector<IplImage*>& images, std::shared_ptr<imgmaker::DataBucket> inputDataBucket,
		const std::vector<label_t>& labels, std::shared_ptr<imgmaker::DataBucket> labelDataBucket,
		const size_t offset, const size_t length)
	{
		//维度不相等，报错终止
		assert(images.size() == labels.size() && inputDataBucket->getSize().number == labelDataBucket->getSize().number);
		if (offset >= images.size())
		{
			return false;
		}
		size_t actualEndPos = offset + length;
		if (actualEndPos > images.size())
		{
			//image data
			auto inputDataSize = inputDataBucket->getSize();//Datasize
			inputDataSize.number = images.size() - offset;
			actualEndPos = offset + inputDataSize.number;
			inputDataBucket.reset(new imgmaker::DataBucket(inputDataSize));
			//label data
			auto labelDataSize = labelDataBucket->getSize();
			labelDataSize.number = inputDataSize.number;
			labelDataBucket.reset(new imgmaker::DataBucket(inputDataSize));
		}
		//copy
		const size_t sizePerImage = inputDataBucket->getSize()._3DSize();
		const size_t sizePerLabel = labelDataBucket->getSize()._3DSize();
		assert(sizePerImage == images[0]->nChannels*images[0]->width*images[0]->height);
		//scale to 0.0f~1.0f 归一化参数
		const float scaleRate = 1.0f / 255.0f;
		for (size_t i = offset; i < actualEndPos; i++)
		{
			//image data
			float* inputData = inputDataBucket->getData().get() + (i - offset)*sizePerImage;
			const uint8_t* mdata = (uchar *)images[i]->imageData;//const uint8_t* imageData = &images[i].data[0];
			//int step = images[i]->widthStep / sizeof(uchar);
			for (size_t j = 0; j < sizePerImage; j++)
			{
				inputData[j] = (float)mdata[j] * scaleRate;
			}
			//label data
			float* labelData = labelDataBucket->getData().get() + (i - offset)*sizePerLabel;
			const uint8_t label = labels[i].data;
			for (size_t j = 0; j < sizePerLabel; j++)
			{
				if (j == label)
				{
					labelData[j] = 1.0f;
				}
				else
				{
					labelData[j] = 0.0f;
				}
			}
		}
		return true;
	}
	//测试数据转换：图像输入数据转换成CNN计算输入数据
	std::shared_ptr<imgmaker::DataBucket> convertLabelToDataBucket(const std::vector<label_t>& test_labels, const size_t start, const size_t len,const size_t classes)
	{
		assert(test_labels.size() > 0);
		const size_t number = len;
		const size_t sizePerLabel = classes;
		std::shared_ptr<imgmaker::DataBucket> result(new imgmaker::DataBucket(imgmaker::DataSize(number, classes, 1, 1)));
		for (size_t i = start; i < start + len; i++)
		{
			//label Data
			float* labelData = result->getData().get() + (i - start)*sizePerLabel;
			const uint8_t label = test_labels[i].data;
			for (size_t j = 0; j < sizePerLabel; j++)
			{
				if (j == label)
				{
					labelData[j] = 1.0f;
				}
				else
				{
					labelData[j] = 0.0f;
				}
			}
		}
		return result;
	}
	std::shared_ptr<imgmaker::DataBucket> convertVectorToDataBucket(const std::vector<IplImage*>& test_images, const size_t start, const size_t len)
	{
		assert(test_images.size() > 0);
		const size_t number = len;
		const size_t channel = test_images[0]->nChannels;
		const size_t width = test_images[0]->width;
		const size_t height = test_images[0]->height;
		const size_t sizePerImage = channel*width*height;
		const float scaleRate = 1.0f / 255.0f;
		std::shared_ptr<imgmaker::DataBucket> result(new imgmaker::DataBucket(imgmaker::DataSize(number, channel, width, height)));
		for (size_t i = start; i < start + len; i++)
		{
			//image data
			float* inputData = result->getData().get() + (i - start)*sizePerImage;
			const uint8_t* mdata = (uchar *)test_images[i]->imageData;//const uint8_t* imageData = &test_images[i].data[0];
			for (size_t j = 0; j < sizePerImage; j++)
			{
				inputData[j] = (float)mdata[j] * scaleRate;
			}
		}
		return result;
	}

	uint8_t getMaxIdxInArray(const float* start, const float* stop)
	{
		assert(start && stop && stop >= start);
		ptrdiff_t result = 0;//机器相关数据用于保存指针相减值
		const ptrdiff_t len = stop - start;
		for (ptrdiff_t i = 0; i < len; i++)
		{
			if (start[i] >= start[result])
			{
				result = i;
			}
		}
		return (uint8_t)result;
	}

	//------------------------------------------------------------------------------------------------------------------------
}