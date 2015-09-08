
#include "error_metrics_funcs.h"



int error_metrics::mse_metrics(std::string fname1, std::string fname2){
	scaled_value = 6;
	error_file.open( "squared_error.csv" );
	filename = fname1.c_str();
	filename_2 = fname2.c_str();

	
	imgName.open(filename, cv::FileStorage::READ);
	cv::FileNode n = imgName[ "Name" ];                         
	if (n.type() != cv::FileNode::SEQ){
		std::cerr << "strings is not a sequence! FAIL" << std::endl;
		return 1;
	}

	imgName_2.open(filename_2, cv::FileStorage::READ);
	cv::FileNode n_2 = imgName_2[ "Name" ];                         
	if (n_2.type() != cv::FileNode::SEQ){
		std::cerr << "strings is not a sequence! FAIL" << std::endl;
		return 1;
	}

	cv::FileNodeIterator iteration = n.begin(), iteration_end = n.end(); 
	error_file <<"Frame Number,MSE Value, scaled value" <<std::endl;
	
	cv::FileNodeIterator iteration_2 = n_2.begin(), iteration_end_2 = n_2.end(); 
	error_file <<"Frame Number,MSE Value, scaled value" <<std::endl;

	for (; iteration != iteration_end, iteration_2 != iteration_end_2; ++iteration, ++iteration_2){		
	imgDir = std::string("left_estimated/"+(std::string)*iteration);
	std::cout <<imgDir <<std::endl;
			
	imgDir_2 = std::string("left_groundtruth/"+(std::string)*iteration_2);
	std::cout <<imgDir_2 <<std::endl;

	estimated_depth = cv::imread( imgDir, CV_LOAD_IMAGE_GRAYSCALE );
	if(estimated_depth.empty()){std::cout <<"Not empty image" <<std::endl;} //Check if image is empty

	true_depth = cv::imread( imgDir_2, CV_LOAD_IMAGE_GRAYSCALE );
	if(true_depth.empty()){std::cout <<"Not empty image" <<std::endl;} //Check if image is empty
	
	
	rows = true_depth.rows;
	cols = true_depth.cols;
	
			
	cv::cv2eigen( estimated_depth, est );
	cv::cv2eigen( true_depth,tru );
	
	Eigen::MatrixXf mody_error(rows,cols);
	mody_error = Eigen::MatrixXf::Constant(rows,cols,scaled_value);
	est.block(0,0,rows,cols) = est.block(0,0,rows,cols)+mody_error;
	
	cv::eigen2cv(est,estimated_depth);
	estimated_depth.convertTo(estimated_depth,CV_8UC1);

	
	
	
	cv::namedWindow( "True_depth", cv::WINDOW_AUTOSIZE );
	cv::imshow( "True_depth", true_depth );
	cv::namedWindow( "Estimated_depth", cv::WINDOW_AUTOSIZE );
	cv::imshow( "Estimated_depth", estimated_depth );
	

	error_depth = tru-est; 
	std::cout << "sum of error: " << error_depth.sum()<< std::endl;
	squared_error = error_depth.cwiseProduct(error_depth);
	MSE = squared_error.sum()/(rows*cols);
	std::cout <<"Root Mean Squared Error: " <<pow(MSE,0.5) <<std::endl;	
	error_file <<(std::string)*iteration <<"," <<MSE <<","<< scaled_value<< std::endl;
	
	cv::waitKey(100);
	}
	
	error_file.close();

	cv::waitKey(0);

	return 0;
}
