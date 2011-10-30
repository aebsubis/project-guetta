/*
 * File:   Guetta.cpp
 * Author: jose
 *
 * Created on 11 de octubre de 2011, 11:25
 */

#include "Guetta.h"

Guetta::Guetta() {
    widget.setupUi(this);
    
    // Creamos los visualizadores
    viewers.resize(5);
    for(int i = 0; i < 5; i++)
        viewers[i] = new Viewer(this,i);
    acumular = false;
    connect(widget.radioButton_sift,SIGNAL(clicked()),this,SLOT(changeKeyPointMethod()));
    connect(widget.radioButton_narf,SIGNAL(clicked()),this,SLOT(changeKeyPointMethod()));
    connect(widget.radioButton_surf,SIGNAL(clicked()),this,SLOT(changeKeyPointMethod()));
    connect(widget.pushButton_cambiar,SIGNAL(clicked()),this,SLOT(changeOptions()));
    connect(widget.comboBox1,SIGNAL(currentIndexChanged(QString)),this,SLOT(changeCloud1(QString)));
    connect(widget.comboBox2,SIGNAL(currentIndexChanged(QString)),this,SLOT(changeCloud2(QString)));
    connect(widget.checkBox_acumular,SIGNAL(clicked()),this,SLOT(changeAcumular()));
    connect(widget.pushButton_procesar,SIGNAL(clicked()),this,SLOT(procesarClouds()));
            
    //connect(widget.comboBox1,SIGNAL(currentIndexChangeg(QString),this,SLOT(changeCloud1
    maxDistanceSIFT = 20000;
    maxKeyPointsAlineamientoSIFT = 7;
    maxKeyPointsSIFT = 1000;
    maxDistanceSURF = 0.01;
    string aux = boost::lexical_cast<std::string>(maxKeyPointsAlineamientoSIFT);
    widget.lineEdit__maxKeyPointsAlineamiento->setText(QString::fromStdString(aux));    
    aux = boost::lexical_cast<std::string>(maxDistanceSIFT);
    widget.lineEdit_maxDistancia->setText(QString::fromStdString(aux));   
    aux = boost::lexical_cast<std::string>(maxKeyPointsSIFT);
    widget.lineEdit_maxKeyPoints->setText(QString::fromStdString(aux)); 
    //widget.lineEdit_maxDistancia->setText(QString::fromStdString(GuettaFeatures::GetInstance()->maxDistanceSIFT));
    //widget.lineEdit_maxDescriptores->setText(QString::fromStdString(GuettaFeatures::GetInstance()->maxKeyPointsSIFT));
    
    //connect(widget.comboBox2,SIGNAL(currentIndexChanged(QString)),this,SLOT(changeCloud2(QString)));
    //widget.gridLayout->addWidget(new Viewer(this),0,0);
    countSelection = 0;
    previousPoint = NULL;
    // Cargamos todas las nubes

    loadClouds();
    

    
    widget.gridLayout->addWidget(viewers[0],0,0);
    widget.gridLayout->addWidget(viewers[1],0,1);
    widget.gridLayout->addWidget(viewers[2],1,0);
    widget.gridLayout->addWidget(viewers[3],1,1);

    widget.gridLayout_2->addWidget(viewers[4],0,0);
    
    widget.gridLayout_3->addWidget(new GuettaCapture());
    
    cloud1 = "cloud2";
    cloud2 = "cloud1";

    viewers[0]->unselectables.insert(viewers[0]->unselectables.end(),new GuettaCloud(pclClouds[cloud1]));
    viewers[1]->unselectables.insert(viewers[1]->unselectables.end(),new GuettaCloud(pclClouds[cloud2]));
    
    GuettaCloud* narfFeatures1 = GuettaFeatures::GetInstance()->getNARFkeypoints(pclClouds[cloud1],RGB(1,0,0));
    viewers[0]->selectables.insert(viewers[0]->selectables.end(),narfFeatures1);
    viewers[2]->selectables.insert(viewers[2]->selectables.end(),narfFeatures1);
    GuettaCloud* narfFeatures2 = GuettaFeatures::GetInstance()->getNARFkeypoints(pclClouds[cloud2],RGB(0,1,0));
    viewers[1]->selectables.insert(viewers[1]->selectables.end(),narfFeatures2);
    viewers[2]->selectables.insert(viewers[2]->selectables.end(),narfFeatures2);
    
    GuettaICP* guettaIcp = GuettaICP::GetInstance();
    guettaIcp->setInputTarget(viewers[1]->selectables[0]);
    guettaIcp->setInputCloud(viewers[2]->selectables[0]);
    
    
    Eigen::Matrix4f transformation_matrix;
    GuettaCloud* icp = guettaIcp->compute(transformation_matrix,maxKeyPointsAlineamientoSIFT,maxDistanceSIFT);
    viewers[3]->unselectables.insert(viewers[3]->unselectables.end(),icp);
    viewers[3]->unselectables.insert(viewers[3]->unselectables.end(),viewers[2]->selectables[0]);
    
   
    //viewers[0]->selectables.insert(viewers[0]->unselectables.end(),cloud1);
    /*
    viewPorts[0]->setPclCloud(pclClouds["cloud0"]);
    viewPorts[1]->setPclCloud(pclClouds["cloud1"]);

    
    
    
    vector<GuettaKeyPoint> keyPoints1 = viewPorts[0]->getNarfKeyPoints();
    vector<GuettaKeyPoint> keyPoints2 = viewPorts[1]->getNarfKeyPoints();
    //keyPoints1.resize(keyPoints1.size()+keyPoints2.size());

    for(int i = 0; i < keyPoints2.size(); i++)
    {
        keyPoints2[i].r = 0;
        keyPoints2[i].g = 1;
        keyPoints1.insert(keyPoints1.end(),keyPoints2[i]);
    }
    
    
    viewPorts[2]->setGuettaCloud(keyPoints1);
    
    widget.gridLayout->addWidget(viewPorts[0],0,0);
    widget.gridLayout->addWidget(viewPorts[1],0,1);
    //widget.gridLayout->addWidget(new newForm(),0,0);
    //widget.gridLayout->addWidget(new newForm(),0,1);
    widget.gridLayout->addWidget(viewPorts[2],1,0);
    //widget.gridLayout->addWidget(new newForm(),1,1);
     */
    
}

