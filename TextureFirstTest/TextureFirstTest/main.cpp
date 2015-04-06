//
//  main.cpp
//  TextureFirstTest
//
//  Created by Young40 on 4/4/15.
//  Copyright (c) 2015 Young40 Inc. All rights reserved.
//

#include <iostream>
#include <math.h>

#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <common/texture.hpp>
#include <common/shader.hpp>
#include <common/controls.hpp>

extern "C"
{
    static void test_error_callback(int error, const char *desc) {
        fprintf(stderr, "OpenGL Error: %d\t %s\n", error, desc);
    }
}

using namespace glm;

int main(int argc, const char * argv[]) {
    if (!glfwInit()) {
        return -1;
    }
    
    glfwSetErrorCallback(test_error_callback);
    
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    glfwWindowHint(GLFW_SAMPLES, 4);
    
    GLFWwindow *window = glfwCreateWindow(1024, 768, "Hello Texture", nullptr, nullptr);
    
    if (!window) {
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
//    glfwSetCursorPos(window, 1024/2, 768/2);
    
    glClearColor(0.3f, 0.2f, 0.4f, 0.0f);
    
    GLuint vertexArrayID;
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);
    
    static const GLfloat g_vertex_buffer_data[] = {
        -0.9f,  -0.9f,  0.0f,
        0.9f,   -0.9f,  0.0f,
        0.0f,   0.9f,   0.0f,
        0.0f,   0.0f,   0.7f,
    };
    
    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    
    static const GLuint g_vertex_index[] = {
        0, 1, 2,
        0, 1, 3,
        1, 2, 3,
        2, 0, 3
    };
    
    GLuint elementBuffer;
    glGenBuffers(1, &elementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_index, GL_STATIC_DRAW);
    
    
    
    GLuint programID = LoadShaders("Test.vsh", "Test.fsh");
    
    GLuint texture = loadBMP_custom("uvtemplate.bmp");
    GLuint textureID = glGetUniformLocation(programID, "myTextureSampler");
    
    static const GLfloat g_uv_buffer_data[] = {
        0.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
    };
    
    GLuint uvBuffer;
    glGenBuffers(1, &uvBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);
    
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");
    
    
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           !glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(programID);
        
        computeMatricesFromInputs(window);
        
        mat4 ProjectionMatrix = getProjectionMatrix();
        mat4 ViewMatrix = getViewMatrix();
        mat4 ModelMatrix = mat4(1.0f);
        
        mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
        
        glUniformMatrix4fv(MatrixID, 1, GL_TRUE, &MVP[0][0]);
        
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE, texture);
        glUniform1i(textureID, 0);
        
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
        glVertexAttribPointer(
                              0,
                              3,
                              GL_FLOAT,
                              GL_FALSE,
                              0,
                              (void*)0);
        
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
        glVertexAttribPointer(1,
                              2,
                              GL_FLOAT,
                              GL_FALSE,
                              0,
                              (void*)0);
        
        
//        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glDrawElements(GL_TRIANGLES, sizeof(g_vertex_index), GL_UNSIGNED_INT, (void*)0);
        
        
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
