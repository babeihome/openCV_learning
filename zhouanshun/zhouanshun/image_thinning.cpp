/*测试程序-加载、显示、修改、保存*/
#include <opencv2/opencv.hpp>
#include <iostream> 
#include <math.h>
using namespace cv;
using namespace std; //使用命名空间std，可以调用C++标准库里面的函数或类 
int main(int argc, char** argv) {    //argc 表示命令行输入参数的个数（以空白符分隔）， argv中存储了所有的命令行参数
	Mat src = imread("D:/path_pic/left.jpg");     //载入图像
	if (src.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("test opencv setup", WINDOW_AUTOSIZE);   //创建窗口，自动大小
	imshow("test opencv setup", src);               //显示图像到指定的窗口
	namedWindow("output windows", CV_WINDOW_AUTOSIZE);
	Mat output_image;
	cvtColor(src, output_image, CV_BGR2HLS);     //修改图像为某色彩空间
	imshow("output windows", output_image);
	imwrite("D:/path_pic/my.tif", output_image);   //重命名为my.tif并保存到D盘
	waitKey(0);
	return 0;
}