void Guetta::changeOptions()
{
    float aux = widget.lineEdit__maxKeyPointsAlineamiento->text().toFloat();
    maxKeyPointsAlineamientoSIFT = aux;
    aux = widget.lineEdit_maxDistancia->text().toFloat();
    cout << "aux: " << aux << endl;
    maxDistanceSIFT = aux;
    changeKeyPointMethod();
    //string maxKeyPointsAlineamientoSIFT = boost::lexical_cast<std::string>(GuettaFeatures::GetInstance()->maxKeyPointsAlineamientoSIFT);
    //widget.lineEdit__maxKeyPointsAlineamiento->setText(QString::fromStdString(maxKeyPointsAlineamientoSIFT));   
}

Guetta::~Guetta() {
}

void Guetta::procesarClouds()
{
    cout << "Procesando clouds" << endl;
    // Cargamos todos los clouds del directorio
    loadClouds(widget.lineEdit_directorio->text().toStdString());
    

    string prefijo = widget.lineEdit_directorio->text().toStdString() + "/";
    GuettaCloud* cloud1 = new GuettaCloud(pclClouds[prefijo+"cloud0"]);
    GuettaCloud* cloud2 = new GuettaCloud(pclClouds[prefijo+"cloud1"]);
    GuettaCloud* features1 = GuettaFeatures::GetInstance()->getSIFTkeypoints(pclClouds[prefijo+"cloud0"],prefijo+"cloud0",RGB(1,0,0));
    GuettaCloud* features2 = GuettaFeatures::GetInstance()->getSIFTkeypoints(pclClouds[prefijo+"cloud1"],prefijo+"cloud1",RGB(0,1,0));
    GuettaCloud* resultado = emparejar(cloud1,cloud2,features1,features2);
    
}

