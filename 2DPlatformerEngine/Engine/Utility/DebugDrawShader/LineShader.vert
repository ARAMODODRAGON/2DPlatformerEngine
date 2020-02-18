#version 450 core
layout (location = 0) in vec2 vertpos;

uniform vec2 scalar;
uniform vec2 offset;

uniform mat4 view;
uniform mat4 proj;

void main() {
	
	vec4 pos = vec4(vertpos.x * scalar.x + offset.x, vertpos.y * scalar.y + offset.y, 0.0, 1.0);

	gl_Position = view * proj * pos;
	//gl_Position = vec4(vertpos, 0.0, 1.0);
}