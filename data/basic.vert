#version 330 core

layout(location = 0) in vec3 vert; 
layout(location = 1) in vec3 norm; 
layout(location = 2) in vec3 coord;

out vec2 texCoord;
out vec3 normal;

uniform mat4 mvp;

uniform vec3 pos;
uniform vec3 rot;
uniform vec3 scl;

void main() {
	texCoord = coord.xy;
	normal = norm;
	
	vec4 v = vec4((vert*scl)+pos, 1.0f);
	
	gl_Position = mvp * v; 
}
