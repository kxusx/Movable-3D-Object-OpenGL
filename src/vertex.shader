#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;

out vec3 ourCol;
uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 rotate;

void main()
{
	gl_Position = projection * view * transform *rotate * vec4(aPos, 1.0);
	ourCol = aCol;
}
