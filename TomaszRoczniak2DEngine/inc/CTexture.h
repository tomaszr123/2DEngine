////////////////////////////////////////////////////////////
//	Creator: Tomasz Roczniak
//	Date: 5-11-2014
//	Description:This class is so you can create a texture
//				and destroy a texture that you create
////////////////////////////////////////////////////////////


#ifndef CTEXTURE_H_
#define CTEXTURE_H_

#ifndef FRAMEWORK2D_EXPORT
#define FRAMEWORK2D __declspec(dllexport)
#else 
#define FRAMEWORK2D __declspec(dllexport)
#endif

#include <hash_map>
#include <iostream>
#include <gl\glew.h>
#include <gl\glfw.h>

class FRAMEWORK2D CTexture
{
public:
	CTexture();
	~CTexture();

	// create the texture and inserts it into the hashmap
	unsigned int CreateTexture(const char* filename);

	// this is to load in a image of the font
	//static unsigned int LoadTexture(const char *filename, unsigned int* width, unsigned int* height);
	
	// destoys the texture and removes it out of the hash map
	void DestroyTexture(unsigned int textureID);

private:
	// Hash_map for all the Textures that will be created and stored
	std::hash_map<const char* , unsigned int >m_textureMap;
};
#endif