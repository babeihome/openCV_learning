#include <iostream>
#include <Windows.h>
#include <opencv2/opencv.hpp>
#include "imageProcessing.h"
#include "file_operation.h"

using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
	// load data path
	string imagePath("..\\..\\shared_data\\stm32\\bmp_sequence_5\\");
	
	vector<string> files;
	getFiles(imagePath, files);

	// loop of experiments start
	queue<queue<string>> experiment_sequence;		// multiple experiment register here
	bool debug = false;
	// experiment describe here
	// 
	queue<string> exp1;
	exp1.push("30"); // first is pre-process
	exp1.push("0");  // then binarization
	exp1.push("0"); // then after-process
	exp1.push("0"); //thining
	exp1.push("0"); //anaylse
	experiment_sequence.push(exp1);	//
	// experiment describe end

	Mat img, pre_img, bi_img, aft_img, thin_img, tmp_img;



	for (int exp_id = 0; exp_id < experiment_sequence.size(); exp_id++) {	
		
		double start, stop, durationTime;
		double sub_start, sub_stop, sub_d;
		//timing start
		start = time(NULL);

		//run into one experiment
		for (int i = 0; i < files.size(); i++)
		{
			queue<string> exp_tmp = experiment_sequence.front();


			//anaylse one image
			img = imread(files[i], -1);
			if (img.empty())
			{
				std::cout << "Error: Could not load image" << endl;
				return 0;
			}
			//debug part: show the image
			if (debug) {
				namedWindow("origin", 0);
				resizeWindow("origin", 640, 480);
				moveWindow("origin", 0, 0);
				imshow("origin", img);
				waitKey(1);
			}
			// image processing start
			

			int tmp_op;

			//pre-process
			sub_start = clock();
			string pre_process = exp_tmp.front();
			exp_tmp.pop();
			tmp_img = img;
			for (int op_id = 0; op_id < pre_process.length(); op_id++) {
				tmp_op = pre_process[op_id] - 48;   // ASCII code of '0' is 48
				preProcess(tmp_img, pre_img, tmp_op);
				tmp_img = pre_img;
			}
			sub_stop = clock();
			std::cout << "pre-processing done:" << (sub_stop - sub_start)/CLK_TCK << "s" << std::endl;

			//debug part: show the image
			if (debug) {
				namedWindow("pre", 0);
				resizeWindow("pre", 640, 480);
				moveWindow("pre", 640, 0);
				imshow("pre", pre_img);
				waitKey(1);
			}


			//binarization img
			sub_start = clock();
			string bi_process = exp_tmp.front();
			exp_tmp.pop();
			tmp_img = pre_img;
			for (int op_id = 0; op_id < bi_process.length(); op_id++) {
				tmp_op = bi_process[op_id] - 48;   // ASCII code of '0' is 48
				binarize(tmp_img, bi_img, tmp_op);
				tmp_img = bi_img;
			}
			std::cout << "binarization done" << std::endl;
			//debug part: show the image
			if (debug) {
				namedWindow("black", 0);
				resizeWindow("black", 640, 480);
				moveWindow("black", 0, 480);
				imshow("black", bi_img);
				//waitKey(1);
				sub_stop = clock();
				std::cout << "pre-processing done:" << (sub_stop - sub_start) / CLK_TCK << "s" << std::endl;
			}


			//after processing img
			string aft_process = exp_tmp.front();
			exp_tmp.pop();
			tmp_img = bi_img;
			for (int op_id = 0; op_id < aft_process.length(); op_id++) {
				tmp_op = aft_process[op_id] - 48;   // ASCII code of '0' is 48
				afterProcess(tmp_img, aft_img, tmp_op);
				tmp_img = aft_img;
			}
			std::cout << "after-processing done" << std::endl;
			//debug part: show the image
			if (debug) {
				//imshow("after", aft_img);
				//waitKey(1);
			}

			//thining img
			string thin_process = exp_tmp.front();
			exp_tmp.pop();
			tmp_img = aft_img;
			for (int op_id = 0; op_id < thin_process.length(); op_id++) {
				tmp_op = thin_process[op_id] - 48;   // ASCII code of '0' is 48
				thinning(tmp_img, thin_img, tmp_op);
				tmp_img = thin_img;
			}
			std::cout << "thinning processing done" << std::endl;
			//debug part: show the image
			if (debug) {
				namedWindow("thin", 0);
				resizeWindow("thin", 640, 480);
				moveWindow("thin", 640, 480);
				imshow("thin", thin_img);
				waitKey(1);
			}

			//analyse img
			string analyse_process = exp_tmp.front();
			vector<pair<float, float>> param_list;
			exp_tmp.pop();
			for (int op_id = 0; op_id < analyse_process.length(); op_id++) {
				tmp_op = analyse_process[op_id] - 48;   // ASCII code of '0' is 48
				analysis(thin_img, param_list, tmp_op);
			}
			std::cout << "analysis done" << std::endl;
		}
		experiment_sequence.pop();
		stop = time(NULL);
		durationTime = (double)difftime(stop, start);
		std::cout << "Experiment:" << exp_id << "\tTime Consuming:" << durationTime << " s" << endl;
	}
	waitKey(0);

	return 0;
}