
// Curs1.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "Curs1.h"
#include "Curs1Dlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <fstream>


// CCurs1App

BEGIN_MESSAGE_MAP(CCurs1App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CCurs1App construction

CCurs1App::CCurs1App()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CCurs1App object

CCurs1App theApp;


// CCurs1App initialization

BOOL CCurs1App::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Activate "Windows Native" visual manager for enabling themes in MFC controls
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CCurs1Dlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
		TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}

	// Delete the shell manager created above.
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}



//class point
Point::Point(short int x, short int y) {
	this->x = x;
	this->y = y;
};

inline short int& Point::GetPointX() {
	return x;
};

inline short int& Point::GetPointY() {
	return y;
};

inline void Point::SetCoords(short int x, short int y) {
	this->x = x;
	this->y = y;
};

void Point::DrawPoint(CPaintDC& dc) {
	CPen Point(BS_SOLID, 7, RGB(0, 0, 0));
	dc.SelectObject(&Point);
	dc.MoveTo(x, y);
	dc.LineTo(x, y);
	//Sleep(100);
};

int Point::PosOfPoint(Point beginLine, Point endLine) {
	int ySubtr = endLine.GetPointY() - beginLine.GetPointY(),
		xSubtr = beginLine.GetPointX() - endLine.GetPointX(),
		lineSubtr = beginLine.GetPointY() * endLine.GetPointX() - beginLine.GetPointX() * endLine.GetPointY(),
		posIndex = ySubtr * x + xSubtr * y + lineSubtr;

	if (posIndex == 0)
		return 0;
	if (posIndex > 0)
		return 1;
	return -1;
};


//class line
Line::Line(Point beginPoint, Point endPoint) {
	this->beginPoint = beginPoint;
	this->endPoint = endPoint;
	A = endPoint.GetPointY() - beginPoint.GetPointY();
	B = beginPoint.GetPointX() - endPoint.GetPointX();
	C = -A * endPoint.GetPointX() - B * endPoint.GetPointY();
	FixKoef();
};

Line::Line(Point beginPoint, Point endPoint, short int r, short int b, short int g) {
	this->beginPoint = beginPoint;
	this->endPoint = endPoint;

	this->r = r;
	this->g = g;
	this->b = b;

	A = endPoint.GetPointY() - beginPoint.GetPointY();
	B = beginPoint.GetPointX() - endPoint.GetPointX();
	C = -A * endPoint.GetPointX() - B * endPoint.GetPointY();
	FixKoef();
};

void Line::FixKoef(){
	double z = sqrt(A * A + b * b);
	if (abs(z) > EPS)
		A /= z, B /= z, C /= z;
}

double Line::DistanceToStraight(Point p) {
	return A * p.GetPointX() + B * p.GetPointY() + C;
}

bool Line::IsMinPoint(double beginP, double endP, double xCord)
{
	return min(beginP, endP) <= xCord + EPS && xCord <= max(beginP, endP) + EPS;
}

bool Line::KoefInters(double Akoef, double Bkoef, double Ckoef, double Dkoef){
	if (Akoef > Bkoef)  std::swap(Akoef, Bkoef);
	if (Ckoef > Dkoef)  std::swap(Ckoef, Dkoef);
	return max(Akoef, Ckoef) <= min(Bkoef, Dkoef) + EPS;
}

bool Line::IntersectionOfLines(Line currLine)
{
	
	Point cAPoint = getBeginLine(),
		cBPoint = getEndLine(),
		cCPoint = currLine.getBeginLine(),
		cDPoint = currLine.getEndLine();

	Point cLeftPoint, cRightPoint;

	if (!KoefInters(cAPoint.GetPointX(), cBPoint.GetPointX(), cCPoint.GetPointX(), cDPoint.GetPointX()) || !KoefInters(cAPoint.GetPointY(), cBPoint.GetPointY(), cCPoint.GetPointY(), cDPoint.GetPointY()))
		return false;

	Line cFirstProp(cAPoint, cBPoint);
	Line cSecondProp(cCPoint, cDPoint);

	double dbZn = det(cFirstProp.GetA(), cFirstProp.GetB(), cSecondProp.GetA(), cSecondProp.GetB());

	if (abs(dbZn) < EPS)
	{
		if (abs(cFirstProp.DistanceToStraight(cCPoint)) > EPS || abs(cSecondProp.DistanceToStraight(cAPoint)) > EPS)
			return false;

		if (cBPoint < cAPoint)  std::swap(cAPoint, cBPoint);
		if (cDPoint < cCPoint)  std::swap(cCPoint, cDPoint);

		cLeftPoint = max(cAPoint, cCPoint);
		cRightPoint = min(cBPoint, cDPoint);

		return true;
	}
	else
	{
		cLeftPoint.GetPointX() = cRightPoint.GetPointX() = -det(cFirstProp.GetC(), cFirstProp.GetB(), cSecondProp.GetC(), cSecondProp.GetB()) / dbZn;
		cLeftPoint.GetPointY() = cRightPoint.GetPointY() = -det(cFirstProp.GetA(), cFirstProp.GetC(), cSecondProp.GetA(), cSecondProp.GetC()) / dbZn;

		return IsMinPoint(cAPoint.GetPointX(), cBPoint.GetPointX(), cLeftPoint.GetPointX())
			&& IsMinPoint(cAPoint.GetPointY(), cBPoint.GetPointY(), cLeftPoint.GetPointY())
			&& IsMinPoint(cCPoint.GetPointX(), cDPoint.GetPointX(), cLeftPoint.GetPointX())
			&& IsMinPoint(cCPoint.GetPointY(), cDPoint.GetPointY(), cLeftPoint.GetPointY());
	}
}

