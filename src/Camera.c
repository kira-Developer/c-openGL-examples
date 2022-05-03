#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <stb/stb_image.h>
#include <stdbool.h>
#include <cglm/cglm.h>
#include <cglm/call.h>
#include <stdio.h>
#include <stdlib.h>
#include "Camera.h"
#include "Vartex.h"
#include "Texture.h"


#define WIDTH  800
#define HEIGHT  800



// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"layout (location = 2) in vec2 aTex;\n"
"out vec3 color;\n"
"out vec2 texCoord;\n"
"uniform float scale;\n"
"uniform mat4 camMatrix;\n"
"void main()\n"
"{\n"
"   	gl_Position = camMatrix * vec4(aPos, 1.0);\n"
"       color = aColor;\n"
"       texCoord = aTex;\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 color;\n"
"in vec2 texCoord;\n"
"uniform sampler2D tex0;\n"
"void main()\n"
"{\n"
"   FragColor = texture(tex0, texCoord);\n"
"}\n\0";


    
    void Matrix(float FOVdeg, float nearPlane, float farPlane, GLuint shader, const char* uniform){
        
            mat4 view;
            mat4 projection;
            mat4 views;
            vec3 add;

            glm_vec3_add(Position , Orientation , add);
            glm_lookat(Position, add, Up , view);
            glm_perspective(glm_rad(FOVdeg), (float) (WIDTH/HEIGHT), farPlane,nearPlane,projection);
            glm_mat4_mul(projection , view , views);
            glUniformMatrix4fv(glGetUniformLocation(shader, uniform), 1, GL_FALSE, views[0]);
            
    }


    void Inputs(GLFWwindow* window){
        

    
        // Handles key inputs
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		
        glm_vec3_muladds(Orientation,speed , Position);
       
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
        glm_vec3_cross(Orientation, Up , cross);
        glm_vec3_normalize(cross);
		glm_vec3_muladds(cross,-speed , Position);
    }
		
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
        glm_vec3_muladds(Orientation,-speed , Position);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
        
        glm_vec3_cross(Orientation, Up , cross);
        glm_vec3_normalize(cross);
		glm_vec3_muladds(cross,speed , Position);
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		
        glm_vec3_muladds(Up,speed , Position);
    }
        
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		
        glm_vec3_muladds(Up,-speed , Position);
        
	}

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		
        glm_vec3_muladds(Orientation,speed , Position);
       
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
        glm_vec3_cross(Orientation, Up , cross);
        glm_vec3_normalize(cross);
		glm_vec3_muladds(cross,-speed , Position);
    }
		
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
         glm_vec3_muladds(Orientation,-speed , Position);
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
        
        glm_vec3_cross(Orientation, Up , cross);
        glm_vec3_normalize(cross);
		glm_vec3_muladds(cross,speed , Position);
	}
	
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		speed = 0.4f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		speed = 0.1f;
	}


	 // Handles mouse inputs
	 if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	 {
	 	// Hides mouse cursor
	 	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	 	// Prevents camera from jumping on the first click
	 	
     }
    } 

void VAOCreate(){glGenVertexArrays(1 ,  &VAO);}
void VBOCreate(){
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Introduce the vertices into the VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

};
void EBOCreate(){
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
};


void VAOBind(){glBindVertexArray(VAO);};
void VBOBind(){glBindBuffer(GL_ARRAY_BUFFER, VBO);};
void EBOBind(){glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);};

void VAOUbind(){glBindVertexArray(0);};
void VBOUbind(){glBindBuffer(GL_ARRAY_BUFFER, 0);};
void EBOUbind(){glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);};

void VAODelete(){glDeleteVertexArrays(1, &VAO);};
void VBODelete(){glDeleteBuffers(1, &VBO);};
void EBODelete(){glDeleteBuffers(1, &EBO);};

void linker(GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) {
VBOBind();
glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
glEnableVertexAttribArray(layout);
VBOUbind();};

