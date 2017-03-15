//
// ImpBrush.cpp
//
// The implementation of virtual brush. All the other brushes inherit from it.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ImpBrush.h"
#include <iostream>

// Static class member initializations
int			ImpBrush::c_nBrushCount	= 0;
ImpBrush**	ImpBrush::c_pBrushes	= NULL;

ImpBrush::ImpBrush(ImpressionistDoc*	pDoc, 
				   char*				name) :
					m_pDoc(pDoc), 
					m_pBrushName(name)
{
}

//---------------------------------------------------
// Return m_pDoc, which connects the UI and brushes
//---------------------------------------------------
ImpressionistDoc* ImpBrush::GetDocument(void)
{
	return m_pDoc;
}

//---------------------------------------------------
// Return the name of the current brush
//---------------------------------------------------
char* ImpBrush::BrushName(void)
{
	return m_pBrushName;
}

//----------------------------------------------------
// Set the color to paint with to the color at source,
// which is the coord at the original window to sample 
// the color from
//----------------------------------------------------
void ImpBrush::SetColor (const Point source, int alpha)
{
	ImpressionistDoc* pDoc = GetDocument();


	GLubyte color[4];

	memcpy ( color, pDoc->GetOriginalPixel( source ), 3 );
 
	color[3] = alpha;

	//for (int i = 0; i < 4; i++)
		//std::cout << (int) color[i] << " ";
	//std::cout << std::endl;

	glColor4ub(color[0], color[1], color[2], color[3]);

}

void ImpBrush::SetColor(const Point source)
{
	ImpressionistDoc* pDoc = GetDocument();
	int alpha = (int) (pDoc->getAlpha() * 255.0);
	SetColor(source, alpha);
}