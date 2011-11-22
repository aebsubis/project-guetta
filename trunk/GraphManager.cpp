#include <map>
#include "GraphManager.h"
#include "GuettaTime.h"
#include "Guetta.h"

GraphManager::GraphManager()
{
    int numLevels = 3;
    int nodeDistance = 2;
    optimizer = shared_ptr<AIS::HCholOptimizer3D>(new AIS::HCholOptimizer3D(numLevels, nodeDistance));
    update = false;
}

GraphManager::~GraphManager()
{
    
}

void GraphManager::addNode(shared_ptr<Node> newNode)
{
    // Generamos una id para el nuevo nodo
    newNode->setId(graph.size());
    cout << "Añadido nuevo nodo con id: " << newNode->getId() << endl;

    // Comprobamos si el grafo esta vacio
    if(graph.size() == 0)
    {
        // Añadimos el nodo al grafo
        graph[newNode->getId()] = newNode;
        // Añadimos el nodo al optimizador en el origen
        optimizer->addVertex(0, Transformation3(), 1e9*Matrix6::eye(1.0));
    }
    else
    {

        GuettaTime timer;
        timer.start();
        GuettaICP* guettaIcp = GuettaICP::GetInstance();
        // Comparamos el nuevo nodo con todos los nodos del grafo
        map<int,shared_ptr<Node> >::iterator it;
        for (it = graph.begin(); it != graph.end(); it++) 
        //for (it = graph.end(); it != graph.begin(); it--) 
        {
            shared_ptr<Node> node = it->second;
  
            guettaIcp->setInputTarget(newNode->getFeatures());
            guettaIcp->setInputCloud(node->getFeatures());
            
            shared_ptr<GuettaCloud> guettaCloud1 (new GuettaCloud());
            shared_ptr<GuettaCloud> guettaCloud2 (new GuettaCloud());
            guettaIcp->getNearestDescriptors(7,20000,guettaCloud1,guettaCloud2);
            
            Ramsac ramsac(guettaCloud1,guettaCloud2);
            ramsac.compute(0,"");
            cout << "menorDistancia: " << ramsac.menorDistancia << endl;
            
            Eigen::Matrix4f  transformation = ramsac.transformacion;
            cout << transformation<< endl;
            double roll = atan2(transformation(2,1),transformation(2,2));
            double pitch = atan2(-transformation(2,0),sqrt(transformation(2,1)*transformation(2,1)+transformation(2,2)*transformation(2,2)));
            double yaw = atan2(transformation(1,0),transformation(0,0));
            roll = roll/M_PI*180;
            pitch = pitch/M_PI*180;
            yaw = yaw/M_PI*180;
            double dist = sqrt(transformation(0,3)*transformation(0,3)+transformation(1,3)*transformation(1,3)+transformation(2,3)*transformation(2,3));
            cout << roll << ";" << pitch << ";" << yaw << ";" << dist << endl;  
    
            if(ramsac.menorDistancia < 0.01 && fabs(yaw) < 30)
            {
                /*
                Eigen::Matrix4f transformation = ramsac.transformacion;
                double roll = atan2(transformation(2,1),transformation(2,2));
                double pitch = atan2(-transformation(2,0),sqrt(transformation(2,1)*transformation(2,1)+transformation(2,2)*transformation(2,2)));
                double yaw = atan2(transformation(1,0),transformation(0,0));
                roll = roll/M_PI*180;
                pitch = pitch/M_PI*180;
                yaw = yaw/M_PI*180;
                double dist = sqrt(transformation(0,3)*transformation(0,3)+transformation(1,3)*transformation(1,3)+transformation(2,3)*transformation(2,3));
                cout << roll << ";" << pitch << ";" << yaw << ";" << dist << endl;
                cout << transformation << endl;*/
                cout << "Encontrado loop: nodos: " << newNode->getId() << " y " << node->getId() << endl;
                cout << "Creando arista entre ambos nodos" << endl;
                AIS::LoadedEdge3D edge;
                edge.id1 = node->getId();
                edge.id2 = newNode->getId();
                edge.mean = eigen2Hogman(ramsac.transformacion);
                edge.informationMatrix = Matrix6::eye(32);
                if(abs(newNode->getId()-node->getId()) == 1)
                        addEdgeToHogman(edge,true);
                if(abs(newNode->getId()-node->getId()) > 8)
                {
                     addEdgeToHogman(edge,true);
                        update = true;
                        
                }
                //break;
                //edge.mean = 
                /*
                if(isBigTransformation(ramsac.transformacion))
                {
                    cout << "Bien" << endl;
                }*/
                
            }
        }
        cout << "Tiempo comparar nodos: " << timer.stop() << " ms" << endl;

        // Mostramos los descrptiores seleccionados
        //shared_ptr<GuettaCloud> guettaCloud1 (new GuettaCloud());
        //shared_ptr<GuettaCloud> guettaCloud2 (new GuettaCloud());
        //guettaIcp->getNearestDescriptors(maxKeyPointsAlineamientoSIFT,maxDistanceSIFT,guettaCloud1,guettaCloud2);
        
        
        /*
        // Comparamos el nuevo nodo con todos los nodos del grafo
        map<int,shared_ptr<Node> >::iterator it;
        map<int,shared_ptr<Node> >::iterator it2;
        for (it = graph.begin(); it != graph.end(); it++) 
        {
            shared_ptr<Node> node = it->second;
            cout << "comparando " << newNode->getId() << " con " << it->first << " -> Empareja con: " << newNode->matchNodePair(node) << endl;
        }
        */
        //if(isBigTransformation(ramsac.
         // Añadimos el nodo al grafo
        graph[newNode->getId()] = newNode;       
        if(update == true)
            optimizeGraph();
    }
}

