#version 450 core

layout (points) in;
layout (points, max_vertices = 1) out;

float halfSize = 0.5f;

void buildQuad(vec4 position)
{
    gl_Position = position + vec4(-halfSize, 0.0, halfSize, 0.0); // Bottom left
    EmitVertex();
    gl_Position = position + vec4(halfSize, 0.0, halfSize, 0.0); // Bottom right
    EmitVertex();
    gl_Position = position + vec4(-halfSize, 0.0, -halfSize, 0.0); // Top left
    EmitVertex();
    //gl_Position = position + vec4(halfSize, 0.0, -halfSize, 0.0); // Top right
    //EmitVertex();
    EndPrimitive();
}

void main()
{
    //buildQuad(gl_in[0].gl_Position);
    gl_Position = gl_in[0].gl_Position;
    EmitVertex();
    EndPrimitive();
}