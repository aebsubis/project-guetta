/* 
 * File:   newForm.h
 * Author: jose
 *
 * Created on 9 de octubre de 2011, 16:21
 */

#ifndef _NEWFORM_H
#define	_NEWFORM_H

#include "ui_newForm.h"
#include "GLWidget.h"
#include <iostream>
using namespace std;
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include "GuettaKeyPoint.h"
#include "StandardCamera.h"
#include "Tetrahedron.h"

#include "GuettaFeatures.h"
using namespace pcl;
using namespace pcl::io;

#include "Viewer.h"
class newForm : public QDialog {
    Q_OBJECT
public:
    newForm(QWidget* parent, int id);
    virtual ~newForm();

        vector<GuettaKeyPoint> getGuettaCloud(PointCloud<PointXYZRGB>::Ptr cloud);
        void setPclCloud(PointCloud<PointXYZRGB>::Ptr cloud);
        void setGuettaCloud(vector<GuettaKeyPoint> cloud);
        vector<GuettaKeyPoint> getGuettaCloud();
        vector<GuettaKeyPoint> getNarfKeyPoints();
        void updateKeyPoints(vector<GuettaKeyPoint> keyPoints);
    Ui::newForm widget;
    public slots:
        void click();
        void clickedShowKeyPoints();
        void selectedKeyPoint(int id);
     signals:
        void selectedKeyPoint(int idPoint, int idViewport);
     
private:
    vector<GuettaKeyPoint> keyPoints;
    vector<GuettaKeyPoint> guettaCloud;
PointCloud<PointXYZRGB>::Ptr pclCloud;
    Viewer* glWidget;
    int id;
    
    //map<string, PointCloud<PointXYZRGB>::Ptr> guettaClouds;
};

#endif	/* _NEWFORM_H */

