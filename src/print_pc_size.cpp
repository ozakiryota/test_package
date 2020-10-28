#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>

class PrintPcSize{
	private:
		/*node handle*/
		ros::NodeHandle _nh;
		/*subscribe*/
		ros::Subscriber _sub_pc;
		/*pc*/
		pcl::PointCloud<pcl::PointXYZ>::Ptr _pc {new pcl::PointCloud<pcl::PointXYZ>};

	public:
		PrintPcSize();
		void callbackPC(const sensor_msgs::PointCloud2ConstPtr& msg);
};

PrintPcSize::PrintPcSize()
{
	std::cout << "--- print_pc_size ---" << std::endl;
	/*subscriber*/
	_sub_pc = _nh.subscribe("/cloud", 1, &PrintPcSize::callbackPC, this);
}

void PrintPcSize::callbackPC(const sensor_msgs::PointCloud2ConstPtr &msg)
{
	pcl::fromROSMsg(*msg, *_pc);
	std::cout << "_pc->points.size() = " << _pc->points.size() << std::endl;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "print_pc_size");
	
	PrintPcSize print_pc_size;

	ros::spin();
}
