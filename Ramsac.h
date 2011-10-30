/* 
 * File:   Ramsac.h
 * Author: jose
 *
 * Created on 23 de octubre de 2011, 17:38
 */

#ifndef RAMSAC_H
#define	RAMSAC_H


#include <iostream>
using namespace std;
#include "GuettaKeyPoint.h"
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include "GuettaCloud.h"
#include <pcl/registration/transforms.h>
#include "pcl/common/transform.h"
#include "pcl/registration/icp.h"
#include "pcl/registration/registration.h"
#include "pcl/sample_consensus/ransac.h"
#include "pcl/sample_consensus/sac_model_registration.h"
#include "GuettaTime.h"
using namespace pcl;
using namespace boost;
class Ramsac
{
    public:
        Ramsac(GuettaCloud* guettaCloud1, GuettaCloud* guettaCloud2);
        void compute(int indice, string combinacion);
        float getDistanciaTotal(GuettaCloud* guettaCloud1, vector<int> indicesGuettaCloud1,GuettaCloud* guettaCloud2, vector<int> indicesGuettaCloud2, GuettaCloud* resultado, Eigen::Matrix4f& transformation_matrix);
        int SplitString(const string& input, const string& delimiter, vector<string>& results, bool includeEmpties);
        void split(const string& str, const string& delimiters , vector<int>& tokens);
               vector<int> mejorCombinacion;
        float menorDistancia;
private:
        GuettaCloud* guettaCloud1;
        GuettaCloud* guettaCloud2;
        int numPoints;

};

#endif	/* RAMSAC_H */

