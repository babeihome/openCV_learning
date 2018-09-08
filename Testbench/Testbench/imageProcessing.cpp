#include <opencv2/opencv.hpp>
#include "imageProcessing.h"

using namespace std;
using namespace cv;

// don't modify origin_img!!!
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
	case 1:

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
	case 0: dst_img = origin_img.clone(); chao_thinimage(dst_img);
		break;
	default: cout << "no this method, sorry" << endl;
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

<<<<<<< HEAD
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
=======
void chao_thinimage(Mat &srcimage)//单通道、二值化后的图像

{

	vector<Point> deletelist1;

	int Zhangmude[9];

	int nl = srcimage.rows;

	int nc = srcimage.cols;

	while (true)

	{

		for (int j = 1; j < (nl - 1); j++)

		{

			uchar* data_last = srcimage.ptr<uchar>(j - 1);

			uchar* data = srcimage.ptr<uchar>(j);

			uchar* data_next = srcimage.ptr<uchar>(j + 1);

			for (int i = 1; i < (nc - 1); i++)

			{

				if (data[i] == 255)

				{

					Zhangmude[0] = 1;

					if (data_last[i] == 255) Zhangmude[1] = 1;

					else  Zhangmude[1] = 0;

					if (data_last[i + 1] == 255) Zhangmude[2] = 1;

					else  Zhangmude[2] = 0;

					if (data[i + 1] == 255) Zhangmude[3] = 1;

					else  Zhangmude[3] = 0;

					if (data_next[i + 1] == 255) Zhangmude[4] = 1;

					else  Zhangmude[4] = 0;

					if (data_next[i] == 255) Zhangmude[5] = 1;

					else  Zhangmude[5] = 0;

					if (data_next[i - 1] == 255) Zhangmude[6] = 1;

					else  Zhangmude[6] = 0;

					if (data[i - 1] == 255) Zhangmude[7] = 1;

					else  Zhangmude[7] = 0;

					if (data_last[i - 1] == 255) Zhangmude[8] = 1;

					else  Zhangmude[8] = 0;

					int whitepointtotal = 0;

					for (int k = 1; k < 9; k++)

					{

						whitepointtotal = whitepointtotal + Zhangmude[k];

					}

					if ((whitepointtotal >= 2) && (whitepointtotal <= 6))

					{

						int ap = 0;

						if ((Zhangmude[1] == 0) && (Zhangmude[2] == 1)) ap++;

						if ((Zhangmude[2] == 0) && (Zhangmude[3] == 1)) ap++;

						if ((Zhangmude[3] == 0) && (Zhangmude[4] == 1)) ap++;

						if ((Zhangmude[4] == 0) && (Zhangmude[5] == 1)) ap++;

						if ((Zhangmude[5] == 0) && (Zhangmude[6] == 1)) ap++;

						if ((Zhangmude[6] == 0) && (Zhangmude[7] == 1)) ap++;

						if ((Zhangmude[7] == 0) && (Zhangmude[8] == 1)) ap++;

						if ((Zhangmude[8] == 0) && (Zhangmude[1] == 1)) ap++;

						if (ap == 1)

						{

							if ((Zhangmude[1] * Zhangmude[7] * Zhangmude[5] == 0) && (Zhangmude[3] * Zhangmude[5] * Zhangmude[7] == 0))

							{

								deletelist1.push_back(Point(i, j));

							}

						}

					}

				}

			}

		}

		if (deletelist1.size() == 0) break;

		for (size_t i = 0; i < deletelist1.size(); i++)

		{

			Point tem;

			tem = deletelist1[i];

			uchar* data = srcimage.ptr<uchar>(tem.y);

			data[tem.x] = 0;

		}

		deletelist1.clear();



		for (int j = 1; j < (nl - 1); j++)

		{

			uchar* data_last = srcimage.ptr<uchar>(j - 1);

			uchar* data = srcimage.ptr<uchar>(j);

			uchar* data_next = srcimage.ptr<uchar>(j + 1);

			for (int i = 1; i < (nc - 1); i++)

			{

				if (data[i] == 255)

				{

					Zhangmude[0] = 1;

					if (data_last[i] == 255) Zhangmude[1] = 1;

					else  Zhangmude[1] = 0;

					if (data_last[i + 1] == 255) Zhangmude[2] = 1;

					else  Zhangmude[2] = 0;

					if (data[i + 1] == 255) Zhangmude[3] = 1;

					else  Zhangmude[3] = 0;

					if (data_next[i + 1] == 255) Zhangmude[4] = 1;

					else  Zhangmude[4] = 0;

					if (data_next[i] == 255) Zhangmude[5] = 1;

					else  Zhangmude[5] = 0;

					if (data_next[i - 1] == 255) Zhangmude[6] = 1;

					else  Zhangmude[6] = 0;

					if (data[i - 1] == 255) Zhangmude[7] = 1;

					else  Zhangmude[7] = 0;

					if (data_last[i - 1] == 255) Zhangmude[8] = 1;

					else  Zhangmude[8] = 0;

					int whitepointtotal = 0;

					for (int k = 1; k < 9; k++)

					{

						whitepointtotal = whitepointtotal + Zhangmude[k];

					}

					if ((whitepointtotal >= 2) && (whitepointtotal <= 6))

					{

						int ap = 0;

						if ((Zhangmude[1] == 0) && (Zhangmude[2] == 1)) ap++;

						if ((Zhangmude[2] == 0) && (Zhangmude[3] == 1)) ap++;

						if ((Zhangmude[3] == 0) && (Zhangmude[4] == 1)) ap++;

						if ((Zhangmude[4] == 0) && (Zhangmude[5] == 1)) ap++;

						if ((Zhangmude[5] == 0) && (Zhangmude[6] == 1)) ap++;

						if ((Zhangmude[6] == 0) && (Zhangmude[7] == 1)) ap++;

						if ((Zhangmude[7] == 0) && (Zhangmude[8] == 1)) ap++;

						if ((Zhangmude[8] == 0) && (Zhangmude[1] == 1)) ap++;

						if (ap == 1)

						{

							if ((Zhangmude[1] * Zhangmude[3] * Zhangmude[5] == 0) && (Zhangmude[3] * Zhangmude[1] * Zhangmude[7] == 0))

							{

								deletelist1.push_back(Point(i, j));

							}

						}

					}

				}

			}

		}

		if (deletelist1.size() == 0) break;

		for (size_t i = 0; i < deletelist1.size(); i++)

		{

			Point tem;

			tem = deletelist1[i];

			uchar* data = srcimage.ptr<uchar>(tem.y);

			data[tem.x] = 0;

		}

		deletelist1.clear();

	}
>>>>>>> f626174f6c30a160c1c6bcd3b3c94029d6a43da8
}