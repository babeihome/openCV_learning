
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
	// image path from command argv
	//Mat img = imread(argv[1], -1);
	String imagePath("../../shared_data/stm32/path1.jpg");
	Mat img = imread(imagePath,-1);
	if (img.empty())
	{
		cout << "Error: Could not load image" << endl;
		return 0;
	}

	Mat gray;
	cvtColor(img, gray, CV_BGR2GRAY);

	Mat dst;
	threshold(gray, dst, 0, 255, CV_THRESH_OTSU);

	imshow("src", img);
	imshow("gray", gray);
	imshow("dst", dst);
	waitKey(0);

	return 0;
}