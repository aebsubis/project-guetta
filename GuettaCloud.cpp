#include <pcl-1.1/pcl/io/openni_grabber.h>
#include <pcl-1.1/pcl/io/io.h>

#include "GuettaCloud.h"

GuettaCloud::GuettaCloud()
{
}

GuettaCloud::GuettaCloud(vector<shared_ptr<GuettaKeyPoint> > data)
{
    this->data = data;
}

GuettaCloud::GuettaCloud(const GuettaCloud& guettaCloud)
{
    *this = guettaCloud;
}

GuettaCloud::~GuettaCloud()
{
}

GuettaCloud::GuettaCloud(PointCloud<PointXYZRGB>::Ptr cloud)
{
    data.resize(cloud->points.size());
    for(int i = 0; i < cloud->points.size(); i++)
    {
        PointXYZRGB point = cloud->points[i];
        shared_array<float> descriptor;
        data[i] = shared_ptr<GuettaKeyPoint>(new GuettaKeyPoint(point.x,point.y,point.z,point.r,point.g,point.b, descriptor));
    }
    pointCloud = cloud;
}

PointCloud<PointXYZRGB>::Ptr GuettaCloud::getPointCloud()
{
     PointCloud<PointXYZRGB>::Ptr pointCloud (new PointCloud<PointXYZRGB>);
    for(int i = 0; i < data.size(); i++)
    {
        shared_ptr<GuettaKeyPoint> guettaPoint = data[i];
        PointXYZRGB point;
        point.x = guettaPoint->x;
        point.y = guettaPoint->y;
        point.z = guettaPoint->z;
        point.r = guettaPoint->r;
        point.g = guettaPoint->g;
        point.b = guettaPoint->b;      
        pointCloud->points.push_back (point);
    }     
     return pointCloud;
}

GuettaCloud& GuettaCloud::operator=(const GuettaCloud& guettaCloud)
{
    if(this != &guettaCloud)
    { 
        this->data.resize(guettaCloud.data.size());
        for(int i = 0; i < data.size(); i++)
        {
            this->data[i] = guettaCloud.data[i]; 
        }
        pointCloud = guettaCloud.pointCloud;
    }
    return *this;
}
