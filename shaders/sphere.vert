#version 330 core

in vec3 point;
in vec3 position;
in vec3 color;
in float radius;

out vec3 col;
out vec3 normal;
out vec3 cameraDirection;

uniform mat4 camera;
uniform vec3 cameraPosition;

void main()
{
	col = color;
	normal = point;
	cameraDirection = cameraPosition - (point * radius + position);
	gl_Position = camera * vec4(point * radius + position, 1);
}