GuettaCloud* Guetta::emparejar(GuettaCloud* cloud1, GuettaCloud* cloud2, GuettaCloud* features1, GuettaCloud* features2)
{
      
    GuettaICP* guettaIcp = GuettaICP::GetInstance();
    guettaIcp->setInputTarget(features2);
    guettaIcp->setInputCloud(features1);
    
    // Mostramos los descrptiores seleccionados
    GuettaCloud* guettaCloud1 = new GuettaCloud();
    GuettaCloud* guettaCloud2 = new GuettaCloud();
    guettaIcp->getNearestDescriptors(maxKeyPointsAlineamientoSIFT,maxDistanceSIFT,guettaCloud1,guettaCloud2);
    //viewers[0]->selectables[0] = guettaCloud1;
    //viewers[1]->selectables[0] = guettaCloud2;  
    GuettaTime timer;
    timer.start();
    Ramsac ramsac(guettaCloud1,guettaCloud2);
    ramsac.compute(0,"");
    //cout << "mejor combinacion: " << ramsac.mejorCombinacion;
    cout << "menorDistancia: " << ramsac.menorDistancia << endl;
    cout << "tiempo ramsac: " << timer.stop() << " ms" << endl;  
    
    Eigen::Matrix4f transformation_matrix;
    GuettaCloud* resultado = new GuettaCloud();
    float distancia = ramsac.getDistanciaTotal(guettaCloud2, ramsac.mejorCombinacion, guettaCloud1, ramsac.mejorCombinacion, resultado, transformation_matrix);
    //viewers[4]->selectables.insert(viewers[4]->selectables.end(),resultado);
    //viewers[4]->selectables.insert(viewers[4]->selectables.end(),guettaCloud1);  

    PointCloud<PointXYZRGB>::Ptr cloudTransformed (new PointCloud<PointXYZRGB>);
    transformPointCloud (*cloud2->pointCloud, *cloudTransformed, transformation_matrix);  
    
    resultado = new GuettaCloud(cloudTransformed);
    viewers[4]->unselectables.insert(viewers[4]->unselectables.end(),new GuettaCloud(cloud1->pointCloud)); 
    viewers[4]->unselectables.insert(viewers[4]->unselectables.end(),resultado);
        
    return resultado;
   // PointCloud<PointXYZRGB>::Ptr cloudTransformed (new PointCloud<PointXYZRGB>);
   // transformPointCloud (*pclClouds[cloud2], *cloudTransformed, transformation_matrix);    
        
}

void Guetta::changeCloud1(QString cloud)
{
    
    if(viewers[0]->unselectables.size() > 0)
    {
        cloud1 = cloud.toStdString();
    viewers[0]->unselectables[0] = new GuettaCloud(pclClouds[cloud.toStdString()]);  
    viewers[0]->updateGL();
    }
}

void Guetta::changeCloud2(QString cloud)
{
    
     //viewPorts[1]->setPclCloud(pclClouds[cloud.toStdString()]);
    if(viewers[1]->unselectables.size() > 0)
    {
         cloud2 = cloud.toStdString();
     viewers[1]->unselectables[0] = new GuettaCloud(pclClouds[cloud.toStdString()]);  
       
    viewers[1]->updateGL();  
    }
}

void Guetta::changeAcumular()
{
    acumular = widget.checkBox_acumular->isChecked();
}

