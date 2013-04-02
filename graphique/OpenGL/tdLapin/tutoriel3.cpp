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

//------------ les variables globales

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
ObjetOFF plane;
float mat[16]={1,0,0,0,
	       0,1,0,0,
	       0,0,1,0,
	       0,0,0,1};


bool calculated;
float alpha =0.0;
double b=0.0;
float minX=0,minY=0,minZ=0,maxX=0,maxY=0,maxZ=0,atX=0,atY=0,atZ=0;
float theSize = 3.;
//SkyBox *skybox;

//-------------------------- les fonctions 

void dessinerManege(){
	//push général
	glPushMatrix();
	
	//toit
  glPushMatrix();
  glTranslatef(0,2*theSize,0);
  glRotatef(90,1,0,0);
  GLUquadricObj * quadtoit = gluNewQuadric();
  gluQuadricNormals(quadtoit, GLU_SMOOTH); 
  gluQuadricTexture(quadtoit, GL_TRUE); 
  gluCylinder(quadtoit,0,2*theSize,1.2*theSize,16,16);
  glPopMatrix();
  //bas du toit
  glPushMatrix();
   glTranslatef(0,0.8*theSize,0); //0.8 =2-1.2
  glRotatef(90,1,0,0);
  gluCylinder(quadtoit,0,2*theSize,0.01*theSize,16,16);
  glPopMatrix();
  
  //core
  glPushMatrix();
  glTranslatef(0,1*theSize,0);
  glRotatef(90,1,0,0);
  GLUquadricObj * quadcore = gluNewQuadric();
  gluQuadricNormals(quadcore, GLU_SMOOTH); 
  gluQuadricTexture(quadcore, GL_TRUE); 
  gluCylinder(quadcore,0.5*theSize,0.5*theSize,2*theSize,16,16);
  glPopMatrix();
  
  
  //sol
  
  //tour du sol
  glPushMatrix();
  glTranslatef(0,-1*theSize,0);
  glRotatef(90,1,0,0);
  GLUquadricObj * quadsol = gluNewQuadric();
   gluQuadricNormals(quadsol, GLU_SMOOTH); 
  gluQuadricTexture(quadsol, GL_TRUE); 
  gluCylinder(quadsol,2*theSize,2*theSize,0.25*theSize,16,16);
  glPopMatrix();
  //disque haut
  glPushMatrix();
  glTranslatef(0,-1*theSize,0);
  glRotatef(90,1,0,0);
  GLUquadricObj * quadDiscHautSol = gluNewQuadric();
   gluQuadricNormals(quadDiscHautSol, GLU_SMOOTH); 
  gluQuadricTexture(quadDiscHautSol, GL_TRUE); 
  gluCylinder(quadDiscHautSol,0,2*theSize,0.001*theSize,16,16);
  glPopMatrix();
  
  //disquebas
  glPushMatrix();
  glTranslatef(0,-1.25*theSize,0);
  glRotatef(90,1,0,0);
  GLUquadricObj * quadDiscBasSol = gluNewQuadric();
   gluQuadricNormals(quadDiscBasSol, GLU_SMOOTH); 
  gluQuadricTexture(quadDiscBasSol, GL_TRUE); 
  gluCylinder(quadDiscBasSol,0,2*theSize,0.001*theSize,16,16);
  glPopMatrix();
  
  //popgénéral
  glPopMatrix();
}


//--------- les fonctinos GLUT
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
  //skybox = new SkyBox();
  //skybox->Initialize();
  lum = new Lumiere();
  lapin.setFilename("./triceratops.off");
  lapin.charger();
  plane.setFilename("./x29_plane.off");
  plane.charger();
}

void Display(void)
{

 

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
    
  
  
  gluLookAt(0,0,20,0,0,0,0,1,0);
  //skybox->SetPosition(0,0,10);
 // skybox->Activate();
 lum->ActiveLight();
  
  glPushMatrix();
  glRotatef(-b,0,1,0);


//dessiner le manege à l'echelle scale
  dessinerManege();
  
  plane.move(0,cos(b/20)*1.5,1.8*theSize);
  plane.setAngleX(-90);
  plane.setAngleZ(90);
  glPushMatrix();
  
  plane.dessiner(0.04);
  glPopMatrix();
  //popgénéral
  glPopMatrix();
  glutSwapBuffers();
    
}



void Reshape(int Width, int Height)
{
  glViewport(0, 0, (GLsizei)Width, (GLsizei)Height);

}

void Idle()
{
	b += 0.1;
    if (b>=360.00)
        b = 0.0;
    
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
