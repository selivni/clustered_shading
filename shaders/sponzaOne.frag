#version 330 core

in vec3 uv;

uniform uint material;

uniform sampler2D Tex0;
uniform sampler2D Tex1;
uniform sampler2D Tex2;
uniform sampler2D Tex3;
uniform sampler2D Tex4;
uniform sampler2D Tex5;
uniform sampler2D Tex6;
uniform sampler2D Tex7;
uniform sampler2D Tex8;
uniform sampler2D Tex9;
uniform sampler2D Tex10;
uniform sampler2D Tex11;
uniform sampler2D Tex12;
uniform sampler2D Tex13;

uniform sampler2D Opac0;
uniform sampler2D Opac1;

out vec4 outColor;

void main()
{
	vec2 TexCoord = vec2(uv.x,1 - uv.y);
	mat4 minimalLight = mat4(0);
	minimalLight[0][0] = 0.35;
	minimalLight[1][1] = 0.35;
	minimalLight[2][2] = 0.35;
	minimalLight[3][3] = 1;
	if (material == uint(0))
		outColor = texture(Tex0, TexCoord);
	else if (material == uint(1))
	{
		vec4 preColor = minimalLight * texture(Tex1, TexCoord);
		preColor.a *= texture(Opac0, TexCoord).y;
		if (preColor.a < 0.5)
			discard;
		outColor = preColor;
	}
	else if (material == uint(2))
		outColor = minimalLight * texture(Tex2, TexCoord);
	else if (material == uint(3))
	{
		vec4 preColor = minimalLight * texture(Tex3, TexCoord);
		preColor.a *= texture(Opac1, TexCoord).y;
//		if (preColor.a < 0.0001)
			discard;
		outColor = preColor;
	}
	else if (material == uint(4))
		outColor = minimalLight * texture(Tex4, TexCoord);
	else if (material == uint(5))
		outColor = minimalLight * texture(Tex5, TexCoord);
	else if (material == uint(6))
		outColor = minimalLight * texture(Tex6, TexCoord);
	else if (material == uint(7))
		outColor = minimalLight * texture(Tex7, TexCoord);
	else if (material == uint(8))
		outColor = minimalLight * texture(Tex8, TexCoord);
	else if (material == uint(9))
		outColor = minimalLight * texture(Tex9, TexCoord);
	else if (material == uint(10))
		outColor = minimalLight * texture(Tex10, TexCoord);
	else if (material == uint(11))
		outColor = minimalLight * texture(Tex11, TexCoord);
	else if (material == uint(12))
		outColor = minimalLight * texture(Tex12, TexCoord);
	else if (material == uint(13))
		outColor = minimalLight * texture(Tex13, TexCoord);
	else
		outColor = vec4(1, 0, 0, 1);
}
