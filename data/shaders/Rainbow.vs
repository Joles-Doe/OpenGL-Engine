#version 330 core

in vec3 aPosition;
in vec2 aPixelColor;

out vec2 vUV;
out float vTime;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uModel;

uniform float uTime;

void main() {
    vUV = aPixelColor;
    vTime = uTime;

    gl_Position = uProjection * uView * uModel * vec4(aPosition, 1.0);
}