#include <iostream>

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
#include "pcl/io/openni_camera/openni_driver.h"

#include "pcl/impl/point_types.hpp"

#include "pcl/keypoints/narf_keypoint.h"

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

#include "pcl/registration/icp.h"
#include "pcl/range_image/range_image.h"

#include "pcl/visualization/cloud_viewer.h"
#include "pcl/visualization/pcl_visualizer.h"
#include "pcl/visualization/range_image_visualizer.h"

#include "Matriz.h"
#include "RGB.h"

using namespace std;
using namespace pcl;
using namespace pcl::visualization;
using namespace pcl::io;
using namespace boost;

class ProjectGuetta
{
  public:

    ProjectGuetta (const string& device_id = "") : viewer ("Project Guetta") , device_id_(device_id)
    {
         // Inicializamos los flags.
         new_rt_cloud_ = false;
         new_processed_cloud_ = false;
         new_captured_cloud_ = false;
         captured_first_cloud_ = false;
         guardar = false;
         
         // Inicializamos las nubes.
         PointCloud<PointXYZRGB>::Ptr c_aux1 (new PointCloud<PointXYZRGB>);
         rt_cloud_ = c_aux1;
         PointCloud<PointXYZRGB>::Ptr c_aux2 (new PointCloud<PointXYZRGB>);
         processed_rgb_cloud_ = c_aux2;
         PointCloud<PointXYZ>::Ptr c_aux3 (new PointCloud<PointXYZ>);
         processed_xyz_cloud_ = c_aux3;
         PointCloud<PointXYZRGB>::Ptr c_aux4 (new PointCloud<PointXYZRGB>);
         captured_rgb_cloud_ = c_aux4;
         PointCloud<PointXYZ>::Ptr c_aux5 (new PointCloud<PointXYZ>);
         captured_xyz_cloud_ = c_aux5;
    }
   
    RangeImage
    createRangeImage(PointCloud<PointXYZ>::Ptr cloud)
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
    
    PointCloud<int>
    getNARFkeypoints(RangeImage rangeImage)
    {
        float support_size = 0.2f;
        RangeImageBorderExtractor range_image_border_extractor;
        NarfKeypoint narf_keypoint_detector (&range_image_border_extractor);
        narf_keypoint_detector.setRangeImage (&rangeImage);
        narf_keypoint_detector.getParameters ().support_size = support_size;
        PointCloud<int> keypoint_indices;
        narf_keypoint_detector.compute (keypoint_indices);
        cout << "Encontrados "<<keypoint_indices.points.size ()<<" puntos clave." << endl;
        return keypoint_indices;
    }
    
    PointCloud<PointXYZ>::Ptr
    getPointCloud(RangeImage rangeImage, PointCloud<int> keyPoints_indices)
    {
      PointCloud<PointXYZ>::Ptr keypoints_ptr (new PointCloud<PointXYZ>);
      PointCloud<PointXYZ>& keyPoints = *keypoints_ptr;
      keyPoints.points.resize (keyPoints_indices.points.size ());
      for (size_t i=0; i<keyPoints_indices.points.size (); ++i)
        keyPoints.points[i].getVector3fMap () = rangeImage.points[keyPoints_indices.points[i]].getVector3fMap ();
      return keypoints_ptr;
    }
    
    bool
    icp(PointCloud<PointXYZ>::Ptr cloudIn, PointCloud<PointXYZ>::Ptr cloudOut, Matriz<double>& matriz)
    {
        bool converge = false;
        IterativeClosestPoint<PointXYZ, PointXYZ> icp;
        icp.setInputCloud(cloudIn);
        icp.setInputTarget(cloudOut);
        
        PointCloud<PointXYZ>::Ptr final (new PointCloud<PointXYZ>);
        icp.setMaximumIterations(1000);

        icp.align(*final);
        
        
        cout << "has converged:" << endl << icp.hasConverged() << endl << " score: " << endl << icp.getFitnessScore() << endl;

        Eigen::Matrix4f* aux = new Eigen::Matrix4f(icp.getFinalTransformation());

        for(int i = 0; i < 4; i++)
        {
          for(int j = 0; j < 4; j++)
            matriz[i][j] = aux->coeff(i,j);
        }
        
        return icp.hasConverged();
    }
    
    void
    keyboardEventOccurred (const visualization::KeyboardEvent &event, void *)
    {
        if (event.getKeySym () == "s" && event.keyDown ())
        {
            guardar = true;  
        }
    } 
    
