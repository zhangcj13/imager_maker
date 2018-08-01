#pragma once
#include "configNN.h"
#include "layerBase.h"

namespace imgmaker
{
	class layerInput : public layerBase
	{
		FRIEND_WITH_NETWORK
	public:
		layerInput();
		virtual ~layerInput();
	protected:
		DECLARE_LAYER_TYPE;
		virtual std::string serializeToString() const override; //���ǻ��ຯ��
		virtual void serializeFromString(const std::string content) override;
		virtual std::string getLayerType() const override;
		virtual void forward(const std::shared_ptr<DataBucket> prev, std::shared_ptr<DataBucket> next) override;
		virtual void backward(std::shared_ptr<DataBucket> prev, const std::shared_ptr<DataBucket> next,
			std::shared_ptr<DataBucket>& prevDiff, const std::shared_ptr<DataBucket>& nextDiff) override;
	};
}

