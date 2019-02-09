#version 330 core

in vec2 f_texture_offset;
out vec4 fragColor;

uniform sampler2D our_texture;

void main() {
	vec4 color = texture(our_texture, f_texture_offset);
	color.a = color.a * 0.5;
	if (color.a < 0.1)
		discard;
	fragColor = color;
}