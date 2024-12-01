#version 330 core

in vec4 vertex;
uniform mat4 modelViewProjMat;
uniform float timer;
uniform float minZoom;
uniform float maxZoom;

in vec2 uv0;
out vec2 vUv0;

void main(){

    float a = (minZoom * maxZoom)/2;
    float b = maxZoom - a;

    float ZF = (timer * b) + a;

    vUv0.s = (uv0.s - minZoom) * ZF + minZoom;
    vUv0.t = (uv0.t - minZoom) * ZF + minZoom;

    gl_Position = modelViewProjMat * vertex;
}