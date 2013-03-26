#include <iostream>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "lecteur.h"

using namespace std;

int test = 0;
bool image = false;
bool color = false;

int material = 0;

float c = 0;
float angle_light = 0;


GLubyte TextureRGBA16[32] = {
  0xFF,0,0,0,//red
  0,0xFF,0,0,//green
  0,0,0xFF,0,//blue
  0xFF,0xFF,0xFF,0, //white
  0xFF,0xFF,0x00,0, //yellow
  0xFF,0x8C,0x00,0, //orange
  0x99,0x33,0x00,0, //brown
  0xCC,0x33,0xCC,0//purple
};


GLubyte TRGBA[36] = {
0xD2,0x69,0x1E,0,	 
0xFF,0x7F,0x24,0,	 
0xEE,0x76,0x21,0,	 
0xCD,0X66,0x1D,0,	 
0x8B,0x45,0x13,0,
0xFF,0x7F,0x50,0	,	 
0xFF,0x72,0x56,0, 
0xEE,0x6A,0x50,0,	 
0xCD,0x5B,0x45,0
};


static GLfloat sommets[] = {-1,-1,-1,                      
			    1,-1,-1,//2
			    1,1,-1,//8
                            -1,1,-1//6
			   };
			   
static GLfloat TextTableauRGBA[] = {
  0.0,0.0,
  0.0,1.0,
  1.0,1.0,
  1.0,0.0
};

static unsigned int indices[4] = {0,1,2,3};

GLuint texid[2];
GLubyte* data;
int width, height;




void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(70,1,0.001,100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    data=glmReadPPM("brick10.ppm", &width , &height); 
    glGenTextures (2, &texid[0]);
    glBindTexture (GL_TEXTURE_2D, texid[0]);
    glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, 2, 4, 0, GL_RGBA, GL_UNSIGNED_BYTE, TextureRGBA16);
    
    glBindTexture (GL_TEXTURE_2D, texid[1]); 
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width,height, 0, GL_RGB, GL_UNSIGNED_BYTE,data);
     
    

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3,GL_FLOAT,0,sommets);
    glEnableClientState(GL_INDEX_ARRAY);
    glIndexPointer(GL_UNSIGNED_INT,0,indices);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, 0, TextTableauRGBA);
    
    glEnable(GL_TEXTURE_2D);
}

