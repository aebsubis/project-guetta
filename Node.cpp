#include <pcl-1.1/pcl/keypoints/keypoint.h>

#include "Node.h"

Node::Node(shared_ptr<GuettaCloud> cloud,shared_ptr<GuettaCloud> keyPoints,shared_ptr<GuettaCloud> features, Eigen::Matrix4f transformation)
{
    this->cloud = cloud;
    this->keyPoints = keyPoints;
    this->features = features;
    this->transformation= transformation;
}

Node::Node(shared_ptr<GuettaCloud> cloud,shared_ptr<GuettaCloud> keyPoints,shared_ptr<GuettaCloud> features)
{
    this->cloud = cloud;
    this->keyPoints = keyPoints;
    this->features = features;
    for(int i = 0; i < 4;  i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(i == j)
                transformation(i,j) = 1;
            else
                transformation(i,j) = 0;
        }
    }
    cout << transformation << endl;
   // this->transformation= transformation;
}

Node::~Node()
{
    
}

void Node::setId(int id)
{
    this->id = id;
}

int Node::getId()
{
    return id;
}

shared_ptr<GuettaCloud> Node::getFeatures()
{
    return features;
}

shared_ptr<GuettaCloud> Node::getCloud()
{
    return cloud;
}

int Node::matchNodePair(shared_ptr<Node> node)
{
    int numMatches = 0;
    float maxDistance = 20000;
    
    for(int i = 0; i < keyPoints->data.size(); i++)
    {
        shared_ptr<GuettaKeyPoint> keyPoint = keyPoints->data[i];
        
        // Calculamos los descriptores más cercanos en el otro nodo
        vector<float> nearest = keyPoint->getNeareastDescriptor3(node->keyPoints->data);       

        // Calculamos si el más cercano es menor que la maxima distancia
        float distancia = node->keyPoints->data[nearest[0]]->distanceDescriptor(keyPoint);
        //cout << "Distancia: " << distancia << endl;
        if(distancia < maxDistance)
        {
            numMatches++;
        }
        /*
        float distanciaXYZ = inputCloud->data[nearest[0]]->distanceXYZ(keyPoint);
        if(distancia < maxDistance)
        {
            contador++;
            // Añadimos los indices
            //cout << contador << " -> distancia: " << i << "," << nearest[0] << " : " << distancia << ", distancia xyz: " << distanciaXYZ << endl;
            
            numDescriptores++;
            indicesInputTarget.insert(indicesInputTarget.end(),i);
            indicesInputCloud.insert(indicesInputCloud.end(),nearest[0]);
        }*/
       
    }    
    //cout << "Num matches: " << numMatches << endl;
    /*
    for(int i = 0; i < keyPoints->data.size(); i++)
    {
        shared_ptr<GuettaKeyPoint> point = keyPoints->data[i];
        float distancia = 
    }*/
    
    //getNearestDescriptors(int maxKeyPointsAlineamiento, float maxDistance, shared_ptr<GuettaCloud> cloud1, shared_ptr<GuettaCloud> cloud2)
    return numMatches;
    
}