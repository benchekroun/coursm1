#include <iostream>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include "SkyBox.h"

using namespace std;

float a = 0;
float b = 0;
float c = 0;

float tx = 0;
float ty = 0;
float tz = 0;

float dx = 0;
float dy = 0;

int mouseXOld;
int mouseYOld;
bool leftbutton = false;
SkyBox * s;

void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-10.0,10.0,-10.0,10.0,-10.0,10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Display(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    
    glTranslatef(tx,ty,tz);
    s->SetPosition(tx,ty,tz);

    s->Activate();
    
    glPushMatrix();
    glTranslatef(dx,dy,0);
    glutWireTeapot(0.5);
    glPopMatrix();
    
    glTranslatef(-3,-5,0);
    glPushMatrix();
    {//O
        glColor3f(1.0,0.0,0.0);
        glBegin(GL_LINE_LOOP);
        glVertex2f(0,0);
        glVertex2f(0,1);
        glVertex2f(1,1);
        glVertex2f(1,0);
        glEnd();
    }
    {//P  
        glColor3f(0.0,0.0,1.0);
        glTranslatef(1.5,0,0);
        glBegin(GL_LINE_STRIP);
        glVertex2f(0,0);
        glVertex2f(0,1);
        glVertex2f(1,1);
        glVertex2f(1,0.5);
        glVertex2f(0,0.5);
        glEnd();
    }
    {//E
        glColor3f(1.0,0.0,0.0);
        glTranslatef(1.5,0,0);
        glBegin(GL_LINE_STRIP);
        glVertex2f(1,0);
        glVertex2f(0,0);
        glVertex2f(0,1);
        glVertex2f(1,1);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(0,0.5);
        glVertex2f(1,0.5);
        glEnd();
    }
    {//N
        glColor3f(0.0,0.0,1.0);
        glTranslatef(1.5,0,0);
        glBegin(GL_LINE_STRIP);
        glVertex2f(0,0);
        glVertex2f(0,1);
        glVertex2f(1,0);
        glVertex2f(1,1);
        glEnd();
    }
    {//G
        glColor3f(1.0,0.0,0.0);
        glTranslatef(1.5,0,0);
        glBegin(GL_LINE_STRIP);
        glVertex2f(0.5,0.25);
        glVertex2f(0.5,0.5);
        glVertex2f(1,0.5);
        glVertex2f(1,0);
        glVertex2f(0,0);
        glVertex2f(0,1);
        glVertex2f(1,1);
        glVertex2f(1,0.75);
        glEnd();
    }
    {//L
        glColor3f(0.0,0.0,1.0);
        glTranslatef(1.5,0,0);
        glBegin(GL_LINE_STRIP);
        glVertex2f(1,0);
        glVertex2f(0,0);
        glVertex2f(0,1);
        glEnd();
    }
    {// Une ellipse
        glPopMatrix();
	glPushMatrix();
        float aa = 5;
        float bb = 3;
        glTranslatef(4.5,0.5,0);
        glRotatef(a,1,0,0);
        glLineWidth(1);
        glBegin(GL_LINE_STRIP);
        for (int i=0; i<=1000; i++) {
            float x = aa*(float)i/1000;
            glColor3f(x,x-0.5,0);
            glVertex2f(x,bb*sqrt(1-(x*x/(aa*aa))));
        }
        glEnd();
	glRotatef(180,0,1,0);
	glBegin(GL_LINE_STRIP);
        for (int i=0; i<=1000; i++) {
            float x = aa*(float)i/1000;
            glColor3f(0,x-0.5,x);
            glVertex2f(x,bb*sqrt(1-(x*x/(aa*aa))));
        }
        glEnd();
        glRotatef(180,0,0,1);
        glBegin(GL_LINE_STRIP);
        for (int i=0; i<=1000; i++) {
            float x = aa*(float)i/1000;
            glColor3f(0.5,0,x-0.5);
            glVertex2f(x,bb*sqrt(1-(x*x/(aa*aa))));
        }
        glEnd();
	glRotatef(180,0,1,0);
	glBegin(GL_LINE_STRIP);
        for (int i=0; i<=1000; i++) {
            float x = aa*(float)i/1000;
            glColor3f(x-0.5,x,0);
            glVertex2f(x,bb*sqrt(1-(x*x/(aa*aa))));
        }
        glEnd();
    }
    {// Une maison
        glPopMatrix();
        glTranslatef(-2,6,0);
        glRotatef(c,0,1,0);
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

        glColor3ub(235,213,167);
        //Faces avant arrière dessus
        glBegin(GL_QUAD_STRIP);
        glVertex3f(-2,-2,-2);
        glVertex3f(2,-2,-2);
        glVertex3f(-2,2,-2);
        glVertex3f(2,2,-2);
        glVertex3f(-2,2,2);
        glVertex3f(2,2,2);
        glVertex3f(-2,-2,2);
        glVertex3f(2,-2,2);
        glEnd();
        glColor3ub(224,189,118);
        // Faces côté gauche et droite
        glBegin(GL_QUADS);
        glVertex3f(-2,-2,-2);
        glVertex3f(-2,2,-2);
        glVertex3f(-2,2,2);
        glVertex3f(-2,-2,2);
        glVertex3f(2,-2,-2);
        glVertex3f(2,2,-2);
        glVertex3f(2,2,2);
        glVertex3f(2,-2,2);
        glEnd();
        // Toit
        glColor3ub(75,79,115);
        glBegin(GL_QUAD_STRIP);
        glVertex3f(-2,2,-2);
        glVertex3f(2,2,-2);
        glVertex3f(-1.5,4,0);
        glVertex3f(1.5,4,0);
        glVertex3f(-2,2,2);
        glVertex3f(2,2,2);
        glEnd();
        glBegin(GL_TRIANGLES);
        glVertex3f(-2,2,-2);
        glVertex3f(-1.5,4,0);
        glVertex3f(-2,2,2);
        glVertex3f(2,2,-2);
        glVertex3f(1.5,4,0);
        glVertex3f(2,2,2);
        glEnd();
	
	//cheminée
	
        // Facade avant
	glColor3ub(255,0,0);
        glBegin(GL_QUADS);
        glVertex3f(-1.5,0.5,2.0001);
        glVertex3f(-0.5,0.5,2.0001);
        glVertex3f(-0.5,1.5,2.0001);
        glVertex3f(-1.5,1.5,2.0001);
        glEnd();
	glColor3f(0,0,0);
	glBegin(GL_LINES);
	glVertex3f(-1,0.5,2.0002);
	glVertex3f(-1,1.5,2.0002);
	glVertex3f(-1.5,1.,2.0002);
	glVertex3f(-0.5,1.,2.0002);
	glEnd();
	glColor3ub(255,0,0);
	glBegin(GL_QUADS);
        glVertex3f(-0.55,-2,2.0001);
        glVertex3f( 0.55,-2,2.0001);
        glVertex3f( 0.55,-0.5,2.0001);
        glVertex3f(-0.55,-0.5,2.0001);
        glEnd();
	
	{//GL_TRIANGLE_FAN
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glTranslatef(-1,4+sqrt(0.5),0);
	
        glRotatef(b,0,1,0);
	glRotatef(45,0,0,1);
        glColor3ub(212,184,213);
	
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0,0);
        glVertex2f(0,0.5);
        glVertex2f(0.5,0.5);
        glVertex2f(0.5,0);
        glVertex2f(0.5,-0.5);
        glVertex2f(0,-0.5);
        glEnd();
	
        glRotatef(180,0,1,0);
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0,0);
        glVertex2f(0,0.5);
        glVertex2f(0.5,0.5);
        glVertex2f(0.5,0);
        glVertex2f(0.5,-0.5);
        glVertex2f(0,-0.5);
        glEnd();
    }
	
    }
    glFlush();
    glutSwapBuffers();

}

