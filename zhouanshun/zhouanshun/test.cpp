#include <iostream>  
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  

using namespace cv;

int main()
{
	// 读入一张图片图片要放在debug的外层目录下才可以   
	Mat img = imread("C:\\Users\\zas\\source\\repos\\openCV_learning\\zhouanshun\\x64\\left.jpg");
	// 创建一个名为 "图片"窗口    
	namedWindow("图片");
	// 在窗口中显示图片   
	imshow("图片", img);
	// 等待6000 ms后窗口自动关闭    
	waitKey(60000);
	return 0;
}
