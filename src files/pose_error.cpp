#include "error_metrics_funcs.h"

int main(int argc,char* argv[]){
	if(argc!=3){
		std::cout<< "Provide two filenames: One for estimated poses and another for ground truth poses \n";
		return 0;
	}
	std::string filename1 = argv[1];
	std::string filename2 = argv[2];

	std::cout<< "Enter an option: 0 or 1: "<<std::endl;
	int option;
	std::cin>> option;
	if(option == 0){
		pose_error test;
		test.rpe(filename1,filename2);
	}
	else{
		error_metrics test_2;
		test_2.mse_metrics(filename1, filename2);
	}
}