float Guetta::getDistanciaTotal(GuettaCloud* guettaCloud1, vector<int> indicesGuettaCloud1,GuettaCloud* guettaCloud2, vector<int> indicesGuettaCloud2, GuettaCloud* resultado)
{
    Eigen::Matrix4f transformation_matrix;
    estimateRigidTransformationSVD(*guettaCloud1->getPointCloud(), indicesGuettaCloud1, *guettaCloud2->getPointCloud(), indicesGuettaCloud2, transformation_matrix);   
    
    cout << "Matriz: " << endl << transformation_matrix << endl;

    PointCloud<PointXYZRGB>::Ptr cloud3 (new PointCloud<PointXYZRGB>);
    transformPointCloud (*(guettaCloud1->getPointCloud()), *cloud3, transformation_matrix);
    
       // Creamos el guettaCloud 
    //GuettaCloud* guettaCloud = new GuettaCloud();
    resultado->data.resize(cloud3->points.size());
    for(int i = 0; i < cloud3->points.size(); i++)
    {
        PointXYZRGB point = cloud3->points[i];
        resultado->data[i] = new GuettaKeyPoint(point.x,point.y,point.z,point.r,point.g,point.b,NULL);
        
    }
    
    float distancia = 0;
    // Calculamos la distancia entre los descriptores
    for(int i = 0; i < indicesGuettaCloud1.size(); i++)
    {
        GuettaKeyPoint* p1 = guettaCloud2->data[i];
        GuettaKeyPoint* p2 = resultado->data[i];
        float aux = p1->distanceXYZ(p2);
        distancia += aux;
        cout << "Distancia.: " << aux << endl;
    }
    cout << "Distancia total: " << distancia << endl;    
    return distancia;
}

