#pragma once
#ifndef ERROR_METRICS_FUNCS_H
#define ERROR_METRICS_FUNCS_H

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <Eigen/Dense>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/eigen.hpp>

class pose_error{
	public:
		void rpe(std::string filename1, std::string filename2);

};

class error_metrics{
private:	
	
public:
		int rows,cols,MSE,scaled_value; //scaled_value is a constant error added to the ground truth disparity to check if the RMSE returns the same scaled_value as it should.
		cv::Mat true_depth, estimated_depth; 
		Eigen::MatrixXf squared_error, error_depth;
		Eigen::Matrix<float,Eigen::Dynamic,Eigen::Dynamic> est, tru;
		std::ofstream error_file;	
		std::ostringstream num2str;
		//error_file.open( "squared_error.csv" );
		std::string filename, filename_2;
		std::string imgDir, imgDir_2;
		cv::FileStorage imgName, imgName_2;
		int mse_metrics(std::string fname1, std::string fname2);

};

#endif