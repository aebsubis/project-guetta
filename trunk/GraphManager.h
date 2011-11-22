#ifndef GRAPHMANAGER_H
#define	GRAPHMANAGER_H

#include "Node.h"
#include <iostream>
#include <boost/shared_ptr.hpp>
#include "aislib/graph/loadEdges3d.h"
#include "aislib/graph_optimizer_hogman/graph_optimizer3d_hchol.h"
#include "GuettaTime.h"
//#include "aislib/math/transformation.h"
using namespace std;
using namespace boost;
namespace AIS = AISNavigation;

class GraphManager
{
    public:
        GraphManager();
        ~GraphManager();
        void addNode(shared_ptr<Node> newNode);
        void clear();
        bool isBigTransformation(const Eigen::Matrix4f& t);
        void mat2RPY(const Eigen::Matrix4f& t, double& roll, double& pitch, double& yaw);
        void mat2dist(const Eigen::Matrix4f& t, double &dist);
        bool addEdgeToHogman(AIS::LoadedEdge3D edge, bool largeEdge);
        Eigen::Matrix4f hogman2Eigen(const Transformation3 hogman_trans);
        Transformation3 eigen2Hogman(const Eigen::Matrix4f eigen_mat);
        void mostrarInformacion();
        void optimizeGraph();
        map<int,shared_ptr<Node> > graph;
        Eigen::Matrix4f getOptimizedTransformation(int idNode);
        bool update;
    private:
        
        shared_ptr<AIS::GraphOptimizer3D> optimizer;
};

#endif