void GraphManager::mostrarInformacion()
{
    AISNavigation::PoseGraph3D::VertexIDMap::iterator vertex_iter = optimizer->vertices().begin();
    for(; vertex_iter != optimizer->vertices().end(); vertex_iter++) 
    {
        AIS::PoseGraph3D::Vertex* v = static_cast<AISNavigation::PoseGraph3D::Vertex*>((*vertex_iter).second);
        cout << "-----------------------------------------------------------" << endl;
        cout << "Vertex: " << v->id() << endl;
        cout << "Transformation " << endl;
        Eigen::Matrix4f transformation = hogman2Eigen(v->transformation);
        cout << transformation << endl;
        
        double roll = atan2(transformation(2,1),transformation(2,2));
        double pitch = atan2(-transformation(2,0),sqrt(transformation(2,1)*transformation(2,1)+transformation(2,2)*transformation(2,2)));
        double yaw = atan2(transformation(1,0),transformation(0,0));
        roll = roll/M_PI*180;
        pitch = pitch/M_PI*180;
        yaw = yaw/M_PI*180;
        double dist = sqrt(transformation(0,3)*transformation(0,3)+transformation(1,3)*transformation(1,3)+transformation(2,3)*transformation(2,3));
        cout << roll << ";" << pitch << ";" << yaw << ";" << dist << endl;
        cout << "-----------------------------------------------------------" << endl;
        //cout << "Local transformation " << endl;
    }
       /*
    for (unsigned int i = 0; i < optimizer->vertices().size(); ++i)
    {
        AIS::PoseGraph3D::Vertex* v = optimizer->vertex(i);
        
        
    }
            AISNavigation::PoseGraph3D::Vertex* v; //used in loop
        AISNavigation::PoseGraph3D::VertexIDMap::iterator vertex_iter = optimizer_->vertices().begin();
        for(; vertex_iter != optimizer_->vertices().end(); vertex_iter++, counter++) {
            v = static_cast<AISNavigation::PoseGraph3D::Vertex*>((*vertex_iter).second);
            //v->transformation.rotation().x()+ v->transformation.rotation().y()+ v->transformation.rotation().z()+ v->transformation.rotation().w();
            tmp = v->transformation * origin;
            tail.x = tmp.x();
            tail.y = tmp.y();
            tail.z = tmp.z();    */
    
}

