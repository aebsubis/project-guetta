#include "Viewer.h"

using namespace std;

Viewer::Viewer(QWidget* parent, int idViewport)
{
    // Cambiamos la cámara
    Camera* c = camera();
    StandardCamera* newCamera = new StandardCamera();
    setCamera(newCamera);
    delete c;
    this->idViewport = idViewport;
    countSelect = 0;
    QObject::connect(this, SIGNAL(selectedKeyPoint(int,int)),parent,SLOT(selectedKeyPoint(int,int)));
    //setAutoBufferSwap(false);
}

Viewer::~Viewer()
{
}

void Viewer::drawKeyPoints(bool name)
{
    glRotatef(180,1,0,0);
    GLUquadricObj* quadratic = gluNewQuadric();    
    for(int j = 0; j < selectables.size(); j++)
    {
        shared_ptr<GuettaCloud> guettaCloud = selectables[j];
        for(int i = 0; i < guettaCloud->data.size() ; i = i++)
        {
            shared_ptr<GuettaKeyPoint> point = guettaCloud->data[i];
            if( !( isnan(point->x) || isnan(point->y) || isnan(point->z)))
            {
                glPushMatrix();
                glTranslatef(point->x,point->y,point->z);
                glColor3f(point->r,point->g,point->b);
                if(name)
                    glPushName(i);
                gluDisk(quadratic,0.0f,0.03,6,6);
                if(name)
                    glPopName();
                glPopMatrix();
            }
        }    
    }
}
void Viewer::drawCloud(bool name)
{
    glRotatef(180,1,0,0); 
    for(int j = 0; j < unselectables.size(); j++)
    {
        shared_ptr<GuettaCloud> guettaCloud = unselectables[j];
        for(int i = 0; i < guettaCloud->data.size() ; i = i++)
        {
            shared_ptr<GuettaKeyPoint> point = guettaCloud->data[i];
            if( !( isnan(point->x) || isnan(point->y) || isnan(point->z)))
            {
                glBegin(GL_POINTS);
                glColor3f(point->r/255.0,point->g/255.0,point->b/255.0);
                glVertex3f(point->x,point->y,point->z);
                glEnd();
            }
        }    
    }
}

// Draws a spiral
void Viewer::draw()
{
    glPushMatrix();
    drawCloud(false);
    glPopMatrix();
    
    glPushMatrix();
    drawKeyPoints(false);
    glPopMatrix();
}

void Viewer::drawWithNames()
{
    glPushMatrix();
    drawKeyPoints(true);
    glPopMatrix();
}

void Viewer::postSelection(const QPoint& point)
{
  // Compute orig and dir, used to draw a representation of the intersecting line
  camera()->convertClickToLine(point, orig, dir);

  // Find the selectedPoint coordinates, using camera()->pointUnderPixel().
  bool found;
  selectedPoint = camera()->pointUnderPixel(point, found);
  selectedPoint -= 0.01f*dir; // Small offset to make point clearly visible.
  // Note that "found" is different from (selectedObjectId()>=0) because of the size of the select region.

  string keyPoint = "";
  string descriptor = "";
  int id = selectedName();
  if (id != -1)
  {
      // Emitimos la señal de que hemos seleccionado un keyPoint
      cout << "Selected: " << id << endl;
      emit selectedKeyPoint(id,idViewport);
  }
}


void Viewer::init()
{
    GLfloat luz_ambiental[] = { 1,1,1, 1.0 };
    glLightModelfv (GL_LIGHT_MODEL_AMBIENT, luz_ambiental); 
}