
#include "error_metrics_funcs.h"



void pose_error::rpe(std::string filename1, std::string filename2){
		std::cout<< filename1<< std::endl;
		std::ifstream in(filename1, std::ifstream::in);
		if(!in) {
			std::cout << "Cannot open camera_track.txt file.\n";
		}
		std::string line, line1;
		int number_of_lines = 0, i = 0, j = 0;
		while (std::getline(in, line1)){
			++number_of_lines;
		}
		in.clear();
		in.seekg (0, std::ios::beg);
		//line = "\0";
		std::cout<<"Line: "<< line1.c_str()<< std::endl;
		double **a;
		a = new double*[number_of_lines];
		for(int iter = 0; iter < number_of_lines; ++iter)
			a[iter] = new double[6];
		Eigen::MatrixXf estimated(4,4), ground_truth(4,4), error(4,4), trans_error(number_of_lines,3);
	

	
	
		while(std::getline(in,line))
		{
			std::stringstream   linestream(line);
			std::string         value;
			j = 0;
			while(getline(linestream,value,','))
			{			
				a[i][j] = std::stod (value,0);
				//std::cout << a[i][j] << ", ";
				//std::cout<< j <<",";
				j++;
			}
			//std::cout<<"\t"<<i<<std::enl;
			std::cout<<std::endl;
			i++;
		}
		in.close();

		// Complete Operations
		double theta, psi, phi;
		for(int iter = 0; iter<number_of_lines; iter++){
			theta = a[iter][3]; psi = a[iter][4]; phi = a[iter][5];
			estimated.row(0)<<cos(theta*(M_PI/180))*cos(psi*(M_PI/180)),sin(phi*(M_PI/180))*sin(theta*(M_PI/180))*cos(psi*(M_PI/180))-cos(phi*(M_PI/180))*sin(psi*(M_PI/180)),cos(phi*(M_PI/180))*sin(theta*(M_PI/180))*cos(psi*(M_PI/180))+sin(phi*(M_PI/180))*sin(psi*(M_PI/180)),a[iter][0];
			estimated.row(1)<<cos(theta*(M_PI/180))*sin(psi*(M_PI/180)),sin(phi*(M_PI/180))*sin(theta*(M_PI/180))*sin(psi*(M_PI/180))+cos(phi*(M_PI/180))*cos(psi*(M_PI/180)),cos(phi*(M_PI/180))*sin(theta*(M_PI/180))*sin(psi*(M_PI/180))-sin(phi*(M_PI/180))*cos(psi*(M_PI/180)),a[iter][1];
			estimated.row(2)<<-sin(theta*(M_PI/180)),sin(phi*(M_PI/180))*cos(theta*(M_PI/180)),cos(phi*(M_PI/180))*cos(theta*(M_PI/180)),a[iter][2];
			estimated.row(3)<<0,0,0,1;

			ground_truth.row(0)<<cos(theta*(M_PI/180))*cos(psi*(M_PI/180)),sin(phi*(M_PI/180))*sin(theta*(M_PI/180))*cos(psi*(M_PI/180))-cos(phi*(M_PI/180))*sin(psi*(M_PI/180)),cos(phi*(M_PI/180))*sin(theta*(M_PI/180))*cos(psi*(M_PI/180))+sin(phi*(M_PI/180))*sin(psi*(M_PI/180)),a[iter][0];
			ground_truth.row(1)<<cos(theta*(M_PI/180))*sin(psi*(M_PI/180)),sin(phi*(M_PI/180))*sin(theta*(M_PI/180))*sin(psi*(M_PI/180))+cos(phi*(M_PI/180))*cos(psi*(M_PI/180)),cos(phi*(M_PI/180))*sin(theta*(M_PI/180))*sin(psi*(M_PI/180))-sin(phi*(M_PI/180))*cos(psi*(M_PI/180)),a[iter][1];
			ground_truth.row(2)<<-sin(theta*(M_PI/180)),sin(phi*(M_PI/180))*cos(theta*(M_PI/180)),cos(phi*(M_PI/180))*cos(theta*(M_PI/180)),a[iter][2];
			ground_truth.row(3)<<0,0,0,1;

			error<< estimated.inverse()*ground_truth;
			trans_error.row(iter) << error(0,3)/error(3,3),error(1,3)/error(3,3),error(2,3)/error(3,3);
	
			//std::cout << "Error: \n"<< error<< std::endl;
		}
		std::cout<< "The Relative Pose Error calculated from all the pose pairs is: \n"<<((trans_error.cwiseProduct(trans_error)).colwise().sum()/50).cwiseSqrt()<<std::endl;

	}

