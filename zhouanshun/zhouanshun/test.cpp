#include <iostream>  
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  

using namespace cv;

int main()
{
	// ����һ��ͼƬͼƬҪ����debug�����Ŀ¼�²ſ���   
	Mat img = imread("C:\\Users\\zas\\source\\repos\\openCV_learning\\zhouanshun\\x64\\left.jpg");
	// ����һ����Ϊ "ͼƬ"����    
	namedWindow("ͼƬ");
	// �ڴ�������ʾͼƬ   
	imshow("ͼƬ", img);
	// �ȴ�6000 ms�󴰿��Զ��ر�    
	waitKey(60000);
	return 0;
}
