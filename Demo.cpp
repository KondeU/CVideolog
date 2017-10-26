/************************************************************

GNU GENERAL PUBLIC LICENSE, Version 3, 29 June 2007
Copyright (c) 2017, KondeU, All rights reserved.

Project:     CVideolog
File:        Demo.cpp
Description: Use the class CVideolog as a logger to show and save video.
             Require OpenCV 2.4.10, could run on multi OS, provide linux version.
Date:        2017-09-06
Version:     1.1
Authors:     Deyou Kong <370242479@qq.com>
History:     01, 17-09-06, Deyou Kong, Create file and implement it.

************************************************************/

#include <iostream>
#include <sys/time.h>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

#include "CVideolog.h"

double Timer()
{
	struct timeval tv;
	gettimeofday(&tv, nullptr);
	return ((double(tv.tv_sec) * 1000) + (double(tv.tv_usec) / 1000));
}

char szVideologFile[] = "./Runlog/Videolog.avi";

int main()
{
	VideoCapture cCaptrue(0);

	if (!cCaptrue.isOpened())
	{
		cout << "Fail to open camera capture!" << endl;
		exit(1);
	}

	cCaptrue.set(CV_CAP_PROP_FRAME_WIDTH,  640);
	cCaptrue.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

	CVideolog cVideolog(480, 640, true, true, CV_8UC1, 1, 2, 1.0);

	Mat mFrame, mFrameGray, mFrameCanny;
	double dTimeStart = 0, dTimeEnd = 0;

	while (true)
	{
		dTimeStart = Timer();

		if (!(cCaptrue.read(mFrame)))
		{
			cout << "Fail to read camera data!" << endl;
			cCaptrue.release();
			exit(2);
		}

		imshow("Frame", mFrame);

		cvtColor(mFrame, mFrameGray, CV_RGB2GRAY);
		cVideolog.AddFrame(mFrame);

		Canny(mFrameGray, mFrameCanny, 50, 100);
		cVideolog.AddFrame(mFrame);

		dTimeEnd = Timer();

		char szOutput[32];
		sprintf(szOutput, "Used time: %d", dTimeEnd - dTimeStart);
		cVideolog.AddText(szOutput);
		sprintf(szOutput, "Current FPS: %d", 1000 / (dTimeEnd - dTimeStart));
		cVideolog.AddText(szOutput);

		char cKey = waitKey(1);
		if ('q' == cKey || 'Q' == cKey)
		{
			break;
		}
	}

	cCaptrue.release();

	return 0;
}

