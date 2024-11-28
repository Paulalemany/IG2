#version 330 core
in vec2 vUv0;

uniform sampler2D spacesky;
uniform sampler2D flare;

uniform float BF;
uniform float intLuzAmb;

uniform float timer;

out vec4 fFragColor;

void main(){
    // Calcula un factor de zoom dinámico para la primera textura
    float zoomFactorBase = 0.8 + 0.4 * abs(sin(timer));
    vec2 zoomedUVBase = (vUv0 - 0.5) * zoomFactorBase + 0.5;

    // Calcula un factor de zoom dinámico (o fijo) para la segunda textura
    float zoomFactorOverlay = 1.0; // No hacemos zoom dinámico en esta textura
    vec2 zoomedUVOverlay = (vUv0 - 0.5) * zoomFactorBase + 0.5;

    // Muestra ambas texturas
    vec4 baseColor = texture(spacesky, zoomedUVBase);
    vec4 overlayColor = texture(flare, zoomedUVOverlay);

    
    // Combina las texturas (por ejemplo, multiplicación)
    fFragColor = baseColor * overlayColor;
}