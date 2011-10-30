#ifndef GUETTAICP_H
#define	GUETTAICP_H


#include <opencv/cv.h>
#include "opencv2/highgui/highgui.hpp"
#include <SiftGPU/SiftGPU.h>
#include <GL/gl.h>

#include <iostream>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <sys/time.h>
#include "GuettaCloud.h"
#include "GuettaKeyPoint.h"
#include <pcl/registration/transforms.h>
#include "pcl/common/transform.h"
#include "pcl/registration/icp.h"
#include "pcl/registration/registration.h"
#include "GuettaTime.h"
#include "pcl/sample_consensus/ransac.h"
#include "pcl/sample_consensus/sac_model_registration.h"
using namespace std;
using namespace pcl;

class GuettaICP 
{
        public:
            ~GuettaICP();
            static GuettaICP* GetInstance();
            // Especificamos la nube que el algoritmo transformará 
            void setInputCloud(GuettaCloud* inputCloud);
            // Especificamos la nube que el algoritmo usará como objetivo 
            void setInputTarget(GuettaCloud* inputTarget);
            GuettaCloud* compute(Eigen::Matrix4f& transformation_matrix, int maxKeyPointsAlineamiento, float maxDistance);
            void getNearestDescriptors(int maxKeyPointsAlineamiento, float maxDistance, GuettaCloud* cloud1, GuettaCloud* cloud2);
        private:
            GuettaICP();
            static GuettaICP* instance;
            GuettaCloud* inputCloud;
            GuettaCloud* inputTarget;
};

#endif

