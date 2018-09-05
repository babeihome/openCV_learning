#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

void thinImage(Mat & srcImg) {
	vector<Point> deleteList;
	int neighbourhood[9];
	int nl = srcImg.rows;
	int nc = srcImg.cols;
	bool inOddIterations = true;
	while (true) {
		for (int j = 1; j < (nl - 1); j++) {
			uchar* data_last = srcImg.ptr<uchar>(j - 1);
			uchar* data = srcImg.ptr<uchar>(j);
			uchar* data_next = srcImg.ptr<uchar>(j + 1);
			for (int i = 1; i < (nc - 1); i++) {
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
		if (deleteList.size() == 0)
			break;
		for (size_t i = 0; i < deleteList.size(); i++) {
			Point tem;
			tem = deleteList[i];
			uchar* data = srcImg.ptr<uchar>(tem.y);
			data[tem.x] = 0;
		}
		deleteList.clear();

		inOddIterations = !inOddIterations;
	}
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
void MedianFlitering(const Mat &src, Mat &dst) {
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


int main(int argc, char* argv[])
{
	// image path from command argv
	//Mat img = imread(argv[1], -1);
	String imagePath("../../shared_data/stm32/path3.jpg");
	Mat img = imread(imagePath, -1);
	if (img.empty())
	{
		cout << "Error: Could not load image" << endl;
		return 0;
	}

	Mat gray;
	cvtColor(img, gray, CV_BGR2GRAY);

	Mat smooth;
	MedianFlitering(img,smooth);//中值滤波意义不大

	Mat dst;
	threshold(gray, dst, 0, 255, CV_THRESH_OTSU);

	Mat dilateion;
	dilate(dst, dilateion, Mat(),Point(),5);

	Mat close;
	morphologyEx(dst, close, MORPH_CLOSE, Mat(), Point(), 5);

	Mat line;
	line = dilateion.clone();   //克隆二值化图像
	thinImage(line);

	Mat line_2;
	line_2 = close.clone();
	thinImage(line_2);

	//Mat combineImages(vector<Mat> imgs, int col, int row, bool hasMargin);//函数声明
	//vector<Mat> imgs(2);
	//imgs[0] = img;
	//imgs[1] = gray;
	//Mat m = combineImages(imgs, 1, 2, true);
	//namedWindow("test", 0);
	//imshow("test", m);

	/*imshow("src", img);
	imshow("gray", gray);
	imshow("dst", dst);*/
	imshow("dilateion", dilateion);
	//imshow("smooth", smooth);
	imshow("line", line);
	imshow("close", close);
	imshow("line_2", line_2);
	waitKey(0);

	return 0;
}

