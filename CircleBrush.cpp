#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "CircleBrush.h"

CircleBrush::CircleBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name) {}

void CircleBrush::BrushBegin(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	BrushMove(source, target);
}

void CircleBrush::BrushMove(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("CircleBrush::BrushMove  document is NULL\n");
		return;
	}
	
	double radius = ((double)pDoc->getSize()) / 2;
	DrawCircle(source, target, radius);
}

void CircleBrush::BrushEnd(const Point source, const Point target) {
	// do nothing so far
}

void CircleBrush::DrawCircle(const Point source, const Point target, double radius) {
	int numTriangleSegment = (int) (10.0 * sqrt(radius));
	glBegin(GL_TRIANGLE_FAN);
		SetColor(source);
		glVertex2d(target.x, target.y);
		for (int i = 0; i <= numTriangleSegment; i++) {
			double x, y;
			x = target.x + (radius * cos(i * 2.0 * PI / numTriangleSegment));
			y = target.y + (radius * sin(i * 2.0 * PI / numTriangleSegment));
			glVertex2d(x, y);
		}
	glEnd();
}