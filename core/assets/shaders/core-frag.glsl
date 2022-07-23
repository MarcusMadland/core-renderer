#version 450 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 ObjectPosition;

uniform uint object_type = 0; // 0 default, 1 billboard

uniform sampler2D texture_diffuse;
uniform sampler2D texture_specular;
uniform sampler2D texture_normal;

uniform vec3 light_pos;
uniform vec4 light_color;
uniform uint light_type;

uniform vec3 camera_pos;

vec4 SpotLight()
{
	float outerCone = 0.9f;
	float innerCone = 0.95f;

	float ambientLight = 0.1f;

	vec3 normal = normalize(Normal);
	vec3 lightDir = normalize(light_pos - ObjectPosition);
	float diffuseLight = max(dot(normal, lightDir), 0.0f);

	float maxIntensity = 0.5f; 
	vec3 viewDir = normalize(camera_pos - ObjectPosition);
	vec3 reflectDir = reflect(-lightDir, normal);
	float specAmount = pow(max(dot(viewDir, reflectDir), 0.0f), 16);
	float specular = specAmount * maxIntensity;

	float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDir);
	float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

	return (texture(texture_diffuse, TexCoords) * (diffuseLight * inten + ambientLight) 
		+ texture(texture_specular, TexCoords).r * specular * inten) * light_color; 
}

vec4 DirectionalLight()
{
	float ambientLight = 0.1f;

	vec3 normal = normalize(Normal);
	vec3 lightDir = normalize(vec3(1.0f, 1.0f, 0.0f));
	float diffuseLight = max(dot(normal, lightDir), 0.0f);

	float maxIntensity = 0.5f; 
	vec3 viewDir = normalize(camera_pos - ObjectPosition);
	vec3 reflectDir = reflect(-lightDir, normal);
	float specAmount = pow(max(dot(viewDir, reflectDir), 0.0f), 16);
	float specular = specAmount * maxIntensity;

	return (texture(texture_diffuse, TexCoords) * (diffuseLight + ambientLight) 
		+ texture(texture_specular, TexCoords).r * specular) * light_color; 
}

vec4 PointLight()
{
	vec3 lightVec = light_pos - ObjectPosition;
	float dist = length(lightVec);
	float a = 1.0f;  // 3.0
	float b = 0.04f; // 0.7
	float inten = 1.0f/ (a * dist * dist * b * dist + 1.0f);

	float ambientLight = 0.1f;

	vec3 normal = normalize(Normal);
	vec3 lightDir = normalize(lightVec);
	float diffuseLight = max(dot(normal, lightDir), 0.0f);

	float specular = 0.0f;
	if (diffuseLight != 0.0f)
	{
		float maxIntensity = 0.5f; 
		vec3 viewDir = normalize(camera_pos - ObjectPosition);
		vec3 reflectDir = reflect(-lightDir, normal);

		vec3 halfwayVec = normalize(viewDir + lightDir);

		float specAmount = pow(max(dot(normal, halfwayVec), 0.0f), 16);
		specular = specAmount * maxIntensity;
	}

	return (texture(texture_diffuse, TexCoords) * (diffuseLight + ambientLight) 
		+ texture(texture_specular, TexCoords).r * specular * inten) * light_color; 
}

// MAIN
void main()
{    
	vec4 texDiffuseCol = PointLight();

	// Calculate final color
	if (light_type == 0)
		texDiffuseCol = PointLight();
	else if (light_type == 1)
		texDiffuseCol = DirectionalLight();
	else if (light_type == 2)
		texDiffuseCol = SpotLight();

	// Alpha is zero, don't render it
	if (texture(texture_diffuse, TexCoords).a < 0.1f)
		discard;
	
	// If texture color have color, render texture
	if (length(texDiffuseCol) != 1.0f)
		FragColor = texDiffuseCol;

	// Else, render a default color
	if (object_type == 1)
		FragColor = texture(texture_diffuse, TexCoords);
}