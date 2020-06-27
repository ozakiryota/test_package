#!/usr/bin/env python

import math
import os
import numpy as np

import cv2
from cv_bridge import CvBridge, CvBridgeError

from PIL import Image

current_dir= os.path.dirname(os.path.abspath(__file__))
print("current_dir = ", current_dir)
save_path = os.path.join(current_dir, "../save/save_numpy.npy")
print("save_path = ", save_path)

m1 = np.load(save_path)
print(m1)

