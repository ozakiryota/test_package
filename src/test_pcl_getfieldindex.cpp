#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

template<class CloutPtr>
void printFields(CloutPtr cloud)
{
	sensor_msgs::PointCloud2 ros_cloud;
	pcl::toROSMsg(*cloud, ros_cloud);

	std::cout << "pcl::getFieldsList(ros_cloud) = " << pcl::getFieldsList(ros_cloud) << std::endl;
}

int main(int argc, char** argv)
{
	ros::init(argc, argv, "test_pcl_getfieldindex");
	
	pcl::PointCloud<pcl::PointXYZ>::Ptr point_xyz (new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PointCloud<pcl::PointXYZI>::Ptr point_xyzi (new pcl::PointCloud<pcl::PointXYZI>);
	pcl::PointCloud<pcl::PointXYZRGBA>::Ptr point_xyzrgba (new pcl::PointCloud<pcl::PointXYZRGBA>);
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr point_xyzrgb (new pcl::PointCloud<pcl::PointXYZRGB>);
	pcl::PointCloud<pcl::PointXY>::Ptr point_xy (new pcl::PointCloud<pcl::PointXY>);
	pcl::PointCloud<pcl::InterestPoint>::Ptr interest_point (new pcl::PointCloud<pcl::InterestPoint>);
	pcl::PointCloud<pcl::PointNormal>::Ptr point_normal (new pcl::PointCloud<pcl::PointNormal>);
	pcl::PointCloud<pcl::PointXYZINormal>::Ptr point_xyzinormal (new pcl::PointCloud<pcl::PointXYZINormal>);

	printFields(point_xyz);
	printFields(point_xyzi);
	printFields(point_xyzrgba);
	printFields(point_xyzrgb);
	printFields(point_xy);
	printFields(interest_point);
	printFields(point_normal);
	printFields(point_xyzinormal);
}
