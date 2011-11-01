/* 
 * File:   GuettaViewer.h
 * Author: jose
 *
 * Created on 11 de octubre de 2011, 11:43
 */

#ifndef _GuettaCapture_H
#define	_GuettaCapture_H

#include "ui_GuettaCapture.h"
#include <iostream>

#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/timer.hpp>

#include "pcl/console/parse.h"
#include "pcl/common/time.h"
#include "pcl/common/common_headers.h"

#include "pcl/features/normal_3d.h"
#include "pcl/features/range_image_border_extractor.h"

#include "pcl/filters/passthrough.h"

#include "pcl/io/openni_grabber.h"
#include "pcl/io/pcd_io.h"

#include "pcl/impl/point_types.hpp"

#include "pcl/keypoints/narf_keypoint.h"

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

#include "pcl/registration/icp.h"
#include "pcl/range_image/range_image.h"

#include "pcl/visualization/range_image_visualizer.h"
#include <pcl/registration/icp_nl.h>
#include <opencv/cv.h>
#include "opencv2/highgui/highgui.hpp"
#include "Viewer.h"

using namespace std;
using namespace pcl;
using namespace pcl::visualization;
using namespace pcl::io;
using namespace boost;
using namespace cv;

class GuettaCapture : public QWidget {
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
            void cloud_cb_ (const PointCloud<PointXYZRGB>::ConstPtr&);
            void cloud2_cb_ (const boost::shared_ptr<openni_wrapper::Image>&);
            Ui::GuettaCapture widget;
            vector<Viewer*> viewers;
            bool guardarXYZ;
            bool guardarRGB;
            PointCloud<PointXYZRGB>::Ptr rt_cloud;
            boost::timer timer;
            int fps;
};

#endif	/* _GUETTAVIEWER_H */

