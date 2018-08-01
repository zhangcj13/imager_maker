#pragma once

//configure
#include "configNN.h"
#include "layerBase.h"

#include "commonTools.h"
#include "threadPool.h"
#include "CNN_FUNC.h"

#include "dataBucket.h"
#include "paramBucket.h"
//layers
#include "layerActivation.h"
#include "layerInput.h"
#include "layerConvolution.h"
#include "layerPooling.h"
#include "layerFullconnect.h"
#include "layerSoftmax.h"
#include "layerDropout.h"
#include "layerBatchNormalization.h"
//network
#include "netWork.h"