attribute vec3 aPosition;
attribute vec2 aPixelColor;
attribute vec3 aNormal;

varying vec2 vTextureCoord;
varying vec3 vNormal;
varying vec3 vFragPos;

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