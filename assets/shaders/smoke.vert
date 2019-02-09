#version 330 core 
layout (location = 0) in vec3 offset;
layout (location = 1) in vec2 texture_offset;
layout (location = 2) in vec3 particle_center;

out vec2 f_texture_offset;

uniform mat4 mvp;
uniform vec3 camera_up;
uniform vec3 camera_right;

void main() {
	vec3 world_space_vertex_offset = particle_center + camera_right * offset.x + camera_up * offset.y;
	gl_Position = mvp * vec4(world_space_vertex_offset, 1.0f);
	f_texture_offset = texture_offset;
}