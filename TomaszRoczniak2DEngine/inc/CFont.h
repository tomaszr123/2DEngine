////////////////////////////////////////////////////////////
//	Creator: Tomasz Roczniak
//	Date: 11-1-2015
//	Description:This class is to Load in the font bitmap so  
//				then we can draw font to the screen.
////////////////////////////////////////////////////////////

#ifndef CFONT_H_
#define CFONT_H_

#ifndef FRAMEWORK2D_EXPORT
#define FRAMEWORK2D __declspec(dllexport)
#else 
#define FRAMEWORK2D __declspec(dllexport)
#endif

#include <vector>;
#include <map>;

class CTexture;


class FRAMEWORK2D CFont
{
public:
	// Constructor and de-Constructor
	CFont();
	~CFont();

	// loads in the font
	unsigned int LoadFont(char* fileName);

	// struct to hold the info for each character 
	struct s_CharData
	{
		// the chars id
		short m_ID;
		// for each chars info as to where is it on the texture
		short m_xPos, m_yPos, m_height, m_width, m_xOffSet, m_yOffSet, m_advanced;
		// this is just an index for the vector of textures
		unsigned char m_pageNumber;
	};

private:

	// the number of pixels representing the height of the individual line
	unsigned char m_lineHeight;

	// a vector to store for each texture 
	std::vector<CTexture*>m_textures;

	// map for the character info loook up
	std::map<short, s_CharData>m_charSet;

	//map to store the kernings for character pairs
	std::map<short, std::map<short , char>>m_kernings;
};

#endif //CFONT_H_