#version 330

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

in vec3 vPosition [];
out vtextureCoords;

uniform mat4 projectionView;

void main()
{
	vec3 corners[4];
	corners[0] = vec3(-0.5, -0.5, 0);
	corners[1] = vec3(-0.5,  0.5, 0);
	corners[2] = vec3( 0.5, -0.5, 0);
	corners[3] = vec3( 0.5,  0.5, 0);
	
	gl_position = projectionView * vec4(corners[0] + vPosition[0], 1);
	vtextureCoords = vec2(0, 0)
	EmitVertex();				   
								   
	gl_position = projectionView * vec4(corners[1] + vPosition[0], 1);
	vtextureCoords = vec2(0, 1)
	EmitVertex();				   
								   
	gl_position = projectionView * vec4(corners[2] + vPosition[0], 1);
	vtextureCoords = vec2(1, 0)
	EmitVertex();

	gl_position = projectionView * vec4(corners[3] + vPosition[0], 1);
	vtextureCoords = vec2(1, 1)
	EmitVertex();
}