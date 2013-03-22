#ifndef _OBJET3D_H
#define _OBJET3D_H

#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

struct OBJ_color
{
  char x,y,z,a;
};

class Objet3D
{


 protected :
  float 
    _posX,
    _posY,
    _posZ,
    _angleX,
    _angleY,
    _angleZ,
    _minZ;

  OBJ_color _c ;
  
  float * _vertices ;
  float * _texcoord ;
  float * _normals;
  
  unsigned int * _index ;
  unsigned int _nb_vertices;
  unsigned int _nb_index;
  unsigned int _nb_texcoord;
  unsigned int _nb_normals;
  
  string _filename;
  string _texname;

 public :
 Objet3D(float x=0., float y=0., float z=0.): _posX(x),_posY(y),_posZ(z)
  {
    _angleX = 0.;
    _angleY = 0.;
    _angleZ = 0.;
    _c.x=255;
    _c.y=255;
    _c.z=255;
    _c.a=0;
    _vertices=NULL ;
    _texcoord=NULL ;
    _index=NULL ;
    _normals=NULL;
    
    _nb_vertices=0;
    _nb_index=0;
    _nb_texcoord=0;
    _nb_normals=0;
    
    _filename="";
    _texname="";
  }
  
  Objet3D(const Objet3D & o)
    {
      /* delete de l'existant */
      if(_vertices)
	{
	  delete [] _vertices;
	}

      if(_index)
	{
	  delete [] _index;
	}
      
      if(_texcoord)
	{
	  delete [] _texcoord; 
	}
      
      if(_normals)
	{
	  delete [] _normals;
	}
      
      _posX = o.getPosX();
      _posY = o.getPosY();
      _posZ = o.getPosZ();
      _angleX = o.getAngleX();
      _angleY = o.getAngleY();
      _angleZ = o.getAngleZ();
      _c = o.getColor();
      
      _nb_vertices = o.getNbVertices();;
      _nb_index = o.getNbIndex();
      _nb_texcoord = o.getNbTexCoord();
      _nb_normals = o.getNbNormals();
      
      _vertices = new float[3*_nb_vertices];
      for (int i = 0; i<3*_nb_vertices ; i++){
	_vertices[i]= o.getVertices()[i];
      }
      
      _index = new unsigned int[_nb_index];
      for (int i = 0; i<_nb_index ; i++){
	_index[i]= o.getIndex()[i];
      }
      
      _texcoord = new float[2*_nb_texcoord];
      for (int i = 0; i<2*_nb_texcoord ; i++){
	_texcoord[i]= o.getTexCoord()[i];
      }
      
      _normals = new float[3*_nb_normals];
      for (int i = 0; i<3*_nb_normals ; i++){
	_normals[i]= o.getNormals()[i];
      }
      
      _filename=o.getFilename();
      _texname=o.getTexname();
    }

  Objet3D & operator= (const Objet3D &o)
    {
      if(this!=&o){
	/* delete de l'existant */
	if(_vertices)
	  {
	    delete [] _vertices;
	  }

	if(_index)
	  {
	    delete [] _index;
	  }
      
	if(_texcoord)
	  {
	    delete [] _texcoord; 
	  }
      
	if(_normals)
	  {
	    delete [] _normals;
	  }
      
	_posX = o.getPosX();
	_posY = o.getPosY();
	_posZ = o.getPosZ();
	_angleX = o.getAngleX();
	_angleY = o.getAngleY();
	_angleZ = o.getAngleZ();
	_c = o.getColor();
      
	_nb_vertices = o.getNbVertices();;
	_nb_index = o.getNbIndex();
	_nb_texcoord = o.getNbTexCoord();
	_nb_normals = o.getNbNormals();
      
	_vertices = new float[3*_nb_vertices];
	for (int i = 0; i<3*_nb_vertices ; i++){
	  _vertices[i]= o.getVertices()[i];
	}
      
	_index = new unsigned int[_nb_index];
	for (int i = 0; i<_nb_index ; i++){
	  _index[i]= o.getIndex()[i];
	}
      
	_texcoord = new float[2*_nb_texcoord];
	for (int i = 0; i<2*_nb_texcoord ; i++){
	  _texcoord[i]= o.getTexCoord()[i];
	}
      
	_normals = new float[3*_nb_normals];
	for (int i = 0; i<3*_nb_normals ; i++){
	  _normals[i]= o.getNormals()[i];
	}

	_filename= o.getFilename();
	_texname= o.getTexname();
	
      }
    }	
  
  virtual ~Objet3D()
    {
      /* delete de l'existant */
      if(_vertices)
	{
	  delete [] _vertices;
	}

      if(_index)
	{
	  delete [] _index;
	}
      
      if(_texcoord)
	{
	  delete [] _texcoord; 
	}
      
      if(_normals)
	{
	  delete [] _normals;
	}
    }
  
  /* observateurs */
  float getPosX() const {return _posX;}
  float getPosY() const {return _posY;}
  float getPosZ() const {return _posZ;}
  float getAngleX() const {return _angleX;}  
  float getAngleY() const {return _angleY;}
  float getAngleZ() const {return _angleZ;}
  OBJ_color getColor() const {return _c;}
  float * getVertices() const {return _vertices;}
  unsigned int * getIndex() const {return _index;}
  float * getTexCoord() const {return _texcoord;}
  float * getNormals() const {return _normals;}
  unsigned int getNbVertices() const {return _nb_vertices;}
  unsigned int getNbIndex() const {return _nb_index;}
  unsigned int getNbTexCoord() const {return _nb_texcoord;}
  unsigned int getNbNormals() const {return _nb_normals;}
  string getFilename() const {return _filename;}
  string getTexname() const {return _texname;}

