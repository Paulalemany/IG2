#version 330 core
in vec2 vUv0;

uniform sampler2D spacesky;
uniform sampler2D flare;

uniform float minLight;
uniform float maxLight;

uniform float timer;

out vec4 fFragColor;

void main(){

    vec3 t1 = vec3(texture(spacesky,vUv0));
    vec3 t2 = vec3(texture(flare,vUv0));

    vec3 mezcla = mix(t1, t2, 0.5);

    float diff = maxLight - minLight;

    float lfactor = minLight + (diff*( (timer+1) / 2));

    fFragColor =  vec4( mezcla.x * lfactor,
                        mezcla.y * lfactor,
                        mezcla.z * lfactor, 1); 

    vec3 color = t1 * t2 * lfactor;

    fFragColor =  vec4(color , 1); 
    
}