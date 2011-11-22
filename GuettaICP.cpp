#include "GuettaICP.h"

GuettaICP* GuettaICP::instance = NULL;

GuettaICP::~GuettaICP()
{

}

GuettaICP* GuettaICP::GetInstance()
{
    if (instance == NULL) 
        instance = new GuettaICP();
    return instance;
}

void GuettaICP::getNearestDescriptors(int maxKeyPointsAlineamiento, float maxDistance, shared_ptr<GuettaCloud> cloud1, shared_ptr<GuettaCloud> cloud2)
{
    // Obtenemos los n descriptores mas parecidos       
    //float maxDistance = 9000; //0.005;
    // Vector de indices con los descriptores más parecidos
    vector<int> indicesInputTarget;
    vector<int> indicesInputCloud;   
    int numDescriptores = 0;
    
    //cout << maxKeyPointsAlineamiento << ";" << maxDistance << ";" << inputTarget->data.size() << ";" << inputCloud->data.size() << endl;
    
    int contador = 0;
    for(int i = 0; i < inputTarget->data.size() && numDescriptores != maxKeyPointsAlineamiento; i++)
    {

        shared_ptr<GuettaKeyPoint> keyPoint = inputTarget->data[i];

        // Calculamos los descriptores más cercanos en el otro input cloud
        vector<float> nearest = keyPoint->getNeareastDescriptor3(inputCloud->data);

        // Calculamos si el más cercano es menor que la maxima distancia
        float distancia = inputCloud->data[nearest[0]]->distanceDescriptor(keyPoint);

        float distanciaXYZ = inputCloud->data[nearest[0]]->distanceXYZ(keyPoint);
        if(distancia < maxDistance)
        {
            contador++;
            // Añadimos los indices
            //cout << contador << " -> distancia: " << i << "," << nearest[0] << " : " << distancia << ", distancia xyz: " << distanciaXYZ << endl;
            
            numDescriptores++;
            indicesInputTarget.insert(indicesInputTarget.end(),i);
            indicesInputCloud.insert(indicesInputCloud.end(),nearest[0]);
        }
    }    
    
    // Creamos el guettaCloud 
   
    for(int i = 0; i < indicesInputTarget.size(); i++)
    {
        
        shared_ptr<GuettaKeyPoint> keyPoint = inputCloud->data[indicesInputCloud[i]];
        shared_ptr<GuettaKeyPoint> guettaPoint (new GuettaKeyPoint(*keyPoint));
        guettaPoint->r = 0;
        guettaPoint->g = 1;
        guettaPoint->b = 0;
        
        cloud1->data.insert(cloud1->data.end(),guettaPoint);
        
        shared_ptr<GuettaKeyPoint> keyPoint2 = inputTarget->data[indicesInputTarget[i]];
        shared_ptr<GuettaKeyPoint> guettaPoint2 (new GuettaKeyPoint(*keyPoint2));
        guettaPoint2->r = 1;
        guettaPoint2->g = 0;
        guettaPoint2->b = 0;       
        cloud2->data.insert(cloud2->data.end(),guettaPoint2);
    }    
}



GuettaCloud* GuettaICP::compute(Eigen::Matrix4f& transformation_matrix, int maxKeyPointsAlineamiento, float maxDistance)
{
    /*
    GuettaTime time;
    time.start();
    // Obtenemos los n descriptores mas parecidos       
    //float maxDistance = 9000; //0.005;
    // Vector de indices con los descriptores más parecidos
    vector<int> indicesInputTarget;
    vector<int> indicesInputCloud;   
    int numDescriptores = 0;
    
    //cout << maxKeyPointsAlineamiento << " y " << maxDistance << endl;
    int contador = 0;
    for(int i = 0; i < inputTarget->data.size() && numDescriptores != maxKeyPointsAlineamiento; i++)
    {
        GuettaKeyPoint* keyPoint = inputTarget->data[i];
        // Calculamos los descriptores más cercanos en el otro input cloud
        vector<int> nearest = keyPoint->getNeareastDescriptor3(inputCloud->data);
        // Calculamos si el más cercano es menor que la maxima distancia
        float distancia = inputCloud->data[nearest[0]]->distanceDescriptor(keyPoint);
        float distanciaXYZ = inputCloud->data[nearest[0]]->distanceXYZ(keyPoint);
        if(distancia < maxDistance)
        {
            contador++;
            // Añadimos los indices
            //cout << contador << " -> distancia: " << i << " : " << distancia << ", distancia xyz: " << distanciaXYZ << endl;
            
            numDescriptores++;
            indicesInputTarget.insert(indicesInputTarget.end(),i);
            indicesInputCloud.insert(indicesInputCloud.end(),nearest[0]);
        }
    }
    
    PointCloud<PointXYZRGB>::Ptr pointCloud1 = inputTarget->getPointCloud();
    PointCloud<PointXYZRGB>::Ptr pointCloud2 = inputCloud->getPointCloud();
    estimateRigidTransformationSVD(*pointCloud1, indicesInputTarget, *pointCloud2, indicesInputCloud, transformation_matrix);    
    cout << transformation_matrix << endl;
    
    PointCloud<PointXYZRGB>::Ptr cloud3 (new PointCloud<PointXYZRGB>);
    transformPointCloud (*pointCloud1, *cloud3, transformation_matrix);
    
    for(int i = 0; i < cloud3->points.size(); i++)
    {
        cloud3->points[i].r = 0;
        cloud3->points[i].g = 0;
        cloud3->points[i].b = 1;
       
    }
    
    cout << "Time icp: " << time.stop() << " ms" << endl;
    
   // Creamos el guettaCloud 
    GuettaCloud* guettaCloud = new GuettaCloud();
    guettaCloud->data.resize(cloud3->points.size());
    for(int i = 0; i < cloud3->points.size(); i++)
    {
        PointXYZRGB point = cloud3->points[i];
        guettaCloud->data[i] = new GuettaKeyPoint(point.x,point.y,point.z,point.r,point.g,point.b,inputTarget->data[i]->descriptor);
        
    }
    
   
    return guettaCloud;
    */
}

GuettaICP::GuettaICP()
{       

}

void GuettaICP::setInputCloud(shared_ptr<GuettaCloud> inputCloud)
{
    this->inputCloud = inputCloud;
}

void GuettaICP::setInputTarget(shared_ptr<GuettaCloud> inputTarget)
{
    this->inputTarget = inputTarget;
}