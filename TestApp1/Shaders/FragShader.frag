#version 330

in vec2 textureCoords

uniform sampler2D diffuseMap

void main()
{
	vec4 color = texture2D(diffuseMap, textureCoords);
	gl_FragColor = color;
}