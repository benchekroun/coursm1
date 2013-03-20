#ifndef _OBJET_OFF_H
#define _OBJET_OFF_H

#include <fstream>
#include <iostream>
#include <string>
#include "Objet3D.h"
#include "Matiere.h"

using namespace std;

class ObjetOFF : public Objet3D
{
 private :

  Matiere m;

 public :
  
  void charger()
  {

    ifstream file (_filename.c_str(), ios::in);    
    if(_filename=="") cout <<"Pas de maillage .OFF associé"<<endl;    
    else {
      if(file) {	
	string filetype;
	int nbbords;
	file >> filetype;	
	if (filetype=="OFF")
	  {	    
	    file >> _nb_vertices;
	    file >> _nb_index;
	    file >> nbbords;	    
	    /* tableau de points */
	    _vertices = new float[_nb_vertices*3];
	    _index = new unsigned int[_nb_index*3];	 
	    int x;
	    for (unsigned int i = 0; i<_nb_vertices*3; i = i+3)
	      {
		file >> _vertices[i] >> _vertices[i+1] >> _vertices [i+2];
	      }
	    
	    for (unsigned int j= 0 ;j<_nb_index*3 ; j=j+3)
	      {
		file >> x; 
		file >> _index[j] >> _index[j+1] >> _index[j+2];
	      }
	    //AfficherVertices();
	  }
	else {cout<< "type de fichier non pris en charge"<<endl;}	
	file.close();	
      }
      else cerr << "Impossible d'ouvrir le fichier !" << endl;
    }
    genNormal();	    
  } 

  void dessiner(float scale = 1.){
    m.ActiveMat();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);  
    glCullFace(GL_BACK);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glVertexPointer(3,GL_FLOAT,0,_vertices);
    glNormalPointer(GL_FLOAT,0,_normals);
    glPushMatrix();
    glColor4ub(_c.x, _c.y, _c.z, _c.a);
    glTranslatef(_posX, _posY, _posZ);
    glRotatef(_angleX,1.,0.,0.); 
    glRotatef(_angleY,0.,1.,0.); 
    glRotatef(_angleZ,0.,0.,1.); 
    glScalef((float)scale,(float)scale,(float)scale);
    glDrawElements(GL_TRIANGLES,_nb_index*3,GL_UNSIGNED_INT,_index);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glColor4f(1., 1., 1., 1.);
    //drawNormals();
    glPopMatrix();

    m.DisactiveMat();
  }

  void set_mat_Ambiente(GLfloat a, GLfloat b, GLfloat c, GLfloat d){
    m.set_Matiere_Ambiente(a, b, c, d);
  }
  void set_mat_Diffuse(GLfloat a, GLfloat b, GLfloat c, GLfloat d){    
    m.set_Matiere_Diffuse(a, b, c, d);
  }
  void set_mat_Speculaire(GLfloat a, GLfloat b, GLfloat c, GLfloat d){
    m.set_Matiere_Speculaire(a, b, c, d);
  }
  void set_shininess(int sh){
    m.set_Shininess(sh);
  }
  void get_All_mat(){
    m.get_All_Mat();
  }

  /*  **** Affichage des tableaux ****  */
  /*
  void AfficherVertices(){
    cout << "Vertices :"<<endl;
    for (unsigned int l = 0; l<_nb_vertices*3; l = l+3)
      { 
	cout << vertices[l] << vertices[l+1] << vertices [l+2];
	cout << endl;
      }	    
    cout << "Index : "<< endl;
    for (unsigned int u= 0 ;u<_nb_index*4 ; u=u+4)
      {
	cout << Index[u] << Index[u+1] << Index[u+2] << Index[u+3];
	cout << endl;
      }
  }
  */
};

#endif
