#ifndef VIEWER_H
#define	VIEWER_H

#include <QGLViewer/qglviewer.h>
#include <QtOpenGL>
#include <QGLWidget>
#include <iostream>
#include "GuettaKeyPoint.h"
#include <QGLViewer/camera.h>
#include "StandardCamera.h"
#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include "GuettaCloud.h"

using namespace pcl;
using namespace qglviewer;
using namespace std;

class Viewer : public QGLViewer
{
    Q_OBJECT
    public:
        Viewer(QWidget* parent, int idViewport);
        void drawCloud(bool name);
        void drawKeyPoints(bool name);
        ~Viewer();
        
    protected:
      virtual void draw();
      virtual void init();
      virtual void postSelection(const QPoint& point);
      virtual void drawWithNames();
      
    public:
        vector<shared_ptr<GuettaCloud> > selectables;
        vector<shared_ptr<GuettaCloud> > unselectables;
        qglviewer::Vec orig, dir, selectedPoint;
        
    signals:
        void selectedKeyPoint(int id, int idViewport);

    private:
        int idViewport;
        int countSelect;
        int idKeyPointPrevious;
};


#endif

