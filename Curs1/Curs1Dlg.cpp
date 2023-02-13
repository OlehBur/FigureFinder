
// Curs1Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Curs1.h"
#include "Curs1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

Cursova Curs1;

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCurs1Dlg dialog



CCurs1Dlg::CCurs1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CURS1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCurs1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_PROGRESS1, ProgressBar);
}

BEGIN_MESSAGE_MAP(CCurs1Dlg, CDialogEx)
	ON_WM_TIMER()
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CCurs1Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CCurs1Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CCurs1Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CCurs1Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CCurs1Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CCurs1Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CCurs1Dlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDCANCEL, &CCurs1Dlg::OnBnClickedCancel)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_PROGRESS1, &CCurs1Dlg::OnNMCustomdrawProgress1)
	ON_BN_CLICKED(IDC_BUTTON7, &CCurs1Dlg::OnBnClickedButton7)
	ON_STN_CLICKED(IDCOUNTFIGURES, &CCurs1Dlg::OnStnClickedCountfigures)
END_MESSAGE_MAP()


// CCurs1Dlg message handlers

BOOL CCurs1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
		
	//CProgressCtrl* pControl;
	//pControl->GetDlgItem(IDC_PROGRESS1);
	//pControl->SetRange(0, 100); // Задаємо границі
	//pControl->SetPos(0); // Задаємо нову позицію прогресу
		////pControl->SetBarColor(0x0000FF00);
	////pControl->SetBkColor(0x0000FF00);
	
	//CProgressCtrl ProgressBar;
	//CWnd* parentWindow;
	
	//ProgressBar.Create(PBS_SMOOTH, CRect(10, 10, 200, 30), parentWindow, IDC_PROGRESS1);
		//ProgressBar.SetRange(0, 100);
	//ProgressBar.SetBarColor(0x0000FF00); //SetBkColor
	//ProgressBar.SetPos(5);
	
	
	//ProgressBar.SetState(20);
	//ProgressBar.put_accValue(100, 10);
	
	
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCurs1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
////  this is automatically done for you by the framework.
//
void CCurs1Dlg::UpdArea()
{
//	CRect cRect;
//	CWnd* pWnd = GetDlgItem(IDC_STATIC);
//	pWnd->GetWindowRect(&cRect);
//
//	ScreenToClient(&cRect);
//
//	/*AllocConsole();
//	FILE* file{};
//	freopen_s(&file, "CONOUT$", "w", stdout);
//
//	printf("%d %d %d %d \n", cRect.left, cRect.bottom, cRect.top, cRect.right);*/
//	cRect.left+=30;
//	cRect.top+=20;
//
//	cRect.right-=20;
//	cRect.bottom-=20;
//
//	InvalidateRect(&cRect, true);
//
}

void CCurs1Dlg::OnPaint()
{
	CPaintDC dc(this); 
	CRect rect;

	

	if (!IsIconic())
	{	

		/*char* info = "ewornceksrleasr";
		GetDlgItem(DescText)->SetWindowText(info);*/
		CProgressCtrl* pControl = (CProgressCtrl*)GetDlgItem(IDC_PROGRESS1);
		// pControl->GetDlgItem(IDC_PROGRESS1);

		pControl->SetRange(0, 100); // Задаємо границі
		
		Curs1.DrawRefresh(dc, rect/*, pControl*/);

		//CRect fr;//get frame drawwing parametres
		//CWnd* pWnd = GetDlgItem(IDC_FRAME);
		//pWnd->GetWindowRect(&fr);
		//ScreenToClient(&fr);
		//int l = fr.left, t = fr.top, w = fr.Width(), h = fr.Height();


		//Point p[] = { {400,200},{360,240},{440,240}, {400,280} };
		//Point p1[] = { {40,200},{200,40},{40,40},{200,200} };
		//Point p2[]={ {50, 400}, { 50,50 }, {400,400}, { 400,50 } };
		////Point p1(400, 200), p2(360, 240), p3(440, 240), p4(400, 280);
		////Quadrangle one(p1,p2,p3,p4);
		//Quadrangle one(p);
		//Quadrangle two(p1);
		//Quadrangle three(p2);
		////if(two.isRectangle()) //work		genial hod
		////if(two.isSquare()) //work
		//if (two.isSquare() && three.isRhomb()) { //work
		//	two.SetQuadrColor(23, 120, 10);
		//	two.Draw(dc);

		//	three.Draw(dc);
		//	if (!Curs1.QuadrIsCross(two, three)) {
		//		two.SetQuadrColor(250, 0, 0);
		//		three.SetQuadrColor(250, 0, 0);
		//	}
		//		two.Draw(dc);
		//		three.Draw(dc);
		///*	if (three.GetRhombArea() < two.GetRhombArea())
		//		three.DrawCircleWithin(dc);
		//	else two.DrawCircleWithin(dc);*/
		//}
		//one.SetQuadrColor(20, 110, 250);
		//one.Draw(dc);
	/*	if(one.isRhomb())
			one.Draw(dc);
		*/


		//Line myL(p[0], p[1]), myL1(p[2], p[3]);
		//if (myL.GetLength() > myL1.GetLength()) {
		//	myL.SetColor(200, 100, 0);
		//	myL1.SetColor(0, 100, 150);
		//}
		//else {
		//	myL.SetColor(255, 0, 0);
		//	myL1.SetColor(0, 0, 255);
		//}

		//myL.DrawLine(dc);
		//myL1.DrawLine(dc);
		GetDlgItem(DescText)->SetWindowText(L"Figures count:");
		CDialogEx::OnPaint();
	}
}


