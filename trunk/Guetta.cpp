/*
 * File:   Guetta.cpp
 * Author: jose
 *
 * Created on 11 de octubre de 2011, 11:25
 */

#include <qt4/QtCore/qthread.h>

#include "Guetta.h"

Guetta::Guetta() {
    widget.setupUi(this);
    /*
   QGLContext* p = new QGLContext(QGLFormat::defaultFormat());
        p->create();
        p->makeCurrent();
      */ 
        cout << "holaaaa" << endl;
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
    connect(widget.pushButton_seleccionarDirectorio,SIGNAL(clicked()),this,SLOT(seleccionarDirectorio()));
    
    connect(widget.pushButton_allselect,SIGNAL(clicked()),this,SLOT(seleccionarTodos()));
    connect(widget.pushButton_allunselect,SIGNAL(clicked()),this,SLOT(deseleccionarTodos()));
    connect(widget.spinBox_incremento,SIGNAL(valueChanged(int)),this,SLOT(cambiarIncremento(int)));
      
    connect(widget.checkBox_showKeypoints,SIGNAL(clicked()),this,SLOT(changeShowKeypoints()));
    
    
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
    
    cloud1 = "cloud0";
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
    

    widget.tableWidget_clouds->setRowCount(60);
  drawKeyPoints = false;



}

void Guetta::changeShowKeypoints()
{
    drawKeyPoints = widget.checkBox_showKeypoints->isChecked();
}

void Guetta::seleccionarTodos()
{
    /*
    int total = widget.lineEdit_total->text().toInt();
    for(int i = 0; i < total; i++)
    {
        QTableWidgetItem *item = widget.tableWidget_clouds->item(i,0);
        item->setCheckState(Qt::Checked);
    } */
    //viewers[4]->updateGL();
    thread = new MyThread(viewers[4]);
    thread->start();
}

void Guetta::deseleccionarTodos()
{
    int total = widget.lineEdit_total->text().toInt();
    for(int i = 0; i < total; i++)
    {
        QTableWidgetItem *item = widget.tableWidget_clouds->item(i,0);
        item->setCheckState(Qt::Unchecked);
    }     
}

void Guetta::cambiarIncremento(int incremento)
{
    deseleccionarTodos();
    int total = widget.lineEdit_total->text().toInt();
    for(int i = 0; i < total; i += incremento)
    {
        QTableWidgetItem *item = widget.tableWidget_clouds->item(i,0);
        item->setCheckState(Qt::Checked);
    }     
}

void Guetta::changeOptions()
{
    float aux = widget.lineEdit__maxKeyPointsAlineamiento->text().toFloat();
    maxKeyPointsAlineamientoSIFT = aux;
    aux = widget.lineEdit_maxDistancia->text().toFloat();
    maxDistanceSIFT = aux;
    changeKeyPointMethod(); 
}

Guetta::~Guetta() 
{
    // Liberamos la memoria de todos los guettaClouds
    //for(int i = 0; i < 5; i++)
    //{
    //    if(viewers[4] != NULL)
    //        delete viewers[4];
    //}
    //viewers.clear();
}

int Guetta::getNextCloud(int actualIndex)
{
    int total = widget.lineEdit_total->text().toInt();
    for(int i = actualIndex+1; i < total; i++)
    {
        QTableWidgetItem *item = widget.tableWidget_clouds->item(i,0);
        if(item->checkState() == Qt::Checked)
            return i;
    }
    return -1;
}

void Guetta::seleccionarDirectorio()
{
    // Cargamos todos los clouds del directorio
    loadClouds(widget.lineEdit_directorio->text().toStdString());
}

