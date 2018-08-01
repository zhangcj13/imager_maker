#pragma once
#include <algorithm>

#include "layerBase.h"
#include "CNN_FUNC.h"
#include "threadPool.h"


namespace imgmaker
{
	class layerActivation : public layerBase
	{
	};

	class layerSigmod : public layerActivation
	{
		FRIEND_WITH_NETWORK
	public:
		layerSigmod();
		virtual ~layerSigmod();
	protected:
		DECLARE_LAYER_TYPE;
		virtual std::string getLayerType() const override;
		virtual void forward(const std::shared_ptr<DataBucket> prev, std::shared_ptr<DataBucket> next) override;
		virtual void backward(std::shared_ptr<DataBucket> prev, const std::shared_ptr<DataBucket> next,
			std::shared_ptr<DataBucket>& prevDiff, const std::shared_ptr<DataBucket>& nextDiff) override;
	};

	class layerTanh : public layerActivation
	{
		FRIEND_WITH_NETWORK
	public:
		layerTanh();
		virtual ~layerTanh();
	protected:
		DECLARE_LAYER_TYPE;
		virtual std::string getLayerType() const override;
		virtual void forward(const std::shared_ptr<DataBucket> prev, std::shared_ptr<DataBucket> next) override;
		virtual void backward(std::shared_ptr<DataBucket> prev, const std::shared_ptr<DataBucket> next,
			std::shared_ptr<DataBucket>& prevDiff, const std::shared_ptr<DataBucket>& nextDiff) override;
	};

	class layerRelu : public layerActivation
	{
		FRIEND_WITH_NETWORK
	public:
		layerRelu();
		virtual ~layerRelu();
	protected:
		DECLARE_LAYER_TYPE;
		virtual std::string getLayerType() const override;
		virtual void forward(const std::shared_ptr<DataBucket> prev, std::shared_ptr<DataBucket> next) override;
		virtual void backward(std::shared_ptr<DataBucket> prev, const std::shared_ptr<DataBucket> next,
			std::shared_ptr<DataBucket>& prevDiff, const std::shared_ptr<DataBucket>& nextDiff) override;
	};
}

