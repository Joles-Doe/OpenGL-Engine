in vec3 aPosition;
in vec2 aPixelColor;

out vec2 vTextureCoord;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uModel;

void main()
{
	gl_Position = uProjection * uView * uModel * vec4(aPosition, 1.0);
	vTextureCoord = aPixelColor;
}