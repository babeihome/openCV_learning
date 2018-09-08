#include "imageProcessing.h"

using namespace std;
using namespace cv;


void preProcess(Mat &origin_img, Mat &dst_img, int method_code) {
	switch (method_code)
	{
	case 0:
		cvtColor(origin_img, dst_img, CV_BGR2GRAY);
	case 1: {
		Mat smooth;
		MedianFlitering(origin_img, smooth);                 //中值滤波效果一般
		cvtColor(smooth, dst_img, CV_BGR2GRAY);
	}
		
	default:
		break;
	}
}
void binarize(Mat &origin_img, Mat &dst_img, int method_code) {
	switch (method_code)
	{
	case 0:
		break;
	default:
		break;
	}
}
void afterProcess(Mat &origin_img, Mat &dst_img, int method_code) {
	switch (method_code)
	{
	case 0:
		dilate(origin_img, dst_img, Mat(), Point(), 5);                  //膨胀5次
	default:
		break;
	}
}
void thinning(Mat &origin_img, Mat &dst_img, int method_code) {
	switch (method_code)
	{
	case 0:
		break;
	default:
		break;
	}
}
// the first of pair is k, the second one is b, this function should return the number of valid pair of k & b
int analysis(Mat &origin_img, vector < pair < float, float >> &kb, int method_code) {
	switch (method_code)
	{
	case 0:
		break;
	default:
		break;
	}
	return 0;
}

//求九个数的中值
uchar Median(uchar n1, uchar n2, uchar n3, uchar n4, uchar n5,
	uchar n6, uchar n7, uchar n8, uchar n9) {
	uchar arr[9];
	arr[0] = n1;
	arr[1] = n2;
	arr[2] = n3;
	arr[3] = n4;
	arr[4] = n5;
	arr[5] = n6;
	arr[6] = n7;
	arr[7] = n8;
	arr[8] = n9;
	for (int gap = 9 / 2; gap > 0; gap /= 2)//希尔排序
		for (int i = gap; i < 9; ++i)
			for (int j = i - gap; j >= 0 && arr[j] > arr[j + gap]; j -= gap)
				swap(arr[j], arr[j + gap]);
	return arr[4];//返回中值
}

//中值滤波
void MedianFlitering(Mat &src, Mat &dst) {
	if (!src.data)return;
	Mat _dst(src.size(), src.type());
	for (int i = 0; i < src.rows; ++i)
		for (int j = 0; j < src.cols; ++j) {
			if ((i - 1) > 0 && (i + 1) < src.rows && (j - 1) > 0 && (j + 1) < src.cols) {
				_dst.at<Vec3b>(i, j)[0] = Median(src.at<Vec3b>(i, j)[0], src.at<Vec3b>(i + 1, j + 1)[0],
					src.at<Vec3b>(i + 1, j)[0], src.at<Vec3b>(i, j + 1)[0], src.at<Vec3b>(i + 1, j - 1)[0],
					src.at<Vec3b>(i - 1, j + 1)[0], src.at<Vec3b>(i - 1, j)[0], src.at<Vec3b>(i, j - 1)[0],
					src.at<Vec3b>(i - 1, j - 1)[0]);
				_dst.at<Vec3b>(i, j)[1] = Median(src.at<Vec3b>(i, j)[1], src.at<Vec3b>(i + 1, j + 1)[1],
					src.at<Vec3b>(i + 1, j)[1], src.at<Vec3b>(i, j + 1)[1], src.at<Vec3b>(i + 1, j - 1)[1],
					src.at<Vec3b>(i - 1, j + 1)[1], src.at<Vec3b>(i - 1, j)[1], src.at<Vec3b>(i, j - 1)[1],
					src.at<Vec3b>(i - 1, j - 1)[1]);
				_dst.at<Vec3b>(i, j)[2] = Median(src.at<Vec3b>(i, j)[2], src.at<Vec3b>(i + 1, j + 1)[2],
					src.at<Vec3b>(i + 1, j)[2], src.at<Vec3b>(i, j + 1)[2], src.at<Vec3b>(i + 1, j - 1)[2],
					src.at<Vec3b>(i - 1, j + 1)[2], src.at<Vec3b>(i - 1, j)[2], src.at<Vec3b>(i, j - 1)[2],
					src.at<Vec3b>(i - 1, j - 1)[2]);
			}
			else
				_dst.at<Vec3b>(i, j) = src.at<Vec3b>(i, j);
		}
	_dst.copyTo(dst);//拷贝
}