void Line::SetCoords(Point beginPoint, Point endPoint) {
	this->beginPoint = beginPoint;
	this->endPoint = endPoint;
};

void Line::SetColor(short int r, short int g, short int b) {
	this->r = r;
	this->g = g;
	this->b = b;
};

inline Point Line::getBeginLine() {
	return this->beginPoint;
};

inline Point Line::getEndLine() {
	return this->endPoint;
};

void Line::DrawLine(CPaintDC& dc) {
	CPen Line(BS_SOLID, 3, RGB(r, g, b));
	dc.SelectObject(&Line);

	dc.MoveTo(beginPoint.GetPointX(), beginPoint.GetPointY());
	dc.LineTo(endPoint.GetPointX(), endPoint.GetPointY());
	//Sleep(150);
};

inline double Line::GetLength() {
	int begX = beginPoint.GetPointX(), endX = endPoint.GetPointX(),
		begY = beginPoint.GetPointY(), endY = endPoint.GetPointY();
	return sqrt(pow(((double)(begX) - endX),2) + pow(((double)(begY)- endY),2));
};//static_cast<__int64>

int Line::PosOfPoint(Point point) {
	int ySubtr = endPoint.GetPointY() - beginPoint.GetPointY(),
	xSubtr = beginPoint.GetPointX() - endPoint.GetPointX(),
	lineSubtr = beginPoint.GetPointY() * endPoint.GetPointX() - beginPoint.GetPointX() * endPoint.GetPointY(),
	posIndex = ySubtr * point.GetPointX() + xSubtr * point.GetPointY() + lineSubtr;

	if (posIndex == 0)
		return 0;
	if (posIndex > 0)
		return 1;
	return -1;
};


//class quadrangle
Quadrangle::Quadrangle(Point currentPoints[]) {
	for (int pointIndex = 0; pointIndex < 4; pointIndex++)
		vertexes[pointIndex] = currentPoints[pointIndex];
	FixPoint();
};

Quadrangle::Quadrangle(Point p, Point p1, Point p2, Point p3) {
	vertexes[0] = p; 
	vertexes[1] = p1;
	vertexes[2] = p2;
	vertexes[3] = p3;
	FixPoint();
	
};

void Quadrangle::FixPoint() {
	for (int pointNumber = 0; pointNumber < 2; pointNumber++)
	{
		Line testLine(vertexes[pointNumber], vertexes[pointNumber + 1]);
		for (int pointIndex = 0; pointIndex < 4; pointIndex++)
			if (testLine.PosOfPoint(vertexes[pointNumber + 2]) * testLine.PosOfPoint(vertexes[pointIndex]) < 0)
			{
				Point buff = vertexes[pointNumber + 1];
				vertexes[pointNumber + 1] = vertexes[pointNumber + 2];
				vertexes[pointNumber + 2] = buff;
			}
	}
};

double Quadrangle::GetDistanceOfPoint(Point point, Point point1) {
	int mulXsubtr = (point.GetPointX() - point1.GetPointX())* (point.GetPointX() - point1.GetPointX()),
	mulYsubtr = (point.GetPointY() - point1.GetPointY()) * (point.GetPointY() - point1.GetPointY());

	return	sqrt((double)mulXsubtr+ mulYsubtr); //C26451
};

