#include "layerInput.h"

namespace imgmaker
{
	layerInput::layerInput()
	{

	}
	layerInput::~layerInput()
	{

	}

// DEFINE_LAYER_TYPE(class_type,type_string) const std::string class_type::layerType = type_string; 
	DEFINE_LAYER_TYPE(layerInput, "layerInput");//

	std::string layerInput::serializeToString() const
	{
		const std::string spliter = " ";
		std::stringstream ss;//输入输出流
		//layer enc
		ss << getLayerType() << spliter
			<< inputSize.channels << spliter << inputSize.width << spliter << inputSize.height << spliter;
		return ss.str();
	}
	//根据输入初始化 尺寸大小
	void layerInput::serializeFromString(const std::string content)
	{
		//layer desc
		std::string _layerType;
		int _number = 1;
		int _channels = 0;
		int _width = 0;
		int _height = 0;
		std::stringstream ss(content);
		ss >> _layerType >> _channels >> _width >> _height;
		easyAssert(_layerType == getLayerType(), "layer type is invalidate.");

		DataSize mapSize;
		mapSize.number = _number;
		mapSize.channels = _channels;
		mapSize.width = _width;
		mapSize.height = _height;
		setInputBucketSize(mapSize);
		setOutpuBuckerSize(mapSize);
		solveInnerParams();
	}

	std::string layerInput::getLayerType() const
	{
		return layerType;
	}

	void layerInput::forward(const std::shared_ptr<DataBucket> prev, std::shared_ptr<DataBucket> next)
	{
		prev->cloneTo(*next);
	}

	void layerInput::backward(std::shared_ptr<DataBucket> prev, const std::shared_ptr<DataBucket> next,
		std::shared_ptr<DataBucket>& prevDiff, const std::shared_ptr<DataBucket>& nextDiff)
	{
		//data layer : nop
	}
}//namespace
