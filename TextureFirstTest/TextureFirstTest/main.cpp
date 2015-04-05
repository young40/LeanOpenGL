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
    
    GLFWwindow *window = glfwCreateWindow(640, 480, "Hello Texture", nullptr, nullptr);
    
    if (!window) {
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    
    glClearColor(0.3f, 0.2f, 0.4f, 0.0f);
    
    GLuint vertexArrayID;
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);
    
    static const GLfloat g_vertex_buffer_data[] = {
        -0.9f,  -0.9f,  0.0f,
        0.9f,   -0.9f,  0.0f,
        0.0f,   0.9f,   0.0f,
    };
    
    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    
    
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
    
    GLuint gWorldLocation = glGetUniformLocation(programID, "gWorld");
    
    static float gScale = 0.0f;
    
    mat4 World = mat4(0.0f);
    
    World[0][0] = 1.0f;
    World[1][1] = 1.0f;
    World[2][2] = 1.0f;
    World[3][3] = 1.0f;
    
    World[0][3] = sinf(gScale);
    
    
    
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(programID);
        
        gScale += 0.01f;
        
        World[0][3] = sinf(gScale);
        
        glUniformMatrix4fv(gWorldLocation, 1, GL_TRUE, &World[0][0]);
        
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE, texture);
        glUniform1i(textureID, 0);
        
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
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
        
        
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
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
