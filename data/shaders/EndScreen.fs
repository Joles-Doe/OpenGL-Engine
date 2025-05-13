#version 330 core

uniform sampler2D uTexture;

in vec2 vUV;
in vec2 vTextureCoord;
in vec2 vMousePos;
in float vRadius;

out vec4 oFragColor;

void main()
{
    float pixelSize = 0.01; // Adjust this for more or less pixelation

    // Quantize the coordinates to the pixel grid
    vec2 pixelUV = floor(vUV / pixelSize) * pixelSize;
    vec2 pixelMouse = floor(vMousePos / pixelSize) * pixelSize;

    float dist = distance(pixelUV, pixelMouse);

    float radius = vRadius;
    float alpha = smoothstep(radius, radius, dist);


    vec4 tex = texture(uTexture, vTextureCoord);
    tex.a *= alpha;

    oFragColor = tex;
}