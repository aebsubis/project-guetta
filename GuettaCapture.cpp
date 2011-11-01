/*
 * File:   GuettaViewer.cpp
 * Author: jose
 *
 * Created on 11 de octubre de 2011, 11:43
 */

#include "GuettaCapture.h"

#include <boost/thread.hpp>
#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

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

//#include "pcl/visualization/cloud_viewer.h"
//#include "pcl/visualization/pcl_visualizer.h"
#include "pcl/visualization/range_image_visualizer.h"
#include <pcl/registration/icp_nl.h>
#include <opencv/cv.h>
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace pcl;
using namespace pcl::visualization;
using namespace pcl::io;
using namespace boost;
using namespace cv;

GuettaCapture::GuettaCapture() {
    widget.setupUi(this);
    
    connect(widget.lineEditSceneName, SIGNAL(editingFinished()), this, SLOT(renameCapture()));
    connect(widget.spinBoxCaptureNumber, SIGNAL(valueChanged(int)), this, SLOT(renameCapture()));
    connect(widget.pushButtonCapture, SIGNAL(clicked()), this, SLOT(capture()));
    connect(widget.pushButtonConnectInputDevice, SIGNAL(clicked()), this, SLOT(connectOpenNIGrabber()));
    //connect(widget.comboBox1,SIGNAL(currentIndexChanged(QString)),this,SLOT(changeCloud1(QString)));
    
    guardarXYZ = false;
    guardarRGB = false;
    
    // Creamos los visualizadores
    viewers.resize(2);
    for(int i = 0; i < 2; i++)
        viewers[i] = new Viewer(this,i);
    
    widget.realTimeViewer->addWidget(viewers[0],0,0);
    widget.capturedViewer->addWidget(viewers[1],0,0);
    
    cout << viewers[0]->unselectables.size() << endl;
    viewers[0]->unselectables.insert(viewers[0]->unselectables.end(), new GuettaCloud());
    cout << viewers[0]->unselectables.size() << endl;
    
    PointCloud<PointXYZRGB>::Ptr aux_rt_cloud (new PointCloud<PointXYZRGB>);
    rt_cloud = aux_rt_cloud;
}

GuettaCapture::~GuettaCapture() {
}

void GuettaCapture::connectOpenNIGrabber(){
   
     Grabber* interface = new OpenNIGrabber();
     
     widget.labelNoInputDeviceConnected->setEnabled(false);
     function<void (const PointCloud<PointXYZRGB>::ConstPtr&)> f = bind (&GuettaCapture::cloud_cb_, this, _1);
     function<void (const boost::shared_ptr<openni_wrapper::Image>&)> f2 = bind (&GuettaCapture::cloud2_cb_, this, _1);

     interface->registerCallback(f);
     interface->registerCallback(f2);

     interface->start();
   
    //while (true)
    //{
    //    sleep (1);
    //}

    //interface->stop();
}

void GuettaCapture::renameCapture() {
    QString text = widget.lineEditSceneName->text();
    text += "/capture";
    text += QString::fromStdString(boost::lexical_cast<std::string>(widget.spinBoxCaptureNumber->value()));
    
    widget.lineEditCaptureName->setText(text);
}

void GuettaCapture::capture() {
    
    if (widget.checkBoxAutoincrementNumber->isChecked()) {
        widget.spinBoxCaptureNumber->setValue(widget.spinBoxCaptureNumber->value()+1);
    }
    guardarXYZ = true;  
    guardarRGB = true;  
}

void GuettaCapture::cloud_cb_ (const PointCloud<PointXYZRGB>::ConstPtr &cloud)
{
    this_thread::sleep(posix_time::milliseconds(1));
    fps++;
    if(timer.elapsed() > 1) {
        widget.labelNoInputDeviceConnected->setText(QString::fromStdString(boost::lexical_cast<std::string>(fps)) + " fps");
        fps = 0;
        timer.restart();
    }
    cout << "a" << endl;
    delete viewers[0]->unselectables[0];
    cout << "b" << endl;
    copyPointCloud(*cloud, *rt_cloud);
    cout << "c" << endl;
    GuettaCloud* gt_cloud = new GuettaCloud(rt_cloud);
    cout << "d" << endl;
    viewers[0]->unselectables[0] = gt_cloud;
    cout << "e" << endl;
    //viewers[0]->updateGL();
    
    if (guardarXYZ) {
       string RGBfilename = widget.lineEditCaptureName->text().toStdString() + ".pcd";
       pcl::io::savePCDFileASCII (RGBfilename, *cloud);
       guardarXYZ = false;
    }
}

void GuettaCapture::cloud2_cb_ (const boost::shared_ptr<openni_wrapper::Image>& data)
{
    if (guardarRGB)
    {
        cv::Mat frameRGB=cv::Mat(data->getHeight(),data->getWidth(),CV_8UC3);

        data->fillRGB(frameRGB.cols,frameRGB.rows,frameRGB.data,frameRGB.step);
        cv::Mat frameBGR;
        cv::cvtColor(frameRGB,frameBGR,CV_RGB2BGR);  

        string RGBfilename = widget.lineEditCaptureName->text().toStdString() + ".jpg";

        cv::imwrite(RGBfilename,frameBGR);

        guardarRGB = false;
    }
}

void GuettaCapture::selectedKeyPoint(int idPoint, int idViewport)
{
}