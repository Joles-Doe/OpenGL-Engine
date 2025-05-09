#version 330 core

in vec2 vUV;
in float vTime;
in vec2 vRes;

out vec4 oFragColor;

void main()
{
    vec2 uv = vUV;
    
    // Increase the frequency of the ripples to create more of them
    float ripplesX = sin(uv.x * 30 + vTime);    
    float ripplesY = sin(uv.y * 30 + vTime);
    float ripplesDiag = sin((uv.x + uv.y) * 30 + vTime);
    
    // Combine the sine waves to create the plasma effect
    float colorValue = ripplesX + ripplesY + ripplesDiag;

    // Add color variations based on the ripples
    float red = 0.5 + 0.5 * sin(colorValue * 3.0 + vTime);
    float green = 0.5 + 0.5 * cos(colorValue * 2.0 + vTime + 1.0);
    float blue = 0.5 + 0.5 * tan(colorValue * 1.5 + vTime + 2.0);

    oFragColor = vec4(red, green, blue, 1.0);
}