#pragma once

#include "pch.h"
#include <iostream>
#include "Vector.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "Point.h"
#include "TransformMath.h"
#include "Model.h"


class RenderV2
{
public:


	//Render();
	//~Render();

	void drawModel(Model theModel, std::vector<sf::CircleShape> *shapeVector) {
		TransformMath mathObject;
		for (int i = 0; i < theModel.pointList.size(); i++) {
			Vector tmpVector = mathObject.pointToWorld(theModel.pointList[i], theModel.scaleVec, theModel.rotateVec, theModel.translateVec);
			Point tmpPoint(tmpVector.x, tmpVector.y, tmpVector.z);
			tmpPoint.drawPoint(shapeVector);
		}
	}

	void drawProjection(Model tM, Camera tC, std::vector<sf::CircleShape> *shapeVector, Model *tMP) {
		TransformMath mathObject;
		tMP->renderPointList.clear();
		for (int i = 0; i < tM.pointList.size(); i++) {
			Vector tmpVector = mathObject.pointToWorld(tM.pointList[i], tM.scaleVec, tM.rotateVec, tM.translateVec);
			Vector tmpVector2 = mathObject.worldToCamera(tmpVector, tC);
			Vector tmpVector3 = mathObject.cameraToProjection(tmpVector2, tC);

			//std::cout << "world";
			//tmpVector.printMe();
			//std::cout << "camera";
			//tmpVector2.printMe();
			//std::cout << "projection";
			//tmpVector3.printMe();

			//divide by our "pseudo W"
			double fakeW = tmpVector3.z;
			fakeW = 1.0 / fakeW;
			tmpVector3.scaleVector(fakeW, fakeW, fakeW);

			bool keepFor = true;
			bool addIt = true;

			//clipping process
			std::vector<double> dummySt{ tmpVector3.x, tmpVector3.y, tmpVector3.z };
			for (int j = 0; keepFor && j < 3; j++) {
				if (abs(dummySt[j]) > 1) {
					keepFor = false;
					addIt = false;
					//std::cout << "failure: ";
					//tmpVector3.printMe();
				}
			}
			addIt = true;
			if (addIt) {
				//std::cout << "pushed";
				//tmpVector3.printMe();
				tmpVector3.x = (tmpVector3.x + 1) / 2 * 1000;
				tmpVector3.y = (tmpVector3.y + 1) / 2 * 1000;
				tmpVector3.z = (tmpVector3.z + 1) / 2 * 1000;
				//std::cout << "finzliaed   " << i << std::endl;
				//tmpVector3.printMe();
				Point tmpPoint(tmpVector3.x, tmpVector3.y, tmpVector3.z, tM.pointList[i].id);
				//tM.renderPointList.push_back(tmpPoint);
				tMP->renderPointList.push_back(tmpPoint);

				tmpPoint.drawPoint(shapeVector);
			}
		}
	}

};