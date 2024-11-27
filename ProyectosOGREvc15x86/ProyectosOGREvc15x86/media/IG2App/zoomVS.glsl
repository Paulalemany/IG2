#version 330 core
in vec4 vertex;
in vec2 uv0;
uniform mat4 modelViewProjMat;
out vec2 vUv0;
//param_named_auto sintime sintime_0_2pi

void main(){
    vUv0 = uv0;

    //Los vertices cambian la posicion
    vUv0.s = (uv0.s - 0.5) * (1) + 0.5;
    vUv0.t = (uv0.t - 0.5) * (1) + 0.5;

    gl_Position = modelViewProjMat * vertex;
}