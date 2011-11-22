#ifndef NODE_H
#define	NODE_H

#include "GuettaCloud.h"
#include <boost/shared_ptr.hpp>
#include <iostream>
using namespace std;
using namespace boost;

class Node
{
    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
        Node(shared_ptr<GuettaCloud> cloud,shared_ptr<GuettaCloud> keyPoints,shared_ptr<GuettaCloud> features,Eigen::Matrix4f transformation);
        Node(shared_ptr<GuettaCloud> cloud,shared_ptr<GuettaCloud> keyPoints,shared_ptr<GuettaCloud> features);
        ~Node();

        void setId(int id);
        int getId();
        int matchNodePair(shared_ptr<Node> node);
        shared_ptr<GuettaCloud> getFeatures();
        shared_ptr<GuettaCloud> getCloud();
        
    private:
        shared_ptr<GuettaCloud> cloud;
        shared_ptr<GuettaCloud> keyPoints;
        shared_ptr<GuettaCloud> features;
        Eigen::Matrix4f transformation;
        int id;
};

#endif

