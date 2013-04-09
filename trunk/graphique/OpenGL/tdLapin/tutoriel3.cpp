#include <iostream>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "ObjetOFF.h"
#include "Lumiere.h"
#include "readpng.h"
using namespace std;

#define PI 3.14

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

//pour stocker les différentes textures
gl_texture_t *Tex[16];


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
ObjetOFF plane[10];
float mat[16]={1,0,0,0,
	       0,1,0,0,
	       0,0,1,0,
	       0,0,0,1};


bool calculated;
float alpha =0.0;
double b=0.0;
float minX=0,minY=0,minZ=0,maxX=0,maxY=0,maxZ=0,atX=0,atY=0,atZ=0;
float theSize = 3.5;
//SkyBox *skybox;

//-------------------------- les fonctions 

void dessinerManege(){
	//push général
	glPushMatrix();
	 

    glBindTexture(GL_TEXTURE_2D,Tex[5]->id);
  //disque du toit
  glPushMatrix();
  glTranslatef(0,1.4*theSize,0);
  glRotatef(90,1,0,0);
  GLUquadricObj * quadDisctoit = gluNewQuadric();
  gluQuadricNormals(quadDisctoit, GLU_SMOOTH); 
  gluQuadricTexture(quadDisctoit, GL_TRUE);
  gluCylinder(quadDisctoit,2*theSize,2*theSize,0.6*theSize,16,16);
  glPopMatrix();
  
  
  //bas du toit
  glBindTexture(GL_TEXTURE_2D,Tex[4]->id);
  glPushMatrix();
   glTranslatef(0,0.8*theSize,0); //0.8 =2-1.2
  glRotatef(90,1,0,0);
  gluCylinder(quadDisctoit,0,2*theSize,0.01*theSize,16,16);
  glPopMatrix();
  
  //binder la pierre
  glBindTexture(GL_TEXTURE_2D,Tex[3]->id);
  //core
  glPushMatrix();
  glTranslatef(0,1*theSize,0);
  //glRotatef(-b/180*PI,0,1,0);
  glRotatef(90,1,0,0);
  GLUquadricObj * quadcore = gluNewQuadric();
  gluQuadricNormals(quadcore, GLU_SMOOTH); 
  gluQuadricTexture(quadcore, GL_TRUE); 
  gluCylinder(quadcore,0.6*theSize,0.6*theSize,2*theSize,8,8);
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
  
  glBindTexture(GL_TEXTURE_2D,Tex[4]->id);
  //disque haut
  glPushMatrix();
  glTranslatef(0,-1*theSize,0);
  glRotatef(90,1,0,0);
  GLUquadricObj * quadDiscHautSol = gluNewQuadric();
  gluQuadricNormals(quadDiscHautSol, GLU_SMOOTH); 
  gluQuadricTexture(quadDiscHautSol, GL_TRUE); 
  gluCylinder(quadDiscHautSol,0,2*theSize,0.001*theSize,16,16);
  glPopMatrix();
  
  //popgénéral
  glPopMatrix();
}

void dessinerSousSol(){
	
  //sol-sous(et oui , y'a un sous-sol)
  glBindTexture(GL_TEXTURE_2D,Tex[1]->id);
  glPushMatrix();
  glTranslatef(0,-1.25*theSize,0);
  glRotatef(90,1,0,0);
  GLUquadricObj * quadSousSol = gluNewQuadric();
  gluQuadricNormals(quadSousSol, GLU_SMOOTH); 
  gluQuadricTexture(quadSousSol, GL_TRUE); 
  gluCylinder(quadSousSol,3*theSize,3*theSize, 0.25*theSize,8,8);
  glPopMatrix();
  
  glBindTexture(GL_TEXTURE_2D,Tex[0]->id);
  glPushMatrix();
  glTranslatef(0,-1.25*theSize,0);
  glRotatef(90,1,0,0);
  GLUquadricObj * quadDiscSousSol = gluNewQuadric();
  gluQuadricNormals(quadDiscSousSol, GLU_SMOOTH); 
  gluQuadricTexture(quadDiscSousSol, GL_TRUE); 
  gluCylinder(quadDiscSousSol,0,3*theSize, 0.00001*theSize,8,8);  
  glPopMatrix();
  
}

