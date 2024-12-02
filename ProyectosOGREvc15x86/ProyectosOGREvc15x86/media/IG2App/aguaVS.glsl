#version 330 core
in vec4 vertex;
in vec2 uv0;

uniform mat4 modelViewProjMat;
uniform float timer;
uniform vec2 centro;

out vec2 vUv0;

void main() {
    vUv0 = uv0;

    vec4 coordenadas = vertex;
    float centre = distance(vec2(coordenadas.x, coordenadas.z), centro);

    float a = 50;   //Velocidad
    float b = 1;    //Altura

    coordenadas.y += sin(coordenadas.x + (timer * a)) * b
                    + sin(coordenadas.z + centre + (timer * a)) * b;

    gl_Position = modelViewProjMat * coordenadas;
}