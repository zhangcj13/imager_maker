#pragma once

#include "imagemaker.h"
#include <QtWidgets/QApplication>
#include <iostream>



#include "IMGMAKER_FUNC.h"
#include "mPlate_Locate.h"

#include "mCNN.h"
#include "TRAIN_FUNC.h"
#include "NNTrain.h"

#include "structPlate.h"

#include "IMGMAKER_FUNC.h"


void IMGMAKER_FUNC_TEST()
{

	char* filename = "C:\\Users\\zhang\\Pictures\\carPlate1.jpg";
	//char* filename = "C:\\Users\\zhang\\Pictures\\1.jpg";
	//char* filename = "C:\\Users\\zhang\\Pictures\\P191.png";

	IplImage* imgin = cvLoadImage(filename);
	IplImage* match;
	CvBox2D rect;

	mPlate_Locate Loc;

	Loc.InitialData(imgin);

	vector<mPlate> candPlates;
	//candPlates.reserve(64);
	//Loc.plateLocateBYColor(Loc.initialImg, 1);

	Loc.LocatePlate();




	//cvShowImage("pic", imgin);
	//cvWaitKey();

	//vector<mPlate> candPlates;

	//mPlate_Locate Loc;

	//Loc.sobelOper(imgin, match, 3, 19, 5);

	//Loc.plateLocateBYColor(imgin, candPlates, 1);

	//candPlates[0].plateShow();



	//rect.center.x=500;
	//rect.center.x = 400;
	//rect.size = CvSize2D32f(250, 120);
	//rect.angle = 1	;
	//IplImage* out = rect2Img(imgin, rect, *match);

	//cvShowImage("pic", out);
	//	cvWaitKey();
}

void CNN_TEST()
{
	//char* foldname = "C://Users//zhang//Documents//Visual Studio 2013//Projects//imageMaker//imageMaker//train//chars2";
	//char* modename = "C://Users//zhang//Documents//Visual Studio 2013//Projects//imageMaker//imageMaker//train//MODEL";

	char* chars2name = "C://Users//zhang//Documents//Visual Studio 2013//Projects//imageMaker//imageMaker//train//chars2";
	char* charsChinesename = "C://Users//zhang//Documents//Visual Studio 2013//Projects//imageMaker//imageMaker//train//charsChinese";
	char* modename = "C://Users//zhang//Documents//Visual Studio 2013//Projects//imageMaker//imageMaker//train//MODEL";
	
	CNNTrain chars2CNN(chars2name, modename);
	chars2CNN.loadModel("chars2");
	CNNTrain charsChineseCNN(charsChinesename, modename);
	charsChineseCNN.loadModel("charsChinese");


	char* testname = "C://Users//zhang//Documents//Visual Studio 2013//Projects//imageMaker//imageMaker//train//chars2//1//9-5.jpg";
	char* testname2 = "C://Users//zhang//Documents//Visual Studio 2013//Projects//imageMaker//imageMaker//train//chars2//0//4-3.jpg";
	IplImage* testimg = cvLoadImage(testname, 0);
	IplImage* testimg2 = cvLoadImage(testname2, 0);

	std::string res = chars2CNN.Predict_Img(testimg);
	std::string res2 = chars2CNN.Predict_Img(testimg2);
	//t1.Predict_Img(testname);
	//t1.train("chars2");
	int x = 1;
	
}

void pathtest()
{
	char   mainfold[MAX_PATH];
	getcwd(mainfold, MAX_PATH);


	char *_chars2 = "\\train\\chars2";
	char *_charschinese = "\\train\\charsChinese";
	char *_model = "\\train\\MODEL";

	char chars2fold[MAX_PATH], charschinesefold[MAX_PATH], modelfold[MAX_PATH];

	strcpy(chars2fold, mainfold);
	strcpy(charschinesefold, mainfold);
	strcpy(modelfold, mainfold);


	strcat(chars2fold, _chars2);
	strcat(charschinesefold, _charschinese);
	strcat(modelfold, _model);

}

void cvCopyMakeBordertest()
{
	char *pathname = "C:\\Users\\zhang\\Pictures\\P191.png";
	IplImage* img = cvLoadImage(pathname);
	IplImage* dst = imgmaker::expandImage(img,180,200,255);
	cvShowImage("img", dst);
	cvWaitKey();

}