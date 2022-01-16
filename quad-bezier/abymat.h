#pragma once
#ifndef ABYMAT_H
#define ABYMAT_H
namespace AbyMat{

	inline double norm(double value, double min, double max);
	inline double abs(double val);
	inline double lerp(double norm, double min, double max);
	inline double pow(double val, double pow);
	class Point2D {
	private:
		double x;
		double y;
	public:
		Point2D(double x, double y) : x(x), y(y) {};
		Point2D(const Point2D& p) { x = p.x; y = p.y; };
		Point2D() { x = 0; y = 0; };
		double getX() { return x; };
		double getY() { return y; };
		void setX(double x) { this->x = x; };
		void setY(double y) { this->y = y; };
	};
	class GR {
	public:
		Point2D quad_bezier(Point2D P0, Point2D P1, Point2D P2, double norm);
		Point2D DDA(int X0, int Y0, int X1, int Y1);
	};
};


inline double AbyMat::norm(double value, double min, double max) {
	return (value - min) / (max - min);
}

inline double AbyMat::abs(double val) {
	return val > 0 ? val : -val;
}

inline double AbyMat::lerp(double norm, double min, double max) {
	return (max - min) * norm + min;
}

inline double AbyMat::pow(double val, double pow) {
	for (int i = 0; i < pow-1; i++)
	{
		val = val * val;
	}
	return val;
}

AbyMat::Point2D AbyMat::GR::quad_bezier(Point2D P0, Point2D P1, Point2D P2, double norm) {
	Point2D B;
	double t = norm;
	double BezierX = (pow((1 - t), 2) * P0.getX()) + (2 * (1 - t) * t * P1.getX() + (pow(t, 2) * P2.getX()));
	double BezierY = (pow((1 - t), 2) * P0.getY()) + (2 * (1 - t) * t * P1.getY() + (pow(t, 2) * P2.getY()));
	B.setX(BezierX);
	B.setY(BezierY);
	return B;
}

AbyMat::Point2D AbyMat::GR::DDA(int X0, int Y0, int X1, int Y1)
{
	Point2D P;
	int dx = X1 - X0;
	int dy = Y1 - Y0;
	int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	float Xinc = dx / (float)steps;
	float Yinc = dy / (float)steps;
	float X = X0;
	float Y = Y0;
	P.setX(X+Xinc);
	P.setY(Y+Yinc);
	return P;
}

#endif