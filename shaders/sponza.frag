#version 330 core

uniform uint material;

out vec4 outColor;

void main()
{
	if (material == uint(0))
		outColor = vec4(0, 0, 0, 1);
	else if (material == uint(1))
		outColor = vec4(1, 0, 0, 1);
	else if (material == uint(2))
		outColor = vec4(0, 1, 0, 1);
	else if (material == uint(3))
		outColor = vec4(0, 0, 1, 1);
	else if (material == uint(4))
		outColor = vec4(1, 1, 0, 1);
	else if (material == uint(5))
		outColor = vec4(0, 1, 1, 1);
	else if (material == uint(6))
		outColor = vec4(1, 0, 1, 1);
	else if (material == uint(7))
		outColor = vec4(0, 1, 1, 1);
	else if (material == uint(8))
		outColor = vec4(0.5, 0, 0, 1);
	else if (material == uint(9))
		outColor = vec4(0, 0.5, 0, 1);
	else if (material == uint(10))
		outColor = vec4(0, 0, 0.5, 1);
	else if (material == uint(11))
		outColor = vec4(0.5, 0.5, 0, 1);
	else if (material == uint(12))
		outColor = vec4(0.5, 0, 0.5, 1);
	else if (material == uint(13))
		outColor = vec4(0, 0.5, 0.5, 1);
	else if (material == uint(14))
		outColor = vec4(0.7, 0, 0, 1);
	else if (material == uint(15))
		outColor = vec4(0, 0.7, 0, 1);
	else if (material == uint(16))
		outColor = vec4(0, 0, 0.7, 1);
	else if (material == uint(17))
		outColor = vec4(0.7, 0.7, 0, 1);
	else if (material == uint(18))
		outColor = vec4(0.7, 0, 0.7, 1);
	else if (material == uint(19))
		outColor = vec4(0, 0.7, 0.7, 1);
	else if (material == uint(20))
		outColor = vec4(0.7, 0.7, 0.7, 1);
	else if (material == uint(21))
		outColor = vec4(0.3, 0, 0, 1);
	else if (material == uint(22))
		outColor = vec4(0.3, 0.3, 0, 1);
	else if (material == uint(23))
		outColor = vec4(0.3, 0, 0.3, 1);
	else if (material == uint(24))
		outColor = vec4(0.3, 0.3, 0.3, 1);
	else if (material == uint(25))
		outColor = vec4(0, 0, 0.3, 1);
	else if (material == uint(26))
		outColor = vec4(0, 0.3, 0.3, 1);
	else if (material == uint(27))
		outColor = vec4(1, 1, 0, 1);
	else
		outColor = vec4(1, 0, 0, 1);
}
