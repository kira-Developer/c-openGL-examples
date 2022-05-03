#pragma once    
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>


int widthImg , heightImg, numColCh;
GLuint texture;

void textureCreate(GLuint texture , int withimg , int heighimge ,int numcol , unsigned char * bytes);
void textureBind();
void textureUind();
void textureDelete();

