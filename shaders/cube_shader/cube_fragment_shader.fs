#version 330 core
uniform vec4 uColor = vec4(0.5, 0.5, 0.5, 1.0);
uniform sampler2D uTexture;
out vec4 fragColor;
in vec2 TexCoord;

void main()
{
	fragColor = texture(uTexture, TexCoord) * uColor;
}