double Quadrangle::GetAngle(int number) {
	Line l1(vertexes[0], vertexes[1]),
		l2(vertexes[1], vertexes[2]),
		l3(vertexes[2], vertexes[3]),
		l4(vertexes[3], vertexes[0]);
	double aLine = l1.GetLength(),//lines[0]->GetLength(),
		bLine = l2.GetLength(),//lines[1]->GetLength(),
		cLine = GetDistanceOfPoint(l1.getBeginLine(), l3.getEndLine()),//diagonal

		aLine1 = l3.GetLength(),//lines[2]->GetLength(),
		bLine1 = l4.GetLength(),//lines[3]->GetLength(),
		cLine1 = GetDistanceOfPoint(l2.getBeginLine(), l4.getEndLine());//diagonal 2

	switch (number) {
	case 0:
		return cos((aLine * aLine + bLine * bLine - cLine * cLine) / 2 * aLine * bLine); //C angle			    1diag
		break;
	case 1:
		return cos((aLine1 * aLine1 + bLine1 * bLine1 - cLine * cLine) / 2 * aLine1 * bLine1); //D angle
		break;
	case 2: 
		return cos((aLine * aLine + bLine1 * bLine1 - cLine1 * cLine1) / 2 * aLine * bLine1); //B angle			2diag
		break;
	case 3:
		return cos((aLine1 * aLine1 + bLine * bLine - cLine1 * cLine1) / 2 * aLine1 * bLine); //A angle
		break;
	default:
		return -1;
	}
};

bool Quadrangle::isRectangle(){
	//Line diagonal1(vertexes[2], vertexes[0]), diagonal2(vertexes[3], vertexes[1]);
	//return (lines[0]->linesCompare(lines[2]) && lines[1]->linesCompare(lines[3])
	//	&& diagonal1.linesCompare(diagonal2)) ? true : false;

	Line l1(vertexes[1], vertexes[0]), l2(vertexes[1], vertexes[2]), l3(vertexes[2], vertexes[3]), l4(vertexes[3], vertexes[0]), l5(vertexes[2], vertexes[0]),l6(vertexes[3], vertexes[1]);
return (l1.linesCompare(l3) && l2.linesCompare(l4)
	&& l5.linesCompare(l6))? true : false;

};

bool Quadrangle::isRhomb(){
	//return (lines[0]->linesCompare(lines[1]) && lines[1]->linesCompare(lines[2]) && lines[2]->linesCompare(lines[3]) && lines[3]->linesCompare(lines[0])) ? true : false;

	Line l1(vertexes[1], vertexes[0]), l2(vertexes[1], vertexes[2]), l3(vertexes[2], vertexes[3]), l4(vertexes[3], vertexes[0]);
	double currentLength = GetDistanceOfPoint(vertexes[1], vertexes[0]),//lines[0]->GetLength(),
		diagonalLength = GetDistanceOfPoint(vertexes[0], vertexes[2]), diagonalLength1 = GetDistanceOfPoint(vertexes[1], vertexes[3]),
		koefDiagonal = (vertexes[0].GetPointY() - vertexes[2].GetPointY()) / (double)(vertexes[0].GetPointX() - vertexes[2].GetPointX()),
		koefDiagonal1 = (vertexes[1].GetPointY() - vertexes[3].GetPointY()) / (double)(vertexes[1].GetPointX() - vertexes[3].GetPointX());

	return (l1.linesCompare(l2) && l2.linesCompare(l3) && l3.linesCompare(l4) && l4.linesCompare(l1)/*&& koefDiagonal=-1/ koefDiagonal1*/) ? true : false;
};
bool Quadrangle::isSquare(){
	//Line diagonal(vertexes[3], vertexes[1]), diagonal1(vertexes[2], vertexes[0]);
	//if (!lines[1]->linesCompare(*lines[0]) || !lines[1]->linesCompare(*lines[2]) || !lines[3]->linesCompare(*lines[2]) || !diagonal.linesCompare(diagonal1))
	//	return false;
	//return true;

	Line l1(vertexes[1], vertexes[0]), l2(vertexes[1], vertexes[2]), l3(vertexes[2], vertexes[3]), l4(vertexes[3], vertexes[0]), l5(vertexes[3], vertexes[1]), l6(vertexes[2], vertexes[0]);
	double currentLength = GetDistanceOfPoint(vertexes[1], vertexes[0]);
		if (!l1.linesCompare(l2)||!l2.linesCompare(l3)||!l3.linesCompare(l4)||!l4.linesCompare(l1)||!l5.linesCompare(l6))			
			return false;
	return true;
};

void Quadrangle::SetQuadrColor(short int R, short int G, short int B) {
	this->R = R;
	this->B = B;
	this->G = G;
};

