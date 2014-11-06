#version 330

in vec2 textureCoords;

uniform sampler2D diffuseMap;

void main()
{
	gl_FragColor = texture( diffuseMap, textureCoords );
}