uniform sampler2D uTexture;

varying vec2 vTextureCoord;

void main()
{
	vec4 tex = texture2D(uTexture, vTextureCoord);
	gl_FragColor = tex;
}