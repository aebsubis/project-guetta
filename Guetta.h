/* 
 * File:   Guetta.h
 * Author: jose
 *
 * Created on 11 de octubre de 2011, 11:25
 */

#ifndef _GUETTA_H
#define	_GUETTA_H

#include "ui_Guetta.h"
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <iostream>
#include "Viewer.h"
#include "GuettaCloud.h"
#include "GuettaFeatures.h"
#include "RGB.h"
#include <pcl/registration/transforms.h>
#include "pcl/common/transform.h"
#include "pcl/registration/icp.h"
#include "pcl/registration/registration.h"
#include "Ramsac.h"
#include "pcl/sample_consensus/ransac.h"
#include "pcl/sample_consensus/sac_model_registration.h"
#include "GuettaICP.h"
#include "GuettaCapture.h"
using namespace std;
using namespace pcl;
using namespace pcl::io;

class Guetta : public QDialog 
{
    Q_OBJECT
        public:
            Guetta();
            virtual ~Guetta();
            void loadClouds();
            
            void loadClouds(string directorio);
            pcl::PointCloud<pcl::PointXYZRGB>::Ptr loadPCD(string name);
            float getDistanciaTotal(GuettaCloud* guettaCloud1, vector<int> indicesGuettaCloud1,GuettaCloud* guettaCloud2, vector<int> indicesGuettaCloud2, GuettaCloud* resultado);
            Eigen::Matrix4f emparejar(bool pintar, GuettaCloud* guettaCloud1, GuettaCloud* guettaCloud2, GuettaCloud* features1, GuettaCloud* features2);
            GuettaCloud* transform(GuettaCloud* guettaCloud, Eigen::Matrix4f transformation_matrix);
            int getNextCloud(int actualIndex);
            
        public slots:
            void changeCloud1(QString cloud);
            void changeCloud2(QString cloud);
            void selectedKeyPoint(int idPoint, int idViewport);
            void changeKeyPointMethod();
            void changeOptions();
            void changeAcumular();
            void procesarClouds();
            void seleccionarDirectorio();
            void seleccionarTodos();
            void deseleccionarTodos();
            void cambiarIncremento(int incremento);
            
        private:
            string convert(float value);
            
            bool acumular;
            string cloud1, cloud2;
            int countSelection;
            Ui::Guetta widget;
            map<string, PointCloud<PointXYZRGB>::Ptr> pclClouds;
            vector<Viewer*> viewers;
            GuettaKeyPoint* previousPoint;
            float maxDistanceSIFT;
            int maxKeyPointsAlineamientoSIFT;
            float maxDistanceSURF;
            int maxKeyPointsSIFT; 
            vector<GuettaCloud> clouds;
};      

#endif	/* _GUETTA_H */

