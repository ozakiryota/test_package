#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>

class PrintMsgHz{
	private:
		/*node handle*/
		ros::NodeHandle _nh;
		/*subscribe*/
		ros::Subscriber _sub_pc;
		/*time*/
		ros::Time _last_stamp;
		/*flag*/
		bool _got_first_msg = false;

	public:
		PrintMsgHz();
		void callbackPC(const sensor_msgs::PointCloud2ConstPtr& msg);
};

PrintMsgHz::PrintMsgHz()
{
	std::cout << "--- print_msg_hz ---" << std::endl;
	/*subscriber*/
	_sub_pc = _nh.subscribe("/cloud", 1, &PrintMsgHz::callbackPC, this);
}

void PrintMsgHz::callbackPC(const sensor_msgs::PointCloud2ConstPtr &msg)
{
	if(!_got_first_msg){
		_got_first_msg = true;
	}
	else{
		double duration = (msg->header.stamp - _last_stamp).toSec();
		double frequency = 1.0/duration;
		std::cout << "duration[s]: " << duration << std::endl;
		std::cout << "frequency[hz]: " << frequency << std::endl;
	}
	_last_stamp = msg->header.stamp;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "print_msg_hz");
	
	PrintMsgHz print_msg_hz;

	ros::spin();
}
