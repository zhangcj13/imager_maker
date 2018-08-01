#pragma once
#include "mOpenCV.h"
#include "mCNN.h"

#include <vector>
#include <cstdint>
#include <fstream>
#include <cassert>

#include <windows.h>

#include <iostream>  
#include <stdlib.h>  
#include <stdio.h>  
#ifdef linux  
#include <unistd.h>  
#include <dirent.h>  
#endif  
#ifdef WIN32  
#include <direct.h>  
#include <io.h>  
#endif  

namespace imgmaker
{
	//const int classes = 10;//类别数量

	struct image_t
	{
		size_t width, height, channels,Tsize;
		std::vector<uint8_t> data;
		//uchar* data;
	};

	struct label_t
	{
		uint8_t data;
	};

	typedef std::pair<std::string, uint8_t> mLabel;
	//数据输入------------------------------------------------------------------------------------------------------------------------
	//bool getFiles(const std::string foldname, std::vector<std::string> &filenames, std::vector<std::string> &filelabels, std::string filecategory = "NO_CAT", uint8_t labeln = 0);
	bool getFiles(const std::string foldname, std::vector<std::string> &filenames, std::vector<label_t> &filelabels, std::vector<std::string> &mCategory,
		std::string filecategory = "NO_CAT", uint8_t labeln = 0);

	bool load_batch_images(const std::vector<std::string> &filenames, std::vector<IplImage*>& images,int ltype);

	void shuffle_data(std::vector<IplImage*>& images, std::vector<label_t>& labels);

	void to_trainset_validateset(const std::vector<IplImage*> images, const std::vector<label_t> labels,
		std::vector<IplImage*> &train_images, std::vector<label_t> &train_labels,
		std::vector<IplImage*> &validate_images, std::vector<label_t> &validate_labels, float rate = 0.8);
	//建立卷积网络------------------------------------------------------------------------------------------------------------------------
	void add_input_layer(imgmaker::NetWork& network);
	void add_active_layer(imgmaker::NetWork& network);
	void add_conv_layer(imgmaker::NetWork& network, const int number, const int input_channel);
	void add_pool_layer(imgmaker::NetWork& network, const int number);
	void add_fc_layer(imgmaker::NetWork& network, const int output_count);
	void add_softmax_layer(imgmaker::NetWork& network);

	imgmaker::NetWork buildConvNet(const size_t batch, const size_t channels, const size_t width, const size_t height, const size_t classes);

	bool fetch_data(const std::vector<IplImage*>& images, std::shared_ptr<imgmaker::DataBucket> inputDataBucket,
		const std::vector<label_t>& labels, std::shared_ptr<imgmaker::DataBucket> labelDataBucket,
		const size_t offset, const size_t length);

	std::shared_ptr<imgmaker::DataBucket> convertVectorToDataBucket(const std::vector<IplImage*>& test_images, const size_t start, const size_t len);
	std::shared_ptr<imgmaker::DataBucket> convertLabelToDataBucket(const std::vector<label_t>& test_labels, const size_t start, const size_t len,const size_t classes);

	uint8_t getMaxIdxInArray(const float* start, const float* stop);
	//------------------------------------------------------------------------------------------------------------------------

}