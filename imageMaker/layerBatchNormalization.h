#pragma once
#include "configNN.h"
#include "layerBase.h"

#include "commonTools.h"

namespace imgmaker
{
	class layerBatchNormalization : public layerBase
	{
		FRIEND_WITH_NETWORK
	public:
		layerBatchNormalization();
		virtual ~layerBatchNormalization();
	public:
		void setParamaters();
	protected:
		DECLARE_LAYER_TYPE;
		virtual std::string serializeToString() const override;
		virtual void serializeFromString(const std::string content) override;
		virtual std::string getLayerType() const override;
		virtual void solveInnerParams() override;
		virtual void forward(const std::shared_ptr<DataBucket> prev, std::shared_ptr<DataBucket> next) override;
		virtual void backward(std::shared_ptr<DataBucket> prev, const std::shared_ptr<DataBucket> next,
			std::shared_ptr<DataBucket>& prevDiff, const std::shared_ptr<DataBucket>& nextDiff) override;
	private:

	};
}