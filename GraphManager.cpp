#include <map>

#include "GraphManager.h"

GraphManager::GraphManager()
{
    int numLevels = 3;
    int nodeDistance = 2;
    optimizer = shared_ptr<AIS::HCholOptimizer3D>(new AIS::HCholOptimizer3D(numLevels, nodeDistance));
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
        // Comparamos el nuevo nodo con todos los nodos del grafo
        
    }
}