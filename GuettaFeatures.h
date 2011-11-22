/* 
 * File:   GuettaFeatures.h
 * Author: jose
 *
 * Created on 10 de octubre de 2011, 21:42
 */

#ifndef GUETTAFEATURES_H
#define	GUETTAFEATURES_H

#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include "pcl/features/range_image_border_extractor.h"
#include "pcl/keypoints/narf_keypoint.h"
#include <pcl/features/narf_descriptor.h>
#include <pcl/features/narf.h>
#include "GuettaKeyPoint.h"
#include "GuettaCloud.h"
#include "RGB.h"
#include "SiftGPUFeatureDetector.h"
#include "pcl/io/openni_grabber.h"
#include "pcl/io/pcd_io.h"
#include "GuettaTime.h"
using namespace pcl;
using namespace cv;
using namespace pcl::io;
class GuettaFeatures
{
    public:
        ~GuettaFeatures();
        static GuettaFeatures* GetInstance();
        static GuettaCloud* getNARFkeypoints(PointCloud<PointXYZRGB>::Ptr pointCloud, RGB color);
        shared_ptr<GuettaCloud> getSIFTkeypoints(PointCloud<PointXYZRGB>::Ptr cloud, string imagen, RGB color);
        GuettaCloud* getSURFkeypoints(PointCloud<PointXYZRGB>::Ptr cloud, string imagen, RGB color);
        static RangeImage createRangeImage(PointCloud<PointXYZRGB>::Ptr cloud);
        cv::Mat cargarImagen(string nombre);

    private:
        GuettaFeatures();        
        static GuettaFeatures* instance;       

};

#endif	/* GUETTAFEATURES_H */

