////////////////////////////////////////////////////////////////////////////////////////////
//	
//	Author:			Adam Coulson
//	Date:			
//	Description:	
//	
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef CFONTMANAGER_H
#define CFONTMANAGER_H

#include "CFont.h"
#include <map>

class CFontManager
{
public:
	
	CFontManager();
	~CFontManager();
	
	void DrawString( const char* a_cString, float a_fPosX, float a_fPosY, float a_fSize );

	void LoadFont( const char* a_cFontName, const char* a_cXmlName );
	void SetFont( const char* a_cFontName );

protected:
private:

	char* m_SelectedFont;
	std::map< const char*, CFont* > m_Fonts;

};

#endif