#pragma once
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void preProcess(Mat &origin_img, Mat &dst_img, int method_code);
void binarize(Mat &origin_img, Mat &dst_img, int method_code);
void afterProcess(Mat &origin_img, Mat &dst_img, int method_code);
void thinning(Mat &origin_img, Mat &dst_img, int method_code);
// the first of pair is k, the second one is b, this function should return the number of valid pair of k & b
int analysis(Mat &origin_img, vector < pair < float, float >> &kb, int method_code);

void MedianFlitering(Mat &src, Mat &dst);
void chao_thinimage(Mat &srcimage, int coreSize);//单通道、二值化后的图像;
void thinImage_alt(Mat &srcImg, int coresize, int loop_times);//可变核大小zhangsuen细化
void thinImage_alt_2(Mat &srcImg, int coresize, int loop_times)//可变核大小zhangsuen细化，降低分辨率

