uniform sampler2D uTexture;
uniform vec3 uViewPos;

varying vec2 vTextureCoord;
varying vec3 vNormal;
varying vec3 vFragPos;

void main()
{
	vec4 tex = texture2D(uTexture, vTextureCoord);
	
	vec3 lightPos = vec3(10, 10, 10);
	vec3 diffuseColor = vec3(1, 1, 1);

	vec3 N = normalize(vNormal);
	vec3 lightDir = normalize(lightPos - vFragPos);
	float diff = max(dot(N, lightDir), 0.0);
	vec3 diffuse = diffuseColor * diff;

	vec3 specularColor = vec3(1, 1, 1);

	vec3 viewDir = normalize(uViewPos - vFragPos);
	vec3 reflectDir = reflect(-lightDir, N);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = spec * specularColor;

	vec3 lighting = diffuse + specular; 
	gl_FragColor = vec4(lighting, 1) * tex;

	viewDir = normalize(uViewPos - vFragPos);
	gl_FragColor = vec4(normalize(uViewPos / 10.0), 1.0);
}