#include <pcl-1.1/pcl/keypoints/keypoint.h>

#include "Node.h"

Node::Node(shared_ptr<GuettaCloud> cloud,shared_ptr<GuettaCloud> keyPoints,shared_ptr<GuettaCloud> features)
{
    this->cloud = cloud;
    this->keyPoints = keyPoints;
    this->features = features;
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