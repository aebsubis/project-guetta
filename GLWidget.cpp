#include "GLWidget.h"
#include <iostream>
using namespace std;


GLWidget::GLWidget(QWidget *parent) : QGLWidget()
{
    setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));
    setMouseTracking(true);
    xrot = 180;
    yrot = 0.0;
    zrot = 0.0;
    
    xpos = 0.0;
    ypos = 0.0;
    zpos = 0.0;
    
    xsca = 0.0;
    ysca = 0.0;
    zsca = 0.0;
    
    pulsado = false;
    setFocus();
    grabKeyboard();
}

GLWidget::~GLWidget()
{
    
}


void GLWidget::initializeGL()
{
 // Set up the rendering context, define display lists etc.:
 glEnable(GL_DEPTH_TEST);
}

void GLWidget::resizeGL(int width, int height)
{
    // setup viewport, projection etc.:
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->width = width;
    this->height = height;
    
    int side = qMin(width, height);
    //glViewport((width - side) / 2, (height - side) / 2, side, side);

     glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)width/(GLfloat)height, 0.01f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
}

void GLWidget::drawObjects()
{
    glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
   
   // glPushMatrix();
    
    glRotatef(xrot,1,0,0);
    glRotatef(yrot,0,1,0);
    glRotatef(zrot,0,0,1);
    glTranslated(xpos, ypos, zpos);
    
    glLoadName(10);
    
    glBegin(GL_QUADS);                      // Draw A Quad
    glColor3f(1.0f, 0,0);
        glVertex3f(-1.0f, 1.0f, 0.0f);              // Top Left
        glVertex3f( 1.0f, 1.0f, 0.0f);              // Top Right
        glVertex3f( 1.0f,-1.0f, 0.0f);              // Bottom Right
        glVertex3f(-1.0f,-1.0f, 0.0f);              // Bottom Left
    glEnd();       
    //glPopName();// Done Drawing The Quad  
}

void GLWidget::paintGL()
{
 // draw the scene:
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
   
   // glPushMatrix();
   
    glRotatef(xrot,1,0,0);
    glRotatef(yrot,0,1,0);
    glRotatef(zrot,0,0,1);
    glTranslated(xpos, ypos, zpos);
    
      GLUquadricObj *quadratic;
    quadratic=gluNewQuadric();    
    int col = 0;
    /*
    GLUquadricObj *quadratic;
    quadratic=gluNewQuadric();  
    glPointSize(3);
    glLoadName(10);
   
 glColor3f(1.0f, 0,0);
 gluDisk(quadratic,0.0f,1,3,3);
 glTranslated(3, 0, 0);
 glLoadName(11);
 gluDisk(quadratic,0.0f,1,3,3);
 */

    //glPopName();
    //glBegin(GL_POINTS);
    
    // cloud.size()
    int contador = 0;
    for(int i = 0; i < cloud.size() ; i = i+10)
    {
        GuettaKeyPoint point = cloud[i];
        if( !( isnan(point.x) || isnan(point.y) || isnan(point.z)))
        {
            //contador++;
            //if(contador > 10000) 
            //    break;
            //glBegin(GL_TRIANGLE_STRIP);
            //cout << "i: " << i << "-> " << cloud[i].x << "," << cloud[i].y << "," << cloud[i].z << endl;
            //cout << point.r << "," << point.g << "," << point.b << endl;
            glPushMatrix();
            glTranslatef(point.x,point.y,point.z);
            //glColor3f(0,1,0);
            glColor3f(point.r/255.0,point.g/255.0,point.b/255.0);
            glLoadName(i);
            gluDisk(quadratic,0.0f,0.01,6,6);
            glPopMatrix();
            //glPopName();
        }
    }
}

void GLWidget::mousePressEvent(QMouseEvent* e) {
    pulsado = true;
    lastx = e->x();
    lasty = e->y();
    Pick3D(e->x(), e->y());
    updateGL();
}

void GLWidget::mouseReleaseEvent(QMouseEvent* e) {
    pulsado = false;
}

