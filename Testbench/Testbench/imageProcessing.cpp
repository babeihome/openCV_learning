#include "imageProcessing.h"

using namespace std;
using namespace cv;


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
		//进行标准霍夫变换
		vector<Vec2f> lines;            //定义一个矢量结构用于存放得到的线段矢量集合
		HoughLines(origin_img, lines, 1, CV_PI / 180, 230, 0, 0);
		break;
	case 1:
		//进行累计概率变换
        vector<Vec4i> lines;
	    HoughLinesP(origin_img, lines, 1, CV_PI / 180, 200, 30 ,10);
	default: cout << "no this method, sorry" << endl;
		break;
	}
	return 0;
}

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
}