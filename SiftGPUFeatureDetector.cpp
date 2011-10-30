#include "SiftGPUFeatureDetector.h"

SiftGPUFeatureDetector* SiftGPUFeatureDetector::instance = NULL;

SiftGPUFeatureDetector::~SiftGPUFeatureDetector()
{
    delete siftgpu;
    instance = NULL;
    if (data != NULL) {
            free(data);
            data = NULL;
    }
}

SiftGPUFeatureDetector* SiftGPUFeatureDetector::GetInstance()
{
    if (instance == NULL) 
        instance = new SiftGPUFeatureDetector();
    return instance;
}


SiftGPUFeatureDetector::SiftGPUFeatureDetector()
{       
    siftgpu = new SiftGPU();

    if (siftgpu->CreateContextGL() != SiftGPU::SIFTGPU_FULL_SUPPORTED) 
    {
        cout << "ERROR: No se puede inicialziar SiftGPU" << endl;
        exit(1);
    }
    
    data = (unsigned char*) malloc(imageWidth * imageHeight);
}

// Covierte una matriz del tipo cv a un array de textura de opengl
void SiftGPUFeatureDetector::CVMatToSiftGPU(const cv::Mat& image, unsigned char* siftImage) const 
{
    cv::Mat tmp;
    image.convertTo(tmp, CV_8U);
    for (int y = 0; y < tmp.rows; ++y) 
    {
        for (int x = 0; x < tmp.cols; ++x)
            siftImage[y * tmp.cols + x] = tmp.at<unsigned char> (y, x);
    }
}

// Detecta las características ( puntos claves ) de la imagen
float* SiftGPUFeatureDetector::detect(const cv::Mat& image, cv::vector<cv::KeyPoint>& keypoints) const 
{
   
    cout << "hola" << endl;
    struct timeval start_;
          struct timeval end_;
                gettimeofday(&start_, NULL);
    //  Covierte una matriz del tipo cv a un array de textura de opengl
    CVMatToSiftGPU(image, data);
    cout << "1" << endl;
    int num_features = 0;
    SiftGPU::SiftKeypoint* keys = 0;
    float* descriptors = 0;
    
    if(image.cols != imageWidth || image.rows != imageHeight)
    {
        cout << "<SiftGPUFeatureDetector> Error: Tamaño de la imagen no válido";
        exit(1);
    }
    cout << "2" << endl;
    bool result = siftgpu->RunSIFT(image.cols, image.rows, data, GL_RGB, GL_UNSIGNED_BYTE);
    if(result)
    {
        cout << "3" << endl;
        num_features = siftgpu->GetFeatureNum();
        keys = new SiftGPU::SiftKeypoint[num_features];
        descriptors = new float[128 * num_features];
        siftgpu->GetFeatureVector(&keys[0], &descriptors[0]);        
    }
    else
    {
        cout << "<SiftGPUFeatureDetector> Error: RunSIFT";
        exit(1);        
    }
    
    // Copiamos los keypoints
    keypoints.clear();
    for (int i = 0; i < num_features; ++i) 
    {
        cv::KeyPoint key(keys[i].x, keys[i].y, keys[i].s, keys[i].o);
        keypoints.push_back(key);
    }
        
    gettimeofday(&end_, NULL);
    double dur = ((end_.tv_sec * 1000000 + end_.tv_usec  ) - (start_.tv_sec * 1000000 + start_.tv_usec)) / 1000.0;
    cout << "Duracion: " << dur << " ms" << endl;
    
    return descriptors;
    /*
	if (siftgpu->RunSIFT(image.cols, image.rows, data, GL_LUMINANCE,
			GL_UNSIGNED_BYTE)) {
		num_features = siftgpu->GetFeatureNum();
		keys = new SiftGPU::SiftKeypoint[num_features];
		descriptors = new float[128 * num_features];
		siftgpu->GetFeatureVector(&keys[0], &descriptors[0]);
	} else {
		ROS_WARN("SIFTGPU->RunSIFT() failed!");
	}
    */
    /*
	if (error) {
		keypoints.clear();
		ROS_ERROR("SiftGPU cannot be used. Detection of keypoints failed");
		return 0;
	}

	//get image
	CVMatToSiftGPU(image, data);

	int num_features = 0;
	SiftGPU::SiftKeypoint* keys = 0;

	float* descriptors = 0;
	ROS_INFO("SIFTGPU: cols: %d, rows: %d", image.cols, image.rows);
	if (siftgpu->RunSIFT(image.cols, image.rows, data, GL_LUMINANCE,
			GL_UNSIGNED_BYTE)) {
		num_features = siftgpu->GetFeatureNum();
		keys = new SiftGPU::SiftKeypoint[num_features];
		descriptors = new float[128 * num_features];
		siftgpu->GetFeatureVector(&keys[0], &descriptors[0]);
	} else {
		ROS_WARN("SIFTGPU->RunSIFT() failed!");
	}

	//copy to opencv structure
	keypoints.clear();
	for (int i = 0; i < num_features; ++i) {
		KeyPoint key(keys[i].x, keys[i].y, keys[i].s, keys[i].o);
		keypoints.push_back(key);
	}

//	FILE *fp = fopen("bla.pgm", "w");
//	WritePGM(fp, data, image.cols, image.rows);
//	fclose(fp);

	return descriptors;*/
}