void Guetta::procesarClouds()
{
    cout << "Procesando clouds" << endl;

    // Eliminamos los clouds anteriores
    for(int i = 0; i < viewers[4]->unselectables.size(); i++)
    {
        if(viewers[4]->unselectables[i] != NULL)
                delete viewers[4]->unselectables[i];
    }
    viewers[4]->unselectables.clear();
    
     for(int i = 0; i < viewers[4]->selectables.size(); i++)
    {
        if(viewers[4]->selectables[i] != NULL)
                delete viewers[4]->selectables[i];
    }
    viewers[4]->selectables.clear();
    
    string prefijo = widget.lineEdit_directorio->text().toStdString() + "/";
    int actualIndex = -1;
    actualIndex = getNextCloud(actualIndex);
    
    string nameCloud1 = widget.tableWidget_clouds->item(actualIndex,1)->text().toStdString();
    GuettaCloud* cloud1 = new GuettaCloud(pclClouds[nameCloud1]);
    
    actualIndex = getNextCloud(actualIndex);
    string nameCloud2 = widget.tableWidget_clouds->item(actualIndex,1)->text().toStdString();
    GuettaCloud* cloud2 = new GuettaCloud(pclClouds[nameCloud2]);
    
    GuettaCloud* features1 = GuettaFeatures::GetInstance()->getSIFTkeypoints(pclClouds[nameCloud1],prefijo+nameCloud1,RGB(1,0,0));
    GuettaCloud* features2 = GuettaFeatures::GetInstance()->getSIFTkeypoints(pclClouds[nameCloud2],prefijo+nameCloud2,RGB(0,1,0));
    Eigen::Matrix4f transformation = emparejar(true,cloud1,cloud2,features1,features2);
    
    GuettaCloud* cloudResultado = transform(cloud2, transformation);
    GuettaCloud* featuresResultado = transform(features2, transformation);
  
    if(drawKeyPoints == false)
    {
        viewers[4]->unselectables.insert(viewers[4]->unselectables.end(),cloud1);
        viewers[4]->unselectables.insert(viewers[4]->unselectables.end(),cloudResultado);
    }
    else
    {
        viewers[4]->unselectables.insert(viewers[4]->unselectables.end(),features1);
        viewers[4]->unselectables.insert(viewers[4]->unselectables.end(),featuresResultado);
    }
    
    cout << transformation << endl;
    double roll = atan2(transformation(2,1),transformation(2,2));
    double pitch = atan2(-transformation(2,0),sqrt(transformation(2,1)*transformation(2,1)+transformation(2,2)*transformation(2,2)));
    double yaw = atan2(transformation(1,0),transformation(0,0));
    roll = roll/M_PI*180;
    pitch = pitch/M_PI*180;
    yaw = yaw/M_PI*180;
    double dist = sqrt(transformation(0,3)*transformation(0,3)+transformation(1,3)*transformation(1,3)+transformation(2,3)*transformation(2,3));
    cout << roll << ";" << pitch << ";" << yaw << ";" << dist << endl;
    
    int total = widget.lineEdit_total->text().toInt();
    for(int i = 2; i < total; i++)
    {
        actualIndex = getNextCloud(actualIndex);
        if(actualIndex == -1)
            break;
        string nameCloud = widget.tableWidget_clouds->item(actualIndex,1)->text().toStdString();
        features1 = featuresResultado; 
        float aux = (rand() % 255)/255.0;

        features2 = GuettaFeatures::GetInstance()->getSIFTkeypoints(pclClouds[nameCloud],prefijo+nameCloud,RGB(0,0,0.9));
        cloud1 = cloudResultado;
        cloud2 = new GuettaCloud(pclClouds[nameCloud]);
        
        transformation = emparejar(true,cloud1,cloud2,features1,features2);
        
        cout << transformation << endl;
        double roll = atan2(transformation(2,1),transformation(2,2));
        double pitch = atan2(-transformation(2,0),sqrt(transformation(2,1)*transformation(2,1)+transformation(2,2)*transformation(2,2)));
        double yaw = atan2(transformation(1,0),transformation(0,0));
        roll = roll/M_PI*180;
        pitch = pitch/M_PI*180;
        yaw = yaw/M_PI*180;
        double dist = sqrt(transformation(0,3)*transformation(0,3)+transformation(1,3)*transformation(1,3)+transformation(2,3)*transformation(2,3));
        cout << roll << ";" << pitch << ";" << yaw << ";" << dist << endl;
    
        cloudResultado = transform(cloud2, transformation);
        featuresResultado = transform(features2, transformation);
        if(drawKeyPoints == false)
        {
            viewers[4]->unselectables.insert(viewers[4]->unselectables.end(),cloudResultado);
        }
        else
        {
            viewers[4]->unselectables.insert(viewers[4]->unselectables.end(),featuresResultado);
        }
        
        //delete cloud1;
        delete cloud2;
        //delete features1;
        //delete features2;
    }
}

