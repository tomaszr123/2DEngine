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
class FRAMEWORK2D CFont
{
public:
	CFont();
	~CFont();

	void CreateFont();
 	void DrawFont();
	void DestroyFont();
	void MessureFontString();

private:


};
#endif //_CFONT_H_