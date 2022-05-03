#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


int main() {
    
    
    glfwInit();
    
    
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    
    GLFWwindow* window = glfwCreateWindow(500, 500, "Hello World", NULL , NULL);

    if (window == NULL){
        //printf("%s" , "failed to create the window");
        glfwTerminate();
        return -1;
}
    glfwMakeContextCurrent(window);
    gladLoadGL();

    glViewport(0 , 0 ,500 , 500);
    glClearColor(0.07f , 0.13f, 0.17f , 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
    
    while (!glfwWindowShouldClose(window)) {

                glfwPollEvents();
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
