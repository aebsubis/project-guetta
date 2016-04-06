# project-guetta

## Description
FINAL THESIS project at [University of Alicante](http://www.ua.es/).

Simultaneous Location and Mapping (SLAM) using a low cost 3D camera (Kinect), Point Cloud Library (PCL), OpenCV, Robot Operating Sytem (ROS), and Tree-based netwORk Optimizer (TORO). It uses an optical flow to detect movement and implements a simple navigation algorithm.

Innovative system for automatic map building and [Simultaneous Localization and Mapping](https://en.wikipedia.org/wiki/Simultaneous_localization_and_mapping) (SLAM) using a Kinect, low cost 3D camera. The method uses [optical flow](https://en.wikipedia.org/wiki/Optical_flow) in order to determine if the robot has done a movement. If so, some visual features which do not accomplish several criteria are deleted, and then the [egomotion](https://en.wikipedia.org/wiki/Visual_odometry) is calculated. 

We use a [tree-based network optimizer](https://www.openslam.org/toro.html) (TORO) in order to rectify the map and solve the SLAM problem. The proposed method provides better efficiency that others. Additionaly, a study of different visual detectors and descriptors have been done in order to identify which of them are more suitable for the SLAM problem.

![Map rectification](http://www.pinkzero.com/dpfportfolio/works/images/finalthesis1.png)
![3D detectors](http://www.pinkzero.com/dpfportfolio/works/images/finalthesis2.png)

[Final documentation](http://www.pinkzero.com/dpfportfolio/memoria.pdf) *Spanish version only.

## Publications
* [A study of 2D features for 3D visual SLAM](http://rua.ua.es/dspace/bitstream/10045/24511/1/ISR%202012v7.pdf) 43rd International Symposium on Robotics (ISR). Taipei (Taiwan).
* [Using a RGB-D camera for 6DoF SLAM](http://rua.ua.es/dspace/bitstream/10045/45466/1/ios-book-article.pdf) Computer Science Research Institute. University of Alicante. Alicante.