void Guetta::changeKeyPointMethod()
{
    float maxDistance = 0;
    GuettaCloud* features1;
    GuettaCloud* features2;
    if(widget.radioButton_sift->isChecked())
    {
        // Sift
        cout << "sift" << endl;
        features1 = GuettaFeatures::GetInstance()->getSIFTkeypoints(pclClouds[cloud1],cloud1,RGB(1,0,0));
        features2 = GuettaFeatures::GetInstance()->getSIFTkeypoints(pclClouds[cloud2],cloud2,RGB(0,1,0));
        maxDistance = maxDistanceSIFT;
    }
    if(widget.radioButton_narf->isChecked())
    {    
        // Narf
        cout << "narf" << endl;
        features1 = GuettaFeatures::GetInstance()->getNARFkeypoints(pclClouds[cloud1],RGB(1,0,0));
        features2 = GuettaFeatures::GetInstance()->getNARFkeypoints(pclClouds[cloud2],RGB(0,1,0));
    }
    if(widget.radioButton_surf->isChecked())
    {       
        // Surf
        cout << "surf" << endl;
        features1 = GuettaFeatures::GetInstance()->getSURFkeypoints(pclClouds[cloud1],cloud1,RGB(1,0,0));
        features2 = GuettaFeatures::GetInstance()->getSURFkeypoints(pclClouds[cloud2],cloud2,RGB(0,1,0));   
        maxDistance = maxDistanceSURF;
    }
    
    GuettaICP* guettaIcp = GuettaICP::GetInstance();
    guettaIcp->setInputTarget(features2);
    guettaIcp->setInputCloud(features1);
    
    // Mostramos los descrptiores seleccionados
    GuettaCloud* guettaCloud1 = new GuettaCloud();
    GuettaCloud* guettaCloud2 = new GuettaCloud();
    guettaIcp->getNearestDescriptors(maxKeyPointsAlineamientoSIFT,maxDistance,guettaCloud1,guettaCloud2);
    viewers[0]->selectables[0] = guettaCloud1;
    viewers[1]->selectables[0] = guettaCloud2;
  
    GuettaTime timer;
    timer.start();
    Ramsac ramsac(guettaCloud1,guettaCloud2);
    ramsac.compute(0,"");
    //cout << "mejor combinacion: " << ramsac.mejorCombinacion;
    cout << "menorDistancia: " << ramsac.menorDistancia << endl;
    cout << "tiempo ramsac: " << timer.stop() << " ms" << endl;
    
Eigen::Matrix4f transformation_matrix;
        GuettaCloud* resultado = new GuettaCloud();
    float distancia = ramsac.getDistanciaTotal(guettaCloud2, ramsac.mejorCombinacion, guettaCloud1, ramsac.mejorCombinacion, resultado, transformation_matrix);
      viewers[2]->selectables[0] = resultado;
    viewers[2]->selectables[1] = guettaCloud1;  
    
    
        PointCloud<PointXYZRGB>::Ptr cloudTransformed (new PointCloud<PointXYZRGB>);
        transformPointCloud (*pclClouds[cloud2], *cloudTransformed, transformation_matrix);    
    
    if(acumular == true)
    {
        cout << "hola1" << endl;
        viewers[3]->unselectables.insert(viewers[3]->unselectables.end(), new GuettaCloud(cloudTransformed));
        //viewers[3]->unselectables.insert(viewers[3]->unselectables.end(),viewers[0]->unselectables[0]);
    }
    else
    {
        //viewers[3]->unselectables.insert(viewers[3]->unselectables.end(),new GuettaCloud(cloudTransformed);
     viewers[3]->unselectables[0] = new GuettaCloud(cloudTransformed);
    viewers[3]->unselectables[1] = viewers[0]->unselectables[0];       
        
    }
    /*
    
    
    vector<int> indicesInputTarget;
    vector<int> indicesInputCloud;   
    for(int i = 0; i < guettaCloud1->data.size(); i++)
    {
        indicesInputCloud.insert(indicesInputCloud.end(),i);
        indicesInputTarget.insert(indicesInputTarget.end(),i);
    }
    
    GuettaCloud* resultado = new GuettaCloud();
    float distancia = getDistanciaTotal(guettaCloud1, indicesInputTarget, guettaCloud2, indicesInputCloud, resultado);*/
   // cout << "Distancia total: " << distancia << endl;
    /*
    Eigen::Matrix4f transformation_matrix;
    estimateRigidTransformationSVD(*guettaCloud1->getPointCloud(), indicesInputTarget, *guettaCloud2->getPointCloud(), indicesInputCloud, transformation_matrix);   
    
    cout << "Matriz: " << endl << transformation_matrix << endl;

    PointCloud<PointXYZRGB>::Ptr cloud3 (new PointCloud<PointXYZRGB>);
    transformPointCloud (*(guettaCloud1->getPointCloud()), *cloud3, transformation_matrix);
    
       // Creamos el guettaCloud 
    GuettaCloud* guettaCloud = new GuettaCloud();
    guettaCloud->data.resize(cloud3->points.size());
    for(int i = 0; i < cloud3->points.size(); i++)
    {
        PointXYZRGB point = cloud3->points[i];
        guettaCloud->data[i] = new GuettaKeyPoint(point.x,point.y,point.z,point.r,point.g,point.b,NULL);
        
    }
    
    float distancia = 0;
    // Calculamos la distancia entre los descriptores
    for(int i = 0; i < indicesInputCloud.size(); i++)
    {
        GuettaKeyPoint* p1 = guettaCloud->data[i];
        GuettaKeyPoint* p2 = guettaCloud2->data[i];
        float aux = p1->distanceXYZ(p2);
        distancia += aux;
        cout << "Distancia: " << aux << endl;
    }
    cout << "Distancia total: " << distancia << endl;
    */
    
    //viewers[2]->selectables[0] = resultado;
    //viewers[2]->selectables[1] = guettaCloud2;   
    /*
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
     */

    /*
    GuettaICP* guettaIcp = GuettaICP::GetInstance();
    
     guettaIcp->setInputTarget(viewers[1]->selectables[0]);
     
    if(acumular == true)
    {
        cout << "Bien, entra" << endl;
        // Añadimos el pointCloud anterior
        guettaIcp->setInputCloud(viewers[2]->selectables[0]);    
        cout << viewers[2]->selectables[0]->data.size() << endl;
    }
    else
        guettaIcp->setInputCloud(viewers[0]->selectables[0]);
     
     
     // void GuettaICP::getNearestDescriptors(int maxKeyPointsAlineamiento, float maxDistance, GuettaCloud* cloud1, GuettaCloud* cloud2)
      
      
      
 
     
     // Mostramos los descrptiores seleccionados
     GuettaCloud* guettaCloud1 = new GuettaCloud();
     GuettaCloud* guettaCloud2 = new GuettaCloud();
     guettaIcp->getNearestDescriptors(maxKeyPointsAlineamientoSIFT,maxDistanceSIFT,guettaCloud1,guettaCloud2);
     viewers[0]->selectables[0] = guettaCloud1;
     viewers[1]->selectables[0] = guettaCloud2;
     
     
    Eigen::Matrix4f transformation_matrix;
    GuettaCloud* icp = guettaIcp->compute(transformation_matrix,maxKeyPointsAlineamientoSIFT,maxDistanceSIFT);
    

    //viewers[2]->selectables[0] = icp;

    viewers[2]->selectables[1] = viewers[0]->selectables[0];

    PointCloud<PointXYZRGB>::Ptr cloudTransformed (new PointCloud<PointXYZRGB>);
    transformPointCloud (*pclClouds[cloud2], *cloudTransformed, transformation_matrix);      
    cout << transformation_matrix << endl;
  

    
      //viewers[3]->unselectables[0] = new GuettaCloud(cloudTransformed);
   // viewers[3]->unselectables[1] = viewers[0]->unselectables[0];      
     
    
    
    
    if(acumular == true)
    {
        cout << "hola1" << endl;
        viewers[3]->unselectables.insert(viewers[3]->unselectables.end(), new GuettaCloud(cloudTransformed));
        //viewers[3]->unselectables.insert(viewers[3]->unselectables.end(),viewers[0]->unselectables[0]);
    }
    else
    {
     viewers[3]->unselectables[0] = new GuettaCloud(cloudTransformed);
    viewers[3]->unselectables[1] = viewers[0]->unselectables[0];       
        
    }
    
      
     // Mostramos los descrptiores seleccionados
     GuettaCloud* guettaCloud1 = new GuettaCloud();
     GuettaCloud* guettaCloud2 = new GuettaCloud();
     guettaIcp->getNearestDescriptors(maxKeyPointsAlineamientoSIFT,maxDistanceSIFT,guettaCloud1,guettaCloud2);
     viewers[0]->selectables[0] = guettaCloud1;
     viewers[1]->selectables[0] = guettaCloud2;
     
       
    cout << "sa" << endl;
    */
    
    viewers[0]->updateGL();
    viewers[1]->updateGL();
    viewers[2]->updateGL();    
    viewers[3]->updateGL(); 
}