void GraphManager::optimizeGraph()
{
    const int iterations = 10;
    int currentIt = optimizer->optimize(iterations, true);

   
   cout << "Hogman Statistics: " << optimizer->vertices().size() << " nodes, " 
                    << optimizer->edges().size() << " edges. "
                    << "chi2: " << optimizer->chi2()
                    << ", Iterations: " << currentIt << endl;
   
    for (unsigned int i = 0; i < optimizer->vertices().size(); ++i)
    {
        AIS::PoseGraph3D::Vertex* v = optimizer->vertex(i);
     
        Eigen::Matrix4f transformation = hogman2Eigen(v->transformation);
        cout << "Matriz transformacion vertice: " << i << endl;
        cout << transformation << endl;
         double roll = atan2(transformation(2,1),transformation(2,2));
        double pitch = atan2(-transformation(2,0),sqrt(transformation(2,1)*transformation(2,1)+transformation(2,2)*transformation(2,2)));
        double yaw = atan2(transformation(1,0),transformation(0,0));
        roll = roll/M_PI*180;
        pitch = pitch/M_PI*180;
        yaw = yaw/M_PI*180;
        double dist = sqrt(transformation(0,3)*transformation(0,3)+transformation(1,3)*transformation(1,3)+transformation(2,3)*transformation(2,3));
        cout << roll << ";" << pitch << ";" << yaw << ";" << dist << endl;
    }
    /*
    freshlyOptimized_ = true;

    AISNavigation::PoseGraph3D::Vertex* v = optimizer_->vertex(optimizer_->vertices().size()-1);
    kinect_transform_ =  hogman2TF(v->transformation);
    //pcl_ros::transformAsMatrix(kinect_transform_, latest_transform_);
    latest_transform_ = hogman2QMatrix(v->transformation); 

    */
}

Eigen::Matrix4f GraphManager::getOptimizedTransformation(int idNode)
{
    Eigen::Matrix4f transformation;
    /*
    for (unsigned int i = 0; i < optimizer->vertices().size(); ++i)
    {
        AIS::PoseGraph3D::Vertex* v = optimizer->vertex(i);
        cout << "i: " << i << " con id " << v->id() << endl;
        if(idNode == v->id())
        {
                transformation = hogman2Eigen(v->transformation);
                return transformation;
        }
    }    
    cout << "no puede ser" << endl;
    exit(-1);*/
    AIS::PoseGraph3D::Vertex* v = optimizer->vertex(idNode);
    transformation = hogman2Eigen(v->transformation);
    return transformation;
}


bool GraphManager::addEdgeToHogman(AIS::LoadedEdge3D edge, bool largeEdge) 
{
    AIS::PoseGraph3D::Vertex* v1 = optimizer->vertex(edge.id1);
    AIS::PoseGraph3D::Vertex* v2 = optimizer->vertex(edge.id2);   
    
    if (!v1) 
    {
        cout << "Añadiendo V1: " << edge.id1 << endl;
        v1 = optimizer->addVertex(edge.id1, Transformation3(), Matrix6::eye(1.0));
        assert(v1);
    } 
    if (!v2) 
    {
        cout << "Añadiendo V2: " << edge.id2 << endl;
        v2 = optimizer->addVertex(edge.id2, Transformation3(), Matrix6::eye(1.0));
        assert(v2);
    }    
    optimizer->addEdge(v1, v2, edge.mean, edge.informationMatrix);
    
    /*
    std::clock_t starttime=std::clock();
    freshlyOptimized_ = false;

    AIS::PoseGraph3D::Vertex* v1 = optimizer_->vertex(edge.id1);
    AIS::PoseGraph3D::Vertex* v2 = optimizer_->vertex(edge.id2);


    // at least one vertex has to be created, assert that the transformation
    // is large enough to avoid to many vertices on the same spot
    if (!v1 || !v2){
        if (!largeEdge) {
            ROS_INFO("Edge to new vertex is to short, vertex will not be inserted");
            return false; 
        }
    }

    if (!v1) {
        v1 = optimizer_->addVertex(edge.id1, Transformation3(), Matrix6::eye(1.0));
        assert(v1);
    }
    if (!v2) {
        v2 = optimizer_->addVertex(edge.id2, Transformation3(), Matrix6::eye(1.0));
        assert(v2);
    }
    optimizer_->addEdge(v1, v2, edge.mean, edge.informationMatrix);
    ROS_INFO_STREAM_COND_NAMED(( (std::clock()-starttime) / (double)CLOCKS_PER_SEC) > ParameterServer::instance()->get<double>("min_time_reported"), "timings", "function runtime: "<< ( std::clock() - starttime ) / (double)CLOCKS_PER_SEC  <<"sec");
    */
    return true;
    
}

