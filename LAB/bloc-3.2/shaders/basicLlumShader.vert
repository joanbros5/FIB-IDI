#version 330 core

in vec3 vertex;
in vec3 normal;

in vec3 matamb;
in vec3 matdiff;
in vec3 matspec;
in float matshin;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 TG;

// Valors per als components que necessitem del focus de llum
//uniform vec3 colorFocus;    ---- Al ser uniform no hace falta declararlo aquí
//vec3 llumAmbient = vec3(0.2, 0.2, 0.2);   ---- Se puede declarar en el fragment shader directamente

uniform vec3 posFocus; //En SCA si es foco de escena

//Booleano para saber si es foco de escena
uniform int focusEscena;

//OUTS
//out vec3 fcolor;  ---- Ya no hace falta
out vec3 matambf;
out vec3 matdifff;
out vec3 matspecf;
out float matshinf;

out vec3 NormSCO;
out vec3 L;
out vec4 vertexSCO;

void main()
{	
    //Calculo de normales
    mat3 NormalMatrix = inverse(transpose(mat3(view * TG)));
    NormSCO = normalize(NormalMatrix*normal);

    //Calculo de vertices
    vertexSCO = view * TG * vec4(vertex, 1.0);

    //Calculo de focus
    vec4 focusSCO;
    
    if (focusEscena == 1) focusSCO = view * vec4(posFocus,1.0);
    else focusSCO = vec4(vec3(0.0,0.0,0.0),1.0);
    
    L = normalize(focusSCO.xyz-vertexSCO.xyz);

    //Paso de cosas de las funciones al fragment shader
    matambf = matamb;
    matdifff = matdiff;
    matspecf = matspec;
    matshinf = matshin;
    
    //Color final, ya no es necesario
    //fcolor = Ambient() + Difus(NormSCO, L, colorFocus) + Especular(NormSCO, L, vertexSCO, colorFocus);
    
    gl_Position = proj * view * TG * vec4 (vertex, 1.0);
}
