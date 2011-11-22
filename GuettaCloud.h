/* 
 * File:   GuettaCloud.h
 * Author: jose
 *
 * Created on 12 de octubre de 2011, 17:57
 */

#ifndef GUETTACLOUD_H
#define	GUETTACLOUD_H

#include <iostream>
using namespace std;
#include "GuettaKeyPoint.h"
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
using namespace pcl;

class GuettaCloud
{
    public:
        GuettaCloud();
        GuettaCloud(vector<shared_ptr<GuettaKeyPoint> > data);
        GuettaCloud(PointCloud<PointXYZRGB>::Ptr cloud);
        GuettaCloud(const GuettaCloud& guettaCloud);
        ~GuettaCloud();
        GuettaCloud& operator=(const GuettaCloud& guettaCloud);
        PointCloud<PointXYZRGB>::Ptr getPointCloud();
        vector<shared_ptr<GuettaKeyPoint> > data;
        PointCloud<PointXYZRGB>::Ptr pointCloud;
};


#endif	/* GUETTACLOUD_H */

