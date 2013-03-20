#ifndef _MATIERE_H
#define _MATIERE_H

#include <fstream>
#include <string>
#include <math.h>
#include <GL/glut.h>

class Matiere
{

 private:
 //{Propriétés réflectives de l'objet touché par la lumière}
  GLfloat Matiere_Ambiente[4];
  GLfloat Matiere_Diffuse[4];
  GLfloat Matiere_Speculaire[4];
  int shine;

 public :
  
  Matiere();
  void ActiveMat ();
  void DisactiveMat ();

  void set_Matiere_Ambiente(GLfloat a, GLfloat b, GLfloat c, GLfloat d);
  void set_Matiere_Diffuse(GLfloat a, GLfloat b, GLfloat c, GLfloat d);
  void set_Matiere_Speculaire(GLfloat a, GLfloat b, GLfloat c, GLfloat d);
  void set_Shininess(int shin);

  void get_All_Mat();
  
};

#endif
