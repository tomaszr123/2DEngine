#version 330

in vec2 vtextureCoords;

uniform sampler2D diffuse;

int main()
{
	gl_FragColor = texture(diffuse, vtextureCoords);
}