#version 330 core

in vec2 vUV;
in float vTime;

out vec4 oFragColor;

void main()
{
    vec2 uv = vUV;
    
    float shift = uv.x + vTime * 0.2;

    vec3 color = 0.5 + 0.5 * cos(6.2831 * shift + vec3(0.0, 2.0, 4.0));

    oFragColor = vec4(color, 1.0);
}