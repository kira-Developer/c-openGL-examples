#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};
GLuint VAO, VBO, EBO;

void VAOCreate();
void VBOCreate();
void EBOCreate();

void VAOBind();
void VBOBind();
void EBOBind();

void VAOUbind();
void VBOUbind();
void EBOUbind();

void VAODelete();
void VBODelete();
void EBODelete();
void linker(GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);