void dessinerSecondEtage(){
  //toit
  glBindTexture(GL_TEXTURE_2D,Tex[2]->id);
  glPushMatrix();
  glTranslatef(0,4.4*theSize,0);
  glRotatef(90,1,0,0);
  GLUquadricObj * quadtoit = gluNewQuadric();
  gluQuadricNormals(quadtoit, GLU_SMOOTH); 
  gluQuadricTexture(quadtoit, GL_TRUE); 
  gluCylinder(quadtoit,0,2*theSize,0.6*theSize,16,16);
  glPopMatrix();
  
  //disctoit2
   glBindTexture(GL_TEXTURE_2D,Tex[10]->id);
  glPushMatrix();
  glTranslatef(0,3.8*theSize,0);
  glRotatef(90,1,0,0);
  GLUquadricObj * quaddisctoit2 = gluNewQuadric();
  gluQuadricNormals(quaddisctoit2, GLU_SMOOTH); 
  gluQuadricTexture(quaddisctoit2, GL_TRUE); 
  gluCylinder(quaddisctoit2,2*theSize,2*theSize,0.4*theSize,16,16);
  glPopMatrix();
  //bas du toit
  //disctoit2
   glBindTexture(GL_TEXTURE_2D,Tex[8]->id);
  glPushMatrix();
  glTranslatef(0,3.4*theSize,0);
  glRotatef(90,1,0,0);
  GLUquadricObj * quadbasdisctoit2 = gluNewQuadric();
  gluQuadricNormals(quadbasdisctoit2, GLU_SMOOTH); 
  gluQuadricTexture(quadbasdisctoit2, GL_TRUE); 
  gluCylinder(quadbasdisctoit2,0,2*theSize,0.001*theSize,16,16);
  glPopMatrix();
  
    
  glBindTexture(GL_TEXTURE_2D,Tex[9]->id);
  //core
  glPushMatrix();
  glTranslatef(0,3.4*theSize,0);
  //glRotatef(-b/180*PI,0,1,0);
  glRotatef(90,1,0,0);
  GLUquadricObj * quadseccore = gluNewQuadric();
  gluQuadricNormals(quadseccore, GLU_SMOOTH); 
  gluQuadricTexture(quadseccore, GL_TRUE); 
  gluCylinder(quadseccore,0.4*theSize,0.4*theSize,2*theSize,8,8);
  glPopMatrix();
  
  //disque du sol
  glBindTexture(GL_TEXTURE_2D,Tex[8]->id);
  glPushMatrix();
  glTranslatef(0,1.4*theSize,0);
  glRotatef(90,1,0,0);
  GLUquadricObj * quadSolSec = gluNewQuadric();
  gluQuadricNormals(quadSolSec, GLU_SMOOTH); 
  gluQuadricTexture(quadSolSec, GL_TRUE); 
  gluCylinder(quadSolSec,0,2*theSize,0.001*theSize,16,16);
  glPopMatrix();
  
  
  
}

void dessinerPoteau(int i, int max, int range){
	if(i<max){
		  //binder la pierre
		 
		 
  glBindTexture(GL_TEXTURE_2D,Tex[6]->id);
  /*//core
  glPushMatrix();
  glTranslatef(cos((i*2*PI)/max)*theSize*range,theSize,sin((i*2*PI)/max)*theSize*range);
  //glRotatef(b,0,1,0);
  glRotatef(90,1,0,0);
  GLUquadricObj * quadcore = gluNewQuadric();
  gluQuadricNormals(quadcore, GLU_SMOOTH); 
  gluQuadricTexture(quadcore, GL_TRUE); 
  gluCylinder(quadcore,0.02*theSize,0.02*theSize,2*theSize,8,8);
  glPopMatrix();*/
  
  if(range==1){
	   glPushMatrix();
  glTranslatef(cos((i*2*PI)/max)*theSize*range*1.2,theSize,sin((i*2*PI)/max)*theSize*range*1.2);
  //glRotatef(b,0,1,0);
  glRotatef(90,1,0,0);
  GLUquadricObj * quadcore = gluNewQuadric();
  gluQuadricNormals(quadcore, GLU_SMOOTH); 
  gluQuadricTexture(quadcore, GL_TRUE); 
  gluCylinder(quadcore,0.02*theSize,0.02*theSize,2*theSize,8,8);
  glPopMatrix();
  plane[i].move(cos((i*2*PI)/max)*theSize*range*1.2,cos(b/20+((i*2*PI)/max))*theSize/1.8,sin((i*2*PI)/max)*theSize*range*1.2);
  //rotation pour apparaitre à plat
    plane[i].setAngleX(-90);
  plane[i].setAngleZ(-(i*360)/max);
  
  glPushMatrix();
  //glRotatef(-(i*2*PI)/max,0,0,1);
  plane[i].dessiner(0.05);
  
  glPopMatrix();
  }
  else{
	   glPushMatrix();
  glTranslatef(cos((i*2*PI)/max)*theSize*range*0.9,theSize,sin((i*2*PI)/max)*theSize*range*0.9);
  //glRotatef(b,0,1,0);
  glRotatef(90,1,0,0);
  GLUquadricObj * quadcore = gluNewQuadric();
  gluQuadricNormals(quadcore, GLU_SMOOTH); 
  gluQuadricTexture(quadcore, GL_TRUE); 
  gluCylinder(quadcore,0.02*theSize,0.02*theSize,2*theSize,8,8);
  glPopMatrix();
	  plane[i].move(cos((i*2*PI)/max)*theSize*range*0.9,sin(b/20+((i*2*PI)/max))*theSize/1.8,sin((i*2*PI)/max)*theSize*range*0.90);
  
  plane[i].setAngleX(-90);
  plane[i].setAngleZ(-(i*360)/max);
  
  glPushMatrix();
  //glRotatef(-(i*2*PI)/max,0,0,1);
  plane[i].dessiner(0.07);
  
  glPopMatrix();
}
	}
}

