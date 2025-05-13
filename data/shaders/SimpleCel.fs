#version 330 core

uniform sampler2D uTexture;

in vec2 vTextureCoord;
in vec3 vNormal;
in vec3 vViewDir;
in vec3 vFragPos;

out vec4 oFragColor;

void main()
{
	vec3 tex = texture2D(uTexture, vTextureCoord).rgb;
	
	// Lighting first
    vec3 lightPos = vec3(0, 10, -8);
    vec3 lightColor = vec3(1.0);
	vec3 diffuseColor = vec3(1.0, 1.0, 1.0);

	vec3 N = normalize(vNormal);
    vec3 L = normalize(lightPos - vFragPos);
    float diff = max(dot(N, L), 0.0);
    vec3 litColor = tex * diffuseColor * diff;
    
    // Cel shade
	float edge = dot(normalize(vNormal), normalize(vViewDir));
	edge = smoothstep(0.0, 0.2, abs(edge));
	vec3 tintColor = vec3(0.0);

	vec3 outputColor = mix(tintColor, litColor, edge);
	oFragColor = vec4(outputColor, 1.0f);
}