#include "layerBatchNormalization.h"


namespace imgmaker
{
	layerBatchNormalization::layerBatchNormalization()
	{

	}
	layerBatchNormalization::~layerBatchNormalization()
	{

	}
	DEFINE_LAYER_TYPE(layerBatchNormalization, "layerBatchNormalization");
	std::string layerBatchNormalization::getLayerType() const
	{
		return layerType;
	}
	void layerBatchNormalization::setParamaters()
	{

	}
	std::string layerBatchNormalization::serializeToString() const
	{
		const std::string spliter = " ";
		std::stringstream ss;
		//layer desc
		ss << getLayerType() << spliter;
		return ss.str();
	}
	void layerBatchNormalization::serializeFromString(const std::string content)
	{
		std::stringstream ss(content);
		//layer desc
		std::string _layerType;
		ss >> _layerType;
		easyAssert(_layerType == getLayerType(), "layer type is invalidate.");
	}
	void layerBatchNormalization::solveInnerParams()
	{
		setOutpuBuckerSize(getInputBucketSize());
	}
	void layerBatchNormalization::forward(const std::shared_ptr<DataBucket> prev, std::shared_ptr<DataBucket> next)
	{
		const DataSize prevDataSize = prev->getSize();
		const DataSize nextDataSize = next->getSize();
		easyAssert(prevDataSize == nextDataSize, "size must be equal!");

		//TODO
	}
	void layerBatchNormalization::backward(std::shared_ptr<DataBucket> prev, const std::shared_ptr<DataBucket> next,
		std::shared_ptr<DataBucket>& prevDiff, const std::shared_ptr<DataBucket>& nextDiff)
	{
		easyAssert(getPhase() == Phase::Train, "backward only in train phase.")
			const DataSize prevSize = prev->getSize();
		const DataSize nextSize = next->getSize();
		const DataSize prevDiffSize = prevDiff->getSize();
		const DataSize nextDiffSize = nextDiff->getSize();
		float* prevDiffData = prevDiff->getData().get();
		const float* nextDiffData = nextDiff->getData().get();
		easyAssert(prevSize == nextSize, "size must be equal!");
		easyAssert(prevDiffSize == prevSize, "size of prevDiff and size of prev must be equals");

		//////////////////////////////////////////////////////////////////////////
		//update prevDiff

		prevDiff->fillData(0.0f);
		//calculate current inner diff && multiply next diff
		//TODO

		//update params
		//TODO
	}
}//namespace
