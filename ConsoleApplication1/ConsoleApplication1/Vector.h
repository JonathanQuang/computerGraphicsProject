#pragma once

#include "pch.h"
#include <iostream>
#include <math.h>

class Vector {

public:
	double x;
	double y;
	double z;

	Vector() {
		x = 0;
		y = 0;
		z = 0;
	}

	Vector(double theX, double theY, double theZ) {
		x = theX;
		y = theY;
		z = theZ;
	}

	Vector addVectorToVector(Vector v) {
		return Vector(x + v.x, y + v.y, z + v.z);
	}

	Vector subtractVectorFromVector(Vector v) {
		return Vector(x - v.x, y - v.y, z - v.z);
	}

	Vector negativeVersion() {
		return Vector(x*-1, y*-1, z*-1);
	}

	void scaleVector(double scaleX, double scaleY, double scaleZ) {
		x *= scaleX;
		y *= scaleY;
		z *= scaleZ;
	}

	void rotateXY(double radians) {
		double sineVal = std::sin(radians);
		double cosineVal = std::cos(radians);
		double newX = cosineVal * x - sineVal * y;
		y = sineVal * x + cosineVal * y;
		x = newX;
	}

	void rotateXZ(double radians) {
		double sineVal = std::sin(radians);
		double cosineVal = std::cos(radians);
		double newX = cosineVal * x + sineVal * z;
		z = cosineVal * z - sineVal * x;
		x = newX;
	}

	void rotateYZ(double radians) {
		double sineVal = std::sin(radians);
		double cosineVal = std::cos(radians);
		double newY = cosineVal * y - sineVal * z;
		z = sineVal * y + cosineVal * z;
		y = newY;
	}

	void printMe() {
		std::cout << x << "," << y << "," << z << std::endl;
	}
};