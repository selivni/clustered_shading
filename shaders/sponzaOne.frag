#version 330 core

in vec3 uv;
in vec3 norm;
in vec3 cameraVector;
in vec3 pointPosition;

uniform uint material;

uniform vec3 lightsPositions[10];
uniform vec3 lightsColors[10];
uniform float lightsPowers[10];

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
	vec4 diffColor;
	vec4 specColor;
	vec3 normal = normalize(norm);
	vec3 camVec = normalize(cameraVector);
	vec3 bissect = normalize((lightDir + camVec) / abs(lightDir + camVec));
	const float specPower = 10.0;

	vec2 TexCoord = vec2(uv.x,1 - uv.y) + vec2(norm) - vec2(norm);
	if (material == uint(0))
		diffColor = texture(Tex0, TexCoord);
	else if (material == uint(1))
	{
		vec4 preColor = texture(Tex1, TexCoord);
		preColor.a *= texture(Opac0, TexCoord).y;
		if (preColor.a < 0.5)
			discard;
		diffColor = preColor;
	}
	else if (material == uint(2))
		diffColor = texture(Tex2, TexCoord);
	else if (material == uint(3))
			discard;
	else if (material == uint(4))
		diffColor = texture(Tex4, TexCoord);
	else if (material == uint(5))
		diffColor = texture(Tex5, TexCoord);
	else if (material == uint(6))
		diffColor = texture(Tex6, TexCoord);
	else if (material == uint(7))
		diffColor = texture(Tex7, TexCoord);
	else if (material == uint(8))
		diffColor = texture(Tex8, TexCoord);
	else if (material == uint(9))
		diffColor = texture(Tex9, TexCoord);
	else if (material == uint(10))
		diffColor = texture(Tex10, TexCoord);
	else if (material == uint(11))
		diffColor = texture(Tex11, TexCoord);
	else if (material == uint(12))
		diffColor = texture(Tex12, TexCoord);
	else if (material == uint(13))
		diffColor = texture(Tex13, TexCoord);
	else
		diffColor = vec4(1, 0, 0, 1);

	specColor = (diffColor + vec4(1, 1, 1, 1)) / 2;
	uint i;
	vec3 colorSum = vec3(0, 0, 0);
	for (i = 0; i < 10, i++)
	{
		if (length(pointVector - lightsPositions[i]))
		vec3 lightDir = normalize(pointVector - lightsPositions[i]);
		vec3 bissect = normalize((lighttDir + camVec) / abs(lightDir + camVec));

	}
	
/*	
	float bisnor = dot(bissect, normal);
	bisnor *= bisnor;
	float norlight = dot(normal, lightDir);
	vec4 diff, spec;
	if (norlight > 0.15)
	{
		diff = diffColor * norlight;
		spec = specColor * exp(-specPower * (1.0 - bisnor) / bisnor);
	} else
	{
		diff = diffColor * 0.15;
		spec = specColor * 0;
	}
//	vec4 spec = specColor * pow(max(dot(normal, bissect), 0.0), specPower);
	outColor = vec4(vec3(diff+spec), 1);
*/
}
