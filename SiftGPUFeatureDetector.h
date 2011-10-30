

#ifndef SIFTGPUFEATUREDETECTOR_H
#define	SIFTGPUFEATUREDETECTOR_H

//#include <opencv2/opencv2/opencv.hpp>
#include <opencv/cv.h>
#include "opencv2/highgui/highgui.hpp"
#include <SiftGPU/SiftGPU.h>
#include <GL/gl.h>
#include <iostream>
#include <sys/time.h>
using namespace std;

class SiftGPUFeatureDetector 
{
        public:
            ~SiftGPUFeatureDetector();
            static SiftGPUFeatureDetector* GetInstance();
            float* detect( const cv::Mat& image, cv::vector<cv::KeyPoint>& keypoints) const;
            void CVMatToSiftGPU(const cv::Mat& image, unsigned char* siftImage) const;
            
        private:
            SiftGPUFeatureDetector();
            
            static const int imageWidth = 640;
            static const int imageHeight = 480;            
            static SiftGPUFeatureDetector* instance;
            SiftGPU* siftgpu;
            unsigned char* data; // Guardamos la imagen como si fuera una textura
};

#endif

