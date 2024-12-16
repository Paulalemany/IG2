#version 330 core 
in vec2 vUv0; 
uniform sampler2D checker;  
uniform sampler2D bumpyMetal;  
uniform float intLuzAmb; 
out vec4 fFragColor; 

void main()
{
    vec3 checkerColor = vec3(texture(checker,vUv0)); 
    vec3 metalColor = vec3(texture(bumpyMetal, vUv0));

    //Si el vertice actual es negro en checker, le ponemos corrosion
    //Si es blanco ponemos el metal

    if (checkerColor.r == 0 && checkerColor.g == 0 && checkerColor.b == 0){
        fFragColor = vec4(metalColor, 1.0);
    } 
    else {
        discard;
    } 
}