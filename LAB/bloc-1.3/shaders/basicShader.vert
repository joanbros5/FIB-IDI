#version 330 core

in vec3 vertex;
uniform mat4 TG; 
uniform float scl;

void main () {
    gl_Position = TG * vec4 (vertex * scl, 1.0);
}
