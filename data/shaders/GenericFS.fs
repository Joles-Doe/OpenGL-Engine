uniform sampler2D uTexture;

in vec2 vTextureCoord;

out vec4 oFragColor;

void main()
{
	vec4 tex = texture2D(uTexture, vTextureCoord);
	oFragColor = tex;
}