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
	
	void DrawString( const char* a_String, float a_fPosX, float a_fPosY, float a_fSize );

protected:
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

};

#endif

////////////////////////////////////////////////////////////////////////////////////////////
//	
//	Author:			Adam Coulson
//	Date:			
//	Description:	
//	
////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CCHARATER_H
#define CCHARATER_H

class CCharacter
{
public:
	
	CCharacter( float a_fAdvance, float a_fMinU, float a_fMinV, float a_fMaxU, float a_fMaxV );
	~CCharacter();

	float GetAdvance( float a_fSize );
	void Draw( float a_fPosX, float a_fPosY, float a_fSizeX, float a_fSizeY, float a_fColour = 1.0f );

protected:
private:

	float m_fAdvancePercent;
	
	int		m_iPosition[8];
	float	m_fUV[8];
	float	m_fColour[16];

};

#endif