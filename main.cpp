#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>

#include "Shader.h"

void key_callback(GLFWwindow* window,int key,int scancode,int action,int mode)
{
    if(key==GLFW_KEY_ESCAPE && action==GLFW_PRESS)
        glfwSetWindowShouldClose(window,GL_TRUE);
}

int main()
{
    glfwInit();
#if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
#endif
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);
    
    GLFWwindow *window=glfwCreateWindow(800,600,"Learn OpenGL",nullptr,nullptr);
    if(window==nullptr)
    {
        std::cout<<"Failed to create GLFW window!"<<std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    glewExperimental=GL_TRUE;
    if(glewInit()!=GLEW_OK)
    {
        std::cout<<"Failed to initialize GLEW!"<<std::endl;
        return -1;
    }
    
    int width,height;
    glfwGetFramebufferSize(window,&width,&height);
    glViewport(0,0,width,height);
    
    glfwSetKeyCallback(window,key_callback);
    
    Shader our_shader("/Users/xenaayala/Desktop/OpenGL/OpenGL/shader.vs","/Users/xenaayala/Desktop/OpenGL/OpenGL/shader.frag");
    
    GLfloat vertices[]={
        // positions        // colors
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };
    
    GLuint VAO,VBO;
    glGenBuffers(1,&VBO);
    glGenVertexArrays(1,&VAO);
    
    // bind vertex array object
    glBindVertexArray(VAO);
    
    // copy the vertices in a buffer
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    
    // set position attribute pointers
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(GL_FLOAT),(GLvoid*)0);
    glEnableVertexAttribArray(0);
    // set color attribute pointers
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(GL_FLOAT),(GLvoid*)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    
    // unbind the vertex array object
    glBindVertexArray(0);
    
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClearColor(.2f,.3f,.3f,1.f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // use shader program
        our_shader.Use();
        
        // draw
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,0,3);
        glBindVertexArray(0);
        
        glfwSwapBuffers(window);
    }
    
    // deallocate all resources
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    // terminate GLFW
    glfwTerminate();
    
    return 0;
}