void Quadrangle::Draw(CPaintDC& dc) {
	//for (int line = 0; line < 4; line++) {
	//	lines[line]->SetColor(R, G, B);//(4+line%4)*50, (4+line % 3) * 80, (4 + line % 4) * 5);
	//	lines[line]->DrawLine(dc);
	//}
	CPen side(BS_SOLID, 3, RGB(R, G, B));
	dc.SelectObject(&side);

	dc.MoveTo(vertexes[0].GetPointX(), vertexes[0].GetPointY());
	dc.LineTo(vertexes[1].GetPointX(), vertexes[1].GetPointY());
	dc.LineTo(vertexes[2].GetPointX(), vertexes[2].GetPointY());
	dc.LineTo(vertexes[3].GetPointX(), vertexes[3].GetPointY());
	dc.LineTo(vertexes[0].GetPointX(), vertexes[0].GetPointY());
};

int Quadrangle::GetRhombArea() {
	short int diagonal = GetDistanceOfPoint(vertexes[0], vertexes[2]),
		diagonal1 = GetDistanceOfPoint(vertexes[1], vertexes[3]);
		return (diagonal * diagonal1) >> 1;
};

double Quadrangle::GetInCircleRadius() {
	//return GetRhombArea() / (2 * lines[0]->GetLength());   //r=S/2a
	return GetRhombArea() / (2 * GetDistanceOfPoint(vertexes[0], vertexes[1]));   //r=S/2a
};

Point Quadrangle::GetRhombCenter() { //x=(x1+x2)/2
	short int x1= vertexes[0].GetPointX(), x2= vertexes[2].GetPointX(),
		y1= vertexes[0].GetPointY(), y2 = vertexes[2].GetPointY();

		return { ((x1 + x2) >> 1), ((y1 + y2) >> 1)};
};

void Quadrangle::DrawCircleWithin(CPaintDC& dc) {
	short int x = GetRhombCenter().GetPointX(),
		y = GetRhombCenter().GetPointY(),
		r = GetInCircleRadius();
	CPen circle(BS_SOLID, 3, RGB(R, G, B));
	dc.SelectObject(&circle);

	dc.Ellipse(x-r,y-r, x+r, y+r);
};


//class cursova
int Cursova::GetFactorial(int currentNumber) {
	return (currentNumber == 0) ? 1 : currentNumber * GetFactorial(currentNumber - 1);
};

bool Cursova::QuadrIsCross(Quadrangle quadrangle, Quadrangle quadrangle1) {
	Line l1[] = { {quadrangle.vertexes[0], quadrangle.vertexes[1]}, {quadrangle.vertexes[2], quadrangle.vertexes[1]},
		{quadrangle.vertexes[2], quadrangle.vertexes[3] }, { quadrangle.vertexes[0], quadrangle.vertexes[3] }};
	Line l2[] = { {quadrangle1.vertexes[0], quadrangle1.vertexes[1]}, {quadrangle1.vertexes[2], quadrangle1.vertexes[1]},
		{quadrangle1.vertexes[2], quadrangle1.vertexes[3] }, { quadrangle1.vertexes[0], quadrangle1.vertexes[3] }};
	for (int i = 0; i < 4; i++)
	for (int j = 0; j < 4; j++)
		if(l1[i].IntersectionOfLines(l2[j]))
		return true;
	return false;
};