void Guetta::selectedKeyPoint(int idPoint, int idViewport)
{
    string keyPoint = "";

    GuettaCloud* cloud = viewers[idViewport]->selectables[0];
    cout << "Hay: " << viewers[idViewport]->selectables[0]->data.size() << endl;
    GuettaKeyPoint* point = cloud->data[idPoint];
  
    keyPoint = boost::lexical_cast<string>(convert(point->x)) + " , " +
      boost::lexical_cast<string>(convert(point->y)) + " , " +
      boost::lexical_cast<string>(convert(point->z));
 
    switch(countSelection)
    { 
        case 0:
        {
            widget.lineEdit_keyPoint1->setText(QString::fromStdString(keyPoint));
            previousPoint = point;
            countSelection++;
            break;
        }
        case 1:
        {
            widget.lineEdit_keyPoint2->setText(QString::fromStdString(keyPoint));
            countSelection++;
            // Calculamos la distanciaXYZ
            float distance = point->distanceXYZ(previousPoint);
            string strDistance = boost::lexical_cast<std::string>(distance);
            widget.lineEdit_distanceXYZ->setText(QString::fromStdString(strDistance));
            // Calculamos la distancia con el descritor
            distance = point->distanceDescriptor(previousPoint);
            strDistance = boost::lexical_cast<std::string>(distance);
            widget.lineEdit_distanceDescriptor->setText(QString::fromStdString(strDistance));

            break;
        }
        case 2:
        {
            widget.lineEdit_keyPoint1->clear();
            widget.lineEdit_keyPoint2->clear();
            widget.lineEdit_distanceXYZ->clear();
            widget.lineEdit_distanceDescriptor->clear();
            widget.lineEdit_keyPoint1->setText(QString::fromStdString(keyPoint));
            previousPoint = point;
            countSelection = 1;
            break;
        }
    }
    
   
    
    
    int idViewport2 = 0;
    if(idViewport == 0)
        idViewport2 = 1;
    
    GuettaCloud* cloud2 = viewers[idViewport2]->selectables[0];
    vector<int> nearest = point->getNearestDescriptor(cloud2->data);
    
    
     /*
    for (int i = 0; i < cloud2->data.size(); i++)
    {
        cloud2->data[i]->r = 0;
        cloud2->data[i]->g = 1;
        cloud2->data[i]->b = 0;
    }*/
    /*
      cout << "bien1" << endl;
    // Cambimaos el color
    cloud2->data[nearest.back()]->r = 0;
    cloud2->data[nearest.back()]->g = 0;
    cloud2->data[nearest.back()]->b = 1;
    nearest.pop_back();
    cloud2->data[nearest.back()]->r = 1;
    cloud2->data[nearest.back()]->g = 0;
    cloud2->data[nearest.back()]->b = 0;
    nearest.pop_back();
    cloud2->data[nearest.back()]->r = 1;
    cloud2->data[nearest.back()]->g = 1;
    cloud2->data[nearest.back()]->b = 1;
    nearest.pop_back();
    cloud2->data[nearest.back()]->r = 1;
    cloud2->data[nearest.back()]->g = 1;
    cloud2->data[nearest.back()]->b = 0;
    nearest.pop_back();
    cloud2->data[nearest.back()]->r = 1;
    cloud2->data[nearest.back()]->g = 0;
    cloud2->data[nearest.back()]->b = 1;*/
 
    viewers[idViewport2]->updateGL();
    /*
    // Buscamos los descriptores mas cercanos en el otro cloud
    vector<GuettaKeyPoint> keyPoints1 = viewPorts[idViewport]->getNarfKeyPoints();
    int idViewport2 = 0;
    if(idViewport == 0)
        idViewport2 = 1;
    vector<GuettaKeyPoint> keyPoints2 = viewPorts[idViewport2]->getNarfKeyPoints();
    // Obtenemos el keyPoint a comparar
    GuettaKeyPoint keyPoint = keyPoints1[idPoint];
    cout << keyPoint.x << endl;
    int nearest = keyPoint.getNeareastDescriptor(keyPoints2);
    cout << "nearest: " << nearest << endl;
    // Cambimaos el color
    keyPoints2[nearest].b = 1;
    keyPoints2[nearest].r = 0;
    viewPorts[idViewport2]->updateKeyPoints(keyPoints2);*/
}

