#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;

out vec2 UV;

uniform float gScale;

void main()
{
    gl_Position.xyz = vec3(gScale*vertexPosition_modelspace.x,
                           gScale*vertexPosition_modelspace.y,
                           gScale*vertexPosition_modelspace.z); //vertexPosition_modelspace;
    gl_Position.w = 1.0;
    
    UV = vertexUV;
}