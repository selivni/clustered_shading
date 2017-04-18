#version 330 core

in vec3 col;
in vec3 normal;
in vec3 cameraDirection;

out vec4 outColor;

void main()
{
	vec3 norm = normalize(normal);
	vec3 camVec = normalize(cameraDirection);
	const float specPower = 1.5;
	vec3 diffColor = col;
	vec3 specColor = vec3(1, 1, 1) * pow(max(dot(norm, camVec), 0), specPower);
	vec3 result = diffColor + specColor;
	if (result.x > 1)
		result.x = 1;
	if (result.y > 1)
		result.y = 1;
	if (result.z > 1)
		result.z = 1;
	outColor = vec4(result, 1);
}
