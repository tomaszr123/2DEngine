#include "CTexture.h"
#include "SOIL.h"

CTexture::CTexture()
{
	
}

CTexture::~CTexture()
{
	for(auto iter = m_textureMap.begin(); iter != m_textureMap.end(); iter++)
	{
		glDeleteTextures(1, &iter->second);
	}

	m_textureMap.clear();
}

unsigned int CTexture::CreateTexture(const char* filename)
{	
	unsigned int texture = -1;

	for(auto iter = m_textureMap.begin(); iter != m_textureMap.end(); ++iter)
	{
		if(iter->first == filename)
		{
			texture = iter->second;
			break;
		}
	}
	if(texture == -1)
	{
		m_textureMap[filename]=  SOIL_load_OGL_texture(filename, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
		texture = m_textureMap[filename];

		glBindTexture(GL_TEXTURE_2D, texture);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_2D, 0);
	}	
	return texture;
}

void CTexture::DestroyTexture(unsigned int textureID)
{
	for(auto iter = m_textureMap.begin(); iter != m_textureMap.end(); iter++)
	{
		if(iter->second == textureID)
		{
			glDeleteTextures(1, &textureID);
			m_textureMap.erase(iter);
			break;
		}
	}
}

unsigned int CTexture::LoadShader(const char *filename, unsigned int type)
{


	return 0;
}