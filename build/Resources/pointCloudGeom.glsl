#version 450 core

layout (points) in;
layout (points, max_vertices = 1) out;

void main()
{
    //buildQuad(gl_in[0].gl_Position);
    gl_Position = gl_in[0].gl_Position;
    EmitVertex();
    EndPrimitive();
}