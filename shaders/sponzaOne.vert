#version 330 core

in vec3 point;
in vec3 uvCoord;
in vec3 normal;

uniform mat4 camera;
uniform vec3 cameraPosition;

out vec3 uv;
out vec3 norm;
out vec3 cameraVector;
out vec3 pointPosition;

void main()
{
	vec4 finalPoint = vec4(point, 1);
	pointPosition = point;
	norm = normal;
	uv = uvCoord;
	cameraVector = cameraPosition - point;
	gl_Position = camera * finalPoint;
}
