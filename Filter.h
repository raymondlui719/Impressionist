#ifndef FILTER_H
#define FILTER_H

#include "ImpressionistDoc.h"
#include <math.h>
#include "FL/gl.h"

extern GLint SobelX[9];
extern GLint SobelY[9];
extern GLdouble Gaussian[9];

inline GLubyte pixelIntensity(const GLubyte * const pixel) {
	double r, g, b;
	r = pixel[0];
	g = pixel[1];
	b = pixel[2];
	double result = 0.299 * r + 0.587 * g + 0.144 * b;
	if (result < 255)
		return (GLubyte) result;
	else
		return 255;
}

template<typename sT, typename fT>
inline GLdouble filterConvolution(const sT* source, int sW, int sH, const fT* filter, int fW, int fH, int x, int y) {
	GLdouble result = 0;
	for (int j = 0; j < fH; j++) {
		for (int i = 0; i < fW; i++) {
			int gIdxX, gIdxY;
			// Convolution
			// use option 2 in lecture notes when dealing with
			// border pixels: reflect the image about the border
			gIdxX = (x + i - 1 < sW) ? abs(x + i - 1) : 2 * (sW - 1) - (x + i - 1);
			gIdxY = (y + j - 1 < sH) ? abs(y + j - 1) : 2 * (sH - 1) - (y + j - 1);
			result += (GLdouble)(source[gIdxY * sW + gIdxX] * filter[j * fW + i]);
		}
	}
	return result;
}

#endif