int Cursova::InitFromFile(){
	
	Point currPoint;
	int pointX = 0, pointY = 0;
	countPoints = 0;
	char sym;

	ifstream fileOfPoints("Points.txt"); //для читання
	if (fileOfPoints.is_open()) {//чи відкритий потік
		while (fileOfPoints >> sym)//зчитуєм по символьно і заносимо в чар
			if (sym == '=')countPoints++;

		fileOfPoints.clear();//очистка стану потоу (ЕОФ)
		fileOfPoints.seekg(0);//виставляєм на початок файлу

		countPoints = (countPoints >> 1);
		allPoints = new Point[countPoints];

		for (int i = 0; i < countPoints; i++) {
			fileOfPoints.ignore(100, '='); //ігноруєм все до =включно, або 100 символів
			fileOfPoints >> pointX;
			fileOfPoints.ignore(10, '=');
			fileOfPoints >> pointY;
			allPoints[i].SetCoords(pointX + Point::xBord, pointY + Point::yBord);
		//	if (pointX > 1025 || pointY > 603)
		//		MessageBox(NULL, (LPCWSTR)L"Ви вказали не вірну кординату точки в певному рядку, вона не співпадає із заданною областю полотна, виправте це, або видаліть точку. Будь ласка, уважно читайте інформацію до програми!" /*strNum.str().c_str()*/, (LPCWSTR)L"Порушення!", MB_OK | MB_ICONERROR);
		//	else if (pointX == NULL || pointY == NULL)
		//		switch(MessageBox(NULL, (LPCWSTR)L"Ви вказали не вказали числове значення кординати точки в певному рядку! (можливо не правильне дотримання синтаксису)" /*strNum.str().c_str()*/, (LPCWSTR)L"Порушення!", MB_OKCANCEL | MB_ICONERROR)){
		//		case IDCANCEL:
		//			return 0;
		//			break;
		//		case IDOK:
		//			break;
		//}
		}
		fileOfPoints.close();
	}

	//if(countPoints>200)
	//	switch (MessageBox(NULL, (LPCWSTR)L"   Ви ввели забагато точок (понад 200), дійсно бажаєте продовжити? Це має непередбачувані наслідки!\n_____________________________________________________\n(гаразд, жартую, однак це дійсно займе багато часу на роздуми програми).", (LPCWSTR)L"Обережно!", MB_OKCANCEL | MB_ICONERROR)){
	//case IDCANCEL:
	//	return 0;
	//	//_spawnlp(_P_WAIT, "C:\\WINDOWS\\system32\\notepad.exe", "notepad.exe", "Points.txt", NULL);
	//	break;
	//case IDOK:
	//	break;
	//}
	SetsOfPoints();
	return 1;
};

 void Cursova::ClearFigeres() {
	currentFigure = 0;
	index = -1;
};

 void Cursova::DrawRefresh(CPaintDC& dc, CRect& rect/*, CProgressCtrl* pControl*/) {
	 //GetClientRect(&rect);
	/* rect.top = 40;
	 rect.bottom -= 60;
	 rect.left = 16;
	 rect.right -= 16;
	 CBrush paper(RGB(20, 0, 10));
	 dc.FillRect(&rect, &paper);*/
	// pControl->SetPos(progressBarPos);
	 Curs1.DrawPoints(dc);
	 if (currentFigure != 0) 
		 switch (currentFigure) {
		 case 1:
			 if (countOfRhombs)
			 Curs1.DrawRhomb(dc);
			 if (index != -1) {
				 rhombs[index].DrawCircleWithin(dc);
				 rhombs[index1].DrawCircleWithin(dc);
				 rhombs[index2].DrawCircleWithin(dc);
			 }
			 break;
		 case 2:
			 if (countOfQuadrates)
			 Curs1.DrawSquare(dc);
			 break;
		 case 3:
			 if (index == -1)
				 PaintCrossQuadr(0);
			 if (countOfRectangles)
			 Curs1.DrawRectangle(dc);
			 break;
		 case 4:
			 if (countOfRhombs)
			 Curs1.DrawRhomb(dc, true);
			 if (countOfQuadrates)
			 Curs1.DrawSquare(dc, true);
			 if (countOfRectangles)
			 Curs1.DrawRectangle(dc, true);
			 if (index != -1) {
				 rhombs[index].DrawCircleWithin(dc);
				 rhombs[index1].DrawCircleWithin(dc);
				 rhombs[index2].DrawCircleWithin(dc);
			 }
		 }

		 CPen quad(BS_SOLID, 3, RGB(255, 255, 255));
		 dc.SelectObject(&quad);

		 /*dc.Rectangle(0, 0, width, 40);
		 dc.Rectangle(0, 40, 20, height);*/
		 //frame clear area
		 //dc.Rectangle(11, 29, 900, 527);
		 dc.Rectangle(0, 0, 1000, 29);
		 dc.Rectangle(0, 29, 11, 600);
		 dc.Rectangle(900, 29, 1000, 600);
		 dc.Rectangle(11, 529, 900, 600);
	 };


void Cursova::DrawPoints(CPaintDC& dc) {
	for (int pointIndex = 0; pointIndex < countPoints; pointIndex++) 
		allPoints[pointIndex].DrawPoint(dc);
};

double Cursova::GetDistanceOfPoint(Point point, Point point1){
	int mulXsubtr = (point.GetPointX() - point1.GetPointX()) * (point.GetPointX() - point1.GetPointX()),
		mulYsubtr = (point.GetPointY() - point1.GetPointY()) * (point.GetPointY() - point1.GetPointY());

	return	sqrt((double)mulXsubtr + mulYsubtr); 
};



