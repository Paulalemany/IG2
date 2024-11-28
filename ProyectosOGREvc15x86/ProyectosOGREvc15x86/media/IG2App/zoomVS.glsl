#version 330 core

in vec4 vertex;
in vec2 uv0;
uniform mat4 modelViewProjMat;
out vec2 vUv0;

void main(){
    //Diria que va por aqui arriba las cosas de zoom

    //El 2 es el ZF para conseguir el efecto necesitamos que varie mientras pasa el tiempo
    vUv0.s = (uv0.s - 0.5) * (2) + 0.5;
    vUv0.t = (uv0.t - 0.5) * (2) + 0.5;

    //vUv0 = uv0;
    gl_Position = modelViewProjMat * vertex;
}