#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 position;
out vec3 normal;

uniform mat4 model;
uniform mat4 mvp;

void main() {
	position = vec3(model * vec4(aPos, 1.f));
	normal = mat3(transpose(inverse(model))) * aNormal;
	gl_Position = mvp * vec4(aPos, 1.f);
}