    void 
    cloud_cb (const PointCloud<PointXYZRGB>::ConstPtr& cloud)
    {
        mutex::scoped_lock lock (mtx_);

        copyPointCloud(*cloud, *rt_cloud_);

        new_rt_cloud_ = true;

        if (guardar == true)
        {
            cout << "Guardando frame." << endl;
            guardar = false;
            
            // Almacenamos la imagen capturada.
            copyPointCloud(*rt_cloud_, *captured_rgb_cloud_);
            copyPointCloud(*rt_cloud_, *captured_xyz_cloud_);
            
            // Creamos la imagen de rango.
            RangeImage rangeImage1 = createRangeImage(captured_xyz_cloud_);
           
            // Obtenemos los puntos clave.
            PointCloud<int> keyPointsIndices1 = getNARFkeypoints(rangeImage1);
            
            // Obtenemos la nube de puntos clave.
            captured_key_cloud_ = getPointCloud(rangeImage1, keyPointsIndices1);
            
            // Se ha capturado una nueva nube.
            new_captured_cloud_ = true;
            
            if (captured_first_cloud_ == true)
            {     
                Matriz<double> matriz(4,4);
                cout << *captured_rgb_cloud_ << endl;
                cout << *processed_rgb_cloud_ << endl;
                
                if (icp(captured_key_cloud_, processed_key_cloud_, matriz))
                {
                    for(int i = 0; i < captured_rgb_cloud_->points.size(); i++)
                    {
                        Matriz<double> aux(4,1);
                        aux[0][0] = captured_rgb_cloud_->points[i].x;
                        aux[1][0] = captured_rgb_cloud_->points[i].y;
                        aux[2][0] = captured_rgb_cloud_->points[i].z;
                        aux[3][0] = 1;
                        Matriz<double> resultado(1,4);
                        resultado = matriz * aux;

                        PointXYZRGB point;
                        point.x = resultado[0][0];
                        point.y = resultado[1][0];
                        point.z = resultado[2][0];
                        point.r = captured_rgb_cloud_->points[i].r;
                        point.g = captured_rgb_cloud_->points[i].g;
                        point.b = captured_rgb_cloud_->points[i].b;
                        processed_rgb_cloud_->insert(processed_rgb_cloud_->end(),point);
                    }
                }
            }
            else
            {
                // Almacenamos la imagen capturada en la imagen procesada.
                copyPointCloud(*captured_rgb_cloud_, *processed_rgb_cloud_);
                
                
                // Se ha capturado la primera nube.
                captured_first_cloud_ = true;
            }
            
            // Copiamos la imagen RGB a XYZ.
            copyPointCloud(*processed_rgb_cloud_, *processed_xyz_cloud_);
                
            // Creamos la imagen de rango.
            RangeImage rangeImage2 = createRangeImage(processed_xyz_cloud_);

            // Obtenemos los puntos clave.
            PointCloud<int> keyPointsIndices2 = getNARFkeypoints(rangeImage2);

            // Obtenemos la nube de puntos clave.
            processed_key_cloud_ = getPointCloud(rangeImage2, keyPointsIndices2);
                
            // Hay una nueva imagen procesada.
            new_processed_cloud_ = true;
        }
    }

    void
    viz_init_cb (PCLVisualizer& viz)
    {
        viz.initCameraParameters ();
        viz.registerKeyboardCallback(&ProjectGuetta::keyboardEventOccurred,*this, 0);
        
        int id;
        viewports.resize(4);
        
        viz.createViewPort (0.0, 0.5, 0.5, 1.0, id);
        viewports[0] = id;
        viz.setBackgroundColor (0.1, 0.1, 0.1, id);
        viz.addText ("Tiempo real", 10, 10, "v0", id);
        
        viz.createViewPort (0.5, 0.5, 1.0, 1.0, id);
        viewports[1] = id;
        viz.setBackgroundColor (0.15, 0.15, 0.15, id);
        viz.addText ("Imagen capturada", 10, 10, "v1", id); 
        
        viz.createViewPort (0.0, 0.0, 0.5, 0.5, id);
        viewports[2] = id;
        viz.setBackgroundColor (0.2, 0.2, 0.2, id);
        viz.addText ("v2", 10, 10, "v2", id);
        
        viz.createViewPort (0.5, 0.0, 1.0, 0.5, id);
        viewports[3] = id;
        viz.setBackgroundColor (0.25, 0.25, 0.25, id);
        viz.addText ("v3", 10, 10, "v3", id);
    }
    
