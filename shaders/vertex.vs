#version 450 core

in vec2 aPos;
in vec4 aColor;

uniform float uVal;

out vec4 vColor;

void main() {
    gl_Position = vec4(aPos.xy + vec2(uVal, 0), 0, 1);
    vColor = aColor;
}
