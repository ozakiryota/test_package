#include <ros/ros.h>

int main(int argc, char** argv)
{
	ros::init(argc, argv, "mesureing_computation_time");
	ros::NodeHandle nh;

	ros::Time t_start = ros::Time::now();

	/*Start*/
	for(int i=0; i<10000; ++i){
		std::cout << "i = " << i << std::endl;
		std::cout << "time[s] = " << (ros::Time::now() - t_start).toSec() << std::endl;
	}
	/*End*/

	std::cout << "Computation is done" << std::endl;
	std::cout << "Computation time[s] = " << (ros::Time::now() - t_start).toSec() << std::endl;

	return 0;
}
