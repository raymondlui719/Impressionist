#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ScatteredPointBrush.h"
#include <time.h>

ScatteredPointBrush::ScatteredPointBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name) {}

void ScatteredPointBrush::BrushBegin(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	glPointSize(1.0f);
	srand(time(0));
	BrushMove(source, target);
}

void ScatteredPointBrush::BrushMove(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("ScatteredPointBrush::BrushMove  document is NULL\n");
		return;
	}

	int size = pDoc->getSize();
	for (int i = 0; i < size * 2; i++) {
		int xoff = rand() % size - size / 2;
		int yoff = rand() % size - size / 2;
		glBegin(GL_POINTS);
			Point newPoint(target.x + xoff, target.y + yoff);
			SetColor(newPoint);
			glVertex2d(newPoint.x, newPoint.y);
		glEnd();
	}

}

void ScatteredPointBrush::BrushEnd(const Point source, const Point target) {
	// do nothing so far
}