#!/usr/bin/env python

import math
import os
import numpy as np

import cv2
from cv_bridge import CvBridge, CvBridgeError

from PIL import Image

current_dir= os.path.dirname(os.path.abspath(__file__))
print("current_dir = ", current_dir)
save_path = os.path.join(current_dir, "../save/save_numpy")
print("save_path = ", save_path)

bridge = CvBridge()

m1 = np.array([[1.1, 2.2, 3.3], [4.4, 5.5, 6.6], [7.7, 8.8, 9.9]])
print(m1)
msg1 = bridge.cv2_to_imgmsg(m1)
print(msg1)
m2 = bridge.imgmsg_to_cv2(msg1)
print(m2)

np.save(save_path, m2)
