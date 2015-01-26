#include "CFont.h"
#include "tinyxml2.h"
#include <string>
#include "CTexture.h"

CFont::CFont()
{
	m_lineHeight = 0;
}

CFont::~CFont()
{
	for(int i = 0; i < m_textures.size(); i++)
	{
		delete m_textures[i];
		m_textures[i] = nullptr;
	}
}

unsigned int CFont::LoadFont(char * fileName)
{
	tinyxml2::XMLDocument doc; 

	if(!doc.LoadFile(fileName))
	{
		// it failed to load quites
		return 0;
	}
	
	tinyxml2::XMLElement *root = doc.RootElement();
	tinyxml2::XMLElement *current = root->FirstChildElement();
	while(current != NULL)
	{
		if(strcmp(current->Name(),"info") == 0)
		{
			
		}
		if(strcmp(current->Name(),"common") == 0)
		{
			m_lineHeight = current->IntAttribute("lineHeight");
		}
		if(strcmp(current->Name(),"pages") == 0)
		{
			tinyxml2::XMLElement *currentpage = current->FirstChildElement();
			while(currentpage != NULL)
			{
				std::string m_path = fileName;
				unsigned int pos = m_path.find_last_of("/\\");
				if(pos != std::string::npos)
				{
					m_path = m_path.substr(0, pos+1);
				}
				else
				{
					m_path = "";
				}
				m_path += currentpage->Attribute("file");

				CTexture* texture = new CTexture();
				texture->CreateTexture(m_path.c_str());
				m_textures.push_back(texture);

				currentpage = currentpage->NextSiblingElement();
			}
		}
		if(strcmp(current->Name(),"chars") == 0)
		{
			tinyxml2::XMLElement *currenchar = current->FirstChildElement();
			while(currenchar != NULL)
			{
				s_CharData c;
				c.m_ID			= currenchar->IntAttribute("id");
				c.m_xPos		= currenchar->IntAttribute("x");
				c.m_yPos		= currenchar->IntAttribute("y");
				c.m_width		= currenchar->IntAttribute("width");
				c.m_height		= currenchar->IntAttribute("height");
				c.m_xOffSet		= currenchar->IntAttribute("xoffset");
				c.m_yOffSet		= currenchar->IntAttribute("yoffset");
				c.m_advanced	= currenchar->IntAttribute("xadvance");
				c.m_pageNumber	= currenchar->IntAttribute("page");

				///TO DO: Push the data into the map and store it
				//
				//m_charSet.insert(c.m_ID,c);
				//
				currenchar = currenchar->NextSiblingElement();
			}
		}
		//------------------TO DO:---------------------------------------------
		// Get all the Kerning information and then store into m_kernings map
		//---------------------------------------------------------------------
		if(strcmp(current->Name(),"kernings") == 0)
		{
			tinyxml2::XMLElement *currentker = current->FirstChildElement();
			while (currentker != NULL)
			{


				current = current->NextSiblingElement();
			}
		}
	}
}
