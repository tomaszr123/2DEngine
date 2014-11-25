
#include "CFont.h"



const char* g_vertexShader = 
"\
#version 330 \r\n\
in vec2 position;\
in vec2 texcoords;\
\
out vec2 texturecoords;\
\
void main()\
{\
	texturecoords = texcoords;\
	gl_Position = vec4(position.x, position.y, 0.0f, 1.0f);\
};\
";
const char* g_fragmentShader = 
"\
#version 330 \r\n\
in vec2 texturecoords;\
uniform sampler2D font;\
out vec4 color;\
void main()\
{\
	vec4 fragcolor = vec4(1,1,1,texture2D(font, texturecoords).a);\
	color = fragcolor;\
};\
";

CFont::CFont()
{
	m_bLoaded = false;
	m_iVAlign = 0;
	m_ihAlign = 0;
}

CFont::~CFont()
{
	for(int i = 0; i < m_Fonts.size(); ++i)
	{
		DestroyFont(i);
		delete m_Fonts[i];
		m_Fonts[i] = nullptr;
	}
	m_Fonts.clear();
}

unsigned int CFont::CreateFont(const char* filename, unsigned int size)
{
	sFont_Data* font = new sFont_Data();
	m_Fonts.push_back(font);

	unsigned int idToUse = m_Fonts.size() - 1;
	
	font->m_Filename = (char*)filename;
	font->m_uiTexture = new unsigned int[256];
	font->m_uiSize	= size;
	font->m_IsAlive = true;

	FT_Library	library;
	FT_Face		Face;

	FT_Init_FreeType(&library);
	FT_New_Face(library, filename, 0, &Face);

	FT_Set_Char_Size(Face, font->m_uiSize << 6, font->m_uiSize << 6, 96, 96);

	font->m_uiFontBase = glGenLists(128);
	glGenTextures(128, font->m_uiTexture);

	for(unsigned char i = 0; i<128; ++i)
		buildFont(Face, i, idToUse);

	FT_Done_Face(Face);
	FT_Done_FreeType(library);

	m_iVAlign = AL_TOP;
	m_ihAlign = AL_LEFT;

	m_bLoaded = true;

	return idToUse;
}

void CFont::DrawFont(unsigned int fontID, std::string text, float xPos, float yPos)
{
	// Check for Dead or Out of Range
	if (!m_Fonts[fontID]->m_IsAlive || fontID >= m_Fonts.size()) { return; }

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glListBase(m_Fonts[fontID]->m_uiFontBase);

	yPos += m_Fonts[fontID]->m_uiSize;
	glTranslatef(xPos, yPos, 0);

	glCallLists(text.length(), GL_UNSIGNED_BYTE, text.c_str());

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
}

void CFont::DestroyFont(unsigned int fontID)
{
	if(m_Fonts[fontID]->m_IsAlive)
	{
		glDeleteLists(m_Fonts[fontID]->m_uiFontBase, 128);
		glDeleteTextures(128, m_Fonts[fontID]->m_uiTexture);
		delete [] m_Fonts[fontID]->m_uiTexture;
		m_Fonts[fontID]->m_IsAlive = false;
	}
}

int CFont::nextPower2(int a)
{
	int retVal = 1;
	while (retVal < a)
	{
		retVal <<=1;
	}
	return retVal;
}

void CFont::buildFont(FT_Face face, char ch, unsigned int fontID)
{
	FT_Glyph glyph;
	
	FT_Load_Glyph( face, FT_Get_Char_Index( face, ch ), FT_LOAD_DEFAULT );
	FT_Get_Glyph( face->glyph, &glyph );

	FT_Glyph_To_Bitmap( &glyph, FT_RENDER_MODE_NORMAL, 0, 1);
	FT_BitmapGlyph bitmapGlyph = ( FT_BitmapGlyph )glyph;

	FT_Bitmap &Bitmap = bitmapGlyph->bitmap;

	int width = nextPower2( Bitmap.width );
	int height= nextPower2( Bitmap.rows );

	m_iCharWidth[ch] = Bitmap.width;

	m_iCharBaseLineOffset[ch] = -bitmapGlyph->bitmap.rows - bitmapGlyph->root.advance.y; 

	GLubyte *expandedData = new GLubyte[2 * width * height];

	for(int j=0; j<height; j++)
	{
		for(int i=0; i<width; i++)
		{
			expandedData[2 * (i + j * width)] = expandedData[2 * (i + j * width)+1] =
				(i>= Bitmap.width || j>= Bitmap.rows) ? 0 :
				Bitmap.buffer[i + Bitmap.width * j];
		}
	}

	glBindTexture(GL_TEXTURE_2D, m_Fonts[fontID]->m_uiTexture[(int)ch]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
		GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, expandedData);

	delete [] expandedData;
}
int CFont::GetFontHeight(unsigned int fontID)const
{
	return m_Fonts[fontID]->m_uiSize;
}