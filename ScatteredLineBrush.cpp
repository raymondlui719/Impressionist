#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ScatteredLineBrush.h"

ScatteredLineBrush::ScatteredLineBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name), length(10), width(1), angle(0), xproj(0), yproj(0) {}

void ScatteredLineBrush::BrushBegin(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	length = pDoc->getSize();
	width = pDoc->getWidth();
	angle = pDoc->getAngle();

	glLineWidth((float)width);

	xproj = (double)length * cos(((double)angle) * PI / 180);
	yproj = (double)length * sin(((double)angle) * PI / 180);
	BrushMove(source, target);
}

void ScatteredLineBrush::BrushMove(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();	
	if (pDoc == NULL) {
		printf("ScatteredLineBrush::BrushMove  document is NULL\n");
		return;
	}
	ImpressionistUI* dlg = pDoc->m_pUI;

	int strokeDirection = dlg->getStrokeDirection();
	switch (strokeDirection) {
	case SLIDER_OR_RIGHTMOUSE:
		break;
	case GRADIENT: {
		GLint gradientX = pDoc->getGradientX(source.x, source.y);
		GLint gradientY = pDoc->getGradientY(source.x, source.y);
		angle = (int)(atan2(gradientX, gradientY) / PI * 180);
		xproj = (double)length * cos(((double)angle) * PI / 180);
		yproj = (double)length * sin(((double)angle) * PI / 180);
		break;
	}
	case BRUSH_DIRECTION: {
		int dx = target.x - prev.x;
		int dy = target.y - prev.y;
		angle = (int)(atan2(dy, dx) / PI * 180);
		xproj = (double)length * cos(((double)angle) * PI / 180);
		yproj = (double)length * sin(((double)angle) * PI / 180);
		// same as LineBrush
		prev.x = target.x;
		prev.y = target.y;
		break;
	}
	}

	int x1 = (int)((double)target.x) - xproj / 2.0;
	int y1 = (int)((double)target.y) - yproj / 2.0;
	int x2 = (int)((double)target.x) + xproj / 2.0;
	int y2 = (int)((double)target.y) + yproj / 2.0;

	for (int i = 0; i < 4; i++) {
		glBegin(GL_LINES);
			int xoff, yoff;
			xoff = rand() % length - length / 2;
			yoff = rand() % length - length / 2;
			SetColor(Point(source.x + xoff, source.y + yoff));
			glVertex2d(x1 + xoff, y1 + yoff);
			glVertex2d(x2 + xoff, y2 + yoff);
		glEnd();
	}

}

void ScatteredLineBrush::BrushEnd(const Point source, const Point target) {
	// do nothing so far
}