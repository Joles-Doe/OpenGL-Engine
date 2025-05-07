#version 330 core

in vec3 aPosition;
in vec2 aPixelColor;

out vec4 vColor;

uniform mat4 uProjection;
uniform mat4 uModel;

uniform vec4 uColor;

void main()
{
	gl_Position = uProjection * uModel * vec4(aPosition, 1.0);
	vColor = uColor;
}