void Display(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glTranslatef(0.0,0.0,-6.0);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);   
    if (!image) {
      glBindTexture (GL_TEXTURE_2D, texid[0]); 
      glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
       
    }
    else {
      glBindTexture (GL_TEXTURE_2D, texid[1]);	  
      if (color)
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
      else
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
      
    }
     //glEnable(GL_TEXTURE_2D);
     //glColor3f(1.0,0.0,0.0);
    
    /*switch (test) {
    case 0:
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);  	
	
	glBegin(GL_QUADS);
        glTexCoord2f(0, 1);
        glVertex3f(-1.0,-1.0,0.0);
        glTexCoord2f(1, 1);
        glVertex3f(1.0,-1.0,0.0);
        glTexCoord2f(1, 0);
        glVertex3f(1.0,1.0,0.0);
        glTexCoord2f(0, 0);
        glVertex3f(-1.0,1.0,0.0);
        glEnd();
        break;
    case 1:
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);       
        glBegin(GL_QUADS);
        glTexCoord2f(0, 1);
        glVertex3f(-1.0,-1.0,0.0);
        glTexCoord2f(1, 1);
        glVertex3f(1.0,-1.0,0.0);
        glTexCoord2f(1, 0);
        glVertex3f(1.0,1.0,0.0);
        glTexCoord2f(0, 0);
        glVertex3f(-1.0,1.0,0.0);
        glEnd();
      break;
    case 2:
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);   
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex3f(-1.0,-1.0,0.0);
        glTexCoord2f(2, 0);
        glVertex3f(1.0,-1.0,0.0);
        glTexCoord2f(2, 2);
        glVertex3f(1.0,1.0,0.0);
        glTexCoord2f(0, 2);
        glVertex3f(-1.0,1.0,0.0);
        glEnd();
        break;
	case 3:
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);   
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex3f(-1.0,-1.0,0.0);
        glTexCoord2f(2, 0);
        glVertex3f(1.0,-1.0,0.0);
        glTexCoord2f(2, 2);
        glVertex3f(1.0,1.0,0.0);
        glTexCoord2f(0, 2);
        glVertex3f(-1.0,1.0,0.0);
        glEnd();
        break;
	case 4:
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);   
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex3f(-1.0,-1.0,0.0);
        glTexCoord2f(2, 0);
        glVertex3f(1.0,-1.0,0.0);
        glTexCoord2f(2, 2);
        glVertex3f(1.0,1.0,0.0);
        glTexCoord2f(0, 2);
        glVertex3f(-1.0,1.0,0.0);
        glEnd();
        break;
	case 5:
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);   
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex3f(-1.0,-1.0,0.0);
        glTexCoord2f(2, 0);
        glVertex3f(1.0,-1.0,0.0);
        glTexCoord2f(2, 2);
        glVertex3f(1.0,1.0,0.0);
        glTexCoord2f(0, 2);
        glVertex3f(-1.0,1.0,0.0);
        glEnd();
        break;
    case 6:
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);   
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0.34);
        glVertex3f(-1.0,-1.0,0.0);
        glTexCoord2f(0.5, 0.34);
        glVertex3f(1.0,-1.0,0.0);
        glTexCoord2f(0.5, 1);
        glVertex3f(1.0,1.0,0.0);
        glTexCoord2f(0, 1);
        glVertex3f(-1.0,1.0,0.0);
        glEnd();
      

  break;
    case 7:
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST); 
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex3f(-1.0,-1.0,0.0);
        glTexCoord2f(0.5, 0);
        glVertex3f(1.0,-1.0,0.0);
        glTexCoord2f(0.5, 2.2);
        glVertex3f(1.0,1.0,0.0);
        glTexCoord2f(0, 2.2);
        glVertex3f(-1.0,1.0,0.0);
        glEnd();
	break;
     case 8:
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST); 
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex3f(-1.0,-1.0,0.0);
        glTexCoord2f(0.5, 0);
        glVertex3f(1.0,-1.0,0.0);
        glTexCoord2f(0.5, 2);
        glVertex3f(1.0,1.0,0.0);
        glTexCoord2f(0, 2);
        glVertex3f(-1.0,1.0,0.0);
        glEnd();
        break;      
    case 9:
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);   
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
        glBegin(GL_QUADS);
        glTexCoord2f(0.25, 0.25);
        glVertex3f(-1.0,-1.0,0.0);
        glTexCoord2f(0.75, 0.25);
        glVertex3f(1.0,-1.0,0.0);
        glTexCoord2f(0.75, 0.75);
        glVertex3f(1.0,1.0,0.0);
        glTexCoord2f(0.25, 0.75);
        glVertex3f(-1.0,1.0,0.0);
        glEnd();
        break;	
    }

    glTranslatef(-2.5,0,0);
    glBegin(GL_TRIANGLES);
    glTexCoord2f(0,0);
    glVertex3f(-1,0,0);
    glTexCoord2f(1,0);
    glVertex3f(1,0,0);
    glTexCoord2f(0.5,2);
    glVertex3f(0,1,0);
    glEnd();
// 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);

    glTranslatef(5,0,0);
    glBegin(GL_TRIANGLES);
    glVertex3f(-1,0,0);
    glVertex3f(0,1,0);
    glVertex3f(1,0,0);
    
    
    
    glEnd();
*/
	//inserer dessins ici
	
	//central
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);   
	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
        //glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(-1.0,-1.0,0.0);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(1.0,-1.0,0.0);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(1.0,1.0,0.0);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(-1.0,1.0,0.0);
        glEnd();

	//haut gauche
	glPushMatrix();
	glTranslatef(-2.0,2.0,0);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);   
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
        glBegin(GL_QUADS);
        glTexCoord2f(2.0, 2.5);
        glVertex3f(-1.0,-1.0,0.0);
        glTexCoord2f(2.0, 0.0);
        glVertex3f(1.0,-1.0,0.0);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(1.0,1.0,0.0);
        glTexCoord2f(0.0, 2.5);
        glVertex3f(-1.0,1.0,0.0);
        glEnd();
	glPopMatrix();

	//haut droite
	glPushMatrix();
	glTranslatef(2.0,2.0,0);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);   
	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
        //glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
        glBegin(GL_QUADS);
        glTexCoord2f(0.15, 1.0);
        glVertex3f(-1.0,-1.0,0.0);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(1.0,-1.0,0.0);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(1.0,1.0,0.0);
        glTexCoord2f(0.15, 0.0);
        glVertex3f(-1.0,1.0,0.0);
        glEnd();
	glPopMatrix();

    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
//     
//     // Avec les tableaux de sommets
//     
 //   glTranslatef(-4.0,2.5,0);
  //  glDrawElements(GL_QUADS,4,GL_UNSIGNED_INT,indices);
    
    glutSwapBuffers();

}

void Reshape(int Width, int Height)
{
    glViewport(0, 0, (GLsizei)Width, (GLsizei)Height);

}

void Idle()
{
 
    glutPostRedisplay();
}

void ClavierClassique(unsigned char key, int x, int y)
{
  switch(key) {	
    case '0':
        test=0;
        break;
    case '1':
        test=1;
        break;
    case '2':
        test=2;
        break;
    case '3':
        test=3;
        break;
    case '4':
        test=4;
        break;
    case '5':
        test=5;
        break;
    case '6':
        test=6;
        break;
    case '7':
        test=7;
        break;	
	case '8':
        test=8;
        break;
    case '9':
        test=9;
        break;
    case 'c':
	color=!color;
	break;
    case 'i':
      image = !image;
      break;
    case 0x1B:
        exit(0);
    }
}

void ClavierSpecial(int key, int x, int y)
{
  switch(key) {
    case GLUT_KEY_UP:
      break;
    case GLUT_KEY_DOWN:
      break;
    case GLUT_KEY_RIGHT:
      break;
    case GLUT_KEY_LEFT:
      break;
    case GLUT_KEY_PAGE_UP:
      break;
    case GLUT_KEY_PAGE_DOWN:
      break;
  }
}

void Souris(int bouton, int etat, int x, int y)
{
  switch (bouton) {
    case GLUT_LEFT_BUTTON :
 
        break;
    }
}

void Motion (int x, int y)
{

    
}
int main(int argc, char** argv)
{
    glutInit (&argc,argv) ;
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH) ;

    glutInitWindowSize (500,500) ;
    glutInitWindowPosition (100, 100) ;
    glutCreateWindow ("Tutoriel 5") ;

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
