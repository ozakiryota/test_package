#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/point_cloud2_iterator.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>

class VelodynePCToRings{
	private:
		/*node handle*/
		ros::NodeHandle _nh;
		ros::NodeHandle _nhPrivate;
		/*subscriber*/
		ros::Subscriber _sub_pc;
		/*publisher*/
		std::vector<ros::Publisher> _pub_pc;
		/*point cloud*/
		std::vector<pcl::PointCloud<pcl::PointXYZI>::Ptr> _rings;
		/*parameter*/
		int _num_ring;
		int _points_per_ring;

	public:
		VelodynePCToRings();
		void callbackPC(const sensor_msgs::PointCloud2ConstPtr& msg);
		void pcToRings(const sensor_msgs::PointCloud2& pc_msg);
		void print(void);
		void publication(std::string frame_id, ros::Time stamp);
};

VelodynePCToRings::VelodynePCToRings()
	: _nhPrivate("~")
{
	std::cout << "--- velodyne_pc_to_rings ---" << std::endl;
	/*parameter*/
	_nhPrivate.param("num_ring", _num_ring, 32);
	std::cout << "_num_ring = " << _num_ring << std::endl;
	_nhPrivate.param("points_per_ring", _points_per_ring, 1092);
	std::cout << "_points_per_ring = " << _points_per_ring << std::endl;
	/*sub*/
	_sub_pc = _nh.subscribe("/velodyne_points", 1, &VelodynePCToRings::callbackPC, this);
	/*pub*/
	_pub_pc.resize(_num_ring);
	for(size_t i=0 ; i<_pub_pc.size() ; ++i){
		_pub_pc[i] = _nh.advertise<sensor_msgs::PointCloud2>("/velodyne_points/ring" + std::to_string(i), 1);
	}
	/*initialize*/
	_rings.resize(_num_ring);
	for(size_t i=0 ; i<_rings.size() ; ++i){
		pcl::PointCloud<pcl::PointXYZI>::Ptr tmp (new pcl::PointCloud<pcl::PointXYZI>);
		_rings[i] = tmp;
	}
}

void VelodynePCToRings::callbackPC(const sensor_msgs::PointCloud2ConstPtr &msg)
{
	std::cout << "-----" << std::endl;
	for(size_t i=0 ; i<_rings.size() ; ++i){
		_rings[i]->points.clear();
	}
	pcToRings(*msg);
	print();
	publication(msg->header.frame_id, msg->header.stamp);
}

void VelodynePCToRings::pcToRings(const sensor_msgs::PointCloud2& pc_msg)
{
	sensor_msgs::PointCloud2ConstIterator<int> iter_ring(pc_msg,"ring");
	sensor_msgs::PointCloud2ConstIterator<float> iter_x(pc_msg,"x");
	sensor_msgs::PointCloud2ConstIterator<float> iter_y(pc_msg,"y");
	sensor_msgs::PointCloud2ConstIterator<float> iter_z(pc_msg,"z");
	sensor_msgs::PointCloud2ConstIterator<float> iter_intensity(pc_msg,"intensity");

	for( ; iter_ring!=iter_ring.end() ; ++iter_ring, ++iter_x, ++iter_y, ++iter_z, ++iter_intensity){
		pcl::PointXYZI tmp;
		tmp.x = *iter_x;
		tmp.y = *iter_y;
		tmp.z = *iter_z;
		tmp.intensity = *iter_intensity;
		_rings[*iter_ring]->points.push_back(tmp);
		/* std::cout << "Ring Number = " << *iter_ring << std::endl; */
	}
}

void VelodynePCToRings::print(void)
{
	double angle_resolution = 2*M_PI/(double)_points_per_ring;
	for(size_t i=0 ; i<_rings.size() ; ++i){
		std::cout << "ring: " << i << std::endl;
		for(size_t j=0 ; j<_rings[i]->points.size() ; ++j){
			double angle = atan2(_rings[i]->points[j].y, _rings[i]->points[j].x);
			_rings[i]->points[j].intensity = angle;
			/* std::cout << i << ": " << j << ": " << angle/M_PI*180.0 << " [deg]" << std::endl; */
			std::cout << "[" << j << "]" << angle/M_PI*180.0 << "(" << (int)((angle + M_PI)/angle_resolution) << ") ";
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
	for(size_t i=0 ; i<_rings.size() ; ++i)	std::cout << "_rings[i]->points.size() = " << _rings[i]->points.size() << std::endl;
}

void VelodynePCToRings::publication(std::string frame_id, ros::Time stamp)
{
	for(size_t i=0 ; i<_pub_pc.size() ; ++i){
		sensor_msgs::PointCloud2 pc_msg;
		pcl::toROSMsg(*_rings[i], pc_msg);
		pc_msg.header.frame_id = frame_id;
		pc_msg.header.stamp = stamp;
		_pub_pc[i].publish(pc_msg);
	}
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "velodyne_pc_to_rings");
	
	VelodynePCToRings velodyne_pc_to_rings;

	ros::spin();
}
