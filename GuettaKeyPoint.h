/* 
 * File:   GuettaKeyPoint.h
 * Author: jose
 *
 * Created on 8 de octubre de 2011, 21:15
 */

#ifndef GUETTAKEYPOINT_H
#define	GUETTAKEYPOINT_H


#include <iostream>
using namespace std;
#include <vector>
#include <math.h>
#include <flann/flann.hpp>
#include <flann/io/hdf5.h>

class GuettaKeyPoint
{
        public:
            
            GuettaKeyPoint()
            {
                x,y,z = 0;
                descriptor = NULL;
            }
            
            GuettaKeyPoint(float x, float y, float z, float r, float g, float b, float* descriptor)
            {
                this->x = x;
                this->y = y;
                this->z = z;
                this->r = r;
                this->g = g;
                this->b = b;
                this->descriptor = descriptor;
            }
            
            GuettaKeyPoint(const GuettaKeyPoint& keyPoint)
            {
                this->x = keyPoint.x;
                this->y = keyPoint.y;
                this->z = keyPoint.z;
                this->r = keyPoint.r;
                this->g = keyPoint.g;
                this->b = keyPoint.b;
                this->descriptor = NULL;
                if(keyPoint.descriptor != NULL)
                {
                    this->descriptor = new float[128];
                    for(int i = 0; i < 128; i++)
                            this->descriptor[i] = keyPoint.descriptor[i];
                }
            }
            
            GuettaKeyPoint& operator=(const GuettaKeyPoint &keyPoint)
            {
                if(this != &keyPoint)
                {
                    this->x = keyPoint.x;
                    this->y = keyPoint.y;
                    this->z = keyPoint.z;
                    this->r = keyPoint.r;
                    this->g = keyPoint.g;
                    this->b = keyPoint.b;
                    this->descriptor = NULL;
                    if(keyPoint.descriptor != NULL)
                    {
                        this->descriptor = new float[128];
                        for(int i = 0; i < 128; i++)
                                this->descriptor[i] = keyPoint.descriptor[i];
                    }
                }
                return *this;
            }
            
            float distanceXYZ(GuettaKeyPoint* point)
            {
                 float distance = pow(x - point->x,2) + pow(y - point->y,2) + pow(z - point->z,2);
                 return distance;
            }
            
            float distanceDescriptor(GuettaKeyPoint* point)
            {
                 float distance = 0;
                 for(int i = 0; i < 128; i++)
                 {
                     distance += pow(descriptor[i] - point->descriptor[i],2);
                 }
                 return distance;
            }     
            
            vector<int> getNeareastDescriptor3(vector<GuettaKeyPoint*> keyPoints)
            {
                vector<int> resultado;
                 float min = 9999999;
                 int pos = 0;
                 for(int i = 0; i < keyPoints.size(); i++)
                 {
                     float distance = distanceDescriptor(keyPoints[i]);
                     //cout << "distance " << i << " : " << distance << endl;
                     if(distance < min)
                     {
                         //cout << "min " << i << " : " << distance << endl;
                         min = distance;
                         pos = i;
                     }
                 }
                 resultado.insert(resultado.end(),pos);
                 return resultado;
            }
             
            vector<int> getNearestDescriptor(vector<GuettaKeyPoint*> keyPoints)
            {
                flann::Matrix<float> dataset;
               
                dataset.rows = keyPoints.size (); // Número de puntos.
                dataset.cols = 128; // numbero de características.
                dataset.data = (float*)malloc (dataset.rows * dataset.cols * sizeof (float));

                for (size_t i = 0; i < dataset.rows; ++i)
                    memcpy (&dataset.data[i * dataset.cols], &keyPoints[i]->descriptor[0], 128 * sizeof (float));

                //cout << dataset.rows << endl;
                flann::Matrix<float> query;
               
                query.rows = 1;
                query.cols = 128;
                query.data = (float*)malloc (query.rows * query.cols * sizeof (float));
                memcpy (&query.data[0], &descriptor[0], 128 * sizeof (float));
               
                int nn = 1;
                flann::Matrix<int> indices(new int[query.rows*nn], query.rows, nn);
                flann::Matrix<float> dists(new float[query.rows*nn], query.rows, nn);
                // construct an randomized kd-tree index using 4 kd-trees
                flann::Index<flann::L2<float> > index(dataset, flann::KDTreeIndexParams(4));
                index.buildIndex();
                // do a knn search, using 128 checks
                index.knnSearch(query, indices, dists, nn, flann::SearchParams(128));
               
                int cercano = indices.data[0];
                float distancia = dists.data[0];
                
                vector<int> resultado;
                
                for (int i = 0; i < nn; i++)
                    resultado.insert(resultado.end(),indices.data[i]);
                
                //memcpy (&resultado[0], &indices.data[0], nn * sizeof (int));
                /*
                cout << "Vecinos: ";
                for (int i = 0; i < nn; i++)
                    cout << indices.data[i] << "(" << dists.data[i] << ") ";
                cout << endl;
                */
                
                dataset.free();
                query.free();
                indices.free();
                dists.free();
               
                return resultado;
            }

            float getDescriptorValue()
            {
                float value = 0;
                for(int i = 0; i < 128; i++)
                        value += pow(descriptor[i],2);
                return value;
            }
            
            ~GuettaKeyPoint()
            {
                if(descriptor != NULL)
                    delete [] descriptor;
            }
   
            float x,y,z,r,g,b;
            float *descriptor;
};


#endif	/* GUETTAKEYPOINT_H */

