#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 Normal;
out vec2 TexCoords;

out vec3 ObjectPosition;

uniform mat4 uCamera;
uniform mat4 uObject;

void main()
{
    TexCoords = mat2(0.0f, -1.0f, 1.0f, 0.0f) *  aTexCoords;
    Normal = aNormal;
    ObjectPosition = vec3(uObject * vec4(aPos, 1.0f)); 
    
    gl_Position = uCamera * vec4(ObjectPosition, 1.0f);
}