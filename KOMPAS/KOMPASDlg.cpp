
// KOMPASDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "KOMPAS.h"
#include "KOMPASDlg.h"
#include "afxdialogex.h"

// WSCADDlg.cpp : файл реализации
//


#include "afxdialogex.h"
#include "math.h"
#include "cmath"
#include "C:\Program Files\ASCON\KOMPAS-3D v22 Study\SDK\Include\ksConstants.h"
#include "C:\Program Files\ASCON\KOMPAS-3D v22 Study\SDK\Include\ksConstants3D.h"
//#include "C:\Program Files\ASCON\KOMPAS-3D v21 Study\SDK\Include\kapi5.h"
#include <atlsafe.h>
//#include <C:\Program Files\ASCON\KOMPAS-3D v21 Study\SDK\Include\Ks_TLB.h>

#include <comutil.h>
#include <string>
using namespace std;



#define PI 4*atan(1)

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma once


#import "C:\Program Files\ASCON\KOMPAS-3D v22 Study\SDK\lib\kAPI5.tlb"



using namespace Kompas6API5;
//using namespace KompasAPI5;
struct Point
{
	double x, y;
};

KompasObjectPtr pKompasApp5;
//KompasObjectPtr pKompasApp5;

ksPartPtr pPart;// = PartDoc->GetTopPart();
ksDocument3DPtr pDoc;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
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


// Диалоговое окно CKOMPASDlg



CKOMPASDlg::CKOMPASDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_KOMPAS_DIALOG, pParent)
{

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKOMPASDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, _button);
	DDX_Control(pDX, IDC_EDIT1, _countExZ);
	DDX_Control(pDX, IDC_EDIT2, _inZKol);
	DDX_Control(pDX, IDC_EDIT3, _inCylR);
	DDX_Control(pDX, IDC_EDIT4, _countEdgeHard);
	DDX_Control(pDX, IDC_EDIT5, _exCylR);
}

BEGIN_MESSAGE_MAP(CKOMPASDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CKOMPASDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT1, &CKOMPASDlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CKOMPASDlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &CKOMPASDlg::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, &CKOMPASDlg::OnEnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT5, &CKOMPASDlg::OnEnChangeEdit5)
END_MESSAGE_MAP()


// Обработчики сообщений CKOMPASDlg

BOOL CKOMPASDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
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

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	_inCylR.SetWindowTextW(L"80");
	_inZKol.SetWindowTextW(L"3");
	_countExZ.SetWindowTextW(L"12");
	_countEdgeHard.SetWindowTextW(L"5");
	_exCylR.SetWindowTextW(L"60");
	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CKOMPASDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CKOMPASDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CKOMPASDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

struct Point3d
{
	double x, y, z;

	Point3d(double xVal, double yVal, double zVal) : x(xVal), y(yVal), z(zVal) {}

	// Вычитание двух точек для получения вектора
	Point3d operator-(const Point3d& other) const
	{
		return Point3d(x - other.x, y - other.y, z - other.z);
	}

	// Добавление вектора к точке
	Point3d operator+(const Point3d& other) const
	{
		return Point3d(x + other.x, y + other.y, z + other.z);
	}

	// Умножение вектора на скаляр
	Point3d operator*(double scalar) const
	{
		return Point3d(x * scalar, y * scalar, z * scalar);
	}
};

double length(const Point3d& vector)
{
	return sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}

Point3d normalize(const Point3d& vector)
{
	double len = length(vector);
	if (len != 0) {
		return vector * (1.0 / len);
	}
	return vector;
}

