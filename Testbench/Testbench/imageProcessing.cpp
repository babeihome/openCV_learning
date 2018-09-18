
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
		cvtColor(origin_img, dst_img, CV_BGR2GRAY);
	case 1: {
		Mat smooth;
		MedianFlitering(origin_img, smooth);                 //��ֵ�˲�Ч��һ��
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
		dilate(origin_img, dst_img, Mat(), Point(), 5);                  //����5��
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
	
	vector<Vec2f> lines0;   //����һ��ʸ���ṹ���ڴ�ŵõ����߶�ʸ������
	vector<Vec4i> lines1;

	switch (method_code)
	{
	case 0: 	
		//���б�׼����任 
		HoughLines(origin_img, lines0, 1, CV_PI / 180, 230, 0, 0);
		break;
	case 1:
		//�����ۼƸ��ʱ任
	    HoughLinesP(origin_img, lines1, 1, CV_PI / 180, 200, 30 ,10);
		break;
	default: cout << "no this method, sorry" << endl;
		break;
	}
	return 0;
}

//��Ÿ�������ֵ
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
	for (int gap = 9 / 2; gap > 0; gap /= 2)//ϣ������
		for (int i = gap; i < 9; ++i)
			for (int j = i - gap; j >= 0 && arr[j] > arr[j + gap]; j -= gap)
				swap(arr[j], arr[j + gap]);
	return arr[4];//������ֵ
}

//��ֵ�˲�
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
	_dst.copyTo(dst);//����
}

void chao_thinimage(Mat &srcimage)//��ͨ������ֵ�����ͼ��
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

int least_square_method(Mat &src, float *theta, float *b )
{
	int i, j,N=0,start=2;
	int count_x[400],count_y[400];
	int nl = src.rows;
	int nc = src.cols;
	float temp,k;

	for (i = start; i < (nl - start); i++) {//i ���У�������
		uchar *data = src.ptr<uchar>(i);
		for (j = start; j < (nc - start); j++) {//j���У�������
			if (data[j] == 255) {
				count_x[N] = j; count_y[N]=i;
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
		E_XX += count_x[i]* count_x[i];
		E_Y += count_y[i];
		E_XY += count_x[i] * count_y[i];
	}

	if (temp=(N*E_XX - E_X * E_X) != 0) {
		k = (N*E_XY - E_X * E_Y) / temp;
		*b = (E_XX*E_Y - E_X * E_XY) / temp;
		*theta = atanf(k);
		return 1;
	}

	else return 0;

	cout << "y=" << k << "x+" << b << endl;
}