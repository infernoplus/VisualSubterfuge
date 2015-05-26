#version 330 core

layout(location = 0) in vec3 vert; 
layout(location = 1) in vec3 norm; 
layout(location = 2) in vec3 coord;

out vec2 texCoord;
out vec3 normal;

uniform mat4 mvp;

uniform float scale; //scale:1.0f

void main() { 
	texCoord = coord.xy;
	normal = norm;
	gl_Position = mvp * vec4(vert,1.0f);
}
