/* 
 * File:   GLWidget.h
 * Author: jose
 *
 * Created on 9 de octubre de 2011, 16:40
 */

#ifndef GLWIDGET_H
#define	GLWIDGET_H
#include <QtOpenGL>
#include <QGLWidget>
#include <iostream>
using namespace std;
#include "GuettaKeyPoint.h"


class GLWidget : public QGLWidget
{
    Q_OBJECT
            
    public:
        GLWidget(QWidget *parent = 0);
        ~GLWidget();
        
 protected:

     void initializeGL();

     void resizeGL(int width, int height);

     void paintGL();
     
     void mousePressEvent(QMouseEvent* e);
     
     void mouseMoveEvent(QMouseEvent* e);
     
     void mouseReleaseEvent(QMouseEvent* e);
     
     void wheelEvent(QWheelEvent *e);
     
     void keyPressEvent(QKeyEvent *e);
     
     void Pick3D(int mouse_x, int mouse_y);
     void drawObjects();
private:
    float xrot, yrot, zrot;
    float xpos, ypos, zpos;
    float xsca, ysca, zsca;
    int lastx, lasty;
    bool pulsado;
    int seleccion;
    float width;
    float height;
     public:
         vector<GuettaKeyPoint> cloud;
};

#endif	/* GLWIDGET_H */

