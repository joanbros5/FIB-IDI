#version 330 core

out vec4 FragColor;

in vec3 fcolor;

void main() {
    //if ( int(gl_FragCoord.y) % 10 < 5) discard;
    FragColor = vec4(fcolor.r * sin(gl_FragCoord.x), fcolor.g * cos(gl_FragCoord.y), fcolor.b ,1.0);
    //if (sin(gl_FragCoord.x) <  && sin(gl_FragCoord.y) > sin(708)) FragColor = vec4(1, 0, 0, 1);
    //if (sin(gl_FragCoord.x) > sin(708) && sin(gl_FragCoord.y) > sin(708)) FragColor = vec4(0, 0, 1, 1);
    //if (gl_FragCoord.x < 354 && gl_FragCoord.y < 354) FragColor = vec4(1, 1, 0, 1);
    
    //ESPAÑA
    //if (gl_FragCoord.y < 708/3) FragColor = vec4(1,0,0,1);
    //else if (gl_FragCoord.y >= 708/3 && gl_FragCoord.y < 2*(708/3)) FragColor = vec4(1,1,0,1);
    //else if (gl_FragCoord.y > 2*(708/3)) FragColor = vec4(1,0,0,1);
    
}
