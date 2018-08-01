#pragma once
#include <memory>
#include <vector>
#include "configNN.h"
#include "layerBase.h"
#include "lossFunction.h"
#include "optimizer.h"
#include "TRAIN_FUNC.h"

#include <io.h>

#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
//configure
#include "configNN.h"
//layers
#include "layerActivation.h"
#include "layerInput.h"
#include "layerConvolution.h"
#include "layerPooling.h"
#include "layerFullconnect.h"
#include "layerSoftmax.h"
#include "layerDropout.h"
#include "layerBatchNormalization.h"

namespace imgmaker
{
	class NetWork
	{
	public:
		DataSize mSize;
		NetWork();
		virtual ~NetWork();
	public:
		//common
		//loss of batch
		float getLoss(const std::shared_ptr<DataBucket> labelDataBucket, const std::shared_ptr<DataBucket> outputDataBucket);
		//test only!
		bool loadModel(const std::string& modelFile, const std::string& trainname, size_t &classes, std::vector<std::string> &Category);
		std::shared_ptr<DataBucket> testBatch(const std::shared_ptr<DataBucket> inputDataBucket);
		//train only!
		void setInputSize(const DataSize size);
		void setLossFunctor(std::shared_ptr<LossFunctor> lossFunctor);
		void setOptimizer(std::shared_ptr<Optimizer> optimizer);
		void setLearningRate(const float lr);
		void addayer(std::shared_ptr<layerBase> layer);
		float trainBatch(const std::shared_ptr<DataBucket> inputDataBucket,
			const std::shared_ptr<DataBucket> labelDataBucket);
		bool saveModel(const std::string& modelFile, const std::string& trainname, size_t &classes, std::vector<std::string> &Category);
	private:
		//common
		void setPhase(Phase phase);
		Phase getPhase() const;
		std::string encrypt(const std::string& content);
		std::string decrypt(const std::string& content);
	private:
		//common
		std::shared_ptr<DataBucket> forward(const std::shared_ptr<DataBucket> inputDataBucket);
		float backward(const std::shared_ptr<DataBucket> labelDataBucket);
		std::shared_ptr<layerBase> createLayerByType(const std::string layerType);
		std::string lookaheadLayerType(const std::string line);
	private:
		Phase phase = Phase::Train;
		//´æ´¢²ã
		std::vector<std::shared_ptr<layerBase>> layers;
		std::vector<std::shared_ptr<DataBucket>> dataBuckets;
		std::vector<std::shared_ptr<DataBucket>> diffBuckets;
		std::shared_ptr<LossFunctor> lossFunctor;
		std::shared_ptr<Optimizer> optimizer;
	};
}