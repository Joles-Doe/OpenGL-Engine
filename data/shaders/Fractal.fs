#version 330 core

in vec2 vUV;
in float vTime;

out vec4 oFragColor;

float Fractal(vec2 pos)
{
    return sin(pos.x * 10.0 + pos.y * 10.0 + sin(vTime) * 5.0);
}

void main()
{
    vec2 pos = vUV / vec2(960.0, 540.0); // Normalize to screen space
    float noise = Fractal(pos * 10.0);

    oFragColor = vec4(vec3(noise * 0.5 + 0.5), 1.0);
}