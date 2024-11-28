#version 330 core

in vec2 vUv0;
uniform sampler2D spacesky;
out vec4 fFragColor;

void main() {

    vec3 color = vec3(texture(spacesky, vUv0));
    
    fFragColor = vec4(color, 1.0);
}