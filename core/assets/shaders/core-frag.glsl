#version 450 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse;

float near = 0.001f;
float far = 500.0f;

// FOG
float linearizeDepth(float depth)
{
	return (2.0 * near * far) / (far + near - (depth * 2.0 - 1.0) * (far - near));
}

float logisticDepth(float depth, float steepness, float offset)
{
	float zVal = linearizeDepth(depth);
	return (1 / (1 + exp(-steepness * (zVal - offset))));
}

// MAIN
void main()
{    
    float depth = logisticDepth(gl_FragCoord.z, 0.5f, 5.0f);

	if (texture(texture_diffuse, TexCoords).a < 0.1)
		discard;

    FragColor = texture(texture_diffuse, TexCoords) *
        (1.0f - depth) + vec4(depth * vec3(0.5f, 0.5f, 0.5f), 1.0f);
}