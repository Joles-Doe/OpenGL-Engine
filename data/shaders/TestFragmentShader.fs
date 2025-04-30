precision mediump float;

varying float vDepth;

void main()
{
    // Map depth to heat color
    float t = clamp(vDepth / 35.0, 0.0, 1.0);  // adjust 10.0 to your scene size
    vec3 heatColor = mix(vec3(1.0, 0.2, 0.0), vec3(0.0, 0.2, 1.0), t);
    gl_FragColor = vec4(heatColor, 1.0);
}
