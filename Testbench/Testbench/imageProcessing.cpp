#pragma once
#include <opencv2/opencv.hpp>
#include "imageProcessing.h"

using namespace cv;
using namespace std;

void binarize(Mat origin_img,Mat dst_img,int method_code)
{
	switch (method_code)
	{
	case 1:
		threshold(origin_img, dst_img, 0, 255, CV_THRESH_OTSU);
	default:
		break;
	}
}

void preProcessing(Mat origin_img, Mat dst_img, int method_code)
{
	switch (method_code)
	{
	case 1:
		cvtColor(origin_img, dst_img, CV_BGR2GRAY);
	default:
		break;
	}
}