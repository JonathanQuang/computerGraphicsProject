#pragma once

#include "pch.h"
#include <iostream>
#include "Vector.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "Point.h"
#include "Camera.h"
#include <cmath>
#include "Model.h"


class TransformMath {
public:
	Vector pointToWorld(Point thePoint, std::vector<double> scaleVec, std::vector<double> rotateVec, std::vector<double> translateVec) {
		//std::cout << "point: " << thePoint.x << "," << thePoint.y << "," << thePoint.z << std::endl;
		Vector tmp(thePoint.x, thePoint.y, thePoint.z);
		tmp.scaleVector(scaleVec[0], scaleVec[1], scaleVec[2]);
		tmp.rotateYZ(rotateVec[0]);
		tmp.rotateXZ(rotateVec[1]);
		tmp.rotateXY(rotateVec[2]);
		Vector transVec(translateVec[0], translateVec[1], translateVec[2]);
		//tmp.addVectorToVector(transVec).printMe();
		return tmp.addVectorToVector(transVec);
	}

	Vector worldToCamera(Vector worldSpaceVector, Camera theCamera) {

		//std::cout << "World to Camera" << worldSpaceVector.x << "," << worldSpaceVector.y << "," << worldSpaceVector.z << std::endl;

		Vector cameraRight = crossProduct(theCamera.aimPos, theCamera.upVector);
		Vector trueUpVector = crossProduct(cameraRight, theCamera.aimPos);
		//These three form an orthonormal matrix
		//We use the negative aimNormal because convention ???
		//f << "camera aim data";
		//theCamera.aimPos.printMe();
		Vector aimNormal = normalizeVector(theCamera.aimPos).negativeVersion();
		Vector cameraRightNormal = normalizeVector(cameraRight);
		Vector trueUpVectorNormal = normalizeVector(trueUpVector);

		Vector worldSpaceVectorTranslated = worldSpaceVector.subtractVectorFromVector(theCamera.position);
		double x = dotProduct(cameraRightNormal, worldSpaceVectorTranslated);
		double y = dotProduct(trueUpVectorNormal, worldSpaceVectorTranslated);
		double z = dotProduct(aimNormal, worldSpaceVectorTranslated);

		//return Vector(x, y, z);
		return Vector(-y, x, z);
	}

	Vector cameraToProjection(Vector cameraSpaceVector, Camera theCamera) {
		//arctan(fovX/2)	0						0										0
		//0					artcan(fovY/2)			0										0
		//0					0						-(zFar+zNear)/(zFar-zNear)				-2(zNear*zFar)/(zFar-zNear)
		//0					0						-1										0


		double dilateX = atan(theCamera.fovX / 2);
		//std::cout << dilateX << "----" << std::endl;
		double dilateY = atan(theCamera.fovY / 2);
		double dilateZ = -(theCamera.zFar + theCamera.zNear) / (theCamera.zFar - theCamera.zNear);
		//Vector dilatedVector = cameraSpaceVector.scaleVector(dilateX, dilateY, dilateZ);
		Vector dilatedVector(cameraSpaceVector.x * dilateX, cameraSpaceVector.y * dilateY, cameraSpaceVector.z * dilateZ);
		//				+= -2
		dilatedVector.z += 2 * ((theCamera.zNear*theCamera.zFar) / (theCamera.zFar - theCamera.zNear));
		return dilatedVector.negativeVersion();
	}

	//Vector allTheTransforms(Point thePoint, Model m, Camera cam) {
	//	//model to world
	//	Vector tmp(thePoint.x, thePoint.y, thePoint.z);
	//	tmp.scaleVector(m.scaleVec[0], m.scaleVec[1], m.scaleVec[2]);
	//	tmp.rotateYZ(m.rotateVec[0]);
	//	tmp.rotateXZ(m.rotateVec[1]);
	//	tmp.rotateXY(m.rotateVec[2]);
	//	tmp = tmp.addVectorToVector(Vector(m.translateVec[0], m.translateVec[1], m.translateVec[2]));

	//	//world to camera
	//	//translate everything so that the camera is at the world oriign
	//	Vector camVec = tmp.addVectorToVector(cam.position.negativeVersion());
	//	
	//		//attempt to generate orthonormal basis for the camera
	//	Vector cameraVec = (cam.aimPos.subtractVectorFromVector(cam.position));
	//	Vector aimVec = normalizeVector(cameraVec);
	//	Vector cameraRight = normalizeVector(crossProduct(cameraVec, cam.upVector));
	//	Vector cameraUp = normalizeVector(crossProduct(cameraRight, cameraVec));

	//	double x = dotProduct(aimVec, camVec);
	//	double y = dotProduct(cameraRight, camVec);
	//	double z = dotProduct(cameraUp, camVec);

	//	Vector cameraSpaceVector(x, y, z);

	//	double dilateX = atan(cam.fovX / 2);
	//	//std::cout << dilateX << "----" << std::endl;
	//	double dilateY = atan(cam.fovY / 2);
	//	double dilateZ = -(cam.zFar + cam.zNear) / (cam.zFar - cam.zNear);
	//	//Vector dilatedVector = cameraSpaceVector.scaleVector(dilateX, dilateY, dilateZ);
	//	Vector dilatedVector(cameraSpaceVector.x * dilateX, cameraSpaceVector.y * dilateY, cameraSpaceVector.z * dilateZ);
	//	dilatedVector.z += -2 * ((cam.zNear*cam.zFar) / (cam.zFar - cam.zNear));
	//	
	//	double wScale = 1.0 / dilatedVector.z;

	//	Vector retVec = dilatedVector.scaleVector(wScale, wScale, wScale);

	//	return retVec;
	//}


private:
	Vector crossProduct(Vector v1, Vector v2) {
		Vector retVec;
		retVec.x = v1.y * v2.z - v1.z * v2.y;
		retVec.y = v1.x * v2.z - v1.z * v2.x;
		retVec.z = v1.x * v2.y - v1.y * v2.x;
		return retVec;
	}

	double distance(Vector v1) {
		return sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
	}

	Vector normalizeVector(Vector v1) {
		//std::cout << "normalize: " << v1.x << "," << v1.y << "," << v1.z << std::endl;
		double distance = sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
		if (distance <= 0.0) {
			return Vector(0.001, 0.001, 0.001);
			throw 1;
		}
		return Vector(v1.x / distance, v1.y / distance, v1.z / distance);
	}

	double dotProduct(Vector v1, Vector v2) {
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}
	

};
