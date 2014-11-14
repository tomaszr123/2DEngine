
#include "CSpritebatch.h"



CSpritebatch::CSpritebatch(unsigned int windowwidth, unsigned int windowheight)
{
	m_windowWidth = windowwidth;
	m_windowHeight = windowheight;
	
	InitShader();
}

CSpritebatch::~CSpritebatch()
{

}

void CSpritebatch::DrawTexture(unsigned int textureID, float xPos, float yPos, float width /*= 0*/, float height /*= 0*/, float rotation /*= 0*/, float xOrigin /*= 0.5f*/, float yOrigin /*= 0.5f*/)
{
	glm::mat3 trans = glm::mat3();

	glm::vec2 tl = (glm::vec2(0,0)			-glm::vec2(xOrigin,yOrigin));
	glm::vec2 tr = (glm::vec2(width,0)		-glm::vec2(xOrigin,yOrigin));
	glm::vec2 br = (glm::vec2(width,height) -glm::vec2(xOrigin,yOrigin));
	glm::vec2 bl = (glm::vec2(0,height)		-glm::vec2(xOrigin,yOrigin));

	trans = glm::mat3(	cosf(rotation),	-sinf(rotation), 0,
						sinf(rotation), cosf(rotation),	 0,
						0.0f,			0.0f,			 1.0f) * 
			glm::mat3(	1.0,			0.0f,			 0.0f, 
						0.0f,			1.0f,			 0.0f,
						xPos,			yPos,			 1.0f);

	tl = TransformPoint(tl);
	tr = TransformPoint(tr);
	br = TransformPoint(br);
	bl = TransformPoint(bl);

	glBindTexture(GL_TEXTURE0, textureID);

	DrawShader();
}

void CSpritebatch::InitShader()
{
	unsigned int vertexShader = LoadShader("./Shaders/VertexShader.vert", GL_VERTEX_SHADER);
	unsigned int fragShader = LoadShader("./Shaders/FragShader.vert", GL_FRAGMENT_SHADER);
	

	m_projection = glm::ortho<float>(0.0f, m_windowWidth, m_windowHeight, 0.0f);
}

void CSpritebatch::DrawShader()
{
	glUseProgram(m_uiProgramID);

	if(m_uiProgramID == NULL)
	{
		printf("Error: There is no program created! \n");
		return;
	}

	unsigned int textureMap = glGetUniformLocation(m_uiProgramID, "diffuseMap");
	glUniform1i(textureMap, 0);

	unsigned int projectViewUniform = glGetUniformLocation(m_uiProgramID, "projectionView");
	glUniformMatrix3fv(projectViewUniform, 1, false, glm::value_ptr(m_projection));
}


glm::vec2 CSpritebatch::TransformPoint(const glm::vec2 &vec)const
{
	glm::mat3 trans = glm::mat3();
	return glm::vec2(vec.x * trans[0][0] + vec.y * trans[1][0] + trans[2][0],
					 vec.x * trans[0][1] + vec.y * trans[1][1] + trans[2][1]);
}

// creates a shader program, links the specified shader stages to it, and binds the specified input/output attributes
unsigned int CSpritebatch::CreateProgram(unsigned int a_vertexShader, unsigned int a_geometryShader, unsigned int a_fragmentShader,
								  unsigned int a_inputAttributeCount /* = 0 */, const char** a_inputAttributes /* = nullptr */,
								  unsigned int a_outputAttributeCount /* = 0 */, const char** a_outputAttributes /* = nullptr */)
{
	int success = GL_FALSE;

	// create a shader program and attach the shaders to it
	unsigned int handle = glCreateProgram();
	glAttachShader(handle, a_vertexShader);
	glAttachShader(handle, a_geometryShader);
	glAttachShader(handle, a_fragmentShader);

	// specify vertex input attributes
	for ( unsigned int i = 0 ; i < a_inputAttributeCount ; ++i )
		glBindAttribLocation(handle, i, a_inputAttributes[i]);

	// specify fragment shader outputs
	for ( unsigned int i = 0 ; i < a_outputAttributeCount ; ++i )
		glBindFragDataLocation(handle, i, a_outputAttributes[i]);

	// link the program together and log errors
	glLinkProgram(handle);

	glGetProgramiv(handle, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		int infoLogLength = 0;		
		glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* infoLog = new char[infoLogLength];

		glGetShaderInfoLog(handle, infoLogLength, 0, infoLog);
		printf("Error: Failed to link shader program!\n");
		printf("%s",infoLog);
		printf("\n");
		delete[] infoLog;
		return 0;
	}

	return handle;
}

unsigned int CSpritebatch::LoadShader(const char *filename, unsigned int type)
{
	int success = GL_FALSE;

	unsigned char* source = fileToBuffer(filename);
	unsigned int handle = glCreateShader(type);

	glShaderSource(handle, 1,(const char**)&source, 0);
	glCompileShader(handle);

	glGetShaderiv(handle, GL_COMPILE_STATUS, &success);
	if(success == GL_FALSE)
	{
		int infoLogLength = 0;
		glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* infoLog = new char[infoLogLength];

		glGetShaderInfoLog(handle, infoLogLength, 0, infoLog);
		printf("Error: Failed to compile shader! \n");
		printf("%s", infoLog);
		printf("\n");
		delete[] infoLog;
		return 0;
	}
	return handle;
}

unsigned char* CSpritebatch::fileToBuffer(const char* sPath)
{
	// open the file for text reading
	FILE* pFile;
	fopen_s(&pFile, sPath, "rb");
	if(pFile == nullptr)
	{
		printf("Error: Unable to open file ' %s ' for reading! \n", sPath);
		return nullptr;
	}
	// gets the number of byts in the file
	fseek(pFile, 0, SEEK_END);
	unsigned int uiLength = (unsigned int)ftell(pFile);
	fseek(pFile, 0, SEEK_SET);

	// allocate buffer and read file contents
	unsigned char* acBuffer = new unsigned char[uiLength + 1];
	memset(acBuffer,0,uiLength +1);
	fread(acBuffer, sizeof(unsigned int), uiLength, pFile);

	fclose(pFile);
	return acBuffer;
}