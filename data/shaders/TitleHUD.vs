#version 330 core

in vec3 aPosition;
in vec2 aPixelColor;

out vec2 vUV;
out vec4 vColor;
out vec2 vMousePos;
out float vRadius;

uniform mat4 uProjection;
uniform mat4 uModel;
uniform vec4 uColor;
uniform vec2 uMousePos;
uniform float uRadius;

void main() {
    vUV = aPosition.xy;
    vColor = uColor;
    vMousePos = uMousePos;
    vRadius = uRadius;

    gl_Position = uProjection * uModel * vec4(aPosition, 1.0);
}