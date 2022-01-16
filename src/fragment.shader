#version 330 core
uniform vec3 khush;
out vec4 FragColor;

void main()
{
	FragColor = vec4(khush, 1.0);
}
