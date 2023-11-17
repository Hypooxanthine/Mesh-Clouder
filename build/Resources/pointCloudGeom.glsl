#version 450 core

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

uniform mat4 u_VP;
uniform vec3 u_CameraRight;
uniform vec3 u_CameraUp;
uniform float u_PointSize;

void main()
{
    // Bottom left
    gl_Position = gl_in[0].gl_Position
                    + u_VP * (-0.5 * u_PointSize) * vec4(u_CameraUp, 0.0)
                    + u_VP * (-0.5 * u_PointSize) * vec4(u_CameraRight, 0.0);
    EmitVertex();

    // Bottom right
    gl_Position = gl_in[0].gl_Position
                    + u_VP * (-0.5 * u_PointSize) * vec4(u_CameraUp, 0.0)
                    + u_VP * ( 0.5 * u_PointSize) * vec4(u_CameraRight, 0.0);
    EmitVertex();

    // Top left
    gl_Position = gl_in[0].gl_Position
                    + u_VP * ( 0.5 * u_PointSize) * vec4(u_CameraUp, 0.0)
                    + u_VP * (-0.5 * u_PointSize) * vec4(u_CameraRight, 0.0);
    EmitVertex();

    // Top right
    gl_Position = gl_in[0].gl_Position
                    + u_VP * ( 0.5 * u_PointSize) * vec4(u_CameraUp, 0.0)
                    + u_VP * ( 0.5 * u_PointSize) * vec4(u_CameraRight, 0.0);
    EmitVertex();

    EndPrimitive();
}
