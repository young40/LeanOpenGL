//
//  main.cpp
//  Tutorial_01
//
//  Created by Young40 on 3/12/15.
//  Copyright (c) 2015 Young40 Inc. All rights reserved.
//

#include <iostream>

#include <OpenGL/gl3.h> //OpenGL3 以上需要include这个.

#include "glfw3.h"

#include "shader.hpp"

#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
///Work/LeanOpenGL/Tutorial_01/glm/glm.hpp

using namespace glm;

extern "C"
{
    static void test_error_cb (int error, const char *description)
    {
        fprintf(stderr, "%d: %s\n", error, description);
    }
}

int main(int argc, const char * argv[]) {
    
    GLFWwindow *window;
    
    if (!glfwInit()) {
        return -1;
    }
    
    glfwSetErrorCallback(test_error_cb);

    
    glfwWindowHint(GLFW_SAMPLES, 4); // 注意glfw3 和之前版本API差异
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    
    window = glfwCreateWindow(640, 480, "", NULL, nullptr);
     if (!window) {
        
        glfwTerminate();
        
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    
    
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    
    
    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f,  -1.0f,  0.0f,
        1.0f,   -1.0f,  0.0f,
        0.0f,   1.0f,   0.0f,
        
    };
    
    GLuint vertexBuffer;
    
    glGenBuffers(1, &vertexBuffer);
    
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    
    
    
    GLuint programID = LoadShaders("T1.vs", "T1.fs");
   
    
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");
    

    
    mat4 Projection = glm::perspective(45.0f, 4.0f/3.0f, 0.1f, 100.0f);
//    mat4 Projection = glm::ortho(-100, 100, 100, -100)
    
    mat4 View = glm::lookAt(vec3(4, 3, 3),
                            vec3(0, 0, 0),
                            vec3(0, 1, 0));
    
    mat4 Model = mat4(1.0f);
    
    mat4 MVP = Projection * View * Model;
    
    
    
    while (!glfwWindowShouldClose(window)) {
//        glfwSwapBuffers(window);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(programID);
        
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
        
        glEnableVertexAttribArray(0);
        
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glDisableVertexAttribArray(0);
        
        
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