void Cursova::SetsOfPoints() {
	//delete[] quadrangles;
	Point p1;
	buffDistance = 0;
	//buffDistance1 = 0;
	countOfSets = 0;
	countOfRhombs = 0,
	countOfRectangles = 0,
	countOfQuadrates = 0,
	maxCountOfRhombs = 0,
	maxCountOfRectangles = 0,
	maxCountOfQuadrates = 0;
	//progressPos = 0;
	Quadrangle buffQuadrangle;
	std::map<int, bool> usedPointsRh = {};
	std::map<int, bool> usedPointsRc = {};
	std::map<int, bool> usedPointsQd = {};

	//rectangles
	for (int firstPoints = 0; firstPoints < countPoints; firstPoints++) {
		for (int secondPoints = firstPoints + 1; secondPoints < countPoints; secondPoints++) {
			if (usedPointsRc[firstPoints] || usedPointsRc[secondPoints])
				continue;
			buffDistance = Curs1.GetDistanceOfPoint(allPoints[firstPoints], allPoints[secondPoints]);
			for (int thirtPoints = secondPoints + 1; thirtPoints < countPoints; thirtPoints++) {
				if ( usedPointsRc[thirtPoints])
					continue;
				for (int fourthPoints = thirtPoints + 1; fourthPoints < countPoints; fourthPoints++) {
					if (usedPointsRc[fourthPoints])
						continue;
					buffQuadrangle = { allPoints[firstPoints], allPoints[secondPoints], allPoints[thirtPoints], allPoints[fourthPoints] };
					if (buffQuadrangle.isRectangle()&& !usedPointsRc[firstPoints] && !usedPointsRc[secondPoints]&& !usedPointsRc[thirtPoints]&& !usedPointsRc[fourthPoints]) {
						maxCountOfRectangles++;
						usedPointsRc[firstPoints] = true;
						usedPointsRc[secondPoints] = true;
						usedPointsRc[thirtPoints] = true;
						usedPointsRc[fourthPoints] = true;
					}
				}
			}
		}
	}rectangles = new Quadrangle[maxCountOfRectangles];
	usedPointsRc.clear();

	indexFigureProc = 1;
	for (int firstPoints = 0; firstPoints < countPoints; firstPoints++) {
		for (int secondPoints = firstPoints + 1; secondPoints < countPoints; secondPoints++) {
			if (usedPointsRc[firstPoints] || usedPointsRc[secondPoints])
				continue;
			buffDistance = Curs1.GetDistanceOfPoint(allPoints[firstPoints], allPoints[secondPoints]);
			for (int thirtPoints = secondPoints + 1; thirtPoints < countPoints; thirtPoints++) {
				if (usedPointsRc[thirtPoints])
					continue;
				for (int fourthPoints = thirtPoints + 1; fourthPoints < countPoints; fourthPoints++) {
					if (usedPointsRc[fourthPoints])
						continue;
					buffQuadrangle = { allPoints[firstPoints], allPoints[secondPoints], allPoints[thirtPoints], allPoints[fourthPoints] };
					if (buffQuadrangle.isRectangle() && !usedPointsRc[firstPoints] && !usedPointsRc[secondPoints] && !usedPointsRc[thirtPoints] && !usedPointsRc[fourthPoints]) {
						rectangles[countOfRectangles] = Quadrangle(allPoints[firstPoints], allPoints[secondPoints], allPoints[thirtPoints], allPoints[fourthPoints]);
						countOfRectangles++;
							usedPointsRc[firstPoints] = true;
							usedPointsRc[secondPoints] = true;
							usedPointsRc[thirtPoints] = true;
							usedPointsRc[fourthPoints] = true;
					}
				}
			}
		}
	}
	usedPointsRc.clear();
	
	for (int  firstPoints = 0; firstPoints < countPoints; firstPoints++) {
		for (int  secondPoints = firstPoints+1; secondPoints < countPoints; secondPoints++) {
			if (usedPointsRh[secondPoints])
				continue;
			buffDistance = Curs1.GetDistanceOfPoint(allPoints[firstPoints], allPoints[secondPoints]);
			for (int  thirtPoints = secondPoints+1; thirtPoints < countPoints; thirtPoints++) {
				if (usedPointsRh[thirtPoints])
					continue;
				for (int  fourthPoints = thirtPoints+1; fourthPoints < countPoints; fourthPoints++) {
					if (usedPointsRh[fourthPoints])
						continue;
					buffQuadrangle = { allPoints[firstPoints], allPoints[secondPoints], allPoints[thirtPoints], allPoints[fourthPoints] };
					if (buffQuadrangle.isRhomb()) {
						maxCountOfRhombs++;
						usedPointsRh[firstPoints] = true;
						usedPointsRh[secondPoints] = true;
						usedPointsRh[thirtPoints] = true;
						usedPointsRh[fourthPoints] = true;
					}

				}
			}
		}
	}rhombs = new Quadrangle[maxCountOfRhombs];
	usedPointsRh.clear();

	indexFigureProc = 2;
	for (int firstPoints = 0; firstPoints < countPoints; firstPoints++) {
		for (int secondPoints = firstPoints + 1; secondPoints < countPoints; secondPoints++) {
			if (usedPointsRh[firstPoints] || usedPointsRh[secondPoints])
				continue;
			buffDistance = Curs1.GetDistanceOfPoint(allPoints[firstPoints], allPoints[secondPoints]);
			for (int thirtPoints = secondPoints + 1; thirtPoints < countPoints; thirtPoints++) {
				if (usedPointsRh[thirtPoints])
					continue;
				for (int fourthPoints = thirtPoints + 1; fourthPoints < countPoints; fourthPoints++) {
					if (usedPointsRh[fourthPoints])
						continue;
					buffQuadrangle = { allPoints[firstPoints], allPoints[secondPoints], allPoints[thirtPoints], allPoints[fourthPoints] };
					if (buffQuadrangle.isRhomb()) {
						rhombs[countOfRhombs] = Quadrangle(allPoints[firstPoints], allPoints[secondPoints], allPoints[thirtPoints], allPoints[fourthPoints]);
						countOfRhombs++;
						usedPointsRh[firstPoints] = true;
						usedPointsRh[secondPoints] = true;
						usedPointsRh[thirtPoints] = true;
						usedPointsRh[fourthPoints] = true;
					}
				}
			}
		}
	}
	usedPointsRh.clear();
	
	for (int firstPoints = 0; firstPoints < countPoints; firstPoints++) {
		for (int secondPoints = firstPoints + 1; secondPoints < countPoints; secondPoints++) {
			if (usedPointsQd[firstPoints] || usedPointsQd[secondPoints])
				continue;
			buffDistance = Curs1.GetDistanceOfPoint(allPoints[firstPoints], allPoints[secondPoints]);
			for (int thirtPoints = secondPoints + 1; thirtPoints < countPoints; thirtPoints++) {
				if (usedPointsQd[thirtPoints])
					continue;
				for (int fourthPoints = thirtPoints + 1; fourthPoints < countPoints; fourthPoints++) {
					if (usedPointsQd[fourthPoints])
						continue;
					buffQuadrangle = { allPoints[firstPoints], allPoints[secondPoints], allPoints[thirtPoints], allPoints[fourthPoints] };
					if (buffQuadrangle.isSquare()) {
						maxCountOfQuadrates++;
						usedPointsQd[firstPoints] = true;
						usedPointsQd[secondPoints] = true;
						usedPointsQd[thirtPoints] = true;
						usedPointsQd[fourthPoints] = true;
					}

				}
			}
		}
	}quadrates = new Quadrangle[maxCountOfQuadrates];
	usedPointsQd.clear();

	indexFigureProc =3;//quadrate
	for (int firstPoints = 0; firstPoints < countPoints; firstPoints++) {
		for (int secondPoints = firstPoints + 1; secondPoints < countPoints; secondPoints++) {
			if (usedPointsQd[firstPoints] || usedPointsQd[secondPoints])
				continue;
			buffDistance = Curs1.GetDistanceOfPoint(allPoints[firstPoints], allPoints[secondPoints]);
			for (int thirtPoints = secondPoints + 1; thirtPoints < countPoints; thirtPoints++) {
				if (usedPointsQd[thirtPoints])
					continue;
				for (int fourthPoints = thirtPoints + 1; fourthPoints < countPoints; fourthPoints++) {
					if (usedPointsQd[fourthPoints])
						continue;
					buffQuadrangle = { allPoints[firstPoints], allPoints[secondPoints], allPoints[thirtPoints], allPoints[fourthPoints] };
					if (buffQuadrangle.isSquare()) {
						quadrates[countOfQuadrates] = Quadrangle(allPoints[firstPoints], allPoints[secondPoints], allPoints[thirtPoints], allPoints[fourthPoints]);
						countOfQuadrates++;
						usedPointsQd[firstPoints] = true;
						usedPointsQd[secondPoints] = true;
						usedPointsQd[thirtPoints] = true;
						usedPointsQd[fourthPoints] = true;
					}
				}
			}
		}
	}
	
	indexFigureProc = 0;
	usedPointsQd.clear();
};

