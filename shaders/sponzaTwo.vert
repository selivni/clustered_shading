#version 330 core

in vec3 point;
in vec3 uvCoord;

uniform mat4 camera;

out vec3 uv;

void main()
{
	vec4 finalPoint = vec4(point, 1);
	uv = uvCoord;
	gl_Position = 0.001 * camera * finalPoint;
}
