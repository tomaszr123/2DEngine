#version 330

in vec2 Position;
int vec2 texCoords

out vec2 textureCoords;
out vec2 vPosition;

uniform mat4 projectionView;


int main()
{
	textureCoords	= texCoords;
	vPosition		= Position;
}