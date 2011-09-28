#include <iostream>

#include <pcl/visualization/cloud_viewer.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/openni_grabber.h>
#include <pcl/common/time.h>
#include <boost/thread/thread.hpp>
#include "pcl/common/common_headers.h"
#include "pcl/common/common_headers.h"
#include "pcl/features/normal_3d.h"
#include "pcl/io/pcd_io.h"
#include "pcl/visualization/pcl_visualizer.h"
#include <pcl/console/parse.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <boost/thread/thread.hpp>
#include "pcl/range_image/range_image.h"
#include "pcl/io/pcd_io.h"
#include "pcl/visualization/range_image_visualizer.h"
#include "pcl/visualization/pcl_visualizer.h"
#include "pcl/features/range_image_border_extractor.h"
#include "pcl/keypoints/narf_keypoint.h"
#include <pcl/console/parse.h>
#include <pcl/impl/point_types.hpp>
#include "Matriz.h"
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/registration/icp.h>


using namespace std;
using namespace pcl;
using namespace io;
using namespace boost;


class RGB
{
    public:
        
        RGB(int r, int g, int b)
        {
            this->r = r;
            this->g = g;
            this->b = b;
        }
        
        RGB(const RGB &rgb)
        {
            this->r = rgb.r;
            this->g = rgb.g;
            this->b = rgb.b;
        }
   
        int r;
        int g;
        int b;
};

class Viewer
{
    public:

    vector<int> viewports;
    map<string, PointCloud<PointXYZ>::Ptr> clouds;
    
    Viewer () 
    {
        viewer = new pcl::visualization::PCLVisualizer("Viewer"); 
        viewer->setBackgroundColor(0.5,0,0);
        viewports.resize(4);
        viewer->initCameraParameters ();
    }

    pcl::PointCloud<pcl::PointXYZ>::Ptr loadPCD(string name)
    {
        PointCloud<PointXYZ>::Ptr cloud (new PointCloud<PointXYZ>);
        if (loadPCDFile<PointXYZ> (name, *cloud) == -1)
        {
                PCL_ERROR ("Couldn't read file test_pcd.pcd \n");
                exit(1);
        }         
        return cloud;
    }
    
    void createViewPort0()
    {
        int id;
        viewer->createViewPort (0.0, 0.5, 0.5, 1.0, id);
        
        viewports[0] = id;
        cout << "ID: " << id << "," << viewports[0] << endl;
        viewer->setBackgroundColor (0.1, 0.1, 0.1, id);
        viewer->addText ("v0", 10, 10, "v0", id);
    }
    
    void createViewPort1()
    {
        int id;
        viewer->createViewPort (0.5, 0.5, 1.0, 1.0, id);
        viewports[1] = id;
        cout << "ID: " << id << "," << viewports[1] << endl;
        viewer->setBackgroundColor (0.15, 0.15, 0.15, id);
        viewer->addText ("v1", 10, 10, "v1", id);
    }
    
    void createViewPort2()
    {
        int id;
        viewer->createViewPort (0.0, 0.0, 0.5, 0.5, id);
        viewports[2] = id;
        cout << "ID: " << id << "," << viewports[2] << endl;
        viewer->setBackgroundColor (0.2, 0.2, 0.2, id);
        viewer->addText ("v2", 10, 10, "v2", id);
    }
    
    void createViewPort3()
    {
        int id;
        viewer->createViewPort (0.5, 0.0, 1.0, 0.5, id);
        viewports[3] = id;
        cout << "ID: " << id << "," << viewports[3] << endl;
        viewer->setBackgroundColor (0.25, 0.25, 0.25, id);
        viewer->addText ("v3", 10, 10, "v3", id);
    }
    
    void createViewPorts()
    {
        createViewPort0();
        createViewPort1();
        createViewPort2();
        createViewPort3();
    }
    
    void loadClouds()
    {
        string name = "cloud1";
        clouds[name] = loadPCD("test_pcd1.pcd");
        //viewer->addPointCloud(clouds[name],name,viewports[0]);
        
        name = "cloud2";
        clouds[name] = loadPCD("test_pcd2.pcd");
        viewer->addPointCloud(clouds[name],name,viewports[1]);  

    }
    
