#version 450 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_screen;

void main()
{
    FragColor = texture(texture_screen, TexCoords);
}