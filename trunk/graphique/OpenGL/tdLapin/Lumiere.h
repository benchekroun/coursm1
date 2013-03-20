#ifndef _LUMIERE_H
#define _LUMIERE_H

#include <fstream>
#include <string>
#include <math.h>
#include <GL/glut.h>

class Lumiere 
{
 private :
  //{Propriété de la lumière}
  GLfloat Lumiere_Ambiente[4];
  GLfloat Lumiere_Diffuse[4];
  GLfloat Lumiere_Speculaire[4];
  GLfloat Lumiere_Position[4];

 public :
  
  Lumiere();
  void ActiveLight ();
  void DisactiveLight ();
 
  void set_Lumiere_Ambiente(GLfloat a, GLfloat b, GLfloat c, GLfloat d);
  void set_Lumiere_Diffuse(GLfloat a, GLfloat b, GLfloat c, GLfloat d);
  void set_Lumiere_Speculaire(GLfloat a, GLfloat b, GLfloat c, GLfloat d);
  void set_Lumiere_Position(GLfloat a, GLfloat b, GLfloat c, GLfloat d);

  void get_All_Light();
  
};

#endif
