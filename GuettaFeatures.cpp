#include <opencv2/features2d/features2d.hpp>

#include "GuettaFeatures.h"

GuettaFeatures* GuettaFeatures::instance = NULL;

GuettaFeatures::~GuettaFeatures()
{
    instance = NULL;
}

GuettaFeatures* GuettaFeatures::GetInstance()
{
    if (instance == NULL) 
        instance = new GuettaFeatures();
    return instance;
}


GuettaFeatures::GuettaFeatures()
{       


}
    cv::Mat GuettaFeatures::cargarImagen(string nombre)
    {
        cv::Mat img = cv::imread(nombre);
        if(img.empty())
        {
            cout << "Error: No se puede abrir la imagen" << endl;
            exit(-1);
        }  
        return img;
    }
    
GuettaCloud* GuettaFeatures::getSURFkeypoints(PointCloud<PointXYZRGB>::Ptr cloud, string imagen, RGB color)
{
    GuettaTime time;
    time.start();
    // Cargamos la imagen
    cv::Mat image = cargarImagen(imagen + ".jpg");
    SurfFeatureDetector detector;
    std::vector<cv::KeyPoint> keypoints;
    detector.detect(image, keypoints);
    
    DescriptorExtractor *extractor = new SurfDescriptorExtractor();
    cv::Mat descriptores;
    extractor->compute(image,keypoints,descriptores);

    cout << "keyPoints: " << descriptores.rows << " de " << descriptores.cols << endl;

    PointCloud<PointXYZ> pc_col;
    copyPointCloud(*cloud,pc_col);

    vector<GuettaKeyPoint*> guettakeyPoints;

    for (int i=0; i<keypoints.size (); i++)
    {
        GuettaKeyPoint* point = new GuettaKeyPoint();
        // Convertimos a 3d
        // Convertimos a 3d
        PointXYZ p3d = pc_col.at((int) keypoints[i].pt.x,(int) keypoints[i].pt.y);
        if (!( isnan(p3d.x) || isnan(p3d.y) || isnan(p3d.z)))
        {
            point->x = p3d.x;
            point->y = p3d.y;
            point->z = p3d.z;
            point->r = color.r;
            point->g = color.g;
            point->b = color.b;
            float* descriptor = new float[128];
            for (int x = 0; x < 128; x++) 
            {
                if(x >= 64)
                    descriptor[x] = 0;
                else
                    descriptor[x] = descriptores.at<float>(i, x);
            }
            point->descriptor = descriptor;
            guettakeyPoints.insert(guettakeyPoints.end(),point);
        }
    }
    cout << "Time surf: " << time.stop() << " ms" << endl;
    return new GuettaCloud(guettakeyPoints);
}

GuettaCloud* GuettaFeatures::getSIFTkeypoints(PointCloud<PointXYZRGB>::Ptr cloud, string imagen, RGB color)
{
    GuettaTime time;
    time.start();
    // Cargamos la imagen
    cv::Mat image = cargarImagen(imagen + ".jpg");
    SiftFeatureDetector detector;
    std::vector<cv::KeyPoint> keypoints;
    detector.detect(image, keypoints);

    DescriptorExtractor *extractor = new SiftDescriptorExtractor();
    cv::Mat descriptores;
    extractor->compute(image,keypoints,descriptores);
    
    cout << "keyPoints: " << descriptores.rows << " de " << descriptores.cols << endl;

    PointCloud<PointXYZ> pc_col;
    copyPointCloud(*cloud,pc_col);

    vector<GuettaKeyPoint*> guettakeyPoints;
    //guettakeyPoints.resize(keypoints.size());
    for (int i=0; i<keypoints.size (); i = i+1)
    {
        GuettaKeyPoint* point = new GuettaKeyPoint();
        // Convertimos a 3d
        PointXYZ p3d = pc_col.at((int) keypoints[i].pt.x,(int) keypoints[i].pt.y);
        if (!( isnan(p3d.x) || isnan(p3d.y) || isnan(p3d.z)))
        {
            point->x = p3d.x;
            point->y = p3d.y;
            point->z = p3d.z;
            point->r = color.r;
            point->g = color.g;
            point->b = color.b;
            float* descriptor = new float[128];
            for (int x = 0; x < 128; x++) 
                    descriptor[x] = descriptores.at<float>(i, x);
            point->descriptor = descriptor;
            guettakeyPoints.insert(guettakeyPoints.end(),point);
        }        
    }
    cout << "tamaño final: " << guettakeyPoints.size() << endl;
    cout << "Time sift: " << time.stop() << " ms" << endl;
    GuettaCloud* resultado = new GuettaCloud(guettakeyPoints);
    resultado->pointCloud = resultado->getPointCloud();
    return resultado;
}