void Reshape(int Width, int Height)
{
    glViewport(0, 0, (GLsizei)Width, (GLsizei)Height);

}

void Idle()
{
    a += 1.0;
    if (a>=360)
         a = a - 360;
    
    b += 0.5;
    if (b>=360)
        b = b -360;
    glutPostRedisplay();
}

void ClavierClassique(unsigned char key, int x, int y)
{
  switch(key) {	
    case 'a':
      c+= 1.0;
      if (c>=360)
	  c = c - 360;
      break;
    case 0x1B:
	exit(0);
    }
}

void ClavierSpecial(int key, int x, int y)
{
  switch(key) {
    case GLUT_KEY_UP:
      ty+=0.1;
      break;
    case GLUT_KEY_DOWN:
      ty-=0.1;
      break;
    case GLUT_KEY_RIGHT:
      tx+=0.1;
      break;
    case GLUT_KEY_LEFT:
      tx-=0.1;
      break;
    case GLUT_KEY_PAGE_UP:
      tz-=0.1;
      break;
    case GLUT_KEY_PAGE_DOWN:
      tz+=0.1;
      break;
  }
}

void Souris(int bouton, int etat, int x, int y)
{
  switch (bouton) {
    case GLUT_LEFT_BUTTON :
        if (etat==GLUT_DOWN) {
            leftbutton=true;
            mouseXOld = x;
            mouseYOld = y;
        }
        else
            leftbutton=false;
        break;
    }
}

void Motion (int x, int y)
{
    if (leftbutton) {
        dx+=(float)(x-mouseXOld)/20;
        dy-=(float)(y-mouseYOld)/20;                
        mouseXOld=x;
        mouseYOld=y;
    }
    
}
int main(int argc, char** argv)
{

    glutInit (&argc,argv) ;
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH) ;

    glutInitWindowSize (500,500) ;
    glutInitWindowPosition (100, 100) ;
    glutCreateWindow ("Tutoriel 1") ;

    init();
    s= new SkyBox();
    s->Initialize();
    glutReshapeFunc(Reshape);
    glutDisplayFunc(Display);
    glutIdleFunc(Idle);
    glutKeyboardFunc(ClavierClassique);
    glutSpecialFunc(ClavierSpecial);
    glutMouseFunc(Souris);
    glutMotionFunc(Motion);

    glutMainLoop () ;

    return 0 ;

}
