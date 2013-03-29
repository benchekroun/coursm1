#include "scene.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include "OBJlib.h"

//void objet();
void assassin();
void lightcycle();
void blackhawk();

// Nombre de textures des non objs
//GLuint texture[19];
//Obj
MeshObj *connor;
MeshObj *bh;

void chargerTextures()
{
    // Exemple de chargement 
    //texture[0] = loadTexture("metal091.jpg");

}

void chargerObj()
{
    connor=new MeshObj("models/connor/Connor_Kenway.obj");
    bh=new MeshObj("models/AC-130_Hercules/AC-130_Hercules.obj");
}

void dessinerScene()
{
    // Appelle des fonctions de chaques objets
    //assassin();
    blackhawk();
}

// Faire une fonction par objet
void assassin()
{
	glPushMatrix();
	glRotated(90,1,0,0);
	glTranslated(0,0,2);
	glRotated(180,0,1,0);
	connor->draw_model(true,true);
	glPopMatrix();
}

void blackhawk() {
	glPushMatrix();
	bh->draw_model(true,true);
	glPopMatrix();
}