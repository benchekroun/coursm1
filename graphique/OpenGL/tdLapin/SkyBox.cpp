#include "SkyBox.h"
#include "readpng.h"
#include <fstream>
#include <iostream>
#include <string>
#include <math.h>

#include <stdio.h>
#include <GL/glut.h>
#include <GL/gl.h> 
  
#define GL_TEXTURE_CUBE_MAP_ARB             0x8513
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB  0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB  0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB  0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB  0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB  0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB  0x851A
using namespace std;


bool SkyBox::Initialize()
{
  GLenum cube_map_target[6] = {           
    GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB,
    GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB,
    GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB,
    GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB,
    GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB,
    GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB
  };


  _posX = 0.0;
  _posY = 0.0;
  _posZ = 0.0;

  _angleX = 0.0;
  _angleY = 0.0;
  _angleZ = 0.0;

  angle = 0.0;

  TexSB = new gl_texture_t *[6];
  CheminTex[0] = "fichiers/images/skybox/interXN.png";
  CheminTex[1] = "fichiers/images/skybox/interXP.png";

  CheminTex[2] = "fichiers/images/skybox/interYN.png";
  CheminTex[3] = "fichiers/images/skybox/interYP.png";

  CheminTex[4] = "fichiers/images/skybox/interZN.png";
  CheminTex[5] = "fichiers/images/skybox/interZP.png";

  glEnable(GL_TEXTURE_2D); 

  // Chargement des six textures
  for(int i=0; i<6; i++)
    {
      TexSB[i] = ReadPNGFromFile(CheminTex[i].c_str());
      glGenTextures(1, &TexSB[i]->id);
      glBindTexture(GL_TEXTURE_2D,TexSB[i]->id);

  // Configuration des parametres de la texture
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
      
      glTexImage2D(GL_TEXTURE_2D, 
		   0, 
		   TexSB[i]->internalFormat, 
		   TexSB[i]->width, 
		   TexSB[i]->height, 
		   0, 
		   TexSB[i]->format, 
		   GL_UNSIGNED_BYTE, 
		   TexSB[i]->texels); 
    }

  // Génération d'une texture CubeMap
  glGenTextures(1, &cube_map_texture_ID);

  // Configuration de la texture
  glBindTexture(GL_TEXTURE_CUBE_MAP_ARB, cube_map_texture_ID);

  for (int i = 0; i < 6; i++)
    {
      if (TexSB[i])				
	{
	  glTexImage2D(cube_map_target[i], 0, 3,  TexSB[i]->width, TexSB[i]->height, 0, GL_RGB, GL_UNSIGNED_BYTE, TexSB[i]->texels);

	  if (TexSB[i]->texels)	
	    {
	      free(TexSB[i]->texels);	
	    }
	  free(TexSB[i]);	
	}
    }
  // Configuration des parametres de la texture
  glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_S, GL_CLAMP );
  glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_T, GL_CLAMP );
}

void SkyBox::Activate()
{
  // Configuration des états OpenGL
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_CUBE_MAP_ARB);
  glColor3ub(255,255,255);
  glEnable(GL_TEXTURE_2D); 
  glDisable(GL_LIGHTING);

  // Désactivation de l'écriture dans le DepthBuffer
  glDepthMask(GL_FALSE);

  // Rendu de la SkyBox
  DrawSkyBox();

  // Réactivation de l'écriture dans le DepthBuffer
  glDepthMask(GL_TRUE);

  // Réinitialisation des états OpenGL
  glDisable(GL_TEXTURE_2D); 
  glDisable(GL_TEXTURE_CUBE_MAP_ARB);
  glEnable(GL_LIGHTING);
  glEnable(GL_DEPTH_TEST);

}

void SkyBox::Disactivate()
{
  // Suppression de la skybox
  for(int i=0; i<6; i++)
    {
      glDeleteTextures( 1, &TexSB[i]->id);
    }
  glDeleteTextures( 1, &cube_map_texture_ID );
}

void SkyBox::SetPosition(float x, float y, float z)
{
  _posX = x;
  _posY = y;
  _posZ = z;
}

void SkyBox::SetRotation(float a, float x, float y, float z)
{
  angle = a;
  _angleX = x;
  _angleY = y;
  _angleZ = z;
}

void SkyBox::DrawSkyBox()
{
  // Taille du cube
  float t = 1.0f;
  
  // Utilisation de la texture CubeMap
  glBindTexture(GL_TEXTURE_CUBE_MAP_ARB, cube_map_texture_ID);

  // Réglages
  glPushMatrix();	
    
  // Position
  glTranslatef(_posX, _posY, _posZ);
  glRotatef(angle, _angleX, _angleY, _angleZ);

  glRotated(90,1,0,0);

  // Rendu de la géométrie
  glBegin(GL_TRIANGLE_STRIP);			// X Négatif		
  glTexCoord3f(-t,-t,-t); glVertex3f(-t,-t,-t); 	
  glTexCoord3f(-t,t,-t); glVertex3f(-t,t,-t);
  glTexCoord3f(-t,-t,t); glVertex3f(-t,-t,t);
  glTexCoord3f(-t,t,t); glVertex3f(-t,t,t);
  glEnd();

  glBegin(GL_TRIANGLE_STRIP);			// X Positif
  glTexCoord3f(t, -t,-t); glVertex3f(t,-t,-t);
  glTexCoord3f(t,-t,t); glVertex3f(t,-t,t);
  glTexCoord3f(t,t,-t); glVertex3f(t,t,-t); 
  glTexCoord3f(t,t,t); glVertex3f(t,t,t); 	
  glEnd();

  glBegin(GL_TRIANGLE_STRIP);			// Y Négatif	
  glTexCoord3f(-t,-t,-t); glVertex3f(-t,-t,-t);
  glTexCoord3f(-t,-t,t); glVertex3f(-t,-t,t);
  glTexCoord3f(t, -t,-t); glVertex3f(t,-t,-t);
  glTexCoord3f(t,-t,t); glVertex3f(t,-t,t);
  glEnd();

  glBegin(GL_TRIANGLE_STRIP);			// Y Positif		
  glTexCoord3f(-t,t,-t); glVertex3f(-t,t,-t);
  glTexCoord3f(t,t,-t); glVertex3f(t,t,-t); 
  glTexCoord3f(-t,t,t); glVertex3f(-t,t,t);
  glTexCoord3f(t,t,t); glVertex3f(t,t,t); 	
  glEnd();

  glBegin(GL_TRIANGLE_STRIP);			// Z Négatif		
  glTexCoord3f(-t,-t,-t); glVertex3f(-t,-t,-t);
  glTexCoord3f(t, -t,-t); glVertex3f(t,-t,-t);
  glTexCoord3f(-t,t,-t); glVertex3f(-t,t,-t);
  glTexCoord3f(t,t,-t); glVertex3f(t,t,-t); 
  glEnd();

  glBegin(GL_TRIANGLE_STRIP);			// Z Positif	
  glTexCoord3f(-t,-t,t); glVertex3f(-t,-t,t);
  glTexCoord3f(-t,t,t); glVertex3f(-t,t,t);
  glTexCoord3f(t,-t,t); glVertex3f(t,-t,t);
  glTexCoord3f(t,t,t); glVertex3f(t,t,t); 	
  glEnd();

  // Réinitialisation de la matrice ModelView
  glPopMatrix();
}