void textureCreate(GLuint texture , int withimg , int heighimg ,int numcol , unsigned char * bytes){
    

    glGenTextures(1,&texture); 
    glActiveTexture(GL_TEXTURE0);
    textureBind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER , GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER , GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S , GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,  GL_TEXTURE_WRAP_S , GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, withimg, heighimg, numcol,  GL_RGB, GL_UNSIGNED_BYTE,bytes);
    glGenerateMipmap(GL_TEXTURE_2D);
};
void textureBind(){ glBindTexture(GL_TEXTURE_2D, texture);};
void textureUind(unsigned char *bytes){
stbi_image_free(bytes);
glBindTexture(GL_TEXTURE_2D,0);
};
void textureDelete(){glDeleteTextures(1,&texture);};
int main()
{


    // Initialize GLFW
    glfwInit();

        // In this case we are using OpenGL 3.3
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        // Tell GLFW we are using the CORE profile
        // So that means we only have the modern functions
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    


    // Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Textures", NULL, NULL);
    // Error check if the window fails to create
    if (window == NULL)
    {
        glfwTerminate();
        return -1;
    }
    // Introduce the window into the current context
    glfwMakeContextCurrent(window);

    //Load GLAD so it configures OpenGL
    gladLoadGL();
    // Specify the viewport of OpenGL in the Window
    // In this case the viewport goes from x = 0, y = 0, to x = 0, y = 0
    //glViewport(0, 0, 800, 800);



    // Create Vertex Shader Object and get its reference
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Attach Vertex Shader source to the Vertex Shader Object
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    // Compile the Vertex Shader into machine code
    glCompileShader(vertexShader);

    // Create Fragment Shader Object and get its reference
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Attach Fragment Shader source to the Fragment Shader Object
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    // Compile the Vertex Shader into machine code
    glCompileShader(fragmentShader);

    // Create Shader Program Object and get its reference
    GLuint shaderProgram = glCreateProgram();
    // Attach the Vertex and Fragment Shaders to the Shader Program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    // Wrap-up/Link all the shaders together into the Shader Program
    glLinkProgram(shaderProgram);

    // Delete the now useless Vertex and Fragment Shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


/// Vertices coordinates


// Indices for vertices order


    // Create reference containers for the Vartex Array Object, the Vertex Buffer Object, and the Element Buffer Object

    // Generate the VAO, VBO, and EBO with only 1 object each
    VAOCreate();

    
    VAOBind();

    VBOCreate();
    EBOCreate();

    linker(0, 3, GL_FLOAT,  8 * sizeof(float), (void*)0);
    linker(1, 3, GL_FLOAT,  8 * sizeof(float), (void*)(3 * sizeof(float)));
    linker(2, 2, GL_FLOAT,  8 * sizeof(float), (void*)(6 * sizeof(float)));

	

    VAOUbind();
    VBOUbind();
    EBOUbind();

    stbi_set_flip_vertically_on_load(true);
    unsigned char* bytes = stbi_load("image/photo-1495578942200-c5f5d2137def.jpg" , &widthImg , &heightImg, &numColCh, 0);
    textureCreate(texture , widthImg , heightImg, numColCh , bytes);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImg, heightImg, 0,  GL_RGB, GL_UNSIGNED_BYTE,bytes);
    glGenerateMipmap(GL_TEXTURE_2D);


textureUind(bytes);
GLuint tex0Uni = glGetUniformLocation(shaderProgram , "tex0");
glUseProgram(shaderProgram);
glUniform1i(tex0Uni,0);




    // Main while loop
    while (!glfwWindowShouldClose(window))
    {
            // Specify the color of the background
            glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
            // Clean the back buffer and assign the new color to it
            
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glUseProgram(shaderProgram);
            

            // Initializes matrices so they are not the null matrix
            
        // Outputs the matrices into the Vertex Shader
        Inputs(window);
        Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");
        glBindTexture(GL_TEXTURE_2D, texture);
        // Tell OpenGL which Shader Program we want to use
        glUniform1f(tex0Uni,0.5f);
        glBindVertexArray(VAO);
        // Draw primitives, number of indices, datatype of indices, index of indices
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
        // Swap the back buffer with the front buffer
        glfwSwapBuffers(window);
        // Take care of all GLFW events
        glfwPollEvents();
    }



    // Delete all the objects we've created
    VAODelete();
    VBODelete();
    EBODelete();
    glDeleteProgram(shaderProgram);
    textureDelete();
    // Delete window before ending the program
    glfwDestroyWindow(window);
    // Terminate GLFW before ending the program
    glfwTerminate();
    return 0;
}
