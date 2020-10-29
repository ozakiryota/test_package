#include <iostream>
#include"cnpy.h"

int main(void)
{
	int size_h = 5;
	int size_w = 10;

	std::vector<int> mat;
	mat.resize(size_h*size_w);

	for(int i=0; i<size_h*size_w; ++i){
		mat[i] = i;
	}

	std::string save_path = "/home/amsl/ros_catkin_ws/src/test_package/save/test_cnpy.npy";
	cnpy::npy_save(save_path, &mat[0], {size_h, size_w}, "w");
	std::cout << "save_path = " << save_path << std::endl;
}

/*output*/
/*
 * >>> import numpy as np
 * >>> np.load("test_cnpy.npy")
 * array([[ 0,  1,  2,  3,  4,  5,  6,  7,  8,  9],
 *        [10, 11, 12, 13, 14, 15, 16, 17, 18, 19],
 *        [20, 21, 22, 23, 24, 25, 26, 27, 28, 29],
 *        [30, 31, 32, 33, 34, 35, 36, 37, 38, 39],
 *        [40, 41, 42, 43, 44, 45, 46, 47, 48, 49]], dtype=int32)
 */
