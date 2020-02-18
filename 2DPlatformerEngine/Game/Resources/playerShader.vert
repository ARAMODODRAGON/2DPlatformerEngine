#version 450 core
layout (location = 0) 
in vec2 vertpos;
layout (location = 1) 
in vec2 vertuv;

uniform vec2 position;
uniform vec2 size;

uniform mat4 view;
uniform mat4 proj;

out vec2 uv;

void main() {
	
	uv = vertuv;

	vec4 pos = vec4(vertpos * size + position, 0.0, 1.0);

	gl_Position = proj * view * pos;
	//gl_Position = vec4(vertpos, 0.0, 1.0);
}