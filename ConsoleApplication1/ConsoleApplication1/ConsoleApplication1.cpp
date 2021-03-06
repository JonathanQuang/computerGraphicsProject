#pragma once

// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Point.h"
#include <vector>
#include <type_traits>
#include "Model.h"
#include "RenderV2.h"
#include <windows.h>
#include "Line.h"




int main()
{
	Point test(1.0, 2.0, 3.0);
	Vector vec(1.0, 2.0, 3.0);
	test.drawPoint();

	Point point1(1, 2, 1);
	Point point2(0, 4, 4);
	Vector vector1(2, 0, 0);
	Vector vector2;

	point1.drawPoint(); //should display (1,2,1)
	point2.drawPoint(); //should display (0,4,4)

	vector2 = point1.subtractPointFromPoint(point2); //(1,-2,-3)

	vector1 = vector1.addVectorToVector(vector2); //(3,2,3)

	point1.addVectorToPoint(vector1);
	point1.drawPoint(); //should display (4,0,-2)

	point2.subtractVectorFromPoint(vector2);
	point2.drawPoint(); //should display (-1,6,7)

	Point unitPoint(1, 1, 1);
	point1.setPointToPoint(unitPoint);

	std::vector<sf::CircleShape> circleRenderList;
	point1.drawPoint(&circleRenderList);
	//circleRenderList.push_back(point1.genCircleShape());
	std::cout << "wtf" << circleRenderList.size() << std::endl;

	std::vector<Line> lineRenderList;
	
	//std::cout << "hello";
    //std::cout << "Hello World!\n"; 

	//sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	//sf::CircleShape shape(100.f);
	//shape.setFillColor(sf::Color::Green);

	bool rotateBoolean = false;

	sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
	
//	Model triangle;
//	triangle.addPointToModel(Point(10, 10, 0));
//	triangle.addPointToModel(Point(10, 40, 0));
//	triangle.addPointToModel(Point(40, 10, 0));
//	//triangle.translateVec = std::vector<double>{ 500,500,0 };
//	//triangle.scaleVec = std::vector<double>{ 2,4,0 };
//
	Model squareThing;
	squareThing.addPointToModel(Point(0, 10, 0));
	squareThing.addPointToModel(Point(0, -10, 0));
	squareThing.addPointToModel(Point(-10, 0, 0));
	squareThing.addPointToModel(Point(10, 0, 0));
	//squareThing.addPointToModel(Point(10, 10, 5));
	//squareThing.translateVec = std::vector<double>{ 500, 500, 0 };
	squareThing.addPointToModel(Point(0, 0, 10));
	
	squareThing.addLine(0, 1);
	squareThing.addLine(0, 2);
	squareThing.addLine(0, 3);
	squareThing.addLine(1, 2);
	squareThing.addLine(1, 3);
	squareThing.addLine(2, 3);
	
	squareThing.addLine(4, 0);
	squareThing.addLine(4, 1);
	squareThing.addLine(4, 2);
	squareThing.addLine(4, 3);

	RenderV2 mainRender;
	Camera theCam;


	//Model tetra;
	//tetra.addPointToModel(Point(0, 0, 10));
	//tetra.addPointToModel(Point(10, 0, 0));
	//tetra.addPointToModel(Point(0, 10, 0));
	//tetra.addPointToModel(Point(6, 6, 0));
	//tetra.addLine(0, 1);
	//tetra.addLine(0, 2);
	//tetra.addLine(0, 3);
	//tetra.addLine(1, 2);
	//tetra.addLine(1, 3);
	//tetra.addLine(1, 3);
	//tetra.addLine(2, 3);
	//tetra.addLine(2, 1);
	//tetra.addLine(0, 1);
	//tetra.addLine(0, 1);

	Model cubeThing;
	cubeThing.addPointToModel(Point(10, 10, 10)); //0
	cubeThing.addPointToModel(Point(-10, 10, 10)); //1
	cubeThing.addPointToModel(Point(10, -10, 10)); //2
	cubeThing.addPointToModel(Point(-10, -10, 10)); //3
	cubeThing.addPointToModel(Point(10, 10, -10)); //4
	cubeThing.addPointToModel(Point(-10, 10, -10)); //5
	cubeThing.addPointToModel(Point(10, -10, -10)); //6
	cubeThing.addPointToModel(Point(-10, -10, -10)); //7
	cubeThing.addLine(0, 1);
	cubeThing.addLine(0, 2);
	cubeThing.addLine(1, 3);
	cubeThing.addLine(2, 3);
	cubeThing.addLine(4, 5);
	cubeThing.addLine(4, 6);
	cubeThing.addLine(5, 7);
	cubeThing.addLine(6, 7);
	for (int i = 0; i < 4; i++) {
		cubeThing.addLine(i, i + 4);
	}

	Model axis;
	axis.addPointToModel(Point(30, 0, 0));
	axis.addPointToModel(Point(-30, 0, 0 ));
	axis.addPointToModel(Point(0, 30, 0));
	axis.addPointToModel(Point(0, -30, 0));
	axis.addPointToModel(Point(0, 0, 30));
	axis.addPointToModel(Point(0, 0, -30));
	axis.addLine(0, 1);
	axis.addLine(2, 3);
	axis.addLine(4, 5);
	
	
	double counter = 0;
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		
		circleRenderList.clear();

		
		//mainRender.drawProjection(squareThing, theCam, &circleRenderList, &squareThing);
		mainRender.drawProjection(cubeThing, theCam, &circleRenderList, &cubeThing);
		mainRender.drawProjection(axis, theCam, &circleRenderList, &axis);

		
		if (false) {
			theCam.changePosition(0, 0, -0.01);
			squareThing.translateVec[0] += 1;
			squareThing.translateVec[1] += 1;
			//std:cout << theCam.position.z << "----1--1-------" << std::endl;
			squareThing.rotateVec[2] += 0.03;
			if (squareThing.rotateVec[2] > 6.14) {
				squareThing.rotateVec[2] = 0.0;
			}
		}
		else {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
				theCam.changePosition(-20, 0, 20);
				theCam.changePosition(10, 0, -10);
				theCam.position.printMe();
				theCam.aimPos.printMe();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
				theCam.changePosition(20, 0, -20);
				theCam.position.printMe();
				theCam.aimPos.printMe();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
				theCam.changePositionAndAimPos(0.01, 0.01, 0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
				theCam.changePosition(0, 0, -0.01);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
				theCam.changePosition(0, 0, 0.01);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {
				cubeThing.translateVec[0] += 1;
				cubeThing.translateVec[1] += 1;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
				cubeThing.translateVec[0] -= 1;
				cubeThing.translateVec[1] -= 1;
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				cubeThing.rotateVec[0] += 0.03;
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				cubeThing.rotateVec[1] += 0.03;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				cubeThing.rotateVec[2] += 0.03;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				theCam.changePosition(0.001, 0, 0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				theCam.changePosition(-0.001, 0, 0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
				theCam.changePosition(0, 0.001, 0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
				theCam.changePosition(0, -0.001, 0);
			}
		}

		


	

		window.clear();

		lineRenderList.clear();
		//squareThing.drawModel(&lineRenderList);
		cubeThing.drawModel(&lineRenderList);
		axis.drawModel(&lineRenderList);

		for (int i = 0; i < circleRenderList.size(); i++) {
			//window.draw(circleRenderList[i]);
		}
		for (int i = 0; i < lineRenderList.size(); i++) {
			Point p1 = lineRenderList[i].p1;
			Point p2 = lineRenderList[i].p2;
			sf::VertexArray lines(sf::LinesStrip, 2);
			lines[0] = sf::Vector2f((float)p1.x, (float)p1.y);
			lines[1] = sf::Vector2f((float)p2.x, (float)p2.y);
			window.draw(lines);
		}


		window.display();
		Sleep(33);
	}
	
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
