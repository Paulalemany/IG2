#version 330 core
in vec2 vUv0;
uniform sampler2D aguaT;
out vec4 fFragColor;

void main(){
    vec4 color = texture(aguaT, vUv0);
    fFragColor = color;
}