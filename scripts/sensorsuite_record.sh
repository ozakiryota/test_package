#!/bin/bash

rosbag record \
    -O "/home/amsl/ozaki/bagfiles/stick/`date "+%Y%m%d_%H%M%S"`" \
    /imu/data \
    /velodyne_packets \
    /realsense_f/color/camera_info \
    /realsense_f/color/image_raw/compressed \
    /realsense_r/color/camera_info \
    /realsense_r/color/image_raw/compressed \
    /realsense_l/color/camera_info \
    /realsense_l/color/image_raw/compressed \
    /realsense_b/color/camera_info \
    /realsense_b/color/image_raw/compressed
