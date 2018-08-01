#ifndef MTRAIN_H_
#define MTRAIN_H_

#include "mOpenCV.h"

namespace imgmaker {

	class mTrain
	{
	public:
		mTrain(){};

		//virtual ~mTrain();

		virtual void train() = 0;

		//virtual void test() = 0;

	private:
		//virtual cv::Ptr<cv::ml::TrainData> tdata() = 0;
	};
}

#endif  // MTRAIN_H_

