
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


	Mat srcImage = img;
	Mat temImage, dstImage1, dstImage2;
	temImage = srcImage;

	//显示原图
	imshow("原图", srcImage);

	//尺寸调整
	resize(temImage, dstImage1, Size(temImage.cols / 2, temImage.rows / 2), 0, 0, INTER_LINEAR);
	resize(temImage, dstImage2, Size(temImage.cols * 2, temImage.rows * 2), 0, 0, INTER_LINEAR);

	imshow("缩小", dstImage1);
	imshow("放大", dstImage2);

	waitKey();
	return 0;

	waitKey(0);

	return 0;
}