#include <GL/glew.h>
#include <GL/wglew.h>
#include <GL/glfw.h>

#include "CFont.h"
#include "CTexture.h"

#include "tinyxml2.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;
using namespace tinyxml2;

////////////////////////////////////////////////////////////////////////////////////////////
//	
//	Author:			Adam Coulson
//	Date:			
//	Description:	
//	
////////////////////////////////////////////////////////////////////////////////////////////

CFont::CFont( const char* a_cXmlName )
{
	sprintf_s( m_Path			, "./font"		);
	sprintf_s( m_XmlName		, a_cXmlName	);
	sprintf_s( m_TextureName	, ""			);
	m_FontTexture = 0;

	for ( int i = 0; i < 256; i++ )
	{
		m_Characters[i]	= 0;
	}

	m_Start			= 0;
	m_End			= 0;
	m_LineSpacing	= 0;
	m_Assent		= 0;
	m_Size			= 0;
	
	float PosU = 0.0f;
	float PosV = 0.0f;

	float SizeU = 1.0f / 16.0f;
	float SizeV = 1.0f / 16.0f;

	char t_File[256];
	sprintf_s(t_File, "%s", m_Path);
	strcat_s( t_File, m_XmlName );
	XMLDocument doc( t_File );

	if (!doc.LoadFile( t_File ))
	{
		XMLElement* root = doc.FirstChildElement();

		if ( root == NULL )
		{
			printf( "Failed to load file: No root element." );
			doc.Clear();
		}
		else
		{
			const char*	t_texture		= root->Attribute("texture");
			const char*	t_start			= root->Attribute("start");
			const char*	t_end			= root->Attribute("end");
			const char*	t_linespacing	= root->Attribute("linespacing");
			const char*	t_assent		= root->Attribute("assent");
			const char*	t_size			= root->Attribute("size");
			
			if (t_texture		!= NULL) { sprintf_s( m_TextureName, "%s", t_texture );							}
			if (t_start			!= NULL) { stringstream str; str << t_start			; str >> m_Start		;	}
			if (t_end			!= NULL) { stringstream str; str << t_end			; str >> m_End			;	}
			if (t_linespacing	!= NULL) { stringstream str; str << t_linespacing	; str >> m_LineSpacing	;	}
			if (t_assent		!= NULL) { stringstream str; str << t_assent		; str >> m_Assent		;	}
			if (t_size			!= NULL) { stringstream str; str << t_size			; str >> m_Size			;	}

			unsigned int Width, Height;	Width=Height=512;

			char t_TexturePath[256];
			sprintf_s(t_TexturePath, "%s", m_Path);
			strcat_s( t_TexturePath, m_TextureName );

			if (m_TextureName != NULL)
			{
				//m_FontTexture = CTexture::LoadTexture(t_TexturePath, &Width, &Height);
			}
			else
			{
				printf( "Unable to Load Font Image - Texture Name Undefined" );
				assert( false );
			}

			// Create Characters With What is in the Array
			int Count = 0;

			XMLElement* element = root->FirstChildElement();

			for(XMLElement* elem = element->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
			{
				string elemName = elem->Value();

				const char* attr;
				if(elemName == "char")
				{
					attr = elem->Attribute("advance");

					if(attr != NULL)
					{
						if ( (Count + m_Start) < m_End )
						{
							int t_Advance;
							stringstream str;

							str << attr;
							str >> t_Advance;

							if ( PosU >= ( 1.0f ) )
							{
								PosU = 0.0f;
								PosV += SizeV;
							}

							float f_Advance = float(t_Advance) / float(m_Size);

							m_Characters[Count + m_Start] = new CCharacter( f_Advance, PosU, PosV, PosU + SizeU, PosV + SizeV );

							PosU += SizeU;
						}
					}

					Count++;
				}
			}
		}
	}
	else
	{
		printf( "Failed To Load arial.xml" );
		assert( false );
	}
}

CFont::~CFont()
{
	for (int i = 0; i < 256; i++)
	{
		if (m_Characters[i] != 0)
		{
			delete m_Characters[i];
		}
	}
}

void CFont::DrawString( const char* a_String, float a_fPosX, float a_fPosY, float a_fSize )
{
	float X = a_fPosX;
	float Y = a_fPosY;

	Begin();

	for(int i = 0; a_String[i] != '\0'; i++)
	{
		int Char = a_String[i];

		if ( Char == '\n' )
		{
			X = a_fPosX;
			Y += a_fSize;
			continue;
		}

		if ( Char == '\t' )
		{
			X += m_Characters[Char]->GetAdvance( a_fSize );
			continue;
		}

		if ( Char < 256 && Char > 0 )
		{
			m_Characters[Char]->Draw( X, Y, a_fSize, a_fSize );
			X += m_Characters[Char]->GetAdvance( a_fSize );
		}
		else
		{
			m_Characters[1]->Draw( X, Y, a_fSize, a_fSize );
			X += m_Characters[1]->GetAdvance( a_fSize );
		}
	}

	End();
}

void CFont::Begin()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindTexture( GL_TEXTURE_2D, m_FontTexture );
}

void CFont::End()
{
	glBindTexture( GL_TEXTURE_2D, 0 );
	
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

////////////////////////////////////////////////////////////////////////////////////////////
//	
//	Author:			Adam Coulson
//	Date:			
//	Description:	
//	
////////////////////////////////////////////////////////////////////////////////////////////

CCharacter::CCharacter( float a_fAdvance, float a_fMinU, float a_fMinV, float a_fMaxU, float a_fMaxV )
{
	// Set Advance
	m_fAdvancePercent = a_fAdvance;

	int iter = 0;
	
	// Set UV
	m_fUV[iter] = a_fMinU; iter++;
	m_fUV[iter] = a_fMinV; iter++;

	m_fUV[iter] = a_fMaxU; iter++;
	m_fUV[iter] = a_fMinV; iter++;

	m_fUV[iter] = a_fMaxU; iter++;
	m_fUV[iter] = a_fMaxV; iter++;

	m_fUV[iter] = a_fMinU; iter++;
	m_fUV[iter] = a_fMaxV; iter++;

	// Set Colour
	for (iter = 0; iter < 16; iter++)
	{
		m_fColour[iter] = 1.0f;
	}
}

CCharacter::~CCharacter()
{
	for(int i = 0; i < 8; ++i)
		m_iPosition[i] = 0;
}

float CCharacter::GetAdvance( float a_fSize )
{
	return m_fAdvancePercent * a_fSize;
}

void CCharacter::Draw( float a_fPosX, float a_fPosY, float a_fSizeX, float a_fSizeY, float a_fColour )
{
	m_iPosition[0] = int( a_fPosX				);
	m_iPosition[1] = int( a_fPosY				);

	m_iPosition[2] = int( a_fPosX + a_fSizeX	);
	m_iPosition[3] = int( a_fPosY				);

	m_iPosition[4] = int( a_fPosX + a_fSizeX	);
	m_iPosition[5] = int( a_fPosY + a_fSizeY	);

	m_iPosition[6] = int( a_fPosX				);
	m_iPosition[7] = int( a_fPosY + a_fSizeY	);

	if ( m_fColour[0] != a_fColour )
	{
		for (int i = 0; i < 16; i++)
		{
			m_fColour[i] = a_fColour;
		}
	}

	glVertexPointer(	2,	 GL_INT,	 0,	 m_iPosition);
	glTexCoordPointer(	2,	 GL_FLOAT,	 0,	 m_fUV);
	glColorPointer(		4,	 GL_FLOAT,	 0,	 m_fColour);
	
	glDrawArrays(GL_POLYGON, 0, 4);
}