void GLWidget::mouseMoveEvent(QMouseEvent* e) {
    
    if(pulsado == true) {
        int diffx=e->x()-lastx; //check the difference between the current x and the last x position
        int diffy=e->y()-lasty; //check the difference between the current y and the last y position
        lastx=e->x(); //set lastx to the current x position
        lasty=e->y(); //set lasty to the current y position
        xrot -= (float) diffy; //set the xrot to xrot with the addition of the difference in the y position
        yrot += (float) diffx;    //set the xrot to yrot with the addition of the difference in the x position
        repaint();
    }
}

void GLWidget::wheelEvent(QWheelEvent *e) {
    if(e->delta() > 0)
        zpos -= 0.5;
    else
        zpos += 0.5;
    repaint();
}

void GLWidget::keyPressEvent(QKeyEvent *e) {
    if(e->key() == Qt::Key_Q)
    {
        xrot += 1;
        if (xrot >360) xrot -= 360;
    }
    if(e->key() == Qt::Key_Z)
    {
        xrot -= 1;
        if (xrot < -360) xrot += 360;
    }
    if(e->key() == Qt::Key_W)
    {
        float xrotrad, yrotrad;
        yrotrad = (yrot / 180 * 3.141592654f);
        xrotrad = (xrot / 180 * 3.141592654f);
        xpos += float(sin(yrotrad)) ;
        zpos -= float(cos(yrotrad)) ;
        ypos -= float(sin(xrotrad)) ;
    }
    if(e->key() == Qt::Key_S)
    {
        float xrotrad, yrotrad;
        yrotrad = (yrot / 180 * 3.141592654f);
        xrotrad = (xrot / 180 * 3.141592654f);
        xpos -= float(sin(yrotrad));
        zpos += float(cos(yrotrad)) ;
        ypos += float(sin(xrotrad));
    }
    if (e->key() == Qt::Key_D)
    {
        float yrotrad;
        yrotrad = (yrot / 180 * 3.141592654f);
        xpos += float(cos(yrotrad)) * 0.2;
        zpos += float(sin(yrotrad)) * 0.2;
    }

    if (e->key() == Qt::Key_A)
    {
        float yrotrad;
        yrotrad = (yrot / 180 * 3.141592654f);
        xpos -= float(cos(yrotrad)) * 0.2;
        zpos -= float(sin(yrotrad)) * 0.2;
    }
    repaint();
}

// Selecciona un objeto a través del ratón
void GLWidget::Pick3D(int mouse_x, int mouse_y)
{
    // formato de buffer, cada cuatro posiciones almacena:
    //      buffer[i]   = número de objetos
    //      buffer[i+1] = profundidad mínima
    //      buffer[i+2] = profuncidad máxima
    //      buffer[i+3] = nombre de la pila

    GLuint	buffer[1024*1024];
    GLint	hits;
    int     profundidad;
 makeCurrent();
    seleccion = 0;
    // Tamaño de la ventana (Viewport) [0] es <x>, [1] es <y>, [2] es <alto>, [3] es <ancho>
	GLint viewport[4];
	glSelectBuffer(1024,buffer);
	glRenderMode(GL_SELECT);
	glInitNames();				  // Inicializa la pila de nombres
	glPushName(-1);				  // Apila 0 (al menos una entrada) en la pila
	glGetIntegerv(GL_VIEWPORT, viewport);
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	

		gluPickMatrix(mouse_x,viewport[3] - mouse_y,1.0,1.0,viewport);
	// Indicamos la proyección (perspective / ortho)
	gluPerspective(45.0, (GLfloat)width/(GLfloat)height, 0.01f, 1000.0f);
//gluPerspective(45.0, (GLfloat)width/(GLfloat)height, 0.01f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);
        
        paintGL();
        
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	//glMatrixMode(GL_MODELVIEW);
	//glFlush();
	
	// returning to normal rendering mode
	hits = glRenderMode(GL_RENDER);
    cout << "hits: " << hits << endl;
    if (hits > 0)
    {
        seleccion = buffer[3];		// Coge como selección el primer objeto de la lista
        profundidad = buffer[1];    // Calcula su profundidad
        
        for (int i = 1; i < hits; i++)  // Recorre todos los objetos
        {
            // Si el objetos está más cerca que el seleccionado ahora
            if (buffer[i*4+1] < GLuint(profundidad))
            {
                seleccion = buffer[i*4+3];	    // Selecciona dicho objeto
                profundidad = buffer[i*4+1];	// Calcula su profundidad
            }
        }
        
        cout << "selección: " << seleccion << endl;
    }
}