    RangeImage createRangeImage(PointCloud<PointXYZ>::Ptr cloud)
    {
        // We now want to create a range image from the above point cloud, with a 1deg angular resolution
        float angularResolution = (float) (  0.5f * (M_PI/180.0f));  //   1.0 degree in radians
        float maxAngleWidth     = (float) (360.0f * (M_PI/180.0f));  // 360.0 degree in radians
        float maxAngleHeight    = (float) (180.0f * (M_PI/180.0f));  // 180.0 degree in radians
        Eigen::Affine3f sensorPose = (Eigen::Affine3f)Eigen::Translation3f(0.0f, 0.0f, 0.0f);
        
        sensorPose = Eigen::Affine3f (Eigen::Translation3f (cloud->sensor_origin_[0],
                                                           cloud->sensor_origin_[1],
                                                           cloud->sensor_origin_[2])) *
                    Eigen::Affine3f (cloud->sensor_orientation_);
        
        RangeImage::CoordinateFrame coordinate_frame = RangeImage::CAMERA_FRAME;
        float noiseLevel=0.00;
        float minRange = 0.0f;
        int borderSize = 1;

        RangeImage rangeImage;
        rangeImage.createFromPointCloud(*cloud, angularResolution, maxAngleWidth, maxAngleHeight,
                                      sensorPose, coordinate_frame, noiseLevel, minRange, borderSize);        
        return rangeImage;
    }
    
    void setViewerPose (pcl::visualization::PCLVisualizer& viewer, const Eigen::Affine3f& viewer_pose)
    {
        Eigen::Vector3f pos_vector = viewer_pose * Eigen::Vector3f (0, 0, 0);
        Eigen::Vector3f look_at_vector = pcl::getRotationOnly (viewer_pose) * Eigen::Vector3f (0, 0, 1) + pos_vector;
        Eigen::Vector3f up_vector = pcl::getRotationOnly (viewer_pose) * Eigen::Vector3f (0, -1, 0);
        viewer.camera_.pos[0] = pos_vector[0];
        viewer.camera_.pos[1] = pos_vector[1];
        viewer.camera_.pos[2] = pos_vector[2];
        viewer.camera_.focal[0] = look_at_vector[0];
        viewer.camera_.focal[1] = look_at_vector[1];
        viewer.camera_.focal[2] = look_at_vector[2];
        viewer.camera_.view[0] = up_vector[0];
        viewer.camera_.view[1] = up_vector[1];
        viewer.camera_.view[2] = up_vector[2];
        viewer.updateCamera ();
    }

    PointCloud<int> getNARFkeypoints(RangeImage rangeImage)
    {
        float support_size = 0.2f;
        RangeImageBorderExtractor range_image_border_extractor;
        NarfKeypoint narf_keypoint_detector (&range_image_border_extractor);
        narf_keypoint_detector.setRangeImage (&rangeImage);
        narf_keypoint_detector.getParameters ().support_size = support_size;
        //narf_keypoint_detector.getParameters ().add_points_on_straight_edges = true;
        //narf_keypoint_detector.getParameters ().distance_for_additional_points = 0.5;

        PointCloud<int> keypoint_indices;
        narf_keypoint_detector.compute (keypoint_indices);
        cout << "Found "<<keypoint_indices.points.size ()<<" key points.\n";
        return keypoint_indices;
    }
    
    PointCloud<PointXYZ>::Ptr getPointCloud(RangeImage rangeImage, PointCloud<int> keyPoints_indices)
    {
      PointCloud<PointXYZ>::Ptr keypoints_ptr (new PointCloud<PointXYZ>);
      PointCloud<PointXYZ>& keyPoints = *keypoints_ptr;
      keyPoints.points.resize (keyPoints_indices.points.size ());
      for (size_t i=0; i<keyPoints_indices.points.size (); ++i)
        keyPoints.points[i].getVector3fMap () = rangeImage.points[keyPoints_indices.points[i]].getVector3fMap ();
      return keypoints_ptr;
    }
    
