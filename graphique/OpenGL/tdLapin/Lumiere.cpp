#include <fstream>
#include <string>
#include <math.h>
#include <iostream>
#include <GL/glut.h>
#include "Lumiere.h"


using namespace std;
  

Lumiere::Lumiere(){
  Lumiere_Ambiente[0] = 0.3;
  Lumiere_Ambiente[1] = 0.3;
  Lumiere_Ambiente[2] = 0.3;
  Lumiere_Ambiente[3] = 1.0;

  Lumiere_Diffuse[0] = 0.6;
  Lumiere_Diffuse[1] = 0.6;
  Lumiere_Diffuse[2] = 0.6;
  Lumiere_Diffuse[3] = 1.0;

  Lumiere_Speculaire[0] = 0.03;
  Lumiere_Speculaire[1] = 0.03;
  Lumiere_Speculaire[2] = 0.03;
  Lumiere_Speculaire[3] = 1.0;

  Lumiere_Position[0] = 512.0;
  Lumiere_Position[1] = 512.0;
  Lumiere_Position[2] = 350.0;
  Lumiere_Position[3] = 1.0;
}
 
void Lumiere::set_Lumiere_Ambiente(GLfloat a, GLfloat b, GLfloat c, GLfloat d){
  Lumiere_Ambiente[0] = a;
  Lumiere_Ambiente[1] = b;
  Lumiere_Ambiente[2] = c;
  Lumiere_Ambiente[3] = d;
}
void Lumiere::set_Lumiere_Diffuse(GLfloat a, GLfloat b, GLfloat c, GLfloat d){
  Lumiere_Diffuse[0] = a;
  Lumiere_Diffuse[1] = b;
  Lumiere_Diffuse[2] = c;
  Lumiere_Diffuse[3] = d;
}
void Lumiere::set_Lumiere_Speculaire(GLfloat a, GLfloat b, GLfloat c, GLfloat d){
  Lumiere_Speculaire[0] = a;
  Lumiere_Speculaire[1] = b;
  Lumiere_Speculaire[2] = c;
  Lumiere_Speculaire[3] = d;
}  
void Lumiere::set_Lumiere_Position(GLfloat a, GLfloat b, GLfloat c, GLfloat d){
  Lumiere_Position[0] = a;
  Lumiere_Position[1] = b;
  Lumiere_Position[2] = c;
  Lumiere_Position[3] = d;
} 
   
void Lumiere::get_All_Light(){
  int i=0;
  cout<<"Lumiere_Ambiente :"<<endl;
  for(i=0;i<4;i++)cout<<Lumiere_Ambiente[i]<<endl;
  cout<<"Lumiere_Diffuse :"<<endl;
  for(i=0;i<4;i++)cout<<Lumiere_Diffuse[i]<<endl;
  cout<<"Lumiere_Speculaire :"<<endl;
  for(i=0;i<4;i++)cout<<Lumiere_Speculaire[i]<<endl;
  cout<<"Lumiere_Position :"<<endl;
  for(i=0;i<4;i++)cout<<Lumiere_Position[i]<<endl;
}

  
void Lumiere::ActiveLight (){
   glEnable(GL_LIGHTING);    
    glEnable(GL_LIGHT0);

    glLightfv( GL_LIGHT0, GL_AMBIENT, Lumiere_Ambiente );
    glLightfv( GL_LIGHT0, GL_DIFFUSE, Lumiere_Diffuse );
    glLightfv( GL_LIGHT0, GL_SPECULAR, Lumiere_Speculaire );
    glLightfv( GL_LIGHT0, GL_POSITION, Lumiere_Position );
  }

void Lumiere::DisactiveLight(){  
    glDisable(GL_LIGHTING); 
    glDisable(GL_LIGHT0);
}
