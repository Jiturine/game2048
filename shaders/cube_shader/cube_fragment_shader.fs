#version 330 core
out vec4 color;

uniform vec4 uColor = vec4(0.5, 0.5, 0.5, 1.0);

void main()
{
	color = uColor;
}