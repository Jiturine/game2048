#version 330 core
layout(location = 0) in vec4 position;

uniform mat4 mvp = mat4(1.0);

void main()
{
	gl_Position = mvp * position;
}