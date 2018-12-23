#pragma once

#include "pch.h"
#include <iostream>
#include "Vector.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "Point.h"

class Line {
public:
	Point p1;
	Point p2;

	Line(Point pF, Point pL) {
		p1 = pF;
		p2 = pL;
	}
};