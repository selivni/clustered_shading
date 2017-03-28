#version 330 core

in vec3 point;

uniform mat4 camera;

void main()
{
	vec4 finalPoint = vec4(point, 1);

	gl_Position = 0.001 * camera * finalPoint;
}
