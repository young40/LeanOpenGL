//
//  main.cpp
//  TextureFirstTest
//
//  Created by Young40 on 4/4/15.
//  Copyright (c) 2015 Young40 Inc. All rights reserved.
//

#include <iostream>
#include <GLFW/glfw3.h>

extern "C"
{
    static void test_error_callback(int error, const char *desc) {
        fprintf(stderr, "OpenGL Error: %d\t %s\n", error, desc);
    }
}

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
    
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        
        
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
