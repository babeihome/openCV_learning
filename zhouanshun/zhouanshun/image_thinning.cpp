/*���Գ���-���ء���ʾ���޸ġ�����*/
#include <opencv2/opencv.hpp>
#include <iostream> 
#include <math.h>
using namespace cv;
using namespace std; //ʹ�������ռ�std�����Ե���C++��׼������ĺ������� 
int main(int argc, char** argv) {    //argc ��ʾ��������������ĸ������Կհ׷��ָ����� argv�д洢�����е������в���
	Mat src = imread("D:/path_pic/left.jpg");     //����ͼ��
	if (src.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("test opencv setup", WINDOW_AUTOSIZE);   //�������ڣ��Զ���С
	imshow("test opencv setup", src);               //��ʾͼ��ָ���Ĵ���
	namedWindow("output windows", CV_WINDOW_AUTOSIZE);
	Mat output_image;
	cvtColor(src, output_image, CV_BGR2HLS);     //�޸�ͼ��Ϊĳɫ�ʿռ�
	imshow("output windows", output_image);
	imwrite("D:/path_pic/my.tif", output_image);   //������Ϊmy.tif�����浽D��
	waitKey(0);
	return 0;
}