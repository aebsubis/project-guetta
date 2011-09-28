#include <iostream>
using namespace std;

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


 class SimpleOpenNIViewer
 {
   public:
       
    bool guardar;
       
    void keyboardEventOccurred (const pcl::visualization::KeyboardEvent &event, void *)
    { 
        //boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer = *static_cast<boost::shared_ptr<pcl::visualization::PCLVisualizer> *> (viewer_void);
        if (event.getKeySym () == "s" && event.keyDown ())
        {
            guardar = true;  
        }
    } 
    
         
     SimpleOpenNIViewer () 
     {
        viewer = new pcl::visualization::CloudViewer("3D Viewer"); 
        //guardar = false;
        interface = new pcl::OpenNIGrabber();
        
        boost::function<void (const pcl::PointCloud<pcl::PointXYZ>::ConstPtr&)> f =
        boost::bind (&SimpleOpenNIViewer::cloud_cb_, this, _1);

        interface->registerCallback (f);

        viewer->registerKeyboardCallback(&SimpleOpenNIViewer::keyboardEventOccurred,*this, 0); 
     }

     void cloud_cb_ (const pcl::PointCloud<pcl::PointXYZ>::ConstPtr &cloud)
     {
       if (!viewer->wasStopped())
         viewer->showCloud (cloud);
       
       
       if(guardar)
       {
           
            pcl::io::savePCDFileASCII ("test_pcd.pcd", *cloud.get());
            
            //std::cerr << "Saved " << cloud->points.size () << " data points to test_pcd.pcd." << std::endl;

            //for (size_t i = 0; i < cloud->points.size (); ++i)
            //std::cerr << "    " << cloud->points[i].x << " " << cloud->points[i].y << " " << cloud->points[i].z << std::endl;           
           
            guardar = false;
       }
        
     }

     void run ()
     {
       interface->start ();
       
       //viewer.runOnVisualizationThreadOnce(cloud_cb_);
       
       while (!viewer->wasStopped())
       {

         sleep (1);
       }

       interface->stop ();
     }
     

     pcl::Grabber* interface;
     pcl::visualization::CloudViewer* viewer;
 };

 int main ()
 {
   SimpleOpenNIViewer v;
   v.run ();

   return 0;
 }

 
/*
#include <pcl/visualization/cloud_viewer.h>
#include <iostream>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
    
int user_data;
    
void 
viewerOneOff (pcl::visualization::PCLVisualizer& viewer)
{
    viewer.setBackgroundColor (1.0, 0.5, 1.0);
    pcl::PointXYZ o;
    o.x = 1.0;
    o.y = 0;
    o.z = 0;
    viewer.addSphere (o, 0.25, "sphere", 0);
    std::cout << "i only run once" << std::endl;
    
}
    
void 
viewerPsycho (pcl::visualization::PCLVisualizer& viewer)
{
    static unsigned count = 0;
    std::stringstream ss;
    ss << "Once per viewer loop: " << count++;
    viewer.removeShape ("text", 0);
    viewer.addText (ss.str(), 200, 300, "text", 0);
    
    //FIXME: possible race condition here:
    user_data++;
}
    
int 
main ()
{
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZRGB>);
    pcl::io::loadPCDFile ("my_point_cloud.pcd", *cloud);
    
    pcl::visualization::CloudViewer viewer("Cloud Viewer");
    
    //blocks until the cloud is actually rendered
    viewer.showCloud(cloud);
    
    //use the following functions to get access to the underlying more advanced/powerful
    //PCLVisualizer
    
    //This will only get called once
    viewer.runOnVisualizationThreadOnce (viewerOneOff);
    
    //This will get called once per visualization iteration
    viewer.runOnVisualizationThread (viewerPsycho);
    while (!viewer.wasStopped ())
    {
    //you can also do cool processing here
    //FIXME: Note that this is running in a separate thread from viewerPsycho
    //and you should guard against race conditions yourself...
    user_data++;
    }
    return 0;
}*/