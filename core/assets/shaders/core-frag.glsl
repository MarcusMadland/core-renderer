#version 450 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse;

// MAIN
void main()
{    
	vec4 texDiffuseCol = texture(texture_diffuse, TexCoords);

	// Alpha is zero, don't render it
	if (texDiffuseCol.a < 0.1f)
		discard;
	
	// If texture color have color, render texture
	if (length(texDiffuseCol) != 1.0f)
		FragColor = texDiffuseCol;

	// Else, render a default color
	else
		FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	
	
}