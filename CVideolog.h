/************************************************************

GNU GENERAL PUBLIC LICENSE, Version 3, 29 June 2007
Copyright (c) 2017, KondeU, All rights reserved.

Project:     CVideolog
File:        CVideolog.h
Description: Implement a class name CVideolog that can show and save video log.
             Require OpenCV 2.4.10, could run on multi OS, provide linux version.
Date:        2017-06-27
Version:     1.1
Authors:     Deyou Kong <370242479@qq.com>
History:     01, 17-06-27, Deyou Kong, Create file and implement it.
             02, 17-09-06, Deyou Kong, Add code comment.

************************************************************/

#pragma once

#include <opencv2/opencv.hpp>

class CVideolog
{
public:

	CVideolog(int iFrameHeight, int iFrameWidth,
		bool bShowVideolog = true, bool bSaveVideolog = true,
		int iMatType = CV_8UC1, int iRowCnt = 2, int iColCnt = 2,
		double dTxtRgnWidthScale = 1);
	~CVideolog();

	void AddFrame(int iIdxRow, int iIdxCol, cv::Mat & mSmlFrm);
	void AddText(const char * szText);

	void Flash();

private:

	int iSmlFrmHeight, iSmlFrmWidth;
	int iRowCnt, iColCnt;
	int iMatType; // Gray: CV_8UC1, Color: CV_8UC3

	double dTxtRgnWidthScale;

	bool bShowVideolog, bSaveVideolog;

	cv::VideoWriter * pVideo;

	cv::Mat mFrame;
	int iTextCrntRow;
};
