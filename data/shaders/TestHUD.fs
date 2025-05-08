#version 330 core

in vec2 vUV;
in vec4 vColor;
in vec2 vMousePos;

out vec4 oFragColor;

void main()
{
	float dist = distance(vUV, vMousePos);

    // Smooth edge circle
    float alpha = smoothstep(0.1, 0.12, dist);

    vec4 color = vColor;
    color.w = alpha;

    oFragColor = color;
}