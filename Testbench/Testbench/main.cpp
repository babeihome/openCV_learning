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
	vector<vector<string>> experiment_sequence;		// multiple experiment register here
	bool debug = true;
	// experiment describe here
	// 
	vector<string> exp1;
	exp1.push_back("11"); // first is pre-process
	exp1.push_back("1");  // then binarization
	exp1.push_back(""); // then after-process
	exp1.push_back("1"); //thining
	exp1.push_back("2"); //anaylse
	experiment_sequence.push_back(exp1);	//
	// experiment describe end



	for (int exp_id = 0; exp_id < experiment_sequence.size(); exp_id++) {
		//run into one experiment
		for (int i = 0; i < files.size(); i++)
		{
			//anaylse one image
			Mat img = imread(files[i], -1);
			if (img.empty())
			{
				cout << "Error: Could not load image" << endl;
				return 0;
			}
			//debug part: show the image
			if (debug) {
				imshow("test", img);
				waitKey(1);
			}
			// image processing start

		}
	}
	waitKey(0);

	return 0;
}