#version 330 core

layout (location = 0) in vec3 aPos;

uniform float offset;
uniform mat4 model;

void main(){
    gl_Position = model * vec4(aPos.x, aPos.yz , 1.0f);
}

