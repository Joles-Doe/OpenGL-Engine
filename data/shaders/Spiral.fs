#version 330 core

in vec2 vUV;
in float vTime;

out vec4 oFragColor;

void main()
{
    vec2 uv = vUV * 2.0 - 1.0;
    float t = vTime * 2.0;

    float angle = atan(uv.y, uv.x);
    float radius = length(uv);
    float spiral = sin(10.0 * radius - t * 5.0 + angle * 5.0);

    float brightness = smoothstep(0.0, 1.0, spiral);
    vec3 color = vec3(brightness);

    oFragColor = vec4(color, 1.0);
}