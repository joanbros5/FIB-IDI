#version 330 core

in vec3  fmatamb;
in vec3  fmatdiff;
in vec3  fmatspec;
in float fmatshin;
in vec3  fvertex;
in vec3  fnormal;

const vec3 llumAmbient = vec3(0.1, 0.1, 0.1);

uniform mat4 TG;
uniform mat4 Proj;
uniform mat4 View;

out vec4 FragColor;

//Nuevo:
in vec3 NormSCO;
in vec4 vertexSCO;

uniform vec3 posFocus1, posFocus2, posFocus3, posFocus4, posFocusLinterna;
uniform vec3 colorFocus1, colorFocus2, colorFocus3, colorFocus4, colorFocusLinterna;

uniform mat4 TGLint;

vec3 Ambient() {
  return llumAmbient*fmatamb;
}

vec3 Difus (vec3 NormSCO, vec3 L, vec3 colFocus)
{
  // Fixeu-vos que SOLS es retorna el terme de Lambert!
  // S'assumeix que els vectors que es reben com a paràmetres estan normalitzats
  vec3 colRes = vec3(0);
  if (dot (L, NormSCO) > 0)
    colRes = colFocus * fmatdiff * dot (L, NormSCO);
  return (colRes);
}

vec3 Especular (vec3 NormSCO, vec3 L, vec3 vertSCO, vec3 colFocus)
{
  // Fixeu-vos que SOLS es retorna el terme especular!
  // Assumim que els vectors estan normalitzats
  vec3 colRes = vec3 (0);
  // Si la llum ve de darrera o el material és mate no fem res
  if ((dot(NormSCO,L) < 0) || (fmatshin == 0))
    return colRes;  // no hi ha component especular

  vec3 R = reflect(-L, NormSCO); // equival a: 2.0*dot(NormSCO,L)*NormSCO - L;
  vec3 V = normalize(-vertSCO); // perquè la càmera està a (0,0,0) en SCO

  if (dot(R, V) < 0)
    return colRes;  // no hi ha component especular

  float shine = pow(max(0.0, dot(R, V)), fmatshin);
  return (colRes + fmatspec * colFocus * shine);
}

void main()
{
    //Calculo de focos:
    vec4 focusSCO1, focusSCO2, focusSCO3, focusSCO4, focusSCOLinterna;
    
    focusSCO1 = View * vec4(posFocus1, 1.0);
    focusSCO2 = View * vec4(posFocus2, 1.0);
    focusSCO3 = View * vec4(posFocus3, 1.0);
    focusSCO4 = View * vec4(posFocus4, 1.0);
    focusSCOLinterna = View * TGLint * vec4(posFocusLinterna, 1.0);
    
    vec3 LSCO1 = focusSCO1.xyz - vertexSCO.xyz;
    vec3 LSCO2 = focusSCO2.xyz - vertexSCO.xyz;
    vec3 LSCO3 = focusSCO3.xyz - vertexSCO.xyz;
    vec3 LSCO4 = focusSCO4.xyz - vertexSCO.xyz;
    vec3 LSCOLinterna = focusSCOLinterna.xyz - vertexSCO.xyz;
    
    vec3 L1,L2,L3,L4,LLinterna;
    
    L1 = normalize(LSCO1);
    L2 = normalize(LSCO2);
    L3 = normalize(LSCO3);
    L4 = normalize(LSCO4);
    LLinterna = normalize(LSCOLinterna);
    
    //Cosa independiente
    vec3 NormSCOF = normalize(NormSCO);

    //Color final (Sumar todos los focos)
    vec3 fcolor = Ambient() + Difus(NormSCOF, L1, colorFocus1) + Especular(NormSCOF, L1, vertexSCO.xyz, colorFocus1)
                            + Difus(NormSCOF, L2, colorFocus2) + Especular(NormSCOF, L2, vertexSCO.xyz, colorFocus2)
                            + Difus(NormSCOF, L3, colorFocus3) + Especular(NormSCOF, L3, vertexSCO.xyz, colorFocus3)
                            + Difus(NormSCOF, L4, colorFocus4) + Especular(NormSCOF, L4, vertexSCO.xyz, colorFocus4)
                            + Difus(NormSCOF, LLinterna, colorFocusLinterna) + Especular(NormSCOF, LLinterna, vertexSCO.xyz, colorFocusLinterna);
    
    FragColor = vec4(fcolor, 1);
}
