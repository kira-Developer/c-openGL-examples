#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include <cglm/call.h>

    vec3 Position = {0.0f, 0.0f, 2.0f};
    vec3 Orientation  = {0.0f, 0.0f, -1.0f};
    vec3 Up = {0.0f, 1.0f, 0.0f};
    float speed = 0.1f;
	float sensitivity = 100.0f;
    bool firstClick = true;
    float deltaTime = 0.0f;	// time between current frame and last frame
    float lastFrame = 0.0f;
    vec3 cross;


void Matrix(float FOVdeg, float nearPlane, float farPlane, GLuint shader, const char* uniform);
void Inputs(GLFWwindow* window);
