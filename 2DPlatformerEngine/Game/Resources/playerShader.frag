#version 450 core

out vec4 fragColor;

in vec2 uv;

layout (binding = 0) 
uniform sampler2D image;

void main() {
	
	fragColor = texture(image, uv);

}