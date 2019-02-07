#version 330 core 
layout (location = 0) in vec3 offset;
layout (location = 1) in vec3 particle_center;

uniform mat4 mvp;

void main() {
	gl_Position = mvp * vec4(particle_center + offset, 1.0f);
}