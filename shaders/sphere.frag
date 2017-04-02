#version 330 core

in vec3 col;
in vec3 normal;
in vec3 cameraDirection;

out vec4 outColor;

void main()
{
	vec3 norm = normalize(normal);
	vec3 camVec = normalize(cameraDirection);
	const float specPower = 5.0;
	vec4 diffColor = vec4(col, 1);
	vec4 specColor = vec4(vec3(1, 1, 1) * pow(max(dot(norm, camVec), 0), specPower), 1);
	outColor = vec4(vec3(normalize(diffColor + specColor)), 1);
}
