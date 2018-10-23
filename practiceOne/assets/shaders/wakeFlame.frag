#version 330 core

in vec2 texCoord;
in vec3 textColor;

out vec4 fragColor;

uniform sampler2D ourTexture;

void main() {
	fragColor = vec4(1,1,1,1);//texture(ourTexture, texCoord);
}