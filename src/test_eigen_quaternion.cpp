#include <ros/ros.h>
#include <tf/tf.h>
#include <Eigen/Core>
#include <Eigen/Geometry>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "test_eigen_quaternion");
	
	/*random*/
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<> urd(-M_PI, M_PI);
	/*set RPY*/
	double r_in =  urd(mt);
	double p_in =  urd(mt);
	double y_in =  urd(mt);
	/*print*/
	std::cout << "original: " << std::endl
		<< "r = " << r_in << ", "
		<< "p = " << p_in << ", "
		<< "y = " << y_in << std::endl;

	/*tf*/
	/*convertion*/
	tf::Quaternion q_tf = tf::createQuaternionFromRPY(r_in, p_in, y_in);
	std::cout << "q_tf: " << std::endl
		<< "x = " << q_tf.x() << ", "
		<< "y = " << q_tf.y() << ", "
		<< "z = " << q_tf.z() << ", "
		<< "w = " << q_tf.w() << std::endl;
	/*re-convertion*/
	double r_out, p_out, y_out;
	tf::Matrix3x3(q_tf).getRPY(r_out, p_out, y_out);
	std::cout << "tf out: " << std::endl
		<< "r = " << r_out << ", "
		<< "p = " << p_out << ", "
		<< "y = " << y_out << std::endl;

	/*Eigen*/
	/*convertion*/
	Eigen::Quaternionf q_eigen =
		Eigen::AngleAxisf(y_in, Eigen::Vector3f::UnitZ())
		* Eigen::AngleAxisf(p_in, Eigen::Vector3f::UnitY())
		* Eigen::AngleAxisf(r_in, Eigen::Vector3f::UnitX());
	std::cout << "q_eigen: " << std::endl
		<< "x = " << q_eigen.x() << ", "
		<< "y = " << q_eigen.y() << ", "
		<< "z = " << q_eigen.z() << ", "
		<< "w = " << q_eigen.w() << std::endl;
	/*re-convertion*/
	Eigen::Vector3f rpy_out = q_eigen.toRotationMatrix().eulerAngles(2, 1, 0);
	std::cout << "Eigen out: " << std::endl
		<< "r = " << rpy_out[2] << ", "
		<< "p = " << rpy_out[1] << ", "
		<< "y = " << rpy_out[0] << std::endl;
}
