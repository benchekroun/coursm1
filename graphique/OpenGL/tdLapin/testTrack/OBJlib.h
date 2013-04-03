#ifndef __OBJ_LIB__
#define __OBJ_LIB__

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "sdlglutils.h"

std::string doubleSlash(std::string s);
std::string remplacerSlash(std::string s);
std::vector<std::string> splitSpace(std::string s);
std::string get_directory(std::string s);
float* vector2float(std::vector<float>& tableau);

class FloatVector
{
    /*
    Classe FloatVector : simple vecteur XYZ ou XYZA (dans le cas de couleurs).
    */
    public:
        FloatVector(float px=0,float py=0,float pz=0,float pa=0);
        /* FloatVector(float px=0,float py=0,float pz=0,float pa=0);
           Constructeur, prend en param�tres des flottants correspondant respectivement � x, y, z et a.
        */
        ~FloatVector();
        /* ~FloatVector();
           Destructeur, totalement inutile.
        */
        FloatVector operator=(const FloatVector &fv);
        /* FloatVector operator=(const FloatVector &fv);
           Affecte au vecteur courant le contenu du vecteur pass� en argument.
           Retourne le vecteur courant ainsi modifi�.
        */
        float x,y,z,a;
};

class Material
{
    /*
    Classe Material : d�finition d'un mat�riau, compos� d'une couleur et d'un nom sp�cifique.
    */
    public:
        Material(float r,float g,float b,std::string n);
        /* Material(float r,float g,float b,std::string n);
           Constructeur, les trois premiers arguments repr�sentent la couleur RGB du mat�riau et n est son nom.
        */
        Material(Material *mat);
        /* Material(Material *mat);
           Constructeur alternatif, affecte au mat�riau courant le contenu du mat�riau pass� en argument.
        */
        ~Material();
        /* ~Material();
           Destructeur, totalement inutile.
        */

        FloatVector coul;
        std::string name;
};

class MeshObj
{
    /*
    Classe MeshObj : d�finition d'un mod�le statique.
    */
    public:
        MeshObj(std::string,MeshObj *first=NULL);
        /* MeshObj(std::string,MeshObj *first=NULL);
           Constructeur, prend en arguments le nom du mod�le � charger et le pointeur de la premi�re frame 
           si le mod�le appartient � une animation (sinon laissez-le � NULL).
        */
        ~MeshObj();
        /* ~MeshObj();
           Destructeur, lib�re toute la m�moire qui lui a �t� allou�e.
        */
        void charger_obj(std::string,MeshObj *first=NULL);
        /* void charger_obj(std::string,MeshObj *first=NULL);
           Charge un fichier OBJ et son MTL, prend en arguments le nom du mod�le � charger et le pointeur
           de la premi�re frame si le mod�le appartient � une animation (sinon laissez-le � NULL). 
           Cette fonction est appel�e par le constructeur.
           Aucune valeur de retour.
        */
        void charger_mtl(std::string);
        /* void charger_mtl(std::string);
           Charge un fichier MTL, prend en argument le nom du fichier � charger.
           Cette fonction est appel�e par charger_obj.
           Aucune valeur de retour.
        */
        void draw_model(bool nor=true,bool tex=false);
        /* void draw_model(bool nor=true,bool tex=false);
           Dessine le mod�le, prend en arguments deux bool�ens repr�sentant respectivement 
           les normales et la texture. Si nor vaut true alors on prend en compte les normales,
           et si tex vaut true alors on applique la texture.
           Aucune valeur de retour.
        */
        void setMaterialsAndTex(std::vector<Material*> mats,GLuint tex);
        /* void setMaterialsAndTex(std::vector<Material*> mats,GLuint tex);
           D�finit directement les mat�riaux et la texture du mod�le, prend en arguments un 
           vector<Material*> et la texture. Cette fonction est appel�e par giveMaterialsAndTex.
           Aucune valeur de retour.
        */
        void giveMaterialsAndTex(MeshObj *target);
        /* void giveMaterialsAndTex(MeshObj *target);
           Modifie les mat�riaux et la texture de target en les rempla�ant par ses propres mat�riaux 
           et sa texture. Cette fonction est appel�e par charger_obj uniquement lorsque first!=NULL.
           Aucune valeur de retour.
        */
    private:
        GLuint *NumeroTextures;
        int n_data;
        float *vertice,*normals,*textures,*colours;

        std::vector<Material*> materiaux;
};

#endif