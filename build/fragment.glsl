#version 450 core

out vec4 fragColor;

in vec4 v_vertexColor;
smooth in vec3 v_normal;
vec3 lightDirection = normalize(vec3(1.f, 1.f, 1.f));

void main()
{
	float intensity = clamp(dot(lightDirection, normalize(v_normal)), 0.0, 1.0) * 1.1;
	fragColor = v_vertexColor * intensity + vec4(0.2, 0.2, 0.2, 1.0);
}