#ifndef GRAPHMANAGER_H
#define	GRAPHMANAGER_H

#include "Node.h"
#include <iostream>
#include <boost/shared_ptr.hpp>
#include "aislib/graph_optimizer_hogman/graph_optimizer3d_hchol.h"
#include "aislib/graph/loadEdges3d.h"

using namespace std;
using namespace boost;
namespace AIS = AISNavigation;

class GraphManager
{
    public:
        GraphManager();
        ~GraphManager();
        void addNode(shared_ptr<Node> newNode);
        
    private:
        map<int,shared_ptr<Node> > graph;
        shared_ptr<AIS::GraphOptimizer3D> optimizer;
};

#endif

