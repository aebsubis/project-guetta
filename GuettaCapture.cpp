/*
 * File:   GuettaViewer.cpp
 * Author: jose
 *
 * Created on 11 de octubre de 2011, 11:43
 */
#include <boost/thread.hpp>

#include "GuettaCapture.h"

GuettaCapture::GuettaCapture() 
{
    /*
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
    
    //cout << viewers[0]->unselectables.size() << endl;
    viewers[0]->unselectables.insert(viewers[0]->unselectables.end(), new GuettaCloud());
    //cout << viewers[0]->unselectables.size() << endl;
    
    PointCloud<PointXYZRGB>::Ptr aux_rt_cloud (new PointCloud<PointXYZRGB>);
    rt_cloud = aux_rt_cloud;*/
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
     
     boost::thread thread(&GuettaCapture::render_thread, this);
//     boost::thread* thr = new boost::thread(boost::bind(&GuettaCapture::render, this));
    //interface->stop();
}

void GuettaCapture::render_thread() {
    while (true)
    {
        this_thread::sleep(posix_time::milliseconds(1000));
        mutex::scoped_lock lock (mtx_);
        cout << "Inicio render" << endl;
        this_thread::sleep(posix_time::milliseconds(1000));
        //viewers[0]->updateGL();
        cout << "Finalizo render" << endl;
    }
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
    /*
    mutex::scoped_lock lock (mtx_);
    cout << "Inicio captura" << endl;
    //delete viewers[0]->unselectables[0];
    cout << "a" << endl;
    //viewers[0]->unselectables.clear();
    copyPointCloud(*cloud, *rt_cloud);
    cout << "a" << endl;
    GuettaCloud* gt_cloud = new GuettaCloud(rt_cloud);
    cout << "a" << endl;
    //viewers[0]->unselectables.insert(viewers[0]->unselectables.end(), gt_cloud);
    viewers[0]->unselectables[0] = gt_cloud;
    cout << "a" << endl;
    if (guardarXYZ) {
       string RGBfilename = widget.lineEditCaptureName->text().toStdString() + ".pcd";
       pcl::io::savePCDFileASCII (RGBfilename, *cloud);
       guardarXYZ = false;
    }
    cout << "Finalizo capatura" << endl;
     */
    
    
    /*
    this_thread::sleep(posix_time::milliseconds(1));
    fps++;
    if(timer.elapsed() > 1) {
        widget.labelNoInputDeviceConnected->setText(QString::fromStdString(boost::lexical_cast<std::string>(fps)) + " fps");
        fps = 0;
        timer.restart();
    }
    */
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