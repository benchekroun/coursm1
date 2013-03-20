#ifndef _SKYBOX_H
#define _SKYBOX_H

#include "readpng.h"
#include <fstream>
#include <iostream>
#include <string>
#include <math.h>

#include <stdio.h>
#include <GL/glut.h>
#include <GL/gl.h> 

using namespace std;

class SkyBox
{
public:
	SkyBox(){}
	~SkyBox(){}

	bool Initialize();
	void Activate();
	void Disactivate();
	void SetPosition(float x, float y, float z);
	void SetRotation(float angle, float x, float y, float z);

private:
	void DrawSkyBox();
	gl_texture_t ** TexSB;
	string CheminTex[6];


	GLuint cube_map_texture_ID;
	float _posX, _posY, _posZ, _angleX, _angleY, _angleZ, angle;
};

#endif
