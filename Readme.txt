Groundtruth_Error_Analysis_template

1. Disparity error

Calculates the root mean squared error (rmse) between the estimated disparity image(s) and corresponding groundtruth disparity image(s).

Input: Two .xml files provided at run time with the filenames and/or directory of the estimated and ground truth disparity images

Output: .csv file with the rmse value for each pair

Sample Input: Frame_File.xml in Input files folder

2. Camera Pose Error

Calculates the Relative pose error (averaging the translation component only) between the estimated and ground truth camera pose(s).

Input: Two .txt files provided at run time with the camera poses<A, B, C, theta, psi, phi> of the estimated and ground truth dataset.
where A, B, C are the position with respect to the camera center, and theta, psi, phi are the Euler angles representing the orientation

Output: Runtime display of the Relative pose error (averaging the translation component only)

Sample Input: camera_track.txt in Input files folder