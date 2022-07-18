#version 450 core

layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 proj;
uniform mat4 view;

void main()
{
    TexCoords = vec3(aPos.x, aPos.y, -aPos.z);

    vec4 pos = proj * view * vec4(aPos, 1.0f);
    gl_Position = vec4(pos.x, pos.y, pos.w, pos.w);
}  