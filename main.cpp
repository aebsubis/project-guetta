/*
 * File:   main.cpp
 * Author: jose
 *
 * Created on 9 de octubre de 2011, 16:17
 */

#include <QtGui/QApplication>
#include <iostream>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>

using namespace pcl;
using namespace pcl::io;

#include "newForm.h"
#include "Guetta.h"
using namespace std;
int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    
    QApplication app(argc, argv);
setlocale(LC_NUMERIC,"C");

// setlocale(LC_ALL, "POSIX");
    
   // newForm form;
   // form.show();
Guetta guetta;
guetta.show();
/*
    // create and show your widgets here
        cv::Mat img = cv::imread("cloud0.jpg");
        if(img.empty())
        {
            cout << "Error: No se puede abrir la imagen" << endl;
            exit(-1);
        }  
 std::vector<cv::KeyPoint> feature_locations_2d_;
         namedWindow("image2", CV_WINDOW_AUTOSIZE);
        imshow("image2", img);   
   SiftGPUFeatureDetector* siftGPUFeatureDetector = SiftGPUFeatureDetector::GetInstance();
        float* descriptors = siftGPUFeatureDetector->detect(img,feature_locations_2d_);      
        
        waitKey();           
        */
    return app.exec();
}

