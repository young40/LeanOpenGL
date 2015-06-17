//
//  main.cpp
//  MasterOpenGL
//
//  Created by Peter Young on 6/15/15.
//  Copyright (c) 2015 Peter Young. All rights reserved.
//  http://www.young40.com/
//

#include <iostream>

#include <GLFW/glfw3.h>

int main(int argc, const char * argv[])
{
    GLFWwindow* window;
    
    if (!glfwInit())
    {
        return -1;
    }
    

    window = glfwCreateWindow(960, 640, "First Window for OpenGL", nullptr, nullptr);
    
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}
