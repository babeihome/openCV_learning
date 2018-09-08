#include "imageProcessing.h"

using namespace std;
using namespace cv;

// don't modify origin_img!!!
void preProcess(Mat &origin_img, Mat &dst_img, int method_code) {
	switch (method_code)
	{
	case 0:
		break;
	default:
		break;
	}
}
void binarize(Mat &origin_img, Mat &dst_img, int method_code) {
	switch (method_code)
	{
	case 0:
		break;
	case 1:

	default:
		break;
	}
}
void afterProcess(Mat &origin_img, Mat &dst_img, int method_code) {
	switch (method_code)
	{
	case 0:
		break;
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