//  the minimized window.
HCURSOR CCurs1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int CallInfoWindows(){
	int authroWindow = MessageBox(NULL, (LPCWSTR)L"Про автора : \n Завдання курсової роботи виконав студент групи 1СП - 21б Бурдейний О.В.", (LPCWSTR)L"Про автора", MB_OK| MB_ICONINFORMATION),
		infoWindow = MessageBox(NULL, (LPCWSTR)L"Завдання програми: \n	* вміти виводити задані користувачем точки з файлу на екран;\n	*знаходити можливі квадрати, прямокутники та ромби із заданого масиву та зображувати їх;\n	*виділяти червоним кольором прямокутники, що перетинаються;\n	*вписувати кола в найбільші три ромби.", (LPCWSTR)L"Інфо додатку", MB_OK| MB_ICONINFORMATION),
		rulesWindow = MessageBox(NULL, (LPCWSTR)L" Вітаю в програмі для графічного малювання точок та певних фігур! Будь ласка, прочитайте дані правила та поради аби розуміти можливості програми.\n_____________________________________________________\n		       Клавіші та дії:  \n	\"Задати точки\" - відкриває текстовий файл для заддання точок у блокноті (по стандарту наведений приклад введення двох точок).Обов'язкове дотримання стандарту вписування точок: \nTochka%: x=n, y=m; де % -порядковий номер точки, а m і n - деякі числа що позначають координати. !!!Увага допустимою областю координат по \"у\" та \"х\" є проміжки  від 0 до 603 та від 0 до 1025 відповідно.Після введення довільної кількості точок збережіть та зактрийте файл блокноту, після чого точки автоматично з\'являться на екрані;\n	\"Ромби/Квадрати/Прямокутники\" - кнопки для знаходження та відображення всіх можливих фігур відповідного типу з даних точок; \n	\"Очистити\" - клавіша очищує намальовані фігури, та залишає на полотні лиш точки; \n	\"Розв'язання\" - клавіша функціонал якої дозволяє візуально розв'язати основну задачу курсової роботи, а саме : \"Вписати кола в три найбільші ромби, а також виділити певним кольором(червоним) прямокутники, що перетинаються.\";\n	\"Про\" - схоже тепер ви знаєте для чого ця клавіша (візуалізація текстових підсказок з детальною інформацією); \n	\"Мікс\" - поєднує в собі Прямокутники, Квадрати та Ромби з незалежністю від точок один одного;\n	\"Вихід\" - закриває додаток курсової. ", (LPCWSTR)L"Правила користування", MB_OK| MB_ICONQUESTION);

	return authroWindow, rulesWindow, infoWindow;
}
TCHAR wstr[10];
//enter coords
void CCurs1Dlg::OnBnClickedButton1()
{	
	GetDlgItem(IDC_PROGRESS1)->ShowWindow(true);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(false);
	GetDlgItem(TEXT_PROGRESS)->ShowWindow(true);
	SetTimer(1, 100, 0);
	SetDlgItemText(TEXT_PROGRESS, (LPCTSTR)L"Entered cords...");
	int openPointsFile = _spawnlp(_P_WAIT, "C:\\WINDOWS\\system32\\notepad.exe", "notepad.exe", "Points.txt", NULL);
	Invalidate();
	//Curs1.~Cursova();
	if (Curs1.InitFromFile()) {
		GetDlgItem(DescText)->ShowWindow(true);
		Curs1.ClearFigeres();
		_itot_s(Curs1.getFiguresCount(0), wstr, _countof(wstr), 10);
		SetDlgItemText(IDCOUNTFIGURES, wstr);
		GetDlgItem(IDC_BUTTON2)->EnableWindow(true);
		GetDlgItem(IDC_BUTTON3)->EnableWindow(true);
		GetDlgItem(IDC_BUTTON4)->EnableWindow(true);
		GetDlgItem(IDC_BUTTON5)->EnableWindow(true);
		GetDlgItem(IDC_BUTTON7)->EnableWindow(true);
	}
	GetDlgItem(IDC_BUTTON1)->EnableWindow(true);
	GetDlgItem(IDC_PROGRESS1)->ShowWindow(false);
	GetDlgItem(TEXT_PROGRESS)->ShowWindow(false);
	
	KillTimer(1);
};

