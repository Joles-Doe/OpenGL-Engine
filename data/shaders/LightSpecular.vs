#version 330 core

in vec3 aPosition;
in vec2 aPixelColor;
in vec3 aNormal;

out vec2 vTextureCoord;
out vec3 vNormal;
out vec3 vFragPos;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uModel;

void main()
{
	gl_Position = uProjection * uView * uModel * vec4(aPosition, 1.0);

	vTextureCoord = aPixelColor;
	vNormal = mat3(uModel) * aNormal;
	vFragPos = vec3(uModel * vec4(aPosition, 1.0));
}