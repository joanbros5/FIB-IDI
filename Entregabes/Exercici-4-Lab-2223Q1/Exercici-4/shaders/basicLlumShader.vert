#version 330 core

in vec3 vertex;
in vec3 normal;

in vec3  matamb;
in vec3  matdiff;
in vec3  matspec;
in float matshin;

uniform mat4 TG;
uniform mat4 Proj;
uniform mat4 View;

out vec3  fmatamb;
out vec3  fmatdiff;
out vec3  fmatspec;
out float fmatshin;
out vec3  fvertex;
out vec3  fnormal;

//Nuevo
out vec3 NormSCO;
out vec4 vertexSCO;


void main()
{	
    //Calculo de vertices
    vertexSCO = View * TG * vec4(vertex, 1.0);
    
    //Calculo de normales
    mat3 NormalMatrix = inverse(transpose(mat3(View * TG)));
    NormSCO = NormalMatrix*normal;

    // Passem les dades al fragment shader
    fmatamb  = matamb;
    fmatdiff = matdiff;
    fmatspec = matspec;
    fmatshin = matshin;
    fvertex = vertex; // CALCULEU CORRECTAMENT
    fnormal = normal; // CALCULEU CORRECTAMENT

    gl_Position = Proj * View * TG * vec4 (vertex, 1.0);
}
