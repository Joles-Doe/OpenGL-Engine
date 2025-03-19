attribute vec3 aPosition;
attribute vec2 aPixelColor;

varying vec2 vTextureCoord;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uModel;

void main()
{
	gl_Position = uProjection * uView * uModel * vec4(aPosition, 1.0);
	vTextureCoord = aPixelColor;
}