#version 330 core

in vec3 aPosition;
in vec2 aPixelColor;
in vec3 aNormal;

out vec2 vTextureCoord;
out vec3 vNormal;
out vec3 vViewDir;
out vec3 vFragPos;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uModel;

void main()
{
	vTextureCoord = aPixelColor;
	vNormal = normalize(mat3(transpose(inverse(uModel))) * aNormal);

	vec4 worldPos = uModel * vec4(aPosition, 1.0);
	vViewDir = normalize(-worldPos.xyz);
	vFragPos = vec3(worldPos.xyz);

	gl_Position = uProjection * uView * worldPos;
}