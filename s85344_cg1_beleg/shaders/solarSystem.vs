#version 450 core  // 420, 330 core , compatibility

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 fragPos;
out vec3 normal;
out vec2 texCoord;

void main() { 
	gl_Position = projection * view * model * vec4(aPosition, 1.0f);
	fragPos = vec3(model * vec4(aPosition, 1.0f));
	
	normal = mat3(model) * aNormal;
	texCoord = vec2(aTexCoord.x, aTexCoord.y);
}
