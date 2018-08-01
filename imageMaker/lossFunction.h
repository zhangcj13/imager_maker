#pragma once

#include "configNN.h"
#include "dataBucket.h"
#include "paramBucket.h"

#include <cmath>
#include "CNN_FUNC.h"

namespace imgmaker
{
	//ËðÊ§º¯Êý»ùÀà
	class LossFunctor
	{
	public:
		virtual float getLoss(const std::shared_ptr<DataBucket> labelDataBucket,
			const std::shared_ptr<DataBucket> outputDataBucket) = 0;
		virtual void getDiff(const std::shared_ptr<DataBucket> labelDataBucket,
			const std::shared_ptr<DataBucket> outputDataBucket, std::shared_ptr<DataBucket>& diff) = 0;
	};



	class crossEntropyFunctor : public LossFunctor
	{
	public:
		virtual float getLoss(const std::shared_ptr<DataBucket> labelDataBucket,
			const std::shared_ptr<DataBucket> outputDataBucket);
		virtual void getDiff(const std::shared_ptr<DataBucket> labelDataBucket,
			const std::shared_ptr<DataBucket> outputDataBucket, std::shared_ptr<DataBucket>& diff);
	};

	class MSEFunctor : public LossFunctor
	{
	public:
		virtual float getLoss(const std::shared_ptr<DataBucket> labelDataBucket,
			const std::shared_ptr<DataBucket> outputDataBucket);
		virtual void getDiff(const std::shared_ptr<DataBucket> labelDataBucket,
			const std::shared_ptr<DataBucket> outputDataBucket, std::shared_ptr<DataBucket>& diff);
	};
}