//---dessiner le sol
void dessinerSolHerbe(){
	glBindTexture(GL_TEXTURE_2D,Tex[7]->id);
	glPushMatrix();
	glTranslatef(0,-1.5*theSize,0);
	glRotatef(90,1,0,0);
	glRotatef(90,0,0,1);
	GLUquadricObj * quadherbe = gluNewQuadric();
	gluQuadricNormals(quadherbe, GLU_SMOOTH); 
  gluQuadricTexture(quadherbe, GL_TRUE);
  gluCylinder(quadherbe,0,100*theSize,0.001,32,32);
	glPopMatrix();
	
}

//--------- les fonctions GLUT
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
  glEnable(GL_TEXTURE_2D);
  lum = new Lumiere();
  for(int i=0;i<10;i++){
  plane[i].setFilename("./x29_plane.off");
  plane[i].charger();
}
  
  //charger les texture, commencons par la pierre
  Tex[0] = ReadPNGFromFile("pierre.png");
      glGenTextures(1, &Tex[0]->id);

      glBindTexture(GL_TEXTURE_2D,Tex[0]->id);

      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      glTexImage2D (GL_TEXTURE_2D, 
		    0, 
		    Tex[0]->internalFormat, 
		    Tex[0]->width, 
		    Tex[0]->height, 
		    0, 
		    Tex[0]->format, 
		    GL_UNSIGNED_BYTE, 
		    Tex[0]->texels);
		    
  //pierre_noire
  Tex[1] = ReadPNGFromFile("pierre_noire.png");
      glGenTextures(1, &Tex[1]->id);

      glBindTexture(GL_TEXTURE_2D,Tex[1]->id);

      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      glTexImage2D (GL_TEXTURE_2D, 
		    0, 
		    Tex[1]->internalFormat, 
		    Tex[1]->width, 
		    Tex[1]->height, 
		    0, 
		    Tex[1]->format, 
		    GL_UNSIGNED_BYTE, 
		    Tex[1]->texels);
  //tuiles
  Tex[2] = ReadPNGFromFile("tuiles.png");
      glGenTextures(1, &Tex[2]->id);

      glBindTexture(GL_TEXTURE_2D,Tex[2]->id);

      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      glTexImage2D (GL_TEXTURE_2D, 
		    0, 
		    Tex[2]->internalFormat, 
		    Tex[2]->width, 
		    Tex[2]->height, 
		    0, 
		    Tex[2]->format, 
		    GL_UNSIGNED_BYTE, 
		    Tex[2]->texels);
		    
		      //core
  Tex[3] = ReadPNGFromFile("core.png");
      glGenTextures(1, &Tex[3]->id);

      glBindTexture(GL_TEXTURE_2D,Tex[3]->id);

      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      glTexImage2D (GL_TEXTURE_2D, 
		    0, 
		    Tex[3]->internalFormat, 
		    Tex[3]->width, 
		    Tex[3]->height, 
		    0, 
		    Tex[3]->format, 
		    GL_UNSIGNED_BYTE, 
		    Tex[3]->texels);
		    
		      //bois
  Tex[4] = ReadPNGFromFile("bois.png");
      glGenTextures(1, &Tex[4]->id);

      glBindTexture(GL_TEXTURE_2D,Tex[4]->id);

      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      glTexImage2D (GL_TEXTURE_2D, 
		    0, 
		    Tex[4]->internalFormat, 
		    Tex[4]->width, 
		    Tex[4]->height, 
		    0, 
		    Tex[4]->format, 
		    GL_UNSIGNED_BYTE, 
		    Tex[4]->texels);
		    
	//tuiles
	Tex[5] = ReadPNGFromFile("fresque.png");
      glGenTextures(1, &Tex[5]->id);

      glBindTexture(GL_TEXTURE_2D,Tex[5]->id);

      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      glTexImage2D (GL_TEXTURE_2D, 
		    0, 
		    Tex[5]->internalFormat, 
		    Tex[5]->width, 
		    Tex[5]->height, 
		    0, 
		    Tex[5]->format, 
		    GL_UNSIGNED_BYTE, 
		    Tex[5]->texels);
		    
	//or
		Tex[6] = ReadPNGFromFile("texturedoree.png");
      glGenTextures(1, &Tex[6]->id);

      glBindTexture(GL_TEXTURE_2D,Tex[6]->id);

      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      glTexImage2D (GL_TEXTURE_2D, 
		    0, 
		    Tex[6]->internalFormat, 
		    Tex[6]->width, 
		    Tex[6]->height, 
		    0, 
		    Tex[6]->format, 
		    GL_UNSIGNED_BYTE, 
		    Tex[6]->texels);
		    
	//herbe
		Tex[7] = ReadPNGFromFile("grass.png");
      glGenTextures(1, &Tex[7]->id);

      glBindTexture(GL_TEXTURE_2D,Tex[7]->id);

      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      glTexImage2D (GL_TEXTURE_2D, 
		    0, 
		    Tex[7]->internalFormat, 
		    Tex[7]->width, 
		    Tex[7]->height, 
		    0, 
		    Tex[7]->format, 
		    GL_UNSIGNED_BYTE, 
		    Tex[7]->texels);	
		//solSec
		
		Tex[8] = ReadPNGFromFile("solsec.png");
      glGenTextures(1, &Tex[8]->id);

      glBindTexture(GL_TEXTURE_2D,Tex[8]->id);

      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      glTexImage2D (GL_TEXTURE_2D, 
		    0, 
		    Tex[8]->internalFormat, 
		    Tex[8]->width, 
		    Tex[8]->height, 
		    0, 
		    Tex[8]->format, 
		    GL_UNSIGNED_BYTE, 
		    Tex[8]->texels);
		    
		    //sun
		    	Tex[9] = ReadPNGFromFile("sun.png");
      glGenTextures(1, &Tex[9]->id);

      glBindTexture(GL_TEXTURE_2D,Tex[9]->id);

      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      glTexImage2D (GL_TEXTURE_2D, 
		    0, 
		    Tex[9]->internalFormat, 
		    Tex[9]->width, 
		    Tex[9]->height, 
		    0, 
		    Tex[9]->format, 
		    GL_UNSIGNED_BYTE, 
		    Tex[9]->texels);
		    
		        //fresque2
		    	Tex[10] = ReadPNGFromFile("fresque2.png");
      glGenTextures(1, &Tex[10]->id);

      glBindTexture(GL_TEXTURE_2D,Tex[10]->id);

      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      glTexImage2D (GL_TEXTURE_2D, 
		    0, 
		    Tex[10]->internalFormat, 
		    Tex[10]->width, 
		    Tex[10]->height, 
		    0, 
		    Tex[10]->format, 
		    GL_UNSIGNED_BYTE, 
		    Tex[10]->texels);
}

