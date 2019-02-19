#version 330 core

in vec2 texture_vert;
out vec4 fragColor;

uniform sampler2D texture_;

void main() {
	vec4 color = texture(texture_, texture_vert);
	if (color.a < 0.1)
			discard;
	fragColor = color;
}