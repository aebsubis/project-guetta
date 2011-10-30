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

void GuettaICP::getNearestDescriptors(int maxKeyPointsAlineamiento, float maxDistance, GuettaCloud* cloud1, GuettaCloud* cloud2)
{
    // Obtenemos los n descriptores mas parecidos       
    //float maxDistance = 9000; //0.005;
    // Vector de indices con los descriptores más parecidos
    vector<int> indicesInputTarget;
    vector<int> indicesInputCloud;   
    int numDescriptores = 0;
    
    cout << maxKeyPointsAlineamiento << " y " << maxDistance << endl;
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
            cout << contador << " -> distancia: " << i << "," << nearest[0] << " : " << distancia << ", distancia xyz: " << distanciaXYZ << endl;
            
            numDescriptores++;
            indicesInputTarget.insert(indicesInputTarget.end(),i);
            indicesInputCloud.insert(indicesInputCloud.end(),nearest[0]);
        }
    }    
    
    // Creamos el guettaCloud 
    cout << "Hay: " << indicesInputTarget.size() << endl;
    for(int i = 0; i < indicesInputTarget.size(); i++)
    {
        
        GuettaKeyPoint* keyPoint = inputCloud->data[indicesInputCloud[i]];
        GuettaKeyPoint* guettaPoint = new GuettaKeyPoint(*keyPoint);
        guettaPoint->r = 0;
        guettaPoint->g = 1;
        guettaPoint->b = 0;
        
        cloud1->data.insert(cloud1->data.end(),guettaPoint);
        
        GuettaKeyPoint* keyPoint2 = inputTarget->data[indicesInputTarget[i]];
        GuettaKeyPoint* guettaPoint2 = new GuettaKeyPoint(*keyPoint2);
        guettaPoint2->r = 1;
        guettaPoint2->g = 0;
        guettaPoint2->b = 0;       
        cloud2->data.insert(cloud2->data.end(),guettaPoint2);
        
        /*
          GuettaKeyPoint* keyPoint = inputCloud->data[indicesInputCloud[i]];

        keyPoint->r = 0;
        keyPoint->g = 0;
        keyPoint->b = 1;
        
        keyPoint = inputTarget->data[indicesInputTarget[i]];
                keyPoint->r = 0;
        keyPoint->g = 0;
        keyPoint->b = 1;*/
        //GuettaKeyPoint* guettaPoint = new GuettaKeyPoint(*keyPoint);
        //point.x = 
        //PointXYZRGB point = cloud3->points[i];
        //guettaCloud->data[i] = new GuettaKeyPoint(point.x,point.y,point.z,point.r,point.g,point.b,inputTarget->data[i]->descriptor);
        
    }    

}



GuettaCloud* GuettaICP::compute(Eigen::Matrix4f& transformation_matrix, int maxKeyPointsAlineamiento, float maxDistance)
{
    GuettaTime time;
    time.start();
    // Obtenemos los n descriptores mas parecidos       
    //float maxDistance = 9000; //0.005;
    // Vector de indices con los descriptores más parecidos
    vector<int> indicesInputTarget;
    vector<int> indicesInputCloud;   
    int numDescriptores = 0;
    
    cout << maxKeyPointsAlineamiento << " y " << maxDistance << endl;
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
            cout << contador << " -> distancia: " << i << " : " << distancia << ", distancia xyz: " << distanciaXYZ << endl;
            
            numDescriptores++;
            indicesInputTarget.insert(indicesInputTarget.end(),i);
            indicesInputCloud.insert(indicesInputCloud.end(),nearest[0]);
        }
    }
    /*
    float media = 0;
    // Calculamos la distancia xyz media entre descriptores
    for(int i = 0; i < indicesInputTarget.size(); i++)
    {
        GuettaKeyPoint* point = inputTarget->data[indicesInputTarget[i]];
        media += point->distanceXYZ(inputCloud->data[indicesInputCloud[i]]);
        
    }
    media = media / indicesInputTarget.size();
    cout << "Media xyz: " << media << endl;
    
    // Eliminamos los descriptores con distancia mayor a un 20% de la media
    vector<int> copia_indicesInputTarget = indicesInputTarget;
    vector<int> copia_indicesInputCloud = indicesInputCloud;
    indicesInputTarget.clear();
    indicesInputCloud.clear();
    for(int i = 0; i < copia_indicesInputTarget.size(); i++)
    {
        GuettaKeyPoint* point = inputTarget->data[copia_indicesInputTarget[i]];
        float distance = point->distanceXYZ(inputCloud->data[copia_indicesInputCloud[i]]);
        if(fabs(media-distance) < media*0.15)
        {
            indicesInputTarget.insert(indicesInputTarget.end(),copia_indicesInputTarget[i]);
            indicesInputCloud.insert(indicesInputCloud.end(),copia_indicesInputCloud[i]);
           // indicesInputTarget.erase(i);
           // indicesInputCloud.erase(i);
        }
    }    
    
    for(int i = 0; i < indicesInputTarget.size(); i++)
    {
        GuettaKeyPoint* point = inputTarget->data[indicesInputTarget[i]];
        float distance = point->distanceXYZ(inputCloud->data[indicesInputCloud[i]]);
        cout << i << "distancia xyz: " << distance << endl;        
    }  */
    
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
}

GuettaICP::GuettaICP()
{       

}

void GuettaICP::setInputCloud(GuettaCloud* inputCloud)
{
    this->inputCloud = inputCloud;
}

void GuettaICP::setInputTarget(GuettaCloud* inputTarget)
{
    this->inputTarget = inputTarget;
}