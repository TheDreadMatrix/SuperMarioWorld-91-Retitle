#version 330


in vec2 fCoord;

uniform sampler2D tex;


out vec4 fragColor;


void main(){


    fragColor = texture(tex, fCoord);
}