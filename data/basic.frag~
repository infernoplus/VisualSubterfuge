#version 330 core

in vec2 texCoord;
in vec3 normal;

out vec3 pixel;

uniform sampler2D tex0;

uniform vec3 color; //color:[1.0f,1.0f,1.0f]

void main() {
	pixel = texture(tex0,texCoord).rgb;
}
