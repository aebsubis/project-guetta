/*
 * File:   newForm.cpp
 * Author: jose
 *
 * Created on 9 de octubre de 2011, 16:21
 */

#include "newForm.h"



newForm::newForm(QWidget* parent, int id) {
    widget.setupUi(this);
    this->id = id;
    //this->setParent(parent);
    
    connect(widget.checkBox_keyPoints,SIGNAL(clicked()),this,SLOT(clickedShowKeyPoints()));
    
    QObject::connect(this, SIGNAL(selectedKeyPoint(int,int)),parent, SLOT(selectedKeyPoint(int,int)));
    
    //GLWidget* glWidget = new GLWidget(this);
    StandardCamera* sc = new StandardCamera();
    glWidget = new Viewer(sc,this);
    widget.verticalLayout->addWidget(glWidget);


    
   // pclCloud = loadPCD("imagen0.pcd");
    
    //guettaCloud = getGuettaCloud(pclCloud);
    
   // glWidget->cloud = this->guettaCloud;
    /*
    cout << "OK" << endl;
    GuettaFeatures* features = GuettaFeatures::GetInstance();
    if(features == NULL)
        cout << "error" << endl;
    vector<GuettaKeyPoint> narfFeatures = features->getNARFkeypoints(cloud);
    glWidget->cloud = narfFeatures;*/
}

void newForm::setPclCloud(PointCloud<PointXYZRGB>::Ptr cloud)
{
    pclCloud = cloud;
    guettaCloud = getGuettaCloud(cloud);
    glWidget->cloud = guettaCloud;
    
    //if(widget.checkBox_keyPoints->isChecked())
    //{
        vector<GuettaKeyPoint> narfFeatures = GuettaFeatures::GetInstance()->getNARFkeypoints(pclCloud);
        glWidget->keyPoints = narfFeatures;   
        keyPoints = narfFeatures;
    //}
    glWidget->updateGL();
}
    
void newForm::clickedShowKeyPoints()
{
    if(widget.checkBox_keyPoints->isChecked())
    {
        vector<GuettaKeyPoint> narfFeatures = GuettaFeatures::GetInstance()->getNARFkeypoints(pclCloud);
        glWidget->keyPoints = narfFeatures;
        keyPoints = narfFeatures;
        glWidget->updateGL();
    }
    else
    {
        glWidget->keyPoints.clear();
        glWidget->updateGL();
    }
}

vector<GuettaKeyPoint> newForm::getNarfKeyPoints()
{
    return keyPoints;
}

vector<GuettaKeyPoint> newForm::getGuettaCloud()
{
    return guettaCloud;
}

void newForm::setGuettaCloud(vector<GuettaKeyPoint> cloud)
{
    this->guettaCloud = cloud;
    glWidget->keyPoints = guettaCloud;
    keyPoints = guettaCloud;
    cout << "total: " << glWidget->keyPoints.size() << endl;
    
    glWidget->updateGL();
}


void newForm::updateKeyPoints(vector<GuettaKeyPoint> keyPoints)
{
    glWidget->keyPoints = keyPoints;
    glWidget->updateGL();
}

newForm::~newForm() 
{
    
}


vector<GuettaKeyPoint> newForm::getGuettaCloud(PointCloud<PointXYZRGB>::Ptr cloud)
{
     vector<GuettaKeyPoint> keyPoints;
     keyPoints.resize(cloud->points.size());

     for(int i = 0; i < cloud->points.size(); i++)
     {
         PointXYZRGB point = cloud->points[i];

         //cout << point.x << "," << point.y << "," << point.z << endl;
         keyPoints[i] = GuettaKeyPoint(point.x,point.y,point.z,point.r,point.g,point.b,NULL);

     }
     return keyPoints;    
}


void newForm::selectedKeyPoint(int idPoint)
{
    emit selectedKeyPoint(idPoint,id);
}
    
void newForm::click()
{
    cout << "click1" << endl;
}