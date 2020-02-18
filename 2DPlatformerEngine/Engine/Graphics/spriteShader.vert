#version 450 core
layout (location = 0) 
in vec2 vertpos;
layout (location = 1) 
in vec2 vertuv;

out vec2 uv;

uniform vec2 position;
uniform vec2 scale;
uniform float depth;
uniform vec2 uvOffset;
uniform vec2 uvScalar;
uniform vec2 imagesize;
uniform mat4 view;
uniform mat4 proj;


void main() {
	
	uv = vec2(vertuv.x * uvScalar.x + uvOffset.x, vertuv.y * uvScalar.y + uvOffset.y);

	vec4 pos = vec4(vertpos.x * imagesize.x * scale.x + position.x, vertpos.y * imagesize.y * scale.y + position.y, depth, 1.0);

	gl_Position = proj * view * pos;

}