string Guetta::convert(float value)
{
  stringstream ss;
  ss << setprecision(5);
  ss << value;
  return ss.str();
}

void Guetta::loadClouds(string directorio)
{
    QStringList listClouds;
    for(int i = 0; i <= 2; i++)
    {
        string name = directorio + "/" + "cloud" + boost::lexical_cast<std::string>(i);
        cout << "Cargando " + name << endl;
        pclClouds[name] = loadPCD(name+".pcd");
        //clouds.insert(clouds.end(),loadPCD(name+".pcd"));
        listClouds.append(QString::fromStdString(name));
    }
}

void Guetta::loadClouds()
{
    QStringList clouds;
    for(int i = 0; i <= 2; i++)
    {
        string name = "cloud" + boost::lexical_cast<std::string>(i);
        cout << "Cargando " + name << endl;
        pclClouds[name] = loadPCD(name+".pcd");
        clouds.append(QString::fromStdString(name));
    }

    widget.comboBox1->addItems(clouds);
    widget.comboBox2->addItems(clouds);
}

pcl::PointCloud<pcl::PointXYZRGB>::Ptr Guetta::loadPCD(string name)
{
    PointCloud<PointXYZRGB>::Ptr cloud (new PointCloud<PointXYZRGB>);
    if (loadPCDFile<PointXYZRGB> (name, *cloud) == -1)
    {
            PCL_ERROR ("Couldn't read file test_pcd.pcd \n");
            exit(1);
    }      
    return cloud;
}