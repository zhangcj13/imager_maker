
#include "layerActivation.h"


namespace imgmaker
{
	layerSigmod::layerSigmod()
	{

	}
	layerSigmod::~layerSigmod()
	{

	}

	DEFINE_LAYER_TYPE(layerSigmod, "layerSigmod");

	std::string layerSigmod::getLayerType() const
	{
		return layerType;
	}
	void layerSigmod::forward(const std::shared_ptr<DataBucket> prev, std::shared_ptr<DataBucket> next)
	{
		const DataSize prevSize = prev->getSize();
		const DataSize nextSize = next->getSize();
		const float* prevData = prev->getData().get();//ptrÊ×µØÖ·
		float* nextData = next->getData().get();

		auto worker = [&](const size_t start, const size_t stop){
			const size_t offset = start*prevSize._3DSize();
			const size_t total_size = (stop - start)*prevSize._3DSize();
			sigmoid(prevData + offset, nextData + offset, total_size);
		};
		dispatch_worker(worker, prevSize.number);
	}
	void layerSigmod::backward(std::shared_ptr<DataBucket> prev, const std::shared_ptr<DataBucket> next,
		std::shared_ptr<DataBucket>& prevDiff, const std::shared_ptr<DataBucket>& nextDiff)
	{
		easyAssert(getPhase() == Phase::Train, "backward only in train phase.")
			const DataSize prevSize = prev->getSize();
		const DataSize nextSize = next->getSize();
		const DataSize prevDiffSize = prevDiff->getSize();
		const DataSize nextDiffSize = nextDiff->getSize();
		const float* prevData = prev->getData().get();
		const float* nextData = next->getData().get();
		float* prevDiffData = prevDiff->getData().get();
		const float* nextDiffData = nextDiff->getData().get();
		easyAssert(prevSize == nextSize, "size must be equal!");
		easyAssert(prevDiffSize == prevSize, "size of prevDiff and size of prev must be equals");

		//update prevDiff
		prevDiff->fillData(0.0f);

		auto worker = [&](const size_t start, const size_t stop){
			const size_t offset = start*prevSize._3DSize();
			const size_t total_size = (stop - start)*prevSize._3DSize();
			//calculate current inner diff
			df_sigmoid(nextData + offset, prevDiffData + offset, total_size);
			//multiply next diff
			mul_inplace(prevDiffData + offset, nextDiffData + offset, total_size);
		};
		dispatch_worker(worker, prevSize.number);

		//update this layer's param
		//Tanh layer : nop
	}
//---------------------------------------------------------------------------------------------------------------
	layerTanh::layerTanh()
	{

	}
	layerTanh::~layerTanh()
	{

	}
	DEFINE_LAYER_TYPE(layerTanh, "layerTanh");
	std::string layerTanh::getLayerType() const
	{
		return layerType;
	}


	void layerTanh::forward(const std::shared_ptr<DataBucket> prev, std::shared_ptr<DataBucket> next)
	{
		const DataSize prevSize = prev->getSize();
		const DataSize nextSize = next->getSize();
		const float* prevData = prev->getData().get();
		float* nextData = next->getData().get();

		auto worker = [&](const size_t start, const size_t stop){
			const size_t offset = start*prevSize._3DSize();
			const size_t total_size = (stop - start)*prevSize._3DSize();
			tanh(prevData + offset, nextData + offset, total_size);
		};
		dispatch_worker(worker, prevSize.number);
	}
	void layerTanh::backward(std::shared_ptr<DataBucket> prev, const std::shared_ptr<DataBucket> next,
		std::shared_ptr<DataBucket>& prevDiff, const std::shared_ptr<DataBucket>& nextDiff)
	{
		easyAssert(getPhase() == Phase::Train, "backward only in train phase.")
			const DataSize prevSize = prev->getSize();
		const DataSize nextSize = next->getSize();
		const DataSize prevDiffSize = prevDiff->getSize();
		const DataSize nextDiffSize = nextDiff->getSize();
		const float* prevData = prev->getData().get();
		const float* nextData = next->getData().get();
		float* prevDiffData = prevDiff->getData().get();
		const float* nextDiffData = nextDiff->getData().get();
		easyAssert(prevSize == nextSize, "size must be equal!");
		easyAssert(prevDiffSize == prevSize, "size of prevDiff and size of prev must be equals");

		//update prevDiff
		prevDiff->fillData(0.0f);

		auto worker = [&](const size_t start, const size_t stop){
			const size_t offset = start*prevSize._3DSize();
			const size_t total_size = (stop - start)*prevSize._3DSize();
			//calculate current inner diff
			df_tanh(nextData + offset, prevDiffData + offset, total_size);
			//multiply next diff
			mul_inplace(prevDiffData + offset, nextDiffData + offset, total_size);
		};
		dispatch_worker(worker, prevSize.number);

		//update this layer's param
		//Tanh layer : nop
	}
//---------------------------------------------------------------------------------------------------------------
	layerRelu::layerRelu()
	{

	}
	layerRelu::~layerRelu()
	{

	}
	DEFINE_LAYER_TYPE(layerRelu, "layerRelu");
	std::string layerRelu::getLayerType() const
	{
		return layerType;
	}


	void layerRelu::forward(const std::shared_ptr<DataBucket> prev, std::shared_ptr<DataBucket> next)
	{
		const DataSize prevSize = prev->getSize();
		const DataSize nextSize = next->getSize();
		const float* prevData = prev->getData().get();
		float* nextData = next->getData().get();

		auto worker = [&](const size_t start, const size_t stop){
			const size_t offset = start*prevSize._3DSize();
			const size_t total_size = (stop - start)*prevSize._3DSize();
			relu(prevData + offset, nextData + offset, total_size);
		};
		dispatch_worker(worker, prevSize.number);
	}
	void layerRelu::backward(std::shared_ptr<DataBucket> prev, const std::shared_ptr<DataBucket> next,
		std::shared_ptr<DataBucket>& prevDiff, const std::shared_ptr<DataBucket>& nextDiff)
	{
		easyAssert(getPhase() == Phase::Train, "backward only in train phase.")
			const DataSize prevSize = prev->getSize();
		const DataSize nextSize = next->getSize();
		const DataSize prevDiffSize = prevDiff->getSize();
		const DataSize nextDiffSize = nextDiff->getSize();
		const float* prevData = prev->getData().get();
		const float* nextData = next->getData().get();
		float* prevDiffData = prevDiff->getData().get();
		const float* nextDiffData = nextDiff->getData().get();
		easyAssert(prevSize == nextSize, "size must be equal!");
		easyAssert(prevDiffSize == prevSize, "size of prevDiff and size of prev must be equals");

		//update prevDiff		
		prevDiff->fillData(0.0f);

		auto worker = [&](const size_t start, const size_t stop){
			const size_t offset = start*prevSize._3DSize();
			const size_t total_size = (stop - start)*prevSize._3DSize();
			//calculate current inner diff
			df_relu(nextData + offset, prevDiffData + offset, total_size);
			//multiply next diff
			mul_inplace(prevDiffData + offset, nextDiffData + offset, total_size);
		};
		dispatch_worker(worker, prevSize.number);

		//update this layer's param
		//RELU layer : nop
	}
}//namespace