    void showKeyPoints(string id, RangeImage rangeImage, PointCloud<int> keyPoints_indices, int viewport, RGB color)
    {
      PointCloud<PointXYZ>::Ptr keypoints_ptr (new PointCloud<PointXYZ>);
      PointCloud<PointXYZ>& keyPoints = *keypoints_ptr;
      keyPoints.points.resize (keyPoints_indices.points.size ());
      for (size_t i=0; i<keyPoints_indices.points.size (); ++i)
        keyPoints.points[i].getVector3fMap () = rangeImage.points[keyPoints_indices.points[i]].getVector3fMap ();

   //   keypoints_ptr->height = rangeImage.height;
    //  keypoints_ptr->width = rangeImage.width;
      pcl::visualization::PointCloudColorHandlerCustom<PointXYZ> keypoints_color_handler (keypoints_ptr, color.r, color.g, color.b);
      clouds[id] = keypoints_ptr;
      viewer->addPointCloud(keypoints_ptr, keypoints_color_handler, id, viewport);

      viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 5, id);        
        
    }
    
    Matriz<double> icp(PointCloud<PointXYZ>::Ptr cloudIn, PointCloud<PointXYZ>::Ptr cloudOut)
    {
        IterativeClosestPoint<PointXYZ, PointXYZ> icp;
        icp.setInputCloud(cloudIn);
        icp.setInputTarget(cloudOut);
        
        
        PointCloud<PointXYZ>::Ptr final (new PointCloud<PointXYZ>);
        icp.setMaximumIterations(1000);

        icp.align(*final);
        
        viewer->addPointCloud(final,"final",viewports[0]);  
        
        //cout << "2" << endl;
        //std::cout << "has converged:" << endl << icp.hasConverged() << endl << " score: " << endl << icp.getFitnessScore() << std::endl;
        //pcl::PointCloud<PointXYZ>::Ptr point_cloud_ptr (final);
        /*
        //std::cout << icp.getFinalTransformation() << std::endl;
        viewer->addPointCloud(point_cloud_ptr,"icp",viewports[3]);  
                */
        cout << "has converged:" << endl << icp.hasConverged() << endl << " score: " << endl << icp.getFitnessScore() << std::endl;
        
        Matriz<double> matriz(4,4);
        Eigen::Matrix4f* aux = new Eigen::Matrix4f(icp.getFinalTransformation());

        for(int i = 0; i < 4; i++)
        {
          for(int j = 0; j < 4; j++)
            matriz[i][j] = aux->coeff(i,j);
        }     

        
        /*
        for(int i = 0; i < 4; i++)
        {
          for(int j = 0; j < 4; j++)
            cout << matriz[i][j] << " ";
          cout << endl;
        }  */        
         
        return matriz;
    }
    
    PointCloud<PointXYZ>::Ptr copyPointCloud(PointCloud<PointXYZ>::Ptr cloud)
    {
        
        PointCloud<pcl::PointXYZ>::Ptr copy (new PointCloud<PointXYZ>);
        copy->width = cloud->width;
        copy->height = cloud->height;
        copy->points.resize (cloud->points.size());
        for(int i=0; i<cloud->points.size(); i++)
        {
            copy->points[i].x = cloud->points[i].x;
            copy->points[i].y = cloud->points[i].y;
            copy->points[i].z = cloud->points[i].z;
        }      
        return copy;
    }

     void run ()
     {
        createViewPorts();
        
        loadClouds();
        
        
        
  
        // Create range image cloud1
        RangeImage rangeImage = createRangeImage(clouds["cloud1"]);
        
        setViewerPose (*viewer, rangeImage.getTransformationToWorldSystem ());
        
        PointCloud<int> keyPointsIndices = getNARFkeypoints(rangeImage);
        showKeyPoints("keyPoints1",rangeImage,keyPointsIndices,viewports[2],RGB(255,0,0));
           
        
        
        // Create range image cloud2
        rangeImage = createRangeImage(clouds["cloud2"]);
        keyPointsIndices = getNARFkeypoints(rangeImage);
        showKeyPoints("keyPoints2",rangeImage,keyPointsIndices,viewports[2],RGB(0,255,0));
        
        Matriz<double> matriz = icp(clouds["keyPoints1"],clouds["keyPoints2"]);
        
         // Show keypoints cloud2
        pcl::visualization::PointCloudColorHandlerCustom<PointXYZ> keypoints_color_handler (clouds["cloud2"], 0, 255, 0);
        viewer->addPointCloud(clouds["cloud2"], keypoints_color_handler, "keyPoints2_icp",viewports[3]); 
        //viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 5, "keyPoints2_icp");        
        
        // Apply transform cloud1
        PointCloud<PointXYZ>::Ptr keyPoints1 = copyPointCloud(clouds["cloud1"]);
        
        for(int i = 0; i < keyPoints1->points.size(); i++)
        {
            Matriz<double> aux(4,1);
            aux[0][0] = keyPoints1->points[i].x;
            aux[1][0] = keyPoints1->points[i].y;
            aux[2][0] = keyPoints1->points[i].z;
            aux[3][0] = 1;
            Matriz<double> resultado(1,4);
            resultado = matriz * aux; 
            //cout << resultado << endl;
            //cout << resultado[0][0] << "," << resultado[1][0] << "," << resultado[2][0] << endl;
            // Save result
            keyPoints1->points[i].x = resultado[0][0];
            keyPoints1->points[i].y = resultado[1][0];
            keyPoints1->points[i].z = resultado[2][0];   
            //cout <<  keyPoints1->points[i] << endl;
            //cout <<  keyPoints1->points[i] << endl;
        }

        // Show result transform
        pcl::visualization::PointCloudColorHandlerCustom<PointXYZ> keypoints_color_handler2 (keyPoints1, 255, 0, 0);
        viewer->addPointCloud(keyPoints1, keypoints_color_handler2, "result_icp",viewports[3]); 
        viewer->addPointCloud(keyPoints1,"result_icp",viewports[3]); 
              
        
        /*
        // Show keypoints cloud2
        pcl::visualization::PointCloudColorHandlerCustom<PointXYZ> keypoints_color_handler (clouds["keyPoints2"], 0, 255, 0);
        viewer->addPointCloud(clouds["keyPoints2"], keypoints_color_handler, "keyPoints2_icp",viewports[3]); 
        viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 5, "keyPoints2_icp");  

        // Apply transform cloud1
        PointCloud<PointXYZ>::Ptr keyPoints1 = copyPointCloud(clouds["keyPoints1"]);
        cout <<"before: " << endl;
        for(int i = 0; i < keyPoints1->points.size(); i++)    
            cout <<  keyPoints1->points[i] << endl;
        
        for(int i = 0; i < keyPoints1->points.size(); i++)
        {
            Matriz<double> aux(4,1);
            aux[0][0] = keyPoints1->points[i].x;
            aux[1][0] = keyPoints1->points[i].y;
            aux[2][0] = keyPoints1->points[i].z;
            aux[3][0] = 1;
            Matriz<double> resultado(1,4);
            resultado = matriz * aux; 
            cout << resultado << endl;
            cout << resultado[0][0] << "," << resultado[1][0] << "," << resultado[2][0] << endl;
            // Save result
            keyPoints1->points[i].x = resultado[0][0];
            keyPoints1->points[i].y = resultado[1][0];
            keyPoints1->points[i].z = resultado[2][0];   
            cout <<  keyPoints1->points[i] << endl;
            //cout <<  keyPoints1->points[i] << endl;
        }
        cout <<"result: " << endl;
        for(int i = 0; i < keyPoints1->points.size(); i++)    
            cout <<  keyPoints1->points[i] << endl;
        // Show result transform
        viewer->addPointCloud(keyPoints1,"result_icp",viewports[3]); 
        
        */
        
        //pcl::visualization::RangeImageVisualizer range_image_widget ("Range image");
        //range_image_widget.setRangeImage (rangeImage);
        
        //viewer->addPointCloud(clouds[name],name,viewports[1]); 
        
        
        

        
        
        
        //viewer->addCoordinateSystem(1.0);
        //viewer->initCameraParameters();
        
        /*
        //viewer->addPointCloud<pcl::PointXYZRGB> (cloud, rgb, "sample cloud1", v1);
        viewer->addPointCloud(cloud,"sample cloud1",v1);
        

        viewer->addPointCloud(cloud,"sample cloud2",v2);
        
        viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "sample cloud1");
        viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "sample cloud2");
        viewer->addCoordinateSystem (1.0);
         */
       
       while (!viewer->wasStopped())
       {
            pcl::visualization::ImageWidgetWX::spinOnce ();  // process GUI events
                viewer->spinOnce (100);
                boost::this_thread::sleep (boost::posix_time::microseconds (100000));
       }
     }
     

     pcl::visualization::PCLVisualizer* viewer;
 };

int main(int argc, char** argv) {

    Viewer viewer;
    
    viewer.run();
    
    return 0;
}

