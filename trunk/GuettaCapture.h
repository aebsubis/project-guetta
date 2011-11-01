/* 
 * File:   GuettaViewer.h
 * Author: jose
 *
 * Created on 11 de octubre de 2011, 11:43
 */

#ifndef _GuettaCapture_H
#define	_GuettaCapture_H

#include "ui_GuettaCapture.h"
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <iostream>
#include "Viewer.h"
#include "GuettaCloud.h"
#include "GuettaFeatures.h"
#include "RGB.h"
#include <pcl/registration/transforms.h>
#include "pcl/common/transform.h"
#include "pcl/registration/icp.h"
#include "pcl/registration/registration.h"
#include "Ramsac.h"
#include "pcl/sample_consensus/ransac.h"
#include "pcl/sample_consensus/sac_model_registration.h"
#include "GuettaICP.h"
#include <boost/timer.hpp>

using namespace std;
using namespace pcl;
using namespace pcl::io;
using namespace boost;
using namespace cv;

class GuettaCapture : public QDialog {
    Q_OBJECT
        public:
            GuettaCapture();
            virtual ~GuettaCapture();
        public slots:
            void selectedKeyPoint(int idPoint, int idViewport);
            void connectOpenNIGrabber();
            void renameCapture();
            void capture();
        private:
            void render_thread();
            void cloud_cb_ (const PointCloud<PointXYZRGB>::ConstPtr&);
            void cloud2_cb_ (const boost::shared_ptr<openni_wrapper::Image>&);
            Ui::GuettaCapture widget;
            vector<Viewer*> viewers;
            bool guardarXYZ;
            bool guardarRGB;
            PointCloud<PointXYZRGB>::Ptr rt_cloud;
            GuettaTime timer;
            GuettaTime timer2;
            int fps;
            mutex mtx_;
};

#endif	/* _GUETTAVIEWER_H */

