/*
 * File:   main.cpp
 * Author: jose
 *
 * Created on 9 de octubre de 2011, 16:17
 */


#include <QtGui/QApplication>
#include <iostream>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>

using namespace pcl;
using namespace pcl::io;
using namespace boost;
//#include "newForm.h"
#include "Guetta.h"
#include <X11/Xlib.h>
#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>
using namespace std;
int main(int argc, char *argv[])
{
    
    if (!XInitThreads()) {
    printf("Xlib not thread safe\n");
    exit(1);
    }
    
    QApplication app(argc, argv);
    setlocale(LC_NUMERIC,"C");

    Guetta guetta;
    guetta.show();
    
    
    return app.exec();
    
    /*
    shared_ptr<int> ptr2(new int);
    *ptr2 = 10;
    shared_array<int> sa1 (new int[100]); 
    
    vector<shared_ptr<int> > numeros;
    numeros.insert(numeros.end(),ptr2);*/
    

}

