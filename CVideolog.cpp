/************************************************************

GNU GENERAL PUBLIC LICENSE, Version 3, 29 June 2007
Copyright (c) 2017, KondeU, All rights reserved.

Project:     CVideolog
File:        CVideolog.cpp
Description: Implement a class name CVideolog that can show and save video log.
             Require OpenCV 2.4.10, could run on multi OS, provide linux version.
Date:        2017-06-27
Version:     1.1
Authors:     Deyou Kong <370242479@qq.com>
History:     01, 17-06-27, Deyou Kong, Create file and implement it.
             02, 17-09-06, Deyou Kong, Add code comment.

************************************************************/

#include <iostream>
#include <fstream>
#include <climits>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

#include "CVideolog.h"

#define ERRPRE(s) ("CVideolog Error: " s) // Error output prefix

//const char szVideologFile[] = "./Runlog/Videolog.avi"; // Local named
extern char * szVideologFile; // Extern named

CVideolog::CVideolog(int iFrameHeight, int iFrameWidth, bool bShow, bool bSave,
	int iInputMatType, int iRowCount, int iColCount, double dTextRegionWidthScale)
{
	iSmlFrmHeight = iFrameHeight;
	iSmlFrmWidth  = iFrameWidth;

	iRowCnt = iRowCount;
	iColCnt = iColCount;

	iMatType = iInputMatType;

	dTxtRgnWidthScale = dTextRegionWidthScale;
	
	bShowVideolog = bShow;
	bSaveVideolog = bSave;

	try
	{
		mFrame = Mat::zeros((iRowCnt + dTxtRgnWidthScale) * iSmlFrmHeight, iColCnt * iSmlFrmWidth, iMatType);

		iTextCrntRow = 0;

		if (bShowVideolog)
		{
			namedWindow("Videolog");
		}

		if (bSaveVideolog)
		{		
			pVideo = new VideoWriter(szVideologFile, CV_FOURCC('D', 'I', 'V', 'X'), 10/*FPS set to 10*/,
				Size(iColCnt * iSmlFrmWidth, (iRowCnt + dTxtRgnWidthScale) * iSmlFrmHeight),
				((iMatType == CV_8UC1) ? false : true));
			
			if (! (pVideo->isOpened()))
			{
				cout << ERRPRE("Create video writer error!") << endl;
			}
		}
		else
		{
			pVideo = nullptr;
		}
	}
	catch (cv::Exception)
	{
		cout << ERRPRE("Catched exception in CVideolog::CVideolog(..) : CV Exception") << endl;
	}
	catch (...)
	{
		cout << ERRPRE("Catched exception in CVideolog::CVideolog(..) : Unknown") << endl;
	}
}
CVideolog::~CVideolog()
{
	if (bShowVideolog)
	{
		destroyWindow("Videolog");
	}

	if (bSaveVideolog && pVideo)
	{
		delete pVideo;
	}
}

void CVideolog::AddFrame(int iIdxRow, int iIdxCol, Mat & mSmlFrm)
{
	try
	{
		Mat mROI = mFrame(Rect(iIdxCol * iSmlFrmWidth, iIdxRow * iSmlFrmHeight, iSmlFrmWidth, iSmlFrmHeight));
		mSmlFrm.copyTo(mROI);
	}
	catch (cv::Exception)
	{
		cout << ERRPRE("Catched exception in CVideolog::AddFrame(..) : CV Exception") << endl;
	}
	catch (...)
	{
		cout << ERRPRE("Catched exception in CVideolog::AddFrame(..) : Unknown") << endl;
	}
}

void CVideolog::AddText(const char * szText)
{	
	const int iLineHeight = 14; // Text height

	iTextCrntRow++;

	try
	{
		putText(mFrame, szText, Point(2, (iRowCnt * iSmlFrmHeight + iTextCrntRow * iLineHeight)),
			FONT_HERSHEY_PLAIN, 1, Scalar(255, 255, 255));
	}
	catch (cv::Exception)
	{
		cout << ERRPRE("Catched exception in CVideolog::AddText(..) : CV Exception") << endl;
	}
	catch (...)
	{
		cout << ERRPRE("Catched exception in CVideolog::AddText(..) : Unknown") << endl;
	}
}

void CVideolog::Flash()
{
	try
	{
		iTextCrntRow = 0;

		if (bShowVideolog)
		{
			imshow("Videolog", mFrame);
		}

		if (bSaveVideolog)
		{
			(*pVideo) << mFrame;
		}
		
		mFrame.release();
		mFrame = Mat::zeros((iRowCnt + dTxtRgnWidthScale) * iSmlFrmHeight, iColCnt * iSmlFrmWidth, iMatType);
	}
	catch (cv::Exception)
	{
		cout << ERRPRE("Catched exception in CVideolog::Flash(..) : CV Exception") << endl;
	}
	catch (...)
	{
		cout << ERRPRE("Catched exception in CVideolog::Flash(..) : Unknown") << endl;
	}
}

