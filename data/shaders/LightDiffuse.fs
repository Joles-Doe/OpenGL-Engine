#version 330 core

uniform sampler2D uTexture;

in vec2 vTextureCoord;
in vec3 vNormal;
in vec3 vFragPos;

out vec4 oFragColor;

void main()
{
	vec4 tex = texture2D(uTexture, vTextureCoord);
	
	vec3 lightPos = vec3(10, 10, 10);
	vec3 diffuseColor = vec3(1, 1, 1);

	vec3 N = normalize(vNormal);
	vec3 lightDir = normalize(lightPos - vFragPos);
	float diff = max(dot(N, lightDir), 0.0);
	vec3 diffuse = diffuseColor * diff;

	vec3 lighting = diffuse;
	oFragColor = vec4(lighting, 1) * tex;
}