////////////////////////////////////////////////////////////
//	Creator: Tomasz Roczniak
//	Date: 24-11-2014
//	Description:This class is so you can Draw Font to 
//				 the screen.
////////////////////////////////////////////////////////////


#ifndef CFONT_H_
#define CFONT_H_

#ifndef FRAMEWORK2D_EXPORT
#define FRAMEWORK2D __declspec(dllexport)
#else 
#define FRAMEWORK2D __declspec(dllexport)
#endif

#include "include\ft2build.h"

#include "include/freetype.h"
#include "include/ftglyph.h"
#include "include/ftoutln.h"
#include "include/fttrigon.h"


#include <gl/glew.h>
#include <gl\GL.h>
#include <gl\GLU.h>

#include <vector>
#include <string>

#include FT_FREETYPE_H

enum 
{
	AL_LEFT = 0,
	AL_CENTRE,
	AL_RIGHT
};

enum
{
	AL_TOP = 0,
	AL_BOTTOM,
	AL_MIDDLE
};

class FRAMEWORK2D CFont
{
public:
	CFont();
	~CFont();

	unsigned int CreateFont(const char* filename, unsigned int size);
 	void DrawFont(unsigned int fontID, std::string text, float xPos, float yPos);
	void DestroyFont(unsigned int fontID);
	//void MessureFontString();

	int GetFontHeight(unsigned int fontID)const;
	int GetFontWidth(char ch)const
	{
		for(char i = 0; i < m_Fonts.size(); ++i)
		{
			if(ch == (char)m_Fonts[i]->m_Filename)
				return i;
		}
	}

	unsigned int GetFont(char ch) const {return m_sFont.m_uiTexture[ch];}
	int GetCharBaseLineOffset(char ch)const{return m_iCharBaseLineOffset[ch];}
private:

	struct sFont_Data
	{
		char* m_Filename;
		unsigned int m_uiSize;
		unsigned int *m_uiTexture;
		unsigned int m_uiFontBase;
		bool m_IsAlive;
	};

	sFont_Data m_sFont;

	bool m_bLoaded;
	int m_iCharWidth[128];
	int m_iCharBaseLineOffset[128];
	int m_iVAlign;
	int m_ihAlign;

	void buildFont(FT_Face face, char ch, unsigned int fontID);

	int nextPower2(int a);

	std::vector<sFont_Data*> m_Fonts;

};
#endif //_CFONT_H_