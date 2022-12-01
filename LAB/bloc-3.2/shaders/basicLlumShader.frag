#version 330 core

//in vec3 fcolor;	---- Ya no es necesario

out vec4 FragColor;

in vec3 NormSCO;
in vec4 vertexSCO;

//Cosas nuevas
uniform mat4 view;

uniform vec3 posFocus; //En SCA si es foco de escena

//Booleano para saber si es foco de escena
uniform int focusEscena;

//Uniform de colorFocus
uniform vec3 colorFocus;

//Ins nuevos
in vec3 matambf;
in vec3 matdifff;
in vec3 matspecf;
in float matshinf;

vec3 llumAmbient = vec3(0.2, 0.2, 0.2);

vec3 Ambient() {
    return llumAmbient * matambf;
}

vec3 Difus (vec3 NormSCO, vec3 L, vec3 colFocus) 
{
    // Tant sols retorna el terme difús
    // S'assumeix que els vectors que es reben com a paràmetres estan normalitzats
    vec3 colRes = vec3(0);
    // Càlcul component difusa, si n'hi ha
    if (dot (L, NormSCO) > 0)
      colRes = colFocus * matdifff * dot (L, NormSCO);
    return (colRes);
}

vec3 Especular (vec3 NormSCO, vec3 L, vec4 vertSCO, vec3 colFocus) 
{
    // Tant sols retorna el terme especular!
    // Els vectors rebuts com a paràmetres (NormSCO i L) estan normalitzats
    vec3 colRes = vec3 (0);
    // Si la llum ve de darrera o el material és mate no fem res
    if ((dot(NormSCO,L) < 0) || (matshinf == 0))
      return colRes;  // no hi ha component especular

    // Calculem R i V
    vec3 R = reflect(-L, NormSCO); // equival a: 2.0*dot(NormSCO,L)*NormSCO - L;
    vec3 V = normalize(-vertSCO.xyz); // perquè la càmera està a (0,0,0) en SCO

    if (dot(R, V) < 0)
      return colRes;  // no hi ha component especular
    
    // Calculem i retornem la component especular
    float shine = pow(max(0.0, dot(R, V)), matshinf);
    return (matspecf * colFocus * shine); 
}

void main()
{	

	//Calculo de focus
    vec4 focusSCO;
    if (focusEscena == 1) focusSCO = view * vec4(posFocus,1.0);
    else focusSCO = vec4(vec3(0.0,0.0,0.0),1.0);
    
    vec3 LSCO = focusSCO.xyz-vertexSCO.xyz;
    
    vec3 L = normalize(LSCO);
    vec3 NormSCOF = normalize(NormSCO);
    
    vec3 fcolor = Ambient() + Difus(NormSCOF, L, colorFocus) + Especular(NormSCOF, L, vertexSCO, colorFocus);
    
	FragColor = vec4(fcolor,1);	
}
