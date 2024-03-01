
#version 450 core  // 420, 330 core , compatibility

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 Color;

void main() { 
	gl_Position = projection * view * model * vPosition;
	Color = vec4(1.0, 0.0, 0.0, 1.0);
}