/*
void GuettaFeatures::projectTo3DSiftGPU(std::vector<cv::KeyPoint>& feature_locations_2d,
    std::vector<Eigen::Vector4f, Eigen::aligned_allocator<Eigen::Vector4f> >& feature_locations_3d,
    const PointCloud<PointXYZ>& point_cloud, float* descriptors_in, cv::Mat& descriptors_out){

  //std::clock_t starttime=std::clock();

  cv::Point2f p2d;

  if(feature_locations_3d.size()){
    cout << "There is already 3D Information in the FrameInfo, clearing it" << endl;
    feature_locations_3d.clear();
  }

  std::list<int> featuresUsed;

  int index = -1;
  for(unsigned int i = 0; i < feature_locations_2d.size(); ){
    ++index;

    p2d = feature_locations_2d[i].pt;
    if (p2d.x >= point_cloud.width || p2d.x < 0 ||
        p2d.y >= point_cloud.height || p2d.y < 0 ||
        std::isnan(p2d.x) || std::isnan(p2d.y)){ //TODO: Unclear why points should be outside the image or be NaN
      cout << "Ignoring invalid keypoint: " << p2d << endl; //Does it happen at all? If not, remove this code block
      feature_locations_2d.erase(feature_locations_2d.begin()+i);
      continue;
    }

    PointXYZ p3d = point_cloud.at((int) p2d.x,(int) p2d.y);

    if ( isnan(p3d.x) || isnan(p3d.y) || isnan(p3d.z)){
      feature_locations_2d.erase(feature_locations_2d.begin()+i);
      continue;
    }

    featuresUsed.push_back(index);  //save id for constructing the descriptor matrix
    feature_locations_3d.push_back(Eigen::Vector4f(p3d.x, p3d.y, p3d.z, 1.0));
    i++; //Only increment if no element is removed from vector
  }

  //create descriptor matrix
  int size = feature_locations_3d.size();
  descriptors_out = cv::Mat(size, 128, CV_32F);
  for (int y = 0; y < size && featuresUsed.size() > 0; ++y) {
    int id = featuresUsed.front();
    featuresUsed.pop_front();

    for (int x = 0; x < 128; ++x) {
      descriptors_out.at<float>(y, x) = descriptors_in[id * 128 + x];
    }
  }

  //ROS_INFO_STREAM_COND_NAMED(( (std::clock()-starttime) / (double)CLOCKS_PER_SEC) > min_time_reported, "timings", "function runtime: "<< ( std::clock() - starttime ) / (double)CLOCKS_PER_SEC  <<"sec");
}
   */