  /* accesseurs */
  void setPosX(float x)
  {
    _posX = x;
  }
  
  void setPosY(float y)
  {
    _posY = y;
  }
  
  void setPosZ(float z)
  {
    _posZ = z;
  }
  
  void move(float x, float y, float z)
  {
    _posX = x; _posY = y; _posZ = z;
  }

  void setAngleX(float ax)
  {
    _angleX = ax ;
  }
  
  void setAngleY(float ay)
  {
    _angleY = ay ;
  }
  
  void setAngleZ(float az)
  {
    _angleZ = az ;
  }

  void setFilename(string fn)
  {
    _filename = fn ;
  }
  
  void setTexname(string tn)
  {
    _texname = tn ;
  }
    
  void rotate(float ax, float ay, float az)
  {
    _angleX = ax ; _angleY = ay ; _angleZ = az ;
  }

  void colorer( char r, char g, char b, char a)
  {
    _c.x = r;
    _c.y = g;
    _c.z = b;
    _c.a = a;
  }

  void genNormal()
  {
    /* on ititialise le tableau de normales */
    _nb_normals=_nb_vertices;
    _normals=new float[_nb_normals*3];
    for(int i=0;i<_nb_normals*3;i++)
      {
	_normals[i]=0;
      }
    /* fin init */
    //cout<<"_normal init"<<endl;
    float u[3],v[3],n[3];
    /* on parcours les triangles */
    for(int j=0; j<_nb_index;j+=1)
      {
	/* on créé une normale pour chaque triangle */
	
	/* on recupere u avec les pts 1&2 du triangle */
	u[0]=_vertices[3*_index[j*3+1]]-_vertices[3*_index[j*3]];
	u[1]=_vertices[3*_index[j*3+1]+1]-_vertices[3*_index[j*3]+1];
	u[2]=_vertices[3*_index[j*3+1]+2]-_vertices[3*_index[j*3]+2];
	//cout<<"u recup"<<endl;
	/* on récupêre v avec les pts 1&3 du triangle */
	v[0]=_vertices[3*_index[j*3+2]]-_vertices[3*_index[j*3]];
	v[1]=_vertices[3*_index[j*3+2]+1]-_vertices[3*_index[j*3]+1];
	v[2]=_vertices[3*_index[j*3+2]+2]-_vertices[3*_index[j*3]+2];
	//cout<<"v recup"<<endl;
	/* on fais le produit scalaire de u&v */
	n[0] = (u[1]*v[2])-(u[2]*v[1]);
	n[1] = (u[2]*v[0])-(u[0]*v[2]);
	n[2] = (u[0]*v[1])-(u[1]*v[0]);
    
	/* on a notre normale du triangle _index & _index+1 & _index+2 */

	/* on normanize */
	float normanizer=sqrt(n[0]*n[0]+n[1]*n[1]+n[2]*n[2]);	
	n[0] = n[0]/normanizer;
	n[1] = n[1]/normanizer;
	n[2] = n[2]/normanizer;
	
	/* on additionne a cette normale les normales stockées pour chaque point du triangle */
	_normals[3 * _index[j*3]] += n[0]; //point 1 sur x
	_normals[3 * _index[j*3+1]] += n[0]; //point 2 sur x
	_normals[3 * _index[j*3+2]] += n[0]; //point3 sur x
	
	_normals[3 * _index[j*3] + 1] += n[1]; //point 1 sur y
	_normals[3 * _index[j*3+1] + 1] += n[1]; //Etc...
	_normals[3 * _index[j*3+2] + 1] += n[1];
	
	_normals[3 * _index[j*3] + 2] += n[2];
	_normals[3 * _index[j*3+1] + 2] += n[2];
	_normals[3 * _index[j*3+2] + 2] += n[2];
	
	
	//cout << "normal : "<< j<<endl;
      }

    //penser a renormaliser toutes les normales, en effet le += fausse la normalisation
    for(int i= 0 ; i< _nb_normals ;i++){
      	float normanizer=sqrt(n[3*i]*n[3*i]+n[3*i+1]*n[3*i+1]+n[3*i-2]*n[3*i+2]);
	n[3*i] = n[3*i]/normanizer;
	n[3*i+1] = n[3*i+1]/normanizer;
	n[3*i+2] = n[3*i+2]/normanizer;
    }
    
  }

  void drawNormals(){
    /* pour chaque point on draw
       une ligne du point jusqua point+ normal coord */
    glBegin(GL_LINES);
    glPushMatrix();
    glColor3ub(255,0,0);
    for( int i=0;i<_nb_vertices*3;i+=3){
      
      glVertex3f(_vertices[i],_vertices[i+1],_vertices[i+2]);
      glVertex3f(_vertices[i]+_normals[i],_vertices[i+1]+_normals[i+1],_vertices[i+2]+_normals[i+2]);
    }
    glPopMatrix();
    glEnd();
  }

  /* fonction virtuelles à redéfinir */
  virtual void dessiner(float scale =1.) = 0 ;
  virtual void charger() = 0 ;
  
  
};
#endif
