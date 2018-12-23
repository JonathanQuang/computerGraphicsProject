#pragma once

#include "pch.h"
#include <iostream>
#include "Vector.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "Point.h"

class Camera {
public:
	Vector position;
	Vector aimPos;
	Vector upVector;

	double fovX = 1.92;
	double fovY = 1.92;
	double zFar = 100;
	double zNear = 10;

	Camera() {
		position = Vector(0.0, 0.0, 20.0);
		//Camera points to origin by default
		aimPos = Vector(0.0, 0.0, -20.0);
		upVector = Vector(1.0, 0.0, 0.0);
	}

	void changePosition(double dx, double dy, double dz) {
		position.x += dx;
		position.y += dy;
		position.z += dz;
		aimPos.x -= dx;
		aimPos.y -= dy;
		aimPos.z -= dz;
	}

	void changePositionAndAimPos(double dx, double dy, double dz) {
		position.x += dx;
		position.y += dy;
		position.z += dz;
		aimPos.x += dx;
		aimPos.y += dy;
		aimPos.z += dz;
	}


	
};