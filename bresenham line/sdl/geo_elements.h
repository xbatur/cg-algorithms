#ifndef GEO_ELEMENTS_H
#define GEO_ELEMENTS_H
#include "SDL.h"
#include <iostream>
class Point2D {
public:
	Point2D() {
		x = 0;
		y = 0;
	}
	Point2D(int x, int y) {
		this->x = x;
		this->y = y;
	}
	void set(int x, int y) {
		this->x = x;
		this->y = y;
	}
	int x, y;
};

class Point3D {
public:
	Point3D() {
		x = 0;
		y = 0;
		z = 0;
	}
	Point3D(int x, int y, int z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	int x, y, z;
};

class Line2D {
public:
	Line2D() {
		x0 = 0;
		y0 = 0;
		x1 = 0;
		y1 = 0;
		absdx = 0;
		absdy = 0;
	}
	Line2D(int x0, int y0, int x1, int y1) {
		this->x0 = x0;
		this->y0 = y0;
		this->x1 = x1;
		this->y1 = y1;
		absdx = x1 - x0;
		if (absdx < 0) absdx = -absdx;
		absdy = y1 - y0;
		if (absdy < 0) absdy = -absdy;
	}

	void DDALine(SDL_Renderer* renderer) {
		double xInc, yInc;
		double x, y;
		if (x0 > x1) {
			x = x1;
			y = y1;
		}
		else {
			x = x0;
			y = y0;
		}
		xInc = ((double)absdx / (double)absdy);
		yInc = 1;
		points = new Point2D[absdy];
		for (int i = 0; i < absdy; i++) {
			x += xInc;
			if (x0 > x1)
				y0 > y1 ? y++ : y--;
			else
				y0 > y1 ? y-- : y++;
			points[i].set((int)x, (int)y);
		}
		for (int i = 0; i < absdy; i++) {
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			SDL_RenderDrawPoint(renderer, points[i].x, points[i].y);
		}
	}

	void drawLine(SDL_Renderer *renderer) {
		if (absdy > absdx) {
			DDALine(renderer);
			return;
		}
		int pk = 2 * absdy - absdx;
		int twoDy = 2 * absdy;
		int twoDyDx = 2 * (absdy - absdx);
		points = new Point2D[absdx];
		int x, y, xEnd;
		int iterator = 0;
		if (x0 > x1) {
			x = x1;
			y = y1;
			xEnd = x0;
		}
		else {
			x = x0;
			y = y0;
			xEnd = x1;
		}
		while (x < xEnd) {
			x++;
			if (pk < 0) {
				pk += twoDy;
			}
			else {
				if(x0>x1)
					y0 > y1 ? y++ : y--;
				else
					y0 > y1 ? y-- : y++;
				pk += twoDyDx;
			}
			points[iterator].set(x, y);
			iterator++;
		}
		for (int i = 0; i < absdx; i++) {
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			SDL_RenderDrawPoint(renderer, points[i].x, points[i].y);
		}

	}
	int x0, y0, x1, y1;
	int absdy, absdx;
	Point2D* points;
};
#endif
