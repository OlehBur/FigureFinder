
// Curs1.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include <math.h>
#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;
// CCurs1App:
// See Curs1.cpp for the implementation of this class
//

class CCurs1App : public CWinApp
{
public:
	CCurs1App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

#define EPS 1E-9
#define det(a,b,c,d)  (a*d-b*c)

class Point {
	short int x{ 0 }, y = { 0 };
public:
	static const int yBord = 42, xBord = 18;
	Point() {};
	Point(short int x, short int y);
	void SetCoords(short int x, short int y);

	short int& GetPointX();
	short int& GetPointY();

	bool operator< (const Point& p) const {
		return x < p.x - EPS || abs(x - p.x) < EPS && y < p.y - EPS;
	}

	bool operator> (const Point& p) const {
		return !(x < p.x - EPS || abs(x - p.x) < EPS && y < p.y - EPS);
	}

	int PosOfPoint(Point beginLine, Point endLine);

	void DrawPoint(CPaintDC& dc);
};

class Line {
	short int r = 0, g = 0, b = 0;
	Point beginPoint, endPoint;
	double A,B,C;
public:
	Line() {};
	Line(Point beginPoint, Point endPoint);
	Line(Point beginPoint, Point endPoint, short int _r, short int _b, short int _g);

	void FixKoef();
	double DistanceToStraight(Point p);
	bool IsMinPoint(double beginP, double endP, double xCord);
	bool KoefInters(double Akoef, double Bkoef, double Ckoef, double Dkoef);
	bool IntersectionOfLines(Line currLine);
	inline bool linesCompare(Line& currLine)
	{
		return (fabs(GetLength() - currLine.GetLength()) < 0.5);
	}

	double& GetA() { return A; }
	double& GetB() { return B; }
	double& GetC() { return C; }

	void SetCoords(Point beginPoint, Point endPoint);
	void SetColor(short int r, short int g, short int b);
	void DrawLine(CPaintDC& dc);

	Point getBeginLine();
	Point getEndLine();
	double GetLength();
	int PosOfPoint(Point point);
};

class Quadrangle {
	short int R = 0, G = 0, B = 0;

	void FixPoint();
	double GetInCircleRadius();
	double GetAngle(int number);
public:
	//Line* lines[4];
	Point vertexes[4];

	Quadrangle(Point currentPoints[]);
	Quadrangle(Point p, Point p1, Point p2, Point p3);
	Quadrangle() {};

	Point GetRhombCenter();

	double GetDistanceOfPoint(Point point, Point point1);
	int GetRhombArea();

	bool isRectangle();
	bool isRhomb();
	bool isSquare();

	void SetQuadrColor(short int R, short int G, short int B);
	void Draw(CPaintDC&dc);
	void DrawCircleWithin(CPaintDC& dc);

	~Quadrangle() {
		//delete[] lines;
	};
};

class Cursova 
{
	
	int buffDistance, buffDistance1;
	int getLengthOfPointsArray;
	Point *allPoints;
	Point regPoinit, vertP, vertP1, vertP2, vertP3;
	//Point** SetsPoints;
	//Quadrangle* figures;
	Quadrangle* rhombs;
	Quadrangle* rectangles;
	Quadrangle* quadrates;
	

		//progressPos = 0;
	short int index = -1, index1, index2;
	short int currentFigure = 0;
	
	//CPaintDC* dcAdr;	
	int GetFactorial(int n);
	double GetDistanceOfPoint(Point point, Point point1);

public:
	int countPoints = 0,
		countOfSets = 0,
		//countFigures = 0
		countOfRhombs = 0,
		countOfRectangles = 0,
		countOfQuadrates = 0,
		maxCountOfRhombs = 0,
		maxCountOfRectangles = 0,
		maxCountOfQuadrates = 0;
	short int indexFigureProc = 0;
	short int progressBarPos = 0;
	//int GetProgress();
	bool QuadrIsCross(Quadrangle quadrangle, Quadrangle quadrangle1);
	//void UnlockElements(CButton* elementId);
	int InitFromFile();
	 void ClearFigeres();
	//void SetDc(CPaintDC& dc);
	void DrawRefresh(CPaintDC& dc, CRect& rect/*, CProgressCtrl* pControl*/);
	void SetsOfPoints();
	void DrawPoints(CPaintDC& dc);
	//void DrawQuadrangles(CPaintDC& dc);

	void DrawRhomb(CPaintDC& dc, bool isMagic = false);
	void DrawSquare(CPaintDC& dc, bool isMagic = false);
	void DrawRectangle(CPaintDC& dc, bool isMagic = false);

	 void FindRhomb();
	 void FindSquare();
	 void FindRectangle();

	 void Mix();
	void PaintCrossQuadr(short int rColor = 255);
	void GetResult();
	void About();

	int getFiguresCount(int figure);

	~Cursova() {
		//потрібно зробити чистку елементів масиву
		delete[] allPoints;
		/*for (int i = 0; i < countOfSets; i++)
			delete quadrangles[i];*/
		//delete[] quadrangles;
		delete[] rhombs;
		delete[] quadrates;
		delete[] rectangles;
		//delete[] figures;
	}
};

extern Cursova Curs1;

extern CCurs1App theApp;
