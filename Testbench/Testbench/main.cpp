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
	string imagePath("..\\..\\shared_data\\stm32\\bmp_sequence_5");
	
	vector<string> files;
	getFiles(imagePath, files);

	// loop of experiments start
	queue<queue<string>> experiment_sequence;		// multiple experiment register here
	bool debug = true;
	// experiment describe here
	// 
	queue<string> exp1;
	exp1.push("0"); // first is pre-process
	exp1.push("0");  // then binarization
	exp1.push("0"); // then after-process
	exp1.push("0"); //thining
	exp1.push(""); //anaylse
	experiment_sequence.push(exp1);	//
	// experiment describe end

	Mat img, pre_img, bi_img, aft_img, thin_img, tmp_img;


	for (int exp_id = 0; exp_id < experiment_sequence.size(); exp_id++) {	
		
		double start, stop, durationTime;
		
		

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
				imshow("origin", img);
				waitKey(1);
			}
			// image processing start


			int tmp_op;

			//pre-process
			string pre_process = exp_tmp.front();
			exp_tmp.pop();
			tmp_img = img;
			for (int op_id = 0; op_id < pre_process.length(); op_id++) {
				tmp_op = pre_process[op_id] - 48;   // ASCII code of '0' is 48
				preProcess(tmp_img, pre_img, tmp_op);
				tmp_img = pre_img;
			}

			//binarization img
			string bi_process = exp_tmp.front();
			exp_tmp.pop();
			tmp_img = pre_img;
			for (int op_id = 0; op_id < bi_process.length(); op_id++) {
				tmp_op = bi_process[op_id] - 48;   // ASCII code of '0' is 48
				binarize(tmp_img, bi_img, tmp_op);
				tmp_img = bi_img;
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

			//thining img
			string thin_process = exp_tmp.front();
			exp_tmp.pop();
			tmp_img = aft_img;
			for (int op_id = 0; op_id < thin_process.length(); op_id++) {
				tmp_op = thin_process[op_id] - 48;   // ASCII code of '0' is 48
				thinning(tmp_img, thin_img, tmp_op);
				tmp_img = thin_img;
			}

			//analyse img
			string analyse_process = exp_tmp.front();
			vector<pair<float, float>> param_list;
			exp_tmp.pop();
			for (int op_id = 0; op_id < analyse_process.length(); op_id++) {
				tmp_op = analyse_process[op_id] - 48;   // ASCII code of '0' is 48
				analysis(thin_img, param_list, tmp_op);
			}
		}
		experiment_sequence.pop();
		stop = time(NULL);
		durationTime = (double)difftime(stop, start);
		std::cout << "Experiment:" << exp_id << "\tTime Consuming:" << durationTime << " s" << endl;
	}
	waitKey(0);

	return 0;
}