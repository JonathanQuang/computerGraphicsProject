#pragma once


#include "pch.h"
#include <iostream>
#include "Vector.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "Point.h"
#include "Line.h"

class Model {
public:
	std::vector<Point> pointList;
	std::vector<double> scaleVec;
	std::vector<double> rotateVec;
	std::vector<double> translateVec;
	std::vector<std::vector<int>> lineList;
	std::vector<Point> renderPointList;
	int idCounter;

	Model() {
		for (int i = 0; i < 3; i++) {
			scaleVec.push_back(1);
			rotateVec.push_back(0);
			translateVec.push_back(0);
		}
	}

	void addPointToModel(Point thePoint) {
		pointList.push_back(Point (thePoint.x, thePoint.y, thePoint.z, idCounter));
		idCounter++;
	}

	void addLine(int pointId1, int pointId2) {
		lineList.push_back(std::vector<int> {pointId1, pointId2});
	}

	void addRenderPointToModel(Point thePoint) {
		renderPointList.push_back(thePoint);
	}

	
	void drawModel(std::vector <Line>  *lineRenderList) {
		/*std::cout << "DURRRRRRRRRRRRRRRRRRRRRRR" << std::endl;
		std::cout << lineList[0][0] << std::endl;*/
		for (int i = 0; i < lineList.size(); i++) {
			int id1 = lineList[i][0];
			int id2 = lineList[i][1];
			//std::cout << renderPointList.size() << std::endl;
			Point p1 = renderPointList[id1];
			Point p2 = renderPointList[id2];

			lineRenderList->push_back(Line(p1, p2));
			/*std::cout << lineRenderList->size() << "----------sizez" << std::endl;*/
		}
	}
	
};