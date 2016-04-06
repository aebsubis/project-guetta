# project-guetta

## Description
FINAL THESIS project at [University of Alicante](http://www.ua.es/).

Innovative system for automatic map building and [Simultaneous Localization and Mapping](https://en.wikipedia.org/wiki/Simultaneous_localization_and_mapping) (SLAM) using a Kinect, low cost 3D camera. The method uses [optical flow](https://en.wikipedia.org/wiki/Optical_flow) to detect movement. If so, some visual features are processed. This process applies acceptance criteria to discriminate the visual features and use only the ones that provide useful information. At the next step the [egomotion](https://en.wikipedia.org/wiki/Visual_odometry) is calculated based on the visual features obtained. Finally it moves using a simple navigation algorithm that avoids obstacles.

We use [Point Cloud Library](http://pointclouds.org/) (PCL), [OpenCV](http://opencv.org/),  [Robot Operating Sytem](http://www.ros.org/) (ROS) and a [Tree-based netwORk Optimizer](https://www.openslam.org/toro.html) (TORO) in order to rectify the map and solve the SLAM problem. The proposed method provides better efficiency that others. Additionaly, a study of different visual detectors and descriptors have been done in order to identify which of them are more suitable for the SLAM problem.

![Map rectification](http://www.pinkzero.com/dpfportfolio/works/images/finalthesis1.png)
![3D detectors](http://www.pinkzero.com/dpfportfolio/works/images/finalthesis2.png)

[Final documentation](http://www.pinkzero.com/dpfportfolio/memoria.pdf) *Spanish version only.

## Publications
* [A study of 2D features for 3D visual SLAM](http://rua.ua.es/dspace/bitstream/10045/24511/1/ISR%202012v7.pdf) 43rd International Symposium on Robotics (ISR). Taipei (Taiwan).
* [Using a RGB-D camera for 6DoF SLAM](http://rua.ua.es/dspace/bitstream/10045/45466/1/ios-book-article.pdf) Computer Science Research Institute. University of Alicante. Alicante.