GuettaCloud* Guetta::transform(GuettaCloud* guettaCloud, Eigen::Matrix4f transformation_matrix)
{
    PointCloud<PointXYZRGB>::Ptr cloudTransformed (new PointCloud<PointXYZRGB>);
    transformPointCloud (*guettaCloud->getPointCloud(), *cloudTransformed, transformation_matrix);  
    GuettaCloud* resultado = new GuettaCloud(cloudTransformed);
    
    for(int i = 0; i < resultado->data.size(); i++)
    {
        GuettaKeyPoint* guettaPoint = resultado->data[i];
        GuettaKeyPoint* original = guettaCloud->data[i];
        
        if(original->descriptor != NULL)
        {
            guettaPoint->descriptor = new float[128];
            for(int i = 0; i < 128; i++)
                guettaPoint->descriptor[i] = original->descriptor[i];
        }
    }    
    
    return resultado;
}

Eigen::Matrix4f Guetta::emparejar(bool pintar, GuettaCloud* cloud1, GuettaCloud* cloud2, GuettaCloud* features1, GuettaCloud* features2)
{
    GuettaICP* guettaIcp = GuettaICP::GetInstance();
    guettaIcp->setInputTarget(features2);
    guettaIcp->setInputCloud(features1);

    // Mostramos los descrptiores seleccionados
    GuettaCloud* guettaCloud1 = new GuettaCloud();
    GuettaCloud* guettaCloud2 = new GuettaCloud();
    guettaIcp->getNearestDescriptors(maxKeyPointsAlineamientoSIFT,maxDistanceSIFT,guettaCloud1,guettaCloud2);

    GuettaTime timer;
    timer.start();
    Ramsac ramsac(guettaCloud1,guettaCloud2);
    ramsac.compute(0,"");

    cout << "menorDistancia: " << ramsac.menorDistancia << endl;
    cout << "tiempo ramsac: " << timer.stop() << " ms" << endl;  

    return ramsac.transformacion;  
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
    
    viewers[0]->updateGL();
    viewers[1]->updateGL();
    viewers[2]->updateGL();    
    viewers[3]->updateGL(); 
}

void Guetta::selectedKeyPoint(int idPoint, int idViewport)
{
    string keyPoint = "";

    GuettaCloud* cloud = viewers[idViewport]->selectables[0];

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
    
    viewers[idViewport2]->updateGL();

}

string Guetta::convert(float value)
{
  stringstream ss;
  ss << setprecision(5);
  ss << value;
  return ss.str();
}

void Guetta::loadClouds(string path)
{
    QDir dir(QString::fromStdString(path));
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);

    QStringList filters;
    filters << "*.pcd";
    dir.setNameFilters(filters);
     
    QFileInfoList list = dir.entryInfoList();
    int max = widget.lineEdit_maxNubes->text().toInt();
    
    int numClouds = 0;
    for (int i = 0; i < list.size() && numClouds < max; i += 1) 
    {
        QFileInfo fileInfo = list.at(i);
        string name = "test_RGB_" + boost::lexical_cast<std::string>(i);
        cout << "Cargando " + name + ".pcd" << endl;
        pclClouds[name] = loadPCD(path + "/" + name+ ".pcd");
         
        QTableWidgetItem *item1 = new QTableWidgetItem(QString::fromStdString(name));
        widget.tableWidget_clouds->setItem(numClouds, 1, item1);
        QCheckBox* item2 = new QCheckBox();
        QTableWidgetItem *item = new QTableWidgetItem(1);
        item->data(Qt::CheckStateRole);
        item->setCheckState(Qt::Checked);
        widget.tableWidget_clouds->setItem(numClouds, 0, item);
        
        numClouds++;
    }
    widget.tableWidget_clouds->resizeColumnsToContents();
    widget.lineEdit_total->setText(QString::fromStdString(boost::lexical_cast<std::string>(numClouds)));
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