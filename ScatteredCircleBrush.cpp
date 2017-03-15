#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ScatteredCircleBrush.h"
#include <time.h>

ScatteredCircleBrush::ScatteredCircleBrush(ImpressionistDoc* pDoc, char* name) :
	CircleBrush(pDoc, name) {}

void ScatteredCircleBrush::BrushBegin(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	size = pDoc->getSize();
	scatteredPoints = 4;
	srand(time(0));
	BrushMove(source, target);
}

void ScatteredCircleBrush::BrushMove(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("ScatteredCircleBrush::BrushMove  document is NULL\n");
		return;
	}

	for (int i = 0; i < scatteredPoints; i++) {
		int pointX, pointY;
		pointX = rand() % size - size / 2;
		pointY = rand() % size - size / 2; // size / 2 for normalization
		Point newPoint(target.x + pointX, target.y + pointY);
		DrawCircle(newPoint, newPoint, (double)(size - (rand() % size) / 2));
	}
}

void ScatteredCircleBrush::BrushEnd(const Point source, const Point target) {
	// do nothing so far
}