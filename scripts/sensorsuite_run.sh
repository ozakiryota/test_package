#!/bin/bash

##### realsense #####
gnome-terminal -e "bash -c '/home/amsl/ozaki/docker_ws/realsense_docker/run_cameras.sh'"
sleep 10s
##### xsens #####
gnome-terminal -e "bash -c '/home/amsl/ozaki/docker_ws/docker_xsens_driver/oq100aa100wr100.sh'"
##### velodyne #####
gnome-terminal -e "bash -c '/home/amsl/ozaki/docker_ws/docker_velodyne/vlp32c.sh'"
##### topic check #####
# gnome-terminal -e "bash -c 'rostopic list'"
gnome-terminal -e "bash -c 'rosrun tf static_transform_publisher 0 0 0 0 0 0 /velodyne /imu 1'"
gnome-terminal -e "bash -c 'rostopic echo /imu/data'"
gnome-terminal -e "bash -c 'rviz -d /home/amsl/ozaki/rviz_config/run_stick.rviz'"