Point3d findCircleCenter(double xa, double ya, double xb, double yb, double radius, int side)
{
	// Точка посередине хорды AB
	Point3d A(xa, ya, 0);
	Point3d B(xb, yb, 0);
	Point3d M((B.x + A.x) / 2.0, (B.y + A.y) / 2.0, 0);


	// Длина хорды AB
	double chordLength = length(B - A);

	// Расстояние от середины M до центра окружности O
	double OM = sqrt(fabs(radius * radius - (chordLength / 2.0) * (chordLength / 2.0)));

	// Направление перпендикуляра к хорде AB
	Point3d AB = A - B;
	Point3d direction(-AB.y, AB.x, 0);
	direction = normalize(direction);

	// Вычисляем центр окружности, используя направление и расстояние OM от M
	Point3d center = M + direction * OM * side;

	return center;
}

 double arcLength( double x1,  double y1,  double x2,  double y2,  double R) {
	// Вычисление длины сторон треугольника
	long double a = std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2)); // Расстояние между точками A и B
	long double b = R; // Радиус равен расстоянию от центра до любой точки на дуге
	long double c = R;

	// Вычисление центрального угла по теореме косинусов
	long double cosTheta = (b * b + c * c - a * a) / (2 * b * c);
	long double theta = std::acos(cosTheta); // Угол в радианах

	// Вычисление длины дуги
	long double length = theta * R;
	return length;
}


