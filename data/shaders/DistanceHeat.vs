#version 330 core

in vec3 aPosition;

uniform mat4 uProjection;
uniform mat4 uView;
uniform vec3 uViewPos;
uniform mat4 uModel;

varying float vDepth;

void main()
{
    vec4 worldPos = uModel * vec4(aPosition, 1.0);
    vec4 viewPos = uView * worldPos;

    vDepth = length(viewPos.xyz);  // Distance from camera

    gl_Position = uProjection * viewPos;
}
