
#include "imageProcessing.h"
#include "math.h"

using namespace std;
using namespace cv;

Mat dst;

// don't modify origin_img!!!
void preProcess(Mat &origin_img, Mat &dst_img, int method_code) {
	switch (method_code)
	{
	case 0:
		cvtColor(origin_img, dst_img, CV_RGB2GRAY);
		break;
	case 1: {
		Mat smooth;
		MedianFlitering(origin_img, smooth);                 //中值滤波效果一般
		cvtColor(smooth, dst_img, CV_BGR2GRAY);
		break;
	}	
	case 2: {
		Mat aChannels[3];
		split(origin_img, aChannels);
		dst_img = aChannels[2];
		break;
	}
	case 3:
	{
		resize(origin_img, dst_img, Size(origin_img.cols / 2, origin_img.rows / 2), 0, 0, INTER_LINEAR);
		break;
	}
	default:
		break;
	}
}
void binarize(Mat &origin_img, Mat &dst_img, int method_code) {
	switch (method_code)
	{
	case 0:
		threshold(origin_img, dst_img, 0, 255, CV_THRESH_OTSU);
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
		dilate(origin_img, dst_img, Mat(), Point(), 5); //膨胀5次
		break;
	default:
		break;
	}
}
void thinning(Mat &origin_img, Mat &dst_img, int method_code) {
	switch (method_code)
	{
	case 0: dst_img = origin_img.clone(); chao_thinimage(dst_img,1);
		break;
	case 1:
		dst_img = origin_img.clone();
		chao_thinimage(dst_img, 2);
		break;
	case 2:
		dst_img = origin_img.clone();
		thinImage_alt(dst_img, 8, 100);
		//thinImage_alt(dst_img, 4, 5);
		thinImage_alt(dst_img, 2, 100);
		//thinImage_alt(dst_img, 1, 200);
		//imshow("test",dst_img);
		//waitKey(200);
		break;
	case 3:
		dst_img = origin_img.clone();
		thinImage_alt_2(dst_img,2,200);
		break;
	default: cout << "no this method, sorry" << endl;
		break;
	}
}
// the first of pair is k, the second one is b, this function should return the number of valid pair of k & b
int analysis(Mat &origin_img, vector < pair < float, float >> &kb, int method_code) {
	switch (method_code)
	{
	case 0: {
		//进行标准霍夫变换
		vector<Vec2f> lines;            //定义一个矢量结构用于存放得到的线段矢量集合
		HoughLines(origin_img, lines, 1, CV_PI / 180, 230, 0, 0);
		break;
	}
	case 1: {
		//进行累计概率变换
		vector<Vec4i> lines;
		HoughLinesP(origin_img, lines, 1, CV_PI / 180, 200, 30, 10);
		break;
	}
	default: cout << "no this method, sorry" << endl;
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
//同一窗口显示多个图片 算法局限只能显示原图
Mat combineImages(vector<Mat> imgs,//@parameter1:需要显示的图像组 
	int col,//parameter2:显示的列数
	int row, //parameter3:显示的行数
	bool hasMargin) {//parameter4:是否设置边框
	int imgAmount = imgs.size();//获取需要显示的图像数量
	int width = imgs[0].cols;//本函数默认需要显示的图像大小相同
	int height = imgs[0].rows;//获取图像宽高
	int newWidth, newHeight;//新图像宽高
	if (!hasMargin) {
		newWidth = col * imgs[0].cols;//无边框，新图像宽/高=原图像宽/高*列/行数
		newHeight = row * imgs[0].rows;
	}
	else {
		newWidth = (col + 1) * 20 + col * width;//有边框，要将上边框的尺寸，这里设置边框为20px
		newHeight = (row + 1) * 20 + row * height;
	}

	Mat newImage(newHeight, newWidth, CV_8UC3, Scalar(255, 255, 255));//显示创建设定尺寸的新的大图像；色深八位三通道；填充为白色


	int x, y, imgCount;//x列号，y行号，imgCount图片序号
	if (hasMargin) {//有边框
		imgCount = 0;
		x = 0; y = 0;
		while (imgCount < imgAmount) {
			Mat imageROI = newImage(Rect(x*width + (x + 1) * 20, y*height + (y + 1) * 20, width, height));//创建感兴趣区域
			imgs[imgCount].copyTo(imageROI);//将图像复制到大图中
			imgCount++;
			if (x == (col - 1)) {
				x = 0;
				y++;
			}
			else {
				x++;
			}//移动行列号到下一个位置
		}
	}
	else {//无边框
		imgCount = 0;
		x = 0; y = 0;
		while (imgCount < imgAmount) {
			Mat imageROI = newImage(Rect(x*width, y*height, width, height));
			imgs[imgCount].copyTo(imageROI);
			imgCount++;
			if (x == (col - 1)) {
				x = 0;
				y++;
			}
			else {
				x++;
			}
		}
	}
	return newImage;//返回新的组合图像
};

void chao_thinimage(Mat &srcimage, int coreSize)//单通道、二值化后的图像
{

	vector<Point> deletelist1;

	int Zhangmude[9];

	int nl = srcimage.rows;

	int nc = srcimage.cols;
	if (coreSize == 1) {
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
	else if (coreSize == 2) {
		vector<Point> deleteList;
		int neighbourhood[9];
		int distinguish[9];
		int nl = srcimage.rows;
		int nc = srcimage.cols;
		bool inOddIterations = true;
		int loop_num = 0;
		while (true) {
			int offset = (int)inOddIterations;
			loop_num++;
			for (int j = 2 + offset; j < (nl - 3); j += 2) {
				uchar* data_s1 = srcimage.ptr<uchar>(j - 1);
				uchar* data_s2 = srcimage.ptr<uchar>(j - 2);
				uchar* data = srcimage.ptr<uchar>(j);
				uchar* data_a1 = srcimage.ptr<uchar>(j + 1);
				uchar* data_a2 = srcimage.ptr<uchar>(j + 2);
				uchar* data_a3 = srcimage.ptr<uchar>(j + 3);
				//uchar* data_next_3 = srcimage.ptr<uchar>(j + 3);
				for (int i = 2 + offset; i < (nc - 3); i += 2) {
					distinguish[0] = (data[i] + data[i + 1] + data_a1[i] + data_a1[i + 1]);
					distinguish[1] = (data_s2[i] + data_s2[i + 1] + data_s1[i] + data_s1[i + 1]);
					distinguish[2] = (data_s2[i + 2] + data_s2[i + 3] + data_s1[i + 2] + data_s1[i + 3]);
					distinguish[3] = (data[i + 2] + data[i + 3] + data_a1[i + 2] + data_a1[i + 3]);
					distinguish[4] = (data_a2[i + 2] + data_a2[i + 3] + data_a3[i + 2] + data_a3[i + 3]);
					distinguish[5] = (data_a2[i] + data_a2[i + 1] + data_a3[i] + data_a3[i + 1]);
					distinguish[6] = (data_a2[i - 2] + data_a2[i - 1] + data_a3[i - 2] + data_a3[i - 1]);
					distinguish[7] = (data[i - 2] + data[i - 1] + data_a1[i - 2] + data_a1[i - 1]);
					distinguish[8] = (data_s2[i - 2] + data_s2[i - 1] + data_s1[i - 2] + data_s1[i - 1]);
					if (distinguish[0] >= 510) {
						int whitePointCount = 0;
						neighbourhood[0] = 1;
						if (distinguish[1] >= 510) neighbourhood[1] = 1;
						else  neighbourhood[1] = 0;
						if (distinguish[2] >= 510) neighbourhood[2] = 1;
						else  neighbourhood[2] = 0;
						if (distinguish[3] >= 510) neighbourhood[3] = 1;
						else  neighbourhood[3] = 0;
						if (distinguish[4] >= 510) neighbourhood[4] = 1;
						else  neighbourhood[4] = 0;
						if (distinguish[5] >= 510) neighbourhood[5] = 1;
						else  neighbourhood[5] = 0;
						if (distinguish[6] >= 510) neighbourhood[6] = 1;
						else  neighbourhood[6] = 0;
						if (distinguish[7] >= 510) neighbourhood[7] = 1;
						else  neighbourhood[7] = 0;
						if (distinguish[8] >= 510) neighbourhood[8] = 1;
						else  neighbourhood[8] = 0;
						for (int k = 1; k < 9; k++) {
							whitePointCount += neighbourhood[k];
						}
						if ((whitePointCount >= 2) && (whitePointCount <= 6)) {
							int ap = 0;
							if ((neighbourhood[1] == 0) && (neighbourhood[2] == 1)) ap++;
							if ((neighbourhood[2] == 0) && (neighbourhood[3] == 1)) ap++;
							if ((neighbourhood[3] == 0) && (neighbourhood[4] == 1)) ap++;
							if ((neighbourhood[4] == 0) && (neighbourhood[5] == 1)) ap++;
							if ((neighbourhood[5] == 0) && (neighbourhood[6] == 1)) ap++;
							if ((neighbourhood[6] == 0) && (neighbourhood[7] == 1)) ap++;
							if ((neighbourhood[7] == 0) && (neighbourhood[8] == 1)) ap++;
							if ((neighbourhood[8] == 0) && (neighbourhood[1] == 1)) ap++;
							if (ap == 1) {
								if (inOddIterations && (neighbourhood[3] * neighbourhood[5] * neighbourhood[7] == 0)
									&& (neighbourhood[1] * neighbourhood[3] * neighbourhood[5] == 0)) {
									deleteList.push_back(Point(i, j));
									deleteList.push_back(Point(i + 1, j));
									deleteList.push_back(Point(i, j + 1));
									deleteList.push_back(Point(i + 1, j + 1));
								}
								else if (!inOddIterations && (neighbourhood[1] * neighbourhood[5] * neighbourhood[7] == 0)
									&& (neighbourhood[1] * neighbourhood[3] * neighbourhood[7] == 0)) {
									deleteList.push_back(Point(i, j));
									deleteList.push_back(Point(i + 1, j));
									deleteList.push_back(Point(i, j + 1));
									deleteList.push_back(Point(i + 1, j + 1));
								}
							}
						}
					}
				}
			}
			if (deleteList.size() == 0)
				break;
			for (size_t i = 0; i < deleteList.size(); i++) {
				Point tem;
				tem = deleteList[i];
				uchar* data = srcimage.ptr<uchar>(tem.y);
				data[tem.x] = 0;
			}
			deleteList.clear();

			inOddIterations = !inOddIterations;
			//imshow("test2", srcimage);
			//imwrite("./results/improved/" + to_string(loop_num) + ".png", srcimage);
			//waitKey(200);
		}

	}
	
}

void thinImage_alt(Mat &srcImg, int coresize, int loop_times) {
	vector<Point> deleteList;
	uchar *groupdata[100];
	int neighbourhood[9];
	int distinguish[9];
	int nl = srcImg.rows;
	int nc = srcImg.cols;
	int upsize = coresize;
	int downsize = 2 * coresize - 1;
	bool inOddIterations = true;
	int loop_num = 0;
	int threshold = 255;
	int offset = 0;
	while (true) {
		/*if (offset < coresize) {
			offset++;
		}
		else {
			offset = 0;
		}*/
		//offset = 0;

		loop_num++;
		for (int j = (upsize + offset); j < (nl - downsize - 1); j = j + coresize)
		{
			// get the data array, n1 is the offset of rows
			for (int n1 = -coresize; n1 < 2 * coresize; n1++) {
				groupdata[coresize + n1] = srcImg.ptr<uchar>(j + n1);
			}
			/*
			for (int n1 = 1; n1 <= upsize; n1++) {
				groupdata[upsize - n1] = srcImg.ptr<uchar>(j - n1);
			}
			groupdata[upsize] = srcImg.ptr<uchar>(j);
			for (int n1 = 1; n1 <= downsize; n1++) {
				groupdata[upsize + n1] = srcImg.ptr<uchar>(j + n1);
			}
			*/
			for (int i = upsize + offset; i < (nc - downsize); i = i + coresize) {
				for (int n4 = 0; n4 <= 8; n4++)
					distinguish[n4] = 0;  //initialize the distinguish				
				for (int n2 = 0; n2 < coresize; n2++) {	//n2 is offset of rows
					for (int n3 = 0; n3 < coresize; n3++) {	//n3 is offset of columns
						distinguish[0] += groupdata[coresize + n2][i + n3];
						distinguish[1] += groupdata[n2][i + n3];
						distinguish[2] += groupdata[n2][i + coresize + n3];
						distinguish[3] += groupdata[coresize + n2][i + coresize + n3];
						distinguish[4] += groupdata[2 * coresize + n2][i + coresize + n3];
						distinguish[5] += groupdata[2 * coresize + n2][i + n3];
						distinguish[6] += groupdata[2 * coresize + n2][i - coresize + n3];
						distinguish[7] += groupdata[coresize + n2][i - coresize + n3];
						distinguish[8] += groupdata[n2][i - coresize + n3];
					}
				}

				if (distinguish[0] >= threshold) {
					int whitePointCount = 0;
					neighbourhood[0] = 1;
					if (distinguish[1] >= threshold) neighbourhood[1] = 1;
					else  neighbourhood[1] = 0;
					if (distinguish[2] >= threshold) neighbourhood[2] = 1;
					else  neighbourhood[2] = 0;
					if (distinguish[3] >= threshold) neighbourhood[3] = 1;
					else  neighbourhood[3] = 0;
					if (distinguish[4] >= threshold) neighbourhood[4] = 1;
					else  neighbourhood[4] = 0;
					if (distinguish[5] >= threshold) neighbourhood[5] = 1;
					else  neighbourhood[5] = 0;
					if (distinguish[6] >= threshold) neighbourhood[6] = 1;
					else  neighbourhood[6] = 0;
					if (distinguish[7] >= threshold) neighbourhood[7] = 1;
					else  neighbourhood[7] = 0;
					if (distinguish[8] >= threshold) neighbourhood[8] = 1;
					else  neighbourhood[8] = 0;
					for (int k = 1; k < 9; k++) {
						whitePointCount += neighbourhood[k];
					}
					if ((whitePointCount >= 2) && (whitePointCount <= 6)) {
						int ap = 0;
						if ((neighbourhood[1] == 0) && (neighbourhood[2] == 1)) ap++;
						if ((neighbourhood[2] == 0) && (neighbourhood[3] == 1)) ap++;
						if ((neighbourhood[3] == 0) && (neighbourhood[4] == 1)) ap++;
						if ((neighbourhood[4] == 0) && (neighbourhood[5] == 1)) ap++;
						if ((neighbourhood[5] == 0) && (neighbourhood[6] == 1)) ap++;
						if ((neighbourhood[6] == 0) && (neighbourhood[7] == 1)) ap++;
						if ((neighbourhood[7] == 0) && (neighbourhood[8] == 1)) ap++;
						if ((neighbourhood[8] == 0) && (neighbourhood[1] == 1)) ap++;
						if (ap == 1) {
							if (inOddIterations && (neighbourhood[3] * neighbourhood[5] * neighbourhood[7] == 0)
								&& (neighbourhood[1] * neighbourhood[3] * neighbourhood[5] == 0)) {
								for (int n5 = 0; n5 < coresize; n5++) {
									for (int n6 = 0; n6 < coresize; n6++) {
										deleteList.push_back(Point(i + n6, j + n5));
									}
								}
							}
							else if (!inOddIterations && (neighbourhood[1] * neighbourhood[5] * neighbourhood[7] == 0)
								&& (neighbourhood[1] * neighbourhood[3] * neighbourhood[7] == 0)) {
								for (int n5 = 0; n5 < coresize; n5++) {
									for (int n6 = 0; n6 < coresize; n6++) {
										deleteList.push_back(Point(i + n6, j + n5));
									}
								}
							}
						}
					}
				}
			}
		}
		if (deleteList.size() == 0 | loop_num > loop_times)
			break;
		for (size_t i = 0; i < deleteList.size(); i++) {
			Point tem;
			tem = deleteList[i];
			uchar* data = srcImg.ptr<uchar>(tem.y);
			data[tem.x] = 0;
		}
		deleteList.clear();

		inOddIterations = !inOddIterations;
		offset = !offset;
		//imshow("test3", srcImg);
		//waitKey(200);
	}

}


	//imshow("test", srcImg);

void thinImage_alt_2(Mat &srcImg, int coresize, int loop_times) {
	vector<Point> deleteList;
	uchar *groupdata[100];
	int neighbourhood[9];
	int distinguish[9];
	int nl = srcImg.rows;
	int nc = srcImg.cols;
	int upsize = coresize;
	int downsize = 2 * coresize - 1;
	bool inOddIterations = true;
	int loop_num = 0;
	int threshold = 255;
	int offset = 0;
	Mat M(nl / coresize + 5, nc / coresize + 5, CV_8UC1);
	for (int j = (upsize + coresize); j < (nl - downsize - 1); j = j + 3 * coresize)
	{
		// get the data array, n1 is the offset of rows
		for (int n1 = -coresize; n1 < 2 * coresize; n1++) {
			groupdata[coresize + n1] = srcImg.ptr<uchar>(j + n1);
		}
		for (int i = upsize + coresize; i < (nc - downsize - 1); i = i + 3 * coresize) {
			for (int n4 = 0; n4 <= 8; n4++)
				distinguish[n4] = 0;  //initialize the distinguish				
			for (int n2 = 0; n2 < coresize; n2++) {	//n2 is offset of rows
				for (int n3 = 0; n3 < coresize; n3++) {	//n3 is offset of columns
					distinguish[0] += groupdata[coresize + n2][i + n3];
					distinguish[1] += groupdata[n2][i + n3];
					distinguish[2] += groupdata[n2][i + coresize + n3];
					distinguish[3] += groupdata[coresize + n2][i + coresize + n3];
					distinguish[4] += groupdata[2 * coresize + n2][i + coresize + n3];
					distinguish[5] += groupdata[2 * coresize + n2][i + n3];
					distinguish[6] += groupdata[2 * coresize + n2][i - coresize + n3];
					distinguish[7] += groupdata[coresize + n2][i - coresize + n3];
					distinguish[8] += groupdata[n2][i - coresize + n3];
				}

			}
			if (distinguish[0] >= threshold) M.at<uchar>(j / coresize, i / coresize) = 255;
			else  M.at<uchar>(j / coresize, i / coresize) = 0;
			if (distinguish[1] >= threshold) M.at<uchar>(j / coresize - 1, i / coresize) = 255;
			else  M.at<uchar>(j / coresize - 1, i / coresize) = 0;
			if (distinguish[2] >= threshold) M.at<uchar>(j / coresize - 1, i / coresize + 1) = 255;
			else M.at<uchar>(j / coresize - 1, i / coresize + 1) = 0;
			if (distinguish[3] >= threshold) M.at<uchar>(j / coresize, i / coresize + 1) = 255;
			else  M.at<uchar>(j / coresize, i / coresize + 1) = 0;
			if (distinguish[4] >= threshold) M.at<uchar>(j / coresize + 1, i / coresize + 1) = 255;
			else  M.at<uchar>(j / coresize + 1, i / coresize + 1) = 0;
			if (distinguish[5] >= threshold) M.at<uchar>(j / coresize + 1, i / coresize) = 255;
			else  M.at<uchar>(j / coresize + 1, i / coresize) = 0;
			if (distinguish[6] >= threshold) M.at<uchar>(j / coresize + 1, i / coresize - 1) = 255;
			else  M.at<uchar>(j / coresize + 1, i / coresize - 1) = 0;
			if (distinguish[7] >= threshold) M.at<uchar>(j / coresize, i / coresize - 1) = 255;
			else  M.at<uchar>(j / coresize, i / coresize - 1) = 0;
			if (distinguish[8] >= threshold) M.at<uchar>(j / coresize - 1, i / coresize - 1) = 255;
			else  M.at<uchar>(j / coresize - 1, i / coresize - 1) = 0;
		}
	}
	while (true) {
		loop_num++;
		for (int j = 1; j < (M.rows - 1); j++) {
			uchar* data_last = M.ptr<uchar>(j - 1);
			uchar* data = M.ptr<uchar>(j);
			uchar* data_next = M.ptr<uchar>(j + 1);
			for (int i = 1; i < (M.cols - 1); i++) {
				if (data[i] == 255) {
					int whitePointCount = 0;
					neighbourhood[0] = 1;
					if (data_last[i] == 255) neighbourhood[1] = 1;
					else  neighbourhood[1] = 0;
					if (data_last[i + 1] == 255) neighbourhood[2] = 1;
					else  neighbourhood[2] = 0;
					if (data[i + 1] == 255) neighbourhood[3] = 1;
					else  neighbourhood[3] = 0;
					if (data_next[i + 1] == 255) neighbourhood[4] = 1;
					else  neighbourhood[4] = 0;
					if (data_next[i] == 255) neighbourhood[5] = 1;
					else  neighbourhood[5] = 0;
					if (data_next[i - 1] == 255) neighbourhood[6] = 1;
					else  neighbourhood[6] = 0;
					if (data[i - 1] == 255) neighbourhood[7] = 1;
					else  neighbourhood[7] = 0;
					if (data_last[i - 1] == 255) neighbourhood[8] = 1;
					else  neighbourhood[8] = 0;
					for (int k = 1; k < 9; k++) {
						whitePointCount += neighbourhood[k];
					}
					if ((whitePointCount >= 2) && (whitePointCount <= 6)) {
						int ap = 0;
						if ((neighbourhood[1] == 0) && (neighbourhood[2] == 1)) ap++;
						if ((neighbourhood[2] == 0) && (neighbourhood[3] == 1)) ap++;
						if ((neighbourhood[3] == 0) && (neighbourhood[4] == 1)) ap++;
						if ((neighbourhood[4] == 0) && (neighbourhood[5] == 1)) ap++;
						if ((neighbourhood[5] == 0) && (neighbourhood[6] == 1)) ap++;
						if ((neighbourhood[6] == 0) && (neighbourhood[7] == 1)) ap++;
						if ((neighbourhood[7] == 0) && (neighbourhood[8] == 1)) ap++;
						if ((neighbourhood[8] == 0) && (neighbourhood[1] == 1)) ap++;
						if (ap == 1) {
							if (inOddIterations && (neighbourhood[3] * neighbourhood[5] * neighbourhood[7] == 0)
								&& (neighbourhood[1] * neighbourhood[3] * neighbourhood[5] == 0)) {
								deleteList.push_back(Point(i, j));
							}
							else if (!inOddIterations && (neighbourhood[1] * neighbourhood[5] * neighbourhood[7] == 0)
								&& (neighbourhood[1] * neighbourhood[3] * neighbourhood[7] == 0)) {
								deleteList.push_back(Point(i, j));
							}
						}
					}
				}
			}
		}
		if (deleteList.size() == 0 | loop_num > loop_times)
			break;
		for (size_t i = 0; i < deleteList.size(); i++) {
			Point tem;
			tem = deleteList[i];
			uchar* data = M.ptr<uchar>(tem.y);
			data[tem.x] = 0;
		}
		deleteList.clear();

		inOddIterations = !inOddIterations;
		offset = !offset;
		imshow("test3", M);
		waitKey(200);
	}
	srcImg = M;
}

int least_square_method(Mat &src, float *theta, float *b)
{
	int i, j, N = 0, start = 2;
	int count_x[400], count_y[400];
	int nl = src.rows;
	int nc = src.cols;
	float temp, k;

	for (i = start; i < (nl - start); i++) {//i 是行，纵坐标
		uchar *data = src.ptr<uchar>(i);
		for (j = start; j < (nc - start); j++) {//j是列，横坐标
			if (data[j] == 255) {
				count_x[N] = j; count_y[N] = i;
				N++;
			}
		}
	}

	float E_X = 0.0;
	float E_XX = 0.0;
	float E_Y = 0.0;
	float E_XY = 0.0;

	for (i = 0; i <= N; i++) {
		E_X += count_x[i];
		E_XX += count_x[i] * count_x[i];
		E_Y += count_y[i];
		E_XY += count_x[i] * count_y[i];
	}

	if (temp = (N*E_XX - E_X * E_X) != 0) {
		k = (N*E_XY - E_X * E_Y) / temp;
		*b = (E_XX*E_Y - E_X * E_XY) / temp;
		*theta = atanf(k);
		return 1;
	}
	else return 0;
}