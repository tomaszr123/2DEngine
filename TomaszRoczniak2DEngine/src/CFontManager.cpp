#include <GL/glew.h>
#include <GL/wglew.h>
#include <GL/glfw.h>

#include "CFontManager.h"
#include <assert.h>

CFontManager::CFontManager()
{
	m_SelectedFont = "";
}

CFontManager::~CFontManager()
{
	for (auto iter = m_Fonts.begin(); iter != m_Fonts.end(); iter++)
	{
		delete iter->second;
	}

	m_Fonts.clear();
}

void CFontManager::DrawString( const char* a_cString, float a_fPosX, float a_fPosY, float a_fSize )
{
	m_Fonts[m_SelectedFont]->DrawString( a_cString, a_fPosX, a_fPosY, a_fSize );
}

void CFontManager::LoadFont( const char* a_cFontName, const char* a_cXmlName )
{
	CFont* t_Font = new CFont( a_cXmlName );
	m_Fonts[a_cFontName] = t_Font;

	if ( m_SelectedFont == "" )
	{
		SetFont( a_cFontName );
	}
}

void CFontManager::SetFont( const char* a_cFontName )
{
	if ( m_Fonts.find( a_cFontName ) == m_Fonts.end() )
	{
		printf( "Can Not Set Font to an Undefined Font!\n" );
		assert( false );
	}
	else
	{
		m_SelectedFont = (char*)a_cFontName;
	}
}