Eigen::Matrix4f GraphManager::hogman2Eigen(const Transformation3 hogman_trans) 
{
    _Matrix< 4, 4, double > mat = hogman_trans.toMatrix(); //_Matrix< 4, 4, double >
    QMatrix4x4 m( static_cast<qreal*>( mat[0] )  );
    Eigen::Matrix4f result;
    
    result << m(0,0), m(0,1),m(0,2),m(0,3),
              m(1,0), m(1,1),m(1,2),m(1,3),
              m(2,0), m(2,1),m(2,2),m(2,3),
              m(3,0), m(3,1),m(3,2),m(3,3);
    return result;
}

Transformation3 GraphManager::eigen2Hogman(const Eigen::Matrix4f eigen_mat)
{
  Eigen::Affine3f eigen_transform(eigen_mat);
  Eigen::Quaternionf eigen_quat(eigen_transform.rotation());
  Vector3 translation(eigen_mat(0, 3), eigen_mat(1, 3), eigen_mat(2, 3));
  Quaterniondd rotation(eigen_quat.x(), eigen_quat.y(), eigen_quat.z(),
      eigen_quat.w());
  Transformation3 result(translation, rotation);

  return result;
}


bool GraphManager::isBigTransformation(const Eigen::Matrix4f& t)
{
    double roll, pitch, yaw, dist;

    mat2RPY(t, roll,pitch,yaw);
    mat2dist(t, dist);

    roll = roll/M_PI*180;
    pitch = pitch/M_PI*180;
    yaw = yaw/M_PI*180;

    double max_angle = max(roll,max(pitch,yaw));

    cout << "Dist: " << dist << "; max_angle: " << max_angle << endl;
    return true;
    // at least 10cm or 5deg
    //return (dist > ParameterServer::instance()->get<double>("min_translation_meter")
    //		|| max_angle > ParameterServer::instance()->get<int>("min_rotation_degree"));    
}

///Get the norm of the translational part of an affine matrix (Helper for isBigTransformation)
void GraphManager::mat2dist(const Eigen::Matrix4f& t, double &dist)
{
    dist = sqrt(t(0,3)*t(0,3)+t(1,3)*t(1,3)+t(2,3)*t(2,3));
}
///Get euler angles from affine matrix (helper for isBigTransformation)
void GraphManager::mat2RPY(const Eigen::Matrix4f& t, double& roll, double& pitch, double& yaw) 
{
    roll = atan2(t(2,1),t(2,2));
    pitch = atan2(-t(2,0),sqrt(t(2,1)*t(2,1)+t(2,2)*t(2,2)));
    yaw = atan2(t(1,0),t(0,0));
}

void GraphManager::clear()
{
    graph.clear();
        int numLevels = 3;
    int nodeDistance = 2;
    optimizer = shared_ptr<AIS::HCholOptimizer3D>(new AIS::HCholOptimizer3D(numLevels, nodeDistance));
    
}