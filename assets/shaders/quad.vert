#version 330 core 
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 texture_v;

out vec2 texture_vert;

uniform mat4 mvp;

void main() {
	texture_vert = texture_v;
	gl_Position = mvp * vec4(aPos, 1.0f);
}