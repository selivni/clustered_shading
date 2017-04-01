#version 330 core

in vec3 point;
in vec3 uvCoord;
in vec3 normal;

uniform mat4 camera;
uniform vec3 cameraPosition;

out vec3 uv;
out vec3 norm;
out vec3 cameraVector;

void main()
{
	vec4 finalPoint = vec4(point, 1);
	norm = normal;
	uv = uvCoord;
	cameraVector = cameraPosition - point;
	gl_Position = 0.001 * camera * finalPoint;
}
