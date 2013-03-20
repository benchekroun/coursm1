#include <fstream>
#include <string>
#include <math.h>
#include <iostream>
#include <GL/glut.h>
#include "Matiere.h"

using namespace std;
  
Matiere::Matiere(){
  Matiere_Ambiente[0] = 0.1;
  Matiere_Ambiente[1] = 0.1;
  Matiere_Ambiente[2] = 0.1;
  Matiere_Ambiente[3] = 1.0;

  Matiere_Diffuse[0] = 0.1;
  Matiere_Diffuse[1] = 0.1;
  Matiere_Diffuse[2] = 0.1;
  Matiere_Diffuse[3] = 1.0;

  Matiere_Speculaire[0] = 0.1;
  Matiere_Speculaire[1] = 0.1;
  Matiere_Speculaire[2] = 0.1;
  Matiere_Speculaire[3] = 1.0;

  shine = 50;
}

void Matiere::set_Matiere_Ambiente(GLfloat a, GLfloat b, GLfloat c, GLfloat d){
  Matiere_Ambiente[0] = a;
  Matiere_Ambiente[1] = b;
  Matiere_Ambiente[2] = c;
  Matiere_Ambiente[3] = d;
}
void Matiere::set_Matiere_Diffuse(GLfloat a, GLfloat b, GLfloat c, GLfloat d){
 
  Matiere_Diffuse[0] = a;
  Matiere_Diffuse[1] = b;
  Matiere_Diffuse[2] = c;
  Matiere_Diffuse[3] = d;
}
void Matiere::set_Matiere_Speculaire(GLfloat a, GLfloat b, GLfloat c, GLfloat d){
  Matiere_Speculaire[0] = a;
  Matiere_Speculaire[1] = b;
  Matiere_Speculaire[2] = c;
  Matiere_Speculaire[3] = d;
}
void Matiere::set_Shininess(int shin){
  shine = shin;
}
   
void Matiere::get_All_Mat(){
  int i=0;
  cout<<"Matiere_Ambiente :"<<endl;
  for(i=0;i<4;i++)cout<<Matiere_Ambiente[i]<<endl;
  cout<<"Matiere_Diffuse :"<<endl;
  for(i=0;i<4;i++)cout<<Matiere_Diffuse[i]<<endl;
  cout<<"Matiere_Speculaire :"<<endl;
  for(i=0;i<4;i++)cout<<Matiere_Speculaire[i]<<endl;
  cout<<"Shininess :"<<shine<<endl;
}

  
void Matiere::ActiveMat (){
    glEnable(GL_COLOR_MATERIAL);

    glMaterialfv( GL_FRONT, GL_AMBIENT, Matiere_Ambiente);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, Matiere_Diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, Matiere_Speculaire);
    glMaterialf( GL_FRONT, GL_SHININESS, shine);
  }

void Matiere::DisactiveMat(){ 
    glDisable(GL_COLOR_MATERIAL);
}
