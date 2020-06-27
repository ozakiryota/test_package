#include <iostream>
#include <opencv2/opencv.hpp>

int main(void)
{
	std::string yaml_path = "/home/amsl/ros_catkin_ws/src/velodyne_pointcloud_to_depthimage/saved/CV_64FC1.yml";
	std::cout << "yaml_path = "  << yaml_path << std::endl;
	cv::FileStorage fs(yaml_path, cv::FileStorage::READ);
	if(!fs.isOpened()){
		std::cout << yaml_path << "cannot be opened" << std::endl;
		exit(1);
	}
	std::string mat_name = "mat1";
	cv::Mat mat;
	fs[mat_name.c_str()] >> mat;
	std::cout << "mat: " << mat << std::endl;
	std::cout << "mat: " << mat.size().width << " x " << mat.size().height << std::endl;
}
