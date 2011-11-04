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
        Node(shared_ptr<GuettaCloud> cloud,shared_ptr<GuettaCloud> keyPoints,shared_ptr<GuettaCloud> features);
        ~Node();

        void setId(int id);
        int getId();
        
    private:
        shared_ptr<GuettaCloud> cloud;
        shared_ptr<GuettaCloud> keyPoints;
        shared_ptr<GuettaCloud> features;
        int id;
};

#endif