    void
    viz_cb (PCLVisualizer& viz)
    {
        if (!viewer.wasStopped()) {

            // No se ha realizado ninguna acción.
            bool action = false;
            
            // Comprobamos si existe una nueva nube de tiempo real.
            if (new_rt_cloud_ == true)
            {
                // Se ha realizado una acción.
                action = true;
                
                mutex::scoped_lock lock (mtx_);

                // Mostramos la nube de tiempo real.
                if (!viz.updatePointCloud (rt_cloud_, "rt_cloud_"))
                {
                    viz.addPointCloud (rt_cloud_, "rt_cloud_", viewports[0]);
                    viz.resetCameraViewpoint("rt_cloud_");
                }

                // No hay nueva nube de tiempo real.
                new_rt_cloud_ = false;
            }
            
            // Comprobamos si existe una nueva nube capturada.
            if (new_captured_cloud_ == true)
            {
                // Se ha realizado una acción.
                action = true;
                
                mutex::scoped_lock lock (mtx_);
                
                // Mostramos las nubes de puntos.
                PointCloudColorHandlerCustom<PointXYZ> keypoints_color_handler1 (processed_key_cloud_, 255, 0, 0);
                if(!viz.updatePointCloud (processed_key_cloud_, keypoints_color_handler1, "processed_key_cloud_vp2"))
                {
                    viz.addPointCloud(processed_key_cloud_, keypoints_color_handler1, "processed_key_cloud_vp2", viewports[2]);
                    viz.setPointCloudRenderingProperties (PCL_VISUALIZER_POINT_SIZE, 5, "processed_key_cloud_vp2");
                }
                
                PointCloudColorHandlerCustom<PointXYZ> keypoints_color_handler2 (captured_key_cloud_, 0, 255, 0);
                if(!viz.updatePointCloud (captured_key_cloud_, keypoints_color_handler2, "captured_key_cloud_vp2"))
                {
                    viz.addPointCloud(captured_key_cloud_, keypoints_color_handler2, "captured_key_cloud_vp2", viewports[2]);
                    viz.setPointCloudRenderingProperties (PCL_VISUALIZER_POINT_SIZE, 5, "captured_key_cloud_vp2");
                }
                
                // Mostramos la nube capturada.
                if (!viz.updatePointCloud (captured_rgb_cloud_, "captured_rgb_cloud_"))
                {
                    viz.addPointCloud (captured_rgb_cloud_, "captured_rgb_cloud_", viewports[1]);
                }
                
                // Mostramos los puntos clave de la nube capturada.
                PointCloudColorHandlerCustom<PointXYZ> keypoints_color_handler3 (captured_key_cloud_, 255, 0, 0);
                if(!viz.updatePointCloud (captured_key_cloud_, keypoints_color_handler3, "captured_key_cloud_vp1"))
                {
                    viz.addPointCloud(captured_key_cloud_, keypoints_color_handler2, "captured_key_cloud_vp1", viewports[1]);
                    viz.setPointCloudRenderingProperties (PCL_VISUALIZER_POINT_SIZE, 5, "captured_key_cloud_vp1");
                }
                
                // No hay nueva nube captuada.
                new_captured_cloud_ = false;
            }
            
            // Comprobamos si existe una nueva nube procesada.
            if (new_processed_cloud_ == true)
            {
                // Se ha realizado una acción.
                action = true;
                
                // Mostramos la nube procesada.
                if (!viz.updatePointCloud (processed_rgb_cloud_, "processed_cloud_"))
                {
                    viz.addPointCloud (processed_rgb_cloud_, "processed_cloud_", viewports[3]);
                }
                
                // No hay nueva nube procesada.
                new_processed_cloud_ = false;
            }
            
            // Comprobamos si se ha realizado alguna acción.
            if (action == false)
            {
                this_thread::sleep(posix_time::milliseconds(1)); 
            }
        }
    }

    void
    run ()
    {
        Grabber* interface = new OpenNIGrabber (device_id_);

        function<void (const PointCloud<PointXYZRGB>::ConstPtr&)> f = bind (&ProjectGuetta::cloud_cb, this, _1);
        interface->registerCallback (f);

        viewer.runOnVisualizationThreadOnce(bind(&ProjectGuetta::viz_init_cb, this, _1));
        viewer.runOnVisualizationThread(bind(&ProjectGuetta::viz_cb, this, _1), "viz_cb");

        interface->start ();

        while (!viewer.wasStopped ())
        {
             this_thread::sleep(posix_time::milliseconds(1));
        }

        interface->stop ();
    }

    CloudViewer viewer;
    vector<int> viewports;

    string device_id_;
    mutex mtx_;
    
    
    // Flags
    bool new_rt_cloud_;
    bool new_processed_cloud_;
    bool new_captured_cloud_;
    bool captured_first_cloud_;
    bool guardar;
    
    // Nube de entrada en tiempo real.
    PointCloud<PointXYZRGB>::Ptr rt_cloud_;
    
    // Nube procesada.
    PointCloud<PointXYZRGB>::Ptr processed_rgb_cloud_;
    PointCloud<PointXYZ>::Ptr processed_xyz_cloud_;
    PointCloud<PointXYZ>::Ptr processed_key_cloud_;
    
    // Nube capturada.
    PointCloud<PointXYZRGB>::Ptr captured_rgb_cloud_;
    PointCloud<PointXYZ>::Ptr captured_xyz_cloud_;
    PointCloud<PointXYZ>::Ptr captured_key_cloud_;
};

int
main (int argc, char ** argv)
{
    ProjectGuetta v ("");
    v.run ();
    return (0);
}
