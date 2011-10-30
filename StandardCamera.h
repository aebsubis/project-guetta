/* 
 * File:   StandardCamera.h
 * Author: jose
 *
 * Created on 10 de octubre de 2011, 17:28
 */

#ifndef STANDARDCAMERA_H
#define	STANDARDCAMERA_H
#include <QGLViewer/camera.h>
using namespace qglviewer;

class StandardCamera : public qglviewer::Camera
{
public :
  StandardCamera();

  virtual float zNear() const;
  virtual float zFar() const;

  void toggleMode() { standard = !standard; }
  bool isStandard() { return standard; }

  void changeOrthoFrustumSize(int delta);
  virtual void getOrthoWidthHeight(GLdouble &halfWidth, GLdouble &halfHeight) const;

private :
  bool standard;
  float orthoSize;
};



#endif	/* STANDARDCAMERA_H */

