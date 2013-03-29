#include <iostream>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "ObjetOFF.h"
#include "Lumiere.h"
#include "SkyBox.h"
using namespace std;



float xRot = 0; 
float yRot = 0;
float zRot = 0;

float zTrans = 0;

int mouseXOld;
int mouseYOld;
bool leftbutton = false;
bool rightbutton = false;
int NbSommet, NbFacet, NbArete;

Lumiere * lum;
ObjetOFF lapin;
float mat[16]={1,0,0,0,
	       0,1,0,0,
	       0,0,1,0,
	       0,0,0,1};


bool calculated;
float alpha =0.0;
float b=0.0;
SkyBox *skybox;
void init()
{
  calculated=false;
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClearDepth(1.0);
  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);
  gluPerspective(70,1,0.001,100);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  skybox = new SkyBox();
  skybox->Initialize();
  lum = new Lumiere();
  lapin.setFilename("./triceratops.off");
  lapin.charger();
}
float minX=0,minY=0,minZ=0,maxX=0,maxY=0,maxZ=0,atX=0,atY=0,atZ=0;
void Display(void)
{

 

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   lum->ActiveLight();
    
  //calcul bounding box
 /* if(!calculated){
    calculated =true;
    float*	lesVertices = lapin.getVertices();
    cout<<"on recup les vertices"<<endl;
    unsigned int nb= lapin.getNbVertices();
    cout<<"on recup les nb "<<nb<<endl;
    for(int i = 0;i<nb*3;i=i+3){
      if(i==0){
	//	cout<<"i = "<<i<<endl;
	minX=lesVertices[i];
	minY=lesVertices[i+1];
	minZ=lesVertices[i+2];
	maxX=lesVertices[i];
	maxY=lesVertices[i+1];
	maxZ=lesVertices[i+2];
      }
      else{
	//6cas
	//	cout<<"i = "<<i<<endl;
	if(lesVertices[i] <minX){
	  minX=lesVertices[i];
	   
	}
	if(lesVertices[i+1] <minY){
	  minY=lesVertices[i+1];
	     
	}
	if(lesVertices[i+2] <minZ){
	  minZ=lesVertices[i+2];
	}
	
		
	if(lesVertices[i] >maxX){
	  maxX=lesVertices[i];
	}

	if(lesVertices[i+1] >maxY){
	  maxY=lesVertices[i+1];
	}
	if(lesVertices[i+2] >maxZ){
	  maxZ=lesVertices[i+2];
	}

	  
      }
    }
    cout<<"fin de calcul bounding box"<<endl<<minX<<" "<<minY<<" "<<minZ<<" "<<maxX<<" "<<maxY<<" "<<maxZ<<endl;
  }*/
  
  gluLookAt(0,0,10,0,0,0,0,1,0);
 
  glRotatef(b,0,1,0);
  //toit
  glPushMatrix();
  glTranslatef(0,2,0);
  glRotatef(90,1,0,0);
  GLUquadric * quadtoit = gluNewQuadric();
  gluCylinder(quadtoit,0,2,2,8,8);
  glPopMatrix();
  //sol
  glPushMatrix();
  glTranslatef(0,-1,0);
  glRotatef(90,1,0,0);
  GLUquadric * quadsol = gluNewQuadric();
  gluCylinder(quadsol,2,2,0.5,8,8);
  glPopMatrix();
  
  glutSwapBuffers();
    
}

void Reshape(int Width, int Height)
{
  glViewport(0, 0, (GLsizei)Width, (GLsizei)Height);

}

void Idle()
{
	b += 0.05;
    if (b>=360)
        b = b -360;
    
  glutPostRedisplay();
}

void ClavierClassique(unsigned char key, int x, int y)
{
  switch(key) {	
	case 'a': alpha+=0.09;break;
	 case 'z': alpha-=0.09;break;
  case 0x1B:
    exit(0);
  }
}

void ClavierSpecial(int key, int x, int y)
{
  switch(key) {
  case GLUT_KEY_UP:
    xRot-=1.5;
    break;
  case GLUT_KEY_DOWN:
    xRot+=1.5;
    break;
  case GLUT_KEY_RIGHT:
    yRot+=1.5;
    break;
  case GLUT_KEY_LEFT:
    yRot-=1.5;
    break;
  case GLUT_KEY_PAGE_UP:
    zTrans-=0.5;
    break;
  case GLUT_KEY_PAGE_DOWN:
    zTrans+=0.5;
    break;

  }
}

void Souris(int bouton, int etat, int x, int y)
{
  switch (bouton) {
  case GLUT_LEFT_BUTTON :
    if (etat==GLUT_DOWN) {
      mouseXOld = x;
      mouseYOld = y;
      leftbutton = true;
    }
    else
      leftbutton=false;
    break;
  case GLUT_RIGHT_BUTTON :
    if (etat==GLUT_DOWN) {
      rightbutton=true;
      mouseXOld = x;
      mouseYOld = y;
    }
    else
      rightbutton=false;
  }
}

void Motion (int x, int y)
{
  if (rightbutton && leftbutton) {
    zTrans+=(float)(y-mouseYOld)/10; 
    yRot+=(float)(x-mouseXOld)/10;
    xRot+=(float)(y-mouseYOld)/10; 
    mouseXOld=x;
    mouseYOld=y;
  }
  if (rightbutton) {
    zTrans+=(float)(y-mouseYOld)/10; 
    mouseXOld=x;
    mouseYOld=y;
  }
  if (leftbutton) {
    yRot+=(float)(x-mouseXOld)/10;
    xRot+=(float)(y-mouseYOld)/10; 
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
