#version 330

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

in vec2 vPosition [];
out vtextureCoords;

uniform mat4 projectionView;

void main()
{
	vec2 corners[4];
	corners[0] = vec3(-0.5, -0.5);
	corners[1] = vec3(-0.5,  0.5);
	corners[2] = vec3( 0.5, -0.5);
	corners[3] = vec3( 0.5,  0.5);
	
	gl_position = projectionView * vec3(corners[0] + vPosition[0], 0);
	vtextureCoords = vec2(0, 0)
	EmitVertex();				   
								   
	gl_position = projectionView * vec3(corners[1] + vPosition[0], 0);
	vtextureCoords = vec2(0, 1)
	EmitVertex();				   
								   
	gl_position = projectionView * vec3(corners[2] + vPosition[0], 0);
	vtextureCoords = vec2(1, 0)
	EmitVertex();

	gl_position = projectionView * vec3(corners[3] + vPosition[0], 0);
	vtextureCoords = vec2(1, 1)
	EmitVertex();
}