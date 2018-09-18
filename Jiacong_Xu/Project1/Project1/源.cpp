
#include <iostream>  
#include <vector>
#include "opencv2/opencv.hpp"



using namespace cv;
using namespace std;



int main()

{
	void chao_thinimage(Mat &srcimage);
	Mat src, dst, src_gray,dst_processed,dst_ok, dst_Image;
	src = imread("C:/OpenCV/straight_line.png");
	/*if (src.data) {
		printf("can not open\n");
		return -1;
	}*/

	cvtColor(src, src_gray, CV_BGR2GRAY); 
	threshold(src_gray, dst, 0, 255,  CV_THRESH_OTSU);
	Mat element(5, 5, CV_8U, Scalar(1));
	morphologyEx(dst, dst_processed, MORPH_OPEN, element);   //开运算
	morphologyEx(dst_processed, dst_ok, MORPH_CLOSE, element);   //闭运算
	chao_thinimage(dst_ok);

	cvtColor(src_gray, dst_Image, COLOR_GRAY2BGR);


	//进行霍夫变换
	/*vector<Vec2f> lines;            //定义一个矢量结构用于存放得到的线段矢量集合
	HoughLines(dst_ok, lines, 1, CV_PI / 180, 230, 0, 0);

	//在图中绘出线段
	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0];
		float theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(dst_Image, pt1, pt2, Scalar(0, 0, 255), 1, LINE_AA);
	}*/



	//进行霍夫变换
	vector<Vec4i> lines;
	HoughLinesP(dst_ok, lines, 1, CV_PI / 180, 10, 3, 10);
	for (size_t i = 0; i < lines.size(); i++)
	{
		 line(dst_Image, Point(lines[i][0], lines[i][1]), Point(lines[i][2], lines[i][3]),
	     Scalar(0, 0, 0), 1, 8);
	}


// show original image
	//namedWindow("input_image", CV_WINDOW_AUTOSIZE);
	//imshow("input_image", src);

// show gray-level image
	//namedWindow("output_image", CV_WINDOW_AUTOSIZE);
	//imshow("output_image", src_gray);

// show segement image
	//namedWindow("output_image", CV_WINDOW_AUTOSIZE);
	//imshow("output_image", dst);

// show smoothed image
	namedWindow("processing_image", CV_WINDOW_AUTOSIZE);
	imshow("processing_image", dst_ok);
	namedWindow("huofu_image", CV_WINDOW_AUTOSIZE);
	imshow("huofu_image", dst_Image);


	waitKey(0);
	cvDestroyWindow("huofu_image");
	cvDestroyWindow("processing_image");
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