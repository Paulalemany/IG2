#version 330 core

in vec2 vUv0;
uniform sampler2D tCorrosion;
uniform sampler2D tBumpy;
uniform sampler2D tDirt;
uniform float target;

out vec4 fFragColor;

void main() {

    vec4 corrosion = texture(tCorrosion, vUv0);
    if (corrosion.r > 0.6) { 
        discard; 
    }

    float cara = 0;
    if (gl_FrontFacing) {
        cara = 1.0;
    }
    else {
        cara = -1.0;
    } 
    

    cara *= target;

    vec4 lado = texture(tBumpy, vUv0);  //Prederterminado es el frente

    if(cara > 0.0){
        lado = texture(tBumpy, vUv0); //Si es el otro lado lo cambiamos
    } 
    else {
         lado = texture(tDirt, vUv0);
    }

    fFragColor = lado;
}