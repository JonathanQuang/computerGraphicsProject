#pragma once


#include "pch.h"
#include <iostream>
#include "Vector.h"
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

class Point {
public:
	int id;
	double x;
	double y;
	double z;

	Point() {
		x = 0;
		y = 0;
		z = 0;
	}

	Point(double theX, double theY, double theZ) {
		x = theX;
		y = theY;
		z = theZ;
	}

	Point(double theX, double theY, double theZ, int identity) {
		x = theX;
		y = theY;
		z = theZ;
		int id = identity;
	}

	/*
	Point addVectorToPoint(Vector v) {
		return Point(x + v.x, y + v.y, z + v.z);
	}
	*/

	void addVectorToPoint(Vector v) {
		x += v.x;
		y += v.y;
		z += v.z;
	}
	/*
	Point subtractVectorFromPoint(Vector v) {
		return Point(x - v.x, y - v.y, z - v.z);
	}
	*/

	void subtractVectorFromPoint(Vector v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
	}

	Vector subtractPointFromPoint(Point p) {
		return Vector(x - p.x, y - p.y, z - p.z);
	}

	void drawPoint() {
		cout << x << "," << y << "," << z << endl;
	}

	void drawPoint(vector<sf::CircleShape> *shapeVector) {
		sf::CircleShape shape(10.f);
		shape.setFillColor(sf::Color::Green);
		shape.setPosition((float) x, (float) y);
		shapeVector->push_back(shape);
		//std::cout << "BLOOOOOP" << shapeVector.size() << std::endl;
	}

	sf::CircleShape genCircleShape() {
		sf::CircleShape shape(5.f);
		shape.setFillColor(sf::Color::Green);
		shape.setPosition((float)x, (float)y);
		return shape;
	}

	void setPointToPoint(Point v) {
		x = v.x;
		y = v.y;
		z = v.z;
	}

};