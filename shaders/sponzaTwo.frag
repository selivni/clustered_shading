#version 330 core

in vec3 uv;
in vec3 norm;
in vec3 cameraVector;
in vec3 pointPosition;

uniform uint material;

uniform vec3 lightsPositions[10];
uniform vec3 lightsColors[10];
uniform float lightsPowers[10];

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
	vec4 diffColor;
	vec4 specColor;
	vec3 normal = normalize(norm);
	vec3 camVec = normalize(cameraVector);
	const float specPower = 50.0;
	vec2 TexCoord = vec2(uv.x,1 - uv.y) + vec2(norm) - vec2(norm);
	if (material == uint(14))
		diffColor = texture(Tex14, TexCoord);
	else if (material == uint(15))
		diffColor = texture(Tex15, TexCoord);
	else if (material == uint(16))
		diffColor = texture(Tex16, TexCoord);
	else if (material == uint(17))
		diffColor = texture(Tex17, TexCoord);
	else if (material == uint(18))
		diffColor = texture(Tex18, TexCoord);
	else if (material == uint(19))
		diffColor = texture(Tex19, TexCoord);
	else if (material == uint(20))
		diffColor = texture(Tex20, TexCoord);
	else if (material == uint(21))
		diffColor = texture(Tex21, TexCoord);
	else if (material == uint(22))
	{
		vec4 preColor = texture(Tex22, TexCoord);
		preColor.a *= texture(Opac2, TexCoord).y;
		if (preColor.a < 0.5)
			discard;
		diffColor = preColor;
	}
	else if (material == uint(23))
		diffColor = texture(Tex23, TexCoord);
	else if (material == uint(24))
		diffColor = texture(Tex24, TexCoord);
	else if (material == uint(25))
		diffColor = texture(Tex25, TexCoord);
	else if (material == uint(26))
		diffColor = texture(Tex26, TexCoord);
	else if (material == uint(27))
		diffColor = texture(Tex27, TexCoord);
	else
		diffColor = vec4(1, 0, 0, 1);

	int i;
	vec3 lightSum = vec3(0, 0, 0);
	float aC = 0.1;
	float aL = 0.01;
	float aD = 0.001;
	for (i = 0; i < 10; i++)
	{
		float d;
		if ((d = length(pointPosition - lightsPositions[i])) < 1000)
		{
			vec3 lightDir = normalize(lightsPositions[i] - pointPosition);
			vec3 bissect = normalize(
				(lightDir + camVec) / abs(lightDir + camVec));
			float bisnor = dot(bissect, normal);
			bisnor *= bisnor;
			float norLight = dot(normal, lightDir);
			specColor = (diffColor + vec4(lightsColors[i], 1)) / 2;
			vec3 diff = vec3(diffColor) * lightsColors[i] * norLight
				   * lightsPowers[i] / (aC + d * aL + d*d * aD);
			vec3 spec = vec3(specColor) *
					exp(-specPower * (1.0 - bisnor) / bisnor);
			lightSum += diff + spec;
		}
	}
	if (lightSum.x < 0.1 && lightSum.y < 0.1 && lightSum.z < 0.1)
		lightSum = vec3(diffColor * 0.1);
	if (lightSum.x > 1)
		lightSum.x = 1;
	if (lightSum.y > 1)
		lightSum.y = 1;
	if (lightSum.z > 1)
		lightSum.z = 1;
	outColor = vec4(lightSum, 1);


/*
	specColor = (diffColor + vec4(1, 1, 1, 1)) / 2;
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
//	vec4 spec = specColor * pow(max(dot(normal, bissect), 0.15), specPower);
	outColor = vec4(vec3(diff+spec), 1);*/
}