//clear(draw points)
void CCurs1Dlg::OnBnClickedButton2()
{
	GetDlgItem(IDC_BUTTON2)->EnableWindow(false);
	Curs1.ClearFigeres();
	//_itot_s(Curs1.getFiguresCount(0), wstr, _countof(wstr), 10);
	SetDlgItemText(IDCOUNTFIGURES, (LPCTSTR)"0");
	Invalidate();
	GetDlgItem(IDC_BUTTON2)->EnableWindow(true);
}

//find rhomb
void CCurs1Dlg::OnBnClickedButton3()
{
	GetDlgItem(IDC_BUTTON3)->EnableWindow(false);
	Curs1.FindRhomb();
	_itot_s(Curs1.getFiguresCount(1), wstr, _countof(wstr), 10);
	SetDlgItemText(IDCOUNTFIGURES, wstr);
	Invalidate();
	GetDlgItem(IDC_BUTTON3)->EnableWindow(true);
	GetDlgItem(IDOK)->EnableWindow(true);
}

//find square
void CCurs1Dlg::OnBnClickedButton4()
{
	GetDlgItem(IDC_BUTTON4)->EnableWindow(false);
	Curs1.FindSquare();
	_itot_s(Curs1.getFiguresCount(2), wstr, _countof(wstr), 10);
	SetDlgItemText(IDCOUNTFIGURES, wstr);
	Invalidate();
	GetDlgItem(IDC_BUTTON4)->EnableWindow(true);
	GetDlgItem(IDOK)->EnableWindow(true);
}

//find rectangle
void CCurs1Dlg::OnBnClickedButton5()
{
	GetDlgItem(IDC_BUTTON5)->EnableWindow(false);
	Curs1.FindRectangle();
	_itot_s(Curs1.getFiguresCount(3), wstr, _countof(wstr), 10);
	SetDlgItemText(IDCOUNTFIGURES, wstr);
	Invalidate();
	GetDlgItem(IDC_BUTTON5)->EnableWindow(true);
	GetDlgItem(IDOK)->EnableWindow(true);
}


//result
void CCurs1Dlg::OnBnClickedOk() {
	//block other buttons;
	GetDlgItem(IDOK)->EnableWindow(false);
	Curs1.GetResult();
	Invalidate();
	GetDlgItem(IDOK)->EnableWindow(true);
}

//info
void CCurs1Dlg::OnBnClickedButton6()
{
	GetDlgItem(IDC_BUTTON6)->EnableWindow(false);
	CallInfoWindows();
	GetDlgItem(IDC_BUTTON6)->EnableWindow(true);
}
inline int ExitCursova() {
	return MessageBox(NULL, (LPCWSTR)L"Ви дійсно бажаєте закрити програму?.", (LPCWSTR)L"Йдете?", MB_OKCANCEL | MB_ICONWARNING);
}


//calncel
void CCurs1Dlg::OnBnClickedCancel()
{
	switch (ExitCursova())
	{
	case IDCANCEL:

		break;
	case IDOK:
		CDialogEx::OnCancel();
	}
	
}

void CCurs1Dlg::OnStnClickedMyLabel()
{
	
}


void CCurs1Dlg::OnNMCustomdrawProgress1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

//mix
void CCurs1Dlg::OnBnClickedButton7()
{
	Curs1.Mix();
	_itot_s(Curs1.getFiguresCount(4), wstr, _countof(wstr), 10);
	SetDlgItemText(IDCOUNTFIGURES, wstr);
	Invalidate();
}


void CCurs1Dlg::OnStnClickedCountfigures()
{
	// TODO: Add your control notification handler code here
}

afx_msg void CCurs1Dlg::OnTimer(UINT ID) {
	static CProgressCtrl* pControl = (CProgressCtrl*)GetDlgItem(IDC_PROGRESS1);
	//pControl->SetRange(0, 100);
	if (Curs1.indexFigureProc) 
		switch (Curs1.indexFigureProc) {
		case 1:
			SetDlgItemText(TEXT_PROGRESS, (LPCTSTR)L"Generic Rectangle!");
			pControl->SetPos(100*Curs1.countOfRectangles/Curs1.maxCountOfRectangles);
			Invalidate();
			break;
		case 2:
			SetDlgItemText(TEXT_PROGRESS, (LPCTSTR)L"Generic Rhombs!");
			pControl->SetPos(100 * Curs1.countOfRhombs / Curs1.maxCountOfRhombs);
			Invalidate();
			break;
		case 3:
			SetDlgItemText(TEXT_PROGRESS, (LPCTSTR)L"Generic Quadrate!");
			pControl->SetPos(100 * Curs1.maxCountOfQuadrates / Curs1.maxCountOfQuadrates); 
			Invalidate();
		}
		//SetDlgItemText(TEXT_PROGRESS, (LPCTSTR)L"Complate coords!");
}