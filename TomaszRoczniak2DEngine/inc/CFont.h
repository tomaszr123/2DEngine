////////////////////////////////////////////////////////////////////////////////////////////
//	
//	Author:			Adam Coulson
//	Date:			
//	Description:	
//	
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef CFONT_H
#define CFONT_H

#include <glm.hpp>
#include <ext.hpp>

class CCharacter;

class CFont
{
public:
	
	CFont( const char* a_cXmlName );
	~CFont();
<<<<<<< HEAD
<<<<<<< HEAD
	// this creates the font loading in the file name and then init the size you want to create it at
	unsigned int CreateFont(const char* filename, unsigned int size);
	// Draws the font with the ID of the font and a string of what the font will say 
	/// and the position it will be placed at
 	void DrawFont(unsigned int fontID, std::string text, float xPos, float yPos);
	// this will destroy the font ID
	void DestroyFont(unsigned int fontID);

	// this will get the font hight of the font ID
	int GetFontHeight(unsigned int fontID)const;
	// Gets the font width of the char
	int GetFontWidth(char ch)const
	{
		for(char i = 0; i < m_Fonts.size(); ++i)
		{
			if(ch == (char)m_Fonts[i]->m_Filename)
				return i;
		}
	}

	// gets the font char
	unsigned int GetFont(char ch) const {return m_sFont.m_uiTexture[ch];}
	// gets the font base line 
	int GetCharBaseLineOffset(char ch)const{return m_iCharBaseLineOffset[ch];}
=======
=======
>>>>>>> origin/master
	
	void DrawString( const char* a_String, float a_fPosX, float a_fPosY, float a_fSize );

protected:
<<<<<<< HEAD
>>>>>>> origin/master
=======
>>>>>>> origin/master
private:
	
	void			Begin();
	void			End();

	char			m_Path[128];
	char			m_XmlName[128];
	char			m_TextureName[128];
	unsigned int	m_FontTexture;
	
	CCharacter*		m_Characters[256];

	int				m_Start;
	int				m_End;
	int				m_LineSpacing;
	int				m_Assent;
	int				m_Size;
<<<<<<< HEAD

};

#endif

<<<<<<< HEAD
	// a structer for the font data and the texture for each texture
	struct sFont_Data
	{
		char* m_Filename;
		unsigned int m_uiSize;
		unsigned int *m_uiTexture;
		unsigned int m_uiFontBase;
		bool m_IsAlive;
	};
=======
=======

};

#endif

>>>>>>> origin/master
////////////////////////////////////////////////////////////////////////////////////////////
//	
//	Author:			Adam Coulson
//	Date:			
//	Description:	
//	
////////////////////////////////////////////////////////////////////////////////////////////
<<<<<<< HEAD
>>>>>>> origin/master
=======
>>>>>>> origin/master

#ifndef CCHARATER_H
#define CCHARATER_H

<<<<<<< HEAD
<<<<<<< HEAD
	// a bool to see if its loaded 
	bool m_bLoaded;
	
	// an array of chars 
	int m_iCharWidth[128];
	
	// an array of chars base line 
	int m_iCharBaseLineOffset[128];
	
	// the allignment for the font 
	int m_iVAlign;
	int m_ihAlign;

	// build the font 
	void buildFont(FT_Face face, char ch, unsigned int fontID);
	
	// 
	int nextPower2(int a);

	// a vector array for the data for each font id
	std::vector<sFont_Data*> m_Fonts;
=======
class CCharacter
{
public:
	
	CCharacter( float a_fAdvance, float a_fMinU, float a_fMinV, float a_fMaxU, float a_fMaxV );
	~CCharacter();

	float GetAdvance( float a_fSize );
	void Draw( float a_fPosX, float a_fPosY, float a_fSizeX, float a_fSizeY, float a_fColour = 1.0f );

protected:
private:

=======
class CCharacter
{
public:
	
	CCharacter( float a_fAdvance, float a_fMinU, float a_fMinV, float a_fMaxU, float a_fMaxV );
	~CCharacter();

	float GetAdvance( float a_fSize );
	void Draw( float a_fPosX, float a_fPosY, float a_fSizeX, float a_fSizeY, float a_fColour = 1.0f );

protected:
private:

>>>>>>> origin/master
	float m_fAdvancePercent;
	
	int		m_iPosition[8];
	float	m_fUV[8];
	float	m_fColour[16];
<<<<<<< HEAD
>>>>>>> origin/master

};

#endif
=======

};

#endif
>>>>>>> origin/master
