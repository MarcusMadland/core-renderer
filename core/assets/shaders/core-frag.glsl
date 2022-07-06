#version 450 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

float near = 0.001f;
float far = 500.0f;

// FOG
float linearizeDepth(float depth)
{
	return (2.0 * near * far) / (far + near - (depth * 2.0 - 1.0) * (far - near));
}

float logisticDepth(float depth, float steepness = 0.5f, float offset = 5.0f)
{
	float zVal = linearizeDepth(depth);
	return (1 / (1 + exp(-steepness * (zVal - offset))));
}

// MAIN
void main()
{    
    float depth = logisticDepth(gl_FragCoord.z);

    //FragColor = texture(texture_diffuse1, TexCoords) * 
    //    (1.0f - depth) + vec4(depth * vec3(0.5f, 0.5f, 0.5f), 1.0f);
	FragColor = vec4(1, 1, 1, 1);
}