#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 uCamera;
uniform mat4 uObject;

void main()
{
    TexCoords = mat2(0.0, -1.0, 1.0, 0.0) *  aTexCoords;
    gl_Position = (uCamera * uObject) * vec4(aPos, 1.0); 
}