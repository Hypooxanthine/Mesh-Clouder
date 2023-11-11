#version 450 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 texCoords;

uniform mat4 u_MVP;
uniform mat4 u_MV;

out vec4 v_vertexColor;
out vec3 v_normal;

void main()
{
	v_vertexColor = vec4(1.0, 1.0, 1.0, 1.0);
	v_normal = mat3(transpose(inverse(u_MV))) * normal;
	gl_Position = u_MVP * vec4(position, 1.0);
}