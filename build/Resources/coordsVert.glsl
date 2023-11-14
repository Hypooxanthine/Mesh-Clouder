#version 450 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 texCoords;

uniform mat4 u_MVP;
uniform mat4 u_M;

out vec4 fragPos;

void main()
{
	fragPos = u_M * vec4(position, 1.0);
	gl_Position = u_MVP * vec4(position, 1.0);
}