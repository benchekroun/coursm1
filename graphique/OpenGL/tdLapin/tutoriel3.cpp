#include <iostream>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "ObjetOFF.h"
#include "Lumiere.h"
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

static GLfloat sommets[] = {-1,-1,-1,//0
                            0,-1,-1,//1
			    1,-1,-1,//2
			    -1,0,-1,//3
                            0,0,-1,//4
			    1,0,-1,//5
			    -1,1,-1,//6
                            0,1,-1,//7
			    1,1,-1,//8
			    
			    -1,-1,0,//9
                            0,-1,0,//10
			    1,-1,0,//11
			    -1,0,0,//12
                            0,0,0,//13
			    1,0,0,//14
			    -1,1,0,//15
                            0,1,0,//16
			    1,1,0,//17
			    
			    -1,-1,1,//18
                            0,-1,1,//19
			    1,-1,1,//20
			    -1,0,1,//21
                            0,0,1,//22
			    1,0,1,//23
			    -1,1,1,//24
                            0,1,1,//25
			    1,1,1	//26		  						 
};
		
static GLfloat couleurs[] = { 1.0,0.0,0.0, 	                
			      1.0,0.0,0.0, 	                      
			      1.0,0.0,0.0, 	                      
	                      1.0,0.0,0.0, 	                      
			      1.0,0.0,0.0, 	                      
			      1.0,0.0,0.0,			      
			      1.0,0.0,0.0, 
			      1.0,0.0,0.0,			      
			      1.0,0.0,0.0,
	                      0.0,1.0,0.0, 
	                      0.0,1.0,0.0, 
			      0.0,1.0,0.0, 
			      0.0,1.0,0.0, 
	                      0.0,1.0,0.0, 
			      0.0,1.0,0.0, 
			      0.0,1.0,0.0, 
			      0.0,1.0,0.0, 
	                      0.0,1.0,0.0, 
	                      0.0,0.0,1.0, 
	                      0.0,0.0,1.0, 
	                      0.0,0.0,1.0, 			      
	                      0.0,0.0,1.0, 
			      0.0,0.0,1.0,
			      0.0,0.0,1.0, 
	                      0.0,0.0,1.0,
			      0.0,0.0,1.0,
			      0.0,0.0,1.0
};
	
static unsigned int indices[] = {
  //red
  0,2,8,
  0,6,8,
  0,2,6,
				 
				 
				 
  //green
  9,11,17,
  9,15,17,
  9,11,15,
				 
				

  //blue
  18,20,26,
  18,24,26,
  18,20,24
};


static GLfloat sommets2[] = {
  /* 18,20,15,
     18,20,17,*/

                           
  -1,1,-1,//6
                         
  1,1,-1,//8
			    
  -1,-1,0,//9
                           
  1,-1,0,//11
			    
  -1,1,0,//15
                            
  1,1,0,//17
			    
  -1,-1,1,//18
                            
  1,-1,1//20
			   	  						 


  /* 9,11,6,
     9,11,8,*/
};
static GLfloat couleurs2[] = {
  //rouge-vert
  1.0,1.0,1.0,
  1.0,1.0,1.0,
  1.0,1.0,1.0,
  1.0,1.0,1.0,

  //vert-blue
  1.0,1.0,1.0,
  1.0,1.0,1.0,
  1.0,1.0,1.0,
  1.0,1.0,1.0
};

static unsigned int indices2[] = {
  //green-blue
  7,8,5,
  7,8,6,
  //green-red
  3,4,1,
  3,4,2

};

bool calculated;
float alpha =0.0;
float b=0.0;
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
  lum = new Lumiere();
  lapin.setFilename("./myfile.off");
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
  if(!calculated){
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
  }

  gluLookAt(minX+((maxX-minX)/2.0),minY+((maxY-minY)/2.0),maxZ+alpha,minX+((maxX-minX)/2.0),minY+((maxY-minY)/2.0),minZ+((maxZ-minZ)/2.0),0,1,0);
    
  lapin.colorer(255,200,200,255);
  lapin.setAngleY(b);
  lapin.dessiner();
  lapin.drawNormals();
  // A obtenir
  // Nouveau tableau d'indices et utiliser glArrayElement puis glDrawElements avec GL_TRIANGLES
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
