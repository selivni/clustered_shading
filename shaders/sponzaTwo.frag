#version 330 core

in vec3 uv;

uniform uint material;

uniform sampler2D Tex14;
uniform sampler2D Tex15;
uniform sampler2D Tex16;
uniform sampler2D Tex17;
uniform sampler2D Tex18;
uniform sampler2D Tex19;
uniform sampler2D Tex20;
uniform sampler2D Tex21;
uniform sampler2D Tex22;
uniform sampler2D Tex23;
uniform sampler2D Tex24;
uniform sampler2D Tex25;
uniform sampler2D Tex26;
uniform sampler2D Tex27;

uniform sampler2D Opac2;

out vec4 outColor;

void main()
{
	vec2 TexCoord = vec2(uv.x,1 - uv.y);
	mat4 minimalLight = mat4(0);
	minimalLight[0][0] = 0.35;
	minimalLight[1][1] = 0.35;
	minimalLight[2][2] = 0.35;
	minimalLight[3][3] = 1;
	if (material == uint(14))
		outColor = minimalLight * texture(Tex14, TexCoord);
	else if (material == uint(15))
		outColor = minimalLight * texture(Tex15, TexCoord);
	else if (material == uint(16))
		outColor = minimalLight * texture(Tex16, TexCoord);
	else if (material == uint(17))
		outColor = minimalLight * texture(Tex17, TexCoord);
	else if (material == uint(18))
		outColor = minimalLight * texture(Tex18, TexCoord);
	else if (material == uint(19))
		outColor = minimalLight * texture(Tex19, TexCoord);
	else if (material == uint(20))
		outColor = minimalLight * texture(Tex20, TexCoord);
	else if (material == uint(21))
		outColor = minimalLight * texture(Tex21, TexCoord);
	else if (material == uint(22))
	{
		vec4 preColor = minimalLight * texture(Tex22, TexCoord);
		preColor.a *= texture(Opac2, TexCoord).y;
		if (preColor.a < 0.5)
			discard;
		outColor = preColor;
	}
	else if (material == uint(23))
		outColor = minimalLight * texture(Tex23, TexCoord);
	else if (material == uint(24))
		outColor = minimalLight * texture(Tex24, TexCoord);
	else if (material == uint(25))
		outColor = minimalLight * texture(Tex25, TexCoord);
	else if (material == uint(26))
		outColor = minimalLight * texture(Tex26, TexCoord);
	else if (material == uint(27))
		outColor = minimalLight * texture(Tex27, TexCoord);
	else
		outColor = vec4(1, 0, 0, 1);
}