void Display(void)
{

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  gluLookAt(0,8,20,0,0,0,0,1,0);
  //skybox->SetPosition(0,0,10);
 // skybox->Activate();
 lum->set_Lumiere_Position(theSize*cos(b/180*PI),0.1*theSize,theSize*sin(b/180*PI),0.0);  
 lum->ActiveLight();
  
  glPushMatrix();
  glRotatef(b,0,1,0);


//dessiner le manege à l'echelle scale
  dessinerSecondEtage();
  dessinerManege();
  dessinerPoteau(0,8,1);
  dessinerPoteau(1,8,1);
  dessinerPoteau(2,8,1);
  dessinerPoteau(3,8,1);
  dessinerPoteau(4,8,1); 
  dessinerPoteau(5,8,1); 
  dessinerPoteau(6,8,1); 
  dessinerPoteau(7,8,1);
  dessinerPoteau(0,8,2);
  dessinerPoteau(1,8,2);
  dessinerPoteau(2,8,2);
  dessinerPoteau(3,8,2);
  dessinerPoteau(4,8,2); 
  dessinerPoteau(5,8,2); 
  dessinerPoteau(6,8,2); 
  dessinerPoteau(7,8,2); 
  

  glPopMatrix();
  
  //popgénéral
  glPopMatrix();
  
  //ici on doit dessiner le sol , si on veux qu'il soit fixe
  dessinerSousSol();
 dessinerSolHerbe();
  glutSwapBuffers();
    
}



void Reshape(int Width, int Height)
{
  glViewport(0, 0, (GLsizei)Width, (GLsizei)Height);

}

void Idle()
{
	b += 0.06;
    
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
