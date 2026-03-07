#version 330 core
out vec4 FragColor;
in vec2 ourCoord;

uniform vec3 rgb;
uniform sampler2D tex;

void main() {
    FragColor = vec4(rgb, 1.0) * texture(tex, ourCoord);
}