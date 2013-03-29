/*
 *  readpng.h
 *  bras
 *
 *  Created by Emmanuel Melin on 24/02/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef config_h
#define config_h


#include <GL/glut.h>
#include <math.h>
#include <cstdlib>
#include <iostream>
#include <png.h>
using namespace std;


#endif

#ifndef TEXTURE_T
#define TEXTURE_T 

//  gltex = ReadPNGFromFile("data/alpes.png");
//glTexImage2D (GL_TEXTURE_2D, 0, gltex->internalFormat, gltex->width, gltex->height, 0, gltex->format, GL_UNSIGNED_BYTE, gltex->texels);

struct gl_texture_t
{
	GLuint width;           /* largeur */
	GLuint height;          /* hauteur */
	
	GLenum format;          /* RVB, RVBA, Luminance, Luminance Alpha */
	GLint  internalFormat;  /* composantes d'un texel */
	GLuint id;
	
	GLubyte *texels;         /* données de l'image */
};

struct gl_texture_t *ReadPNGFromFile (const char *filename) ;


#endif
