#version 330 core
layout(location = 0) in vec4 aPosition;
layout(location = 1) in vec2 aTexCoord;
out vec2 TexCoord;

uniform mat4 mvp = mat4(1.0);

void main()
{
	gl_Position = mvp * aPosition;
	TexCoord = aTexCoord;
}