void CKOMPASDlg::OnBnClickedButton1()
{
	UpdateData();

	CString kolZV;
	_inZKol.GetWindowTextW(kolZV);
	double kolInZ = _tstof(kolZV);

	CString IT;
	_inCylR.GetWindowTextW(IT);
	double InT = _tstof(IT);

	CString ET;
	_exCylR.GetWindowTextW(ET);
	double ExT = _tstof(ET);

	CString KZ;
	_countEdgeHard.GetWindowTextW(KZ);
	double Krebr = _tstof(KZ);

	CString poh;
	_countExZ.GetWindowTextW(poh);
	double Kzub = _tstof(poh);

	
	//точки для внутр зуба
	double exPx = InT-20;
	int    exPy = 2;
	double inPx = InT-40;
	int    inPy = 12;
	double rIn = sqrt(inPx * inPx + inPy * inPy);
	
	double lenInArc = arcLength(inPx, inPy, inPx, -inPy, rIn);
	double lenInCircle = 2*PI*rIn;
	
	int kolvoz = lenInCircle / lenInArc;
	int kolvozE = 2*PI*(InT + ExT + 20)/16;

	if (kolInZ > kolvoz || kolInZ == 0)
	{
		CString outpt = L"Введено некорректное значение для количества внутренних зубьев";
		outpt += "\r\n";
		outpt += "Значение от 1 до ";
		outpt += CString(to_string(kolvoz).c_str());
		MessageBox(outpt);
		return;
	}

	if (InT < 45)
	{
		MessageBox(L"Введено некорректное значение для внутреннего цилиндра");
		return;
	}

	if (Kzub > kolvozE || Kzub == 0)
	{
		CString outpt = L"Введено некорректное значение для количества внешних зубьев";
		outpt += "\r\n";
		outpt += "Значение от 1 до ";
		outpt += CString(to_string(kolvozE).c_str());
		MessageBox(outpt);
		return;
	}

	if (Krebr > 15)
	{
		MessageBox(L"Введено некорректное значение для количества ребер жесткости");
		return;
	}


	UpdateData(FALSE);

	BeginWaitCursor();


	CComPtr<IUnknown> pKompasAppUnk = nullptr;
	if (!pKompasApp5)
	{
		// Получаем CLSID для Компас
		CLSID InvAppClsid;
		HRESULT hRes = CLSIDFromProgID(L"Kompas.Application.5", &InvAppClsid);
		if (FAILED(hRes)) {
			pKompasApp5 = nullptr;
			return;
		}

		// Проверяем есть ли запущенный экземпляр Компас
		//если есть получаем IUnknown
		hRes = ::GetActiveObject(InvAppClsid, NULL, &pKompasAppUnk);
		if (FAILED(hRes)) {
			// Приходится запускать Компас самим так как работающего нет
			// Также получаем IUnknown для только что запущенного приложения Компас
			TRACE(L"Could not get hold of an active Inventor, will start a new session\n");
			hRes = CoCreateInstance(InvAppClsid, NULL, CLSCTX_LOCAL_SERVER, __uuidof(IUnknown), (void**)&pKompasAppUnk);
			if (FAILED(hRes)) {
				pKompasApp5 = nullptr;
				return;
			}
		}

		// Получаем интерфейс приложения Компас
		hRes = pKompasAppUnk->QueryInterface(__uuidof(KompasObject), (void**)&pKompasApp5);
		if (FAILED(hRes)) {
			return;
		}
	}

	// делаем Компас видимым
	pKompasApp5->Visible = true;

	pDoc = pKompasApp5->Document3D();

	pDoc->Create(false, true);

	pPart = pDoc->GetPart(pTop_Part);


	//эскиз главный
	ksEntityPtr pSketch = pPart->NewEntity(o3d_sketch);

	ksSketchDefinitionPtr pSketchDef = pSketch->GetDefinition();

	pSketchDef->SetPlane(pPart->GetDefaultEntity(o3d_planeXOY));

	pSketch->Create();

	ksDocument2DPtr p2DDoc = pSketchDef->BeginEdit();
	//внутр толщ
	

	//vnesh толщ
	

	p2DDoc->ksLineSeg(0, 0, 0, 120, 1);
	p2DDoc->ksLineSeg(0, 120, InT, 120, 1);
	p2DDoc->ksLineSeg(InT, 120, InT, 120 - 30, 1);
	p2DDoc->ksLineSeg(InT, 120 - 30, InT+ExT, 120-30, 1);
	p2DDoc->ksLineSeg(InT + ExT, 120 - 30, InT+ExT, 120, 1);
	p2DDoc->ksLineSeg(InT + ExT, 120, InT + ExT+20, 120, 1);

	p2DDoc->ksLineSeg(InT + ExT + 20, 120, InT + ExT + 20, 0, 1);

	p2DDoc->ksLineSeg(InT + ExT + 20, 0, InT + ExT, 0, 1);
	p2DDoc->ksLineSeg(InT + ExT, 0, InT + ExT, 30, 1);
	p2DDoc->ksLineSeg(InT + ExT, 30, InT, 30, 1);
	p2DDoc->ksLineSeg(InT, 30, InT, 0, 1);

	p2DDoc->ksLineSeg(InT, 0, 0, 0, 1);


	p2DDoc->ksLineSeg(0, 10, 0, 0, 3);


	pSketchDef->EndEdit();
	//конец главного эскиза


	//тело вр
	ksEntityPtr pRotate = pPart->NewEntity(o3d_bossRotated);

	ksBossRotatedDefinitionPtr pRotDef = pRotate->GetDefinition();
	pRotDef->SetSketch(pSketch);
	pRotDef->SetSideParam(TRUE, 360);


	pRotate->Create();
	//конец тела вращ


	//эскиз зуба в сток клоскости
	ksEntityPtr pSketch2 = pPart->NewEntity(o3d_sketch);

	pSketchDef = pSketch2->GetDefinition();

	pSketchDef->SetPlane(pPart->GetDefaultEntity(o3d_planeXOZ));

	pSketch2->Create();

	p2DDoc = pSketchDef->BeginEdit();



	p2DDoc->ksLineSeg(InT + ExT + 20 - 2, -8, InT + ExT + 20 - 2, 8, 1);

	double tr = InT + ExT + 20 + 14;
	p2DDoc->ksLineSeg(InT + ExT + 20 +14, -4, InT + ExT + 20 + 14, 4, 1);
	p2DDoc->ksLineSeg(InT + ExT + 20 + 14, -4, InT + ExT + 20 - 2, -8, 1);
	p2DDoc->ksLineSeg(InT + ExT + 20 + 14, 4, InT + ExT + 20 - 2, 8, 1);


	pSketchDef->EndEdit();
	//конец эскиз зуба в сток клоскости


	//Создание смещенной плоскости
	ksEntityPtr pPlane1 = pPart->NewEntity(o3d_planeOffset);
	ksPlaneOffsetDefinitionPtr pSketch3 = pPlane1->GetDefinition();
	pSketch3->direction = true;
	pSketch3->offset = 120;
	pSketch3->SetPlane(pPart->GetDefaultEntity(o3d_planeXOZ));
	pPlane1->Create();
	//конец Создание смещенной плоскости


	//эскиз зуба в смещенной клоскости
	ksEntityPtr pSketch4 = pPart->NewEntity(o3d_sketch);

	pSketchDef = pSketch4->GetDefinition();

	pSketchDef->SetPlane(pPlane1);

	pSketch4->Create();

	p2DDoc = pSketchDef->BeginEdit();

	p2DDoc->ksLineSeg(InT + ExT + 20 - 2, -8, InT + ExT + 20 - 2, 8, 1);

	p2DDoc->ksLineSeg(InT + ExT + 20 + 14, -4, InT + ExT + 20 + 14, 4, 1);
	p2DDoc->ksLineSeg(InT + ExT + 20 + 14, -4, InT + ExT + 20 - 2, -8, 1);
	p2DDoc->ksLineSeg(InT + ExT + 20 + 14, 4, InT + ExT + 20 - 2, 8, 1);


	pSketchDef->EndEdit();
	//конец эскиз зуба в смещенной клоскости


	//эл по сеч
	ksEntityPtr pLoft = pPart->NewEntity(o3d_bossLoft);

	ksBossLoftDefinitionPtr pLoftDef = pLoft->GetDefinition();
	pLoftDef->SetLoftParam(FALSE, TRUE, TRUE);

	ksEntityCollectionPtr sk = pLoftDef->Sketchs();
	sk->Clear();
	sk->Add(pSketch2);
	sk->Add(pSketch4);
	pLoft->Create();
	//конец эл по сеч


	//vnesh zubs
	ksEntityCollectionPtr fledges = pPart->EntityCollection(o3d_edge);
	ksEntityPtr pFillet = pPart->NewEntity(o3d_fillet);

	ksFilletDefinitionPtr pFilletDef = pFillet->GetDefinition();
	pFilletDef->radius = 0.2f;
	ksEntityCollectionPtr fl = pFilletDef->array();
	fl->Clear();


	ksEntityPtr pCircCopy = pPart->NewEntity(o3d_circularCopy);

	ksCircularCopyDefinitionPtr pCircDef = pCircCopy->GetDefinition();
	
	
	pCircDef->Putcount2(Kzub);

	pCircDef->SetAxis(pPart->GetDefaultEntity(o3d_axisOY));

	fl = pCircDef->GetOperationArray();
	fl->Clear();

	fl->Add(pLoft);
	fl->Add(pFillet);

	pCircCopy->Create();
	//конец масссива


	//плоскость
	ksEntityPtr pPlane2 = pPart->NewEntity(o3d_planeOffset);
	ksPlaneOffsetDefinitionPtr pSketch5 = pPlane2->GetDefinition();
	pSketch5->direction = true;
	pSketch5->offset = 60;
	pSketch5->SetPlane(pPart->GetDefaultEntity(o3d_planeXOZ));
	pPlane2->Create();
	//конец плоскости


	// эскиз ребра жоскасти
	ksEntityPtr pSketch6 = pPart->NewEntity(o3d_sketch);

	pSketchDef = pSketch6->GetDefinition();

	pSketchDef->SetPlane(pPlane2);

	pSketch6->Create();

	p2DDoc = pSketchDef->BeginEdit();

	double l = InT + ExT + 20 - 2;
	p2DDoc->ksLineSeg(0, -10, 0, 10, 1);
	p2DDoc->ksLineSeg(InT + ExT + 20 - 2, -10, InT + ExT + 20 - 2, 10, 1);
	p2DDoc->ksLineSeg(InT + ExT + 20 - 2, -10, 0, -10, 1);
	p2DDoc->ksLineSeg(InT + ExT + 20 - 2, 10, 0, 10, 1);


	pSketchDef->EndEdit();
	//конец эскиз ребра жоскасти


	//выдавливание ребра жоскости
	ksEntityPtr pExtrude1 = pPart->NewEntity(o3d_bossExtrusion);
	ksBossExtrusionDefinitionPtr PEP = pExtrude1->GetDefinition();
	PEP->directionType = 3;
	PEP->SetSketch(pSketch6);
	PEP->SetSideParam(true, 0, 110, 0, false);
	pExtrude1->Create();
	//конец выдавливание ребра жоскости


	//массив ребер жоскасти конц
	ksEntityPtr pCircCopy2 = pPart->NewEntity(o3d_circularCopy); // Получаем интерфейс объекта операции
	pCircDef = pCircCopy2->GetDefinition(); // Получаем интерфейс параметров операции

	// Установка параметров копирования
	
	pCircDef->Putcount2(Krebr); // Количество копий
	pCircDef->SetAxis(pPart->GetDefaultEntity(o3d_axisOY)); // Установка оси

	ksEntityCollectionPtr fl1 = pCircDef->GetOperationArray();
	fl1->Clear();
	fl1->Add(pExtrude1);

	pCircCopy2->Create();
	//конец массив ребер жоскасти конц



	// эскиз внутр шест
	ksEntityPtr pSketch7 = pPart->NewEntity(o3d_sketch);

	pSketchDef = pSketch7->GetDefinition();

	pSketchDef->SetPlane(pPart->GetDefaultEntity(o3d_planeXOZ));

	pSketch7->Create();

	p2DDoc = pSketchDef->BeginEdit();
	
	p2DDoc->ksLineSeg(exPx, -exPy, exPx, exPy, 1);
	Point3d center = findCircleCenter(exPx, exPy, inPx, inPy, 25, -1);
	p2DDoc->ksArcByPoint(
		center.x, center.y, 25,
		exPx, exPy, inPx, inPy, 0, 1);
	p2DDoc->ksArcByPoint(
		center.x, -center.y, 25, 
		inPx, -inPy, exPx, -exPy, 0, 1);
	p2DDoc->ksArcByPoint(
		0, 0, rIn,
		inPx, inPy, inPx, -inPy, 1, 1);

	pSketchDef->EndEdit();
	//конец эскиз внутр шест


	//выдавливание внутр шест
	ksEntityPtr pCutExtrude2 = pPart->NewEntity(o3d_cutExtrusion);
	ksCutExtrusionDefinitionPtr BED = pCutExtrude2->GetDefinition();
	BED->directionType = dtReverse;
	BED->SetSketch(pSketch7);
	BED->SetSideParam(false, etBlind, 100, 0, false);
	pCutExtrude2->Create();
	//конец выдавливание внутр шест


	//массив ребер внутр шест
	ksEntityPtr pCircCopy3 = pPart->NewEntity(o3d_circularCopy); // Получаем интерфейс объекта операции
	pCircDef = pCircCopy3->GetDefinition(); // Получаем интерфейс параметров операции

	// Установка параметров копирования
	pCircDef->Putcount2(kolInZ); // Количество копий
	pCircDef->SetAxis(pPart->GetDefaultEntity(o3d_axisOY)); // Установка оси

	ksEntityCollectionPtr fl2 = pCircDef->GetOperationArray();
	fl2->Clear();
	fl2->Add(pCutExtrude2);

	pCircCopy3->Create();
	//конец массив внутр шест



	// эскиз 
	ksEntityPtr pSketch8 = pPart->NewEntity(o3d_sketch);

	pSketchDef = pSketch8->GetDefinition();

	pSketchDef->SetPlane(pPlane1);

	pSketch8->Create();

	p2DDoc = pSketchDef->BeginEdit();

	p2DDoc->ksCircle(0, 0, 14, 1);

	pSketchDef->EndEdit();
	//конец эскиз внутр шест



	ksEntityPtr pExtrude2 = pPart->NewEntity(o3d_cutExtrusion);
	BED = pExtrude2->GetDefinition();
	BED->directionType = dtNormal;
	BED->SetSketch(pSketch8);
	BED->SetSideParam(true, etUpToNearSurface, 0, 0, false);
	pExtrude2->Create();

}



void CKOMPASDlg::OnEnChangeEdit1()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// функция и вызов CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
}


void CKOMPASDlg::OnEnChangeEdit2()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// функция и вызов CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
}


void CKOMPASDlg::OnEnChangeEdit3()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// функция и вызов CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
}


void CKOMPASDlg::OnEnChangeEdit4()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// функция и вызов CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
}


void CKOMPASDlg::OnEnChangeEdit5()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// функция и вызов CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
}




