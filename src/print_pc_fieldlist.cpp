#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>

class PrintPcFieldlist{
	private:
		/*node handle*/
		ros::NodeHandle _nh;
		/*subscribe*/
		ros::Subscriber _sub_pc;

	public:
		PrintPcFieldlist();
		void callbackPC(const sensor_msgs::PointCloud2ConstPtr& msg);
};

PrintPcFieldlist::PrintPcFieldlist()
{
	std::cout << "--- print_pc_fieldlist ---" << std::endl;
	/*subscriber*/
	_sub_pc = _nh.subscribe("/cloud", 1, &PrintPcFieldlist::callbackPC, this);
}

void PrintPcFieldlist::callbackPC(const sensor_msgs::PointCloud2ConstPtr &msg)
{
	std::string fields = pcl::getFieldsList(*msg);
	std::cout << "fields = " << fields << std::endl;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "print_pc_fieldlist");
	
	PrintPcFieldlist print_pc_fieldlist;

	ros::spin();
}
