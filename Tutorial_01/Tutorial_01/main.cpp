//
//  main.cpp
//  Tutorial_01
//
//  Created by Young40 on 3/12/15.
//  Copyright (c) 2015 Young40 Inc. All rights reserved.
//

#include <iostream>

#include "glfw3.h"

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

    
    glfwWindowHint(GLFW_SAMPLES, 4);
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
    
    while (!glfwWindowShouldClose(window)) {
//        glfwSwapBuffers(window);
        
        glfwPollEvents();
    }
    
    glfwTerminate();
    
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
