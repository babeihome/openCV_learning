#pragma once
#include <opencv2/opencv.hpp>
using namespace cv;

void preProcess(Mat origin_img, Mat dst_img, int method_code);
void binarize(Mat origin_img, Mat dst_img, int method_code);
void afterProcess(Mat origin_img, Mat dst_img, int method_code);
void thinning(Mat origin_img, Mat dst_img, int method_code);
void analysis(Mat origin_img, float k, float b, int method_code);

