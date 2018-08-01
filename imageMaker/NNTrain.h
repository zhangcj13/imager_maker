#pragma once
#include <iostream>
#include <cassert>
#include <algorithm>
#include <random>
#include "mCNN.h"


#include "mTrain.h"
#include "TRAIN_FUNC.h"

#include "IMGMAKER_FUNC.h"



namespace imgmaker
{

	//--------------------------------------------------------------------------------------------------
	class CNNTrain //:public mTrain
	{
	public:
		size_t classes;//输出分类个数
		vector<std::string> mCategory;
	    const char* filefold;
	    const char* modelFilePath;
		NetWork mNetWork;
	public:
		CNNTrain(){};
		CNNTrain(const char* _filefold, const char* _modelFilePath);
		~CNNTrain();

		void setFileFold(const char* _filefold){ filefold = _filefold;}
		void setModelPath(const char* _modelFilePath){ modelFilePath = _modelFilePath; }
		const char *getFileFold(){ return filefold;}
		const char *getModelPath(){ return modelFilePath; }

	public:
		bool loadModel(const char * trainname);
		bool train(const char *_trainname);// override;
		//测试函数，测试训练集准确率
		std::pair<float, float> test(imgmaker::NetWork& network, const size_t batch,
			const std::vector<IplImage*>& test_images, const std::vector<label_t>& test_labels);

		void Predict_Img(const char* filepath);
		std::string Predict_Img(IplImage* PreImg);
	private:
		std::shared_ptr<imgmaker::DataBucket> LoadPredictImage(IplImage* &PreImg);
	};

}


