#version 330 core
in vec2 vUv0;
uniform sampler2D spacesky;
uniform sampler2D flare;
uniform float BF;
uniform float intLuzAmb;
out vec4 fFragColor;

void main(){
    vec3 colorL = vec3(texture(spacesky, vUv0));
    vec3 colorM = vec3(texture(flare, vUv0));
    vec3 color = mix(colorL, colorM, BF) * intLuzAmb;
    fFragColor = vec4(color, 1.0);
}