GuettaCloud* GuettaFeatures::getNARFkeypoints(PointCloud<PointXYZRGB>::Ptr pointCloud, RGB color)
{
    // Creamos la imagen de rango
    vector<GuettaKeyPoint*> keyPoints;
    
    RangeImage rangeImage = createRangeImage(pointCloud);

    float support_size = 0.2f;
    RangeImageBorderExtractor range_image_border_extractor;
    NarfKeypoint narf_keypoint_detector (&range_image_border_extractor);
    narf_keypoint_detector.setRangeImage (&rangeImage);
    narf_keypoint_detector.getParameters().support_size = support_size;
    /*
    narf_keypoint_detector.getParameters().add_points_on_straight_edges = true;
    narf_keypoint_detector.getParameters().max_no_of_interest_points = 50;
    narf_keypoint_detector.getParameters().no_of_polynomial_approximations_per_point = false;
    narf_keypoint_detector.getParameters().optimal_range_image_patch_size = 15;*/
    //narf_keypoint_detector.getParameters().
    //narf_keypoint_detector.getParameters ().distance_for_additional_points = 2.9;
//narf_keypoint_detector.getParameters().
    PointCloud<int> keypoint_indices;
    narf_keypoint_detector.compute (keypoint_indices);
   
    cout << "Found " << keypoint_indices.points.size () << " key points.\n";
   
    vector<int> keypoint_indices3;
   
    keypoint_indices3.resize(keypoint_indices.points.size());
   
    keyPoints.resize(keypoint_indices.points.size());
   
    for (int i=0; i<keypoint_indices.points.size (); i++)
    {
        GuettaKeyPoint* point = new GuettaKeyPoint();
        point->x = rangeImage.points[keypoint_indices.points[i]].getVector3fMap()[0];
        point->y = rangeImage.points[keypoint_indices.points[i]].getVector3fMap()[1];
        point->z = rangeImage.points[keypoint_indices.points[i]].getVector3fMap()[2];
        point->r = color.r;
        point->g = color.g;
        point->b = color.b;
        keyPoints[i] = point;
        keypoint_indices3[i]=keypoint_indices.points[i];
    }

    NarfDescriptor narf_descriptor(&rangeImage, &keypoint_indices3);
    narf_descriptor.getParameters().support_size = support_size;
    narf_descriptor.getParameters().rotation_invariant = true;
    PointCloud<Narf36> narf_descriptors;
    narf_descriptor.compute(narf_descriptors);
    cout << "Extracted "<< narf_descriptors.size()<<" descriptors for "<< keyPoints.size()<< " keypoints.\n";

    float epsilon = 0.05;
    int iterKeyPoints = 0;
    int iterDescriptors = 0;
    while (iterKeyPoints < keyPoints.size())
    {
        if( (abs(keyPoints[iterKeyPoints]->x - narf_descriptors[iterDescriptors].x)<epsilon) &&
            (abs(keyPoints[iterKeyPoints]->y - narf_descriptors[iterDescriptors].y)<epsilon) &&
            (abs(keyPoints[iterKeyPoints]->z - narf_descriptors[iterDescriptors].z)<epsilon))
        {
            //keyPoints[iterKeyPoints].descriptor = narf_descriptors[iterDescriptors].descriptor;
            float* descriptor128 = new float[128];
            for(int i=0; i<128; i++)
            {
                if(i<36)
                    descriptor128[i] = narf_descriptors[iterDescriptors].descriptor[i];
                else
                    descriptor128[i] = 0;
            }
            keyPoints[iterKeyPoints]->descriptor = descriptor128;
            //cout << iterKeyPoints << "- (" << keyPoints[iterKeyPoints].x << "," << keyPoints[iterKeyPoints].y << "," << keyPoints[iterKeyPoints].z << ")->0) \t" << iterDescriptors << "- (" << narf_descriptors[iterDescriptors].x << "," << narf_descriptors[iterDescriptors].y << "," << narf_descriptors[iterDescriptors].z << ")->" << narf_descriptors[iterDescriptors].descriptor << endl;
           
            iterKeyPoints++;
            iterDescriptors ++;
        }
        else
        {
            //cout << "\t\t\t\t\t" << iterDescriptors << "- (" << narf_descriptors[iterDescriptors].x << "," << narf_descriptors[iterDescriptors].y << "," << narf_descriptors[iterDescriptors].z << ")->" << narf_descriptors[iterDescriptors].descriptor << endl;
            //cout << "Fallo <" << iterKeyPoints << "," << iterDescriptors << ">" << endl;
            iterDescriptors++;
        }
    }
   
    return new GuettaCloud(keyPoints);
}

RangeImage GuettaFeatures::createRangeImage(PointCloud<PointXYZRGB>::Ptr cloud)
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
    rangeImage.setUnseenToMaxRange();
    rangeImage.createFromPointCloud(*cloud, angularResolution, maxAngleWidth, maxAngleHeight,
                                  sensorPose, coordinate_frame, noiseLevel, minRange, borderSize);        
    return rangeImage;
}