int Cursova::getFiguresCount(int figure) {
	switch (figure) {
	case 1:
		return countOfRhombs;
		break;
	case 2:
		return countOfQuadrates;
		break;
	case 3:
		return countOfRectangles;
		break;
	case 4: 
		return countOfRhombs + countOfQuadrates + countOfRectangles;
		break;
	default:
		return 0;
	}
};


void Cursova::DrawRhomb(CPaintDC& dc, bool isMagic) {
	if (isMagic) 
		for (int i = 0; i < countOfRhombs; i++) {
			rhombs[i].SetQuadrColor(0, 0, 255);
			rhombs[i].Draw(dc);
			//Sleep(110);
		}
	else
		for (int i = 0; i < countOfRhombs; i++) {
			rhombs[i].SetQuadrColor(0, 0, 0);
			rhombs[i].Draw(dc);
		}
};

void Cursova::DrawSquare(CPaintDC& dc, bool isMagic) {
	if (isMagic) 
		for (int i = 0; i < countOfQuadrates; i++) {
			quadrates[i].SetQuadrColor(10, 250, 0);
			quadrates[i].Draw(dc);
			//Sleep(110);
		}
	else
		for (int i = 0; i < countOfQuadrates; i++) {
			quadrates[i].SetQuadrColor(0, 0, 0);
			quadrates[i].Draw(dc);
	}
};

void Cursova::DrawRectangle(CPaintDC& dc, bool isMagic) {
	short int currRedColor;
	if(isMagic)
		for (int i = 0; i < countOfRectangles; i++) {
			//rectangles[i].SetQuadrColor(250, 0, 10);
			rectangles[i].Draw(dc);
			//Sleep(110);
		}
	else
		for (int i = 0; i < countOfRectangles; i++)
			rectangles[i].Draw(dc);
};

 void Cursova::FindRhomb() {
	currentFigure = 1;
};

 void Cursova::FindSquare() {
	currentFigure = 2;
};

 void Cursova::FindRectangle() {
	currentFigure = 3;
};

 void Cursova::Mix() {
	 currentFigure = 4;
 };

 void Cursova::PaintCrossQuadr(short int rColor) {
	 for (int firstQuadr = 0; firstQuadr < countOfRectangles; firstQuadr++)
		 for (int secondQuadr = firstQuadr + 1; secondQuadr < countOfRectangles; secondQuadr++)
			 if (rectangles[firstQuadr].isRectangle() && rectangles[secondQuadr].isRectangle()
				 && QuadrIsCross(rectangles[firstQuadr], rectangles[secondQuadr])) {
				 rectangles[firstQuadr].SetQuadrColor(rColor, 0, 0);
				 rectangles[secondQuadr].SetQuadrColor(rColor, 0, 0);

			 }
 };

void Cursova::GetResult() {
	double firstS = 0, secondS = 0, thirtS = 0;
	Point upVert, upVert1, upVert2, buffPoint;


	(currentFigure != 0) ? PaintCrossQuadr() : PaintCrossQuadr(0);

	//max rhomb
	for(int rhomb=0; rhomb< countOfRhombs; rhomb++)
		if (rhombs[rhomb].isRhomb() && rhombs[rhomb].GetRhombArea() > firstS) {
			firstS = rhombs[rhomb].GetRhombArea();
			upVert = Point(rhombs[rhomb].vertexes[0].GetPointX(), rhombs[rhomb].vertexes[0].GetPointY());
			index = rhomb;
		}
	for (int rhomb = 0; rhomb < countOfRhombs; rhomb++) {
		buffPoint = Point(rhombs[rhomb].vertexes[0].GetPointX(), rhombs[rhomb].vertexes[0].GetPointY());
		if (rhombs[rhomb].isRhomb() && rhombs[rhomb].GetRhombArea() > secondS
			&& buffPoint.GetPointX() != upVert.GetPointX()
			&& buffPoint.GetPointY() != upVert.GetPointY()) {
			secondS = rhombs[rhomb].GetRhombArea();
			upVert1 = Point(rhombs[rhomb].vertexes[0].GetPointX(), rhombs[rhomb].vertexes[0].GetPointY());
			index1 = rhomb;
		}
	}
	for (int rhomb = 0; rhomb < countOfRhombs; rhomb++) {
		buffPoint = Point(rhombs[rhomb].vertexes[0].GetPointX(), rhombs[rhomb].vertexes[0].GetPointY());
		if (rhombs[rhomb].isRhomb() && rhombs[rhomb].GetRhombArea() > thirtS
			&& buffPoint.GetPointX() != upVert.GetPointX()
			&& buffPoint.GetPointY() != upVert.GetPointY()
			&& buffPoint.GetPointX() != upVert1.GetPointX()
			&& buffPoint.GetPointY() != upVert1.GetPointY()) {
				thirtS = rhombs[rhomb].GetRhombArea();
				upVert2 = Point(rhombs[rhomb].vertexes[0].GetPointX(), rhombs[rhomb].vertexes[0].GetPointY());
				index2 = rhomb;
		}
	}
};

 void Cursova::About() {

};

