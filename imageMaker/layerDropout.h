#pragma once
#include "layerBase.h"
#include "CNN_FUNC.h"

#include <random>
#include <ctime>

#include "commonTools.h"
#include "CNN_FUNC.h"

namespace imgmaker
{
	class layerDropout : public layerBase
	{
		FRIEND_WITH_NETWORK
	public:
		layerDropout();
		layerDropout(const float _rate);
		virtual ~layerDropout();
	public:
		void setParamaters(const float _rate);
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
		float rate = 0.5f;
		std::shared_ptr<ParamBucket> mask;
	};
}
