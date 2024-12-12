
// KOMPASDlg.h: файл заголовка
//

#pragma once


// Диалоговое окно CKOMPASDlg
class CKOMPASDlg : public CDialogEx
{
// Создание
public:
	CKOMPASDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_KOMPAS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CButton _button;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeEdit1();
	CEdit _countExZ;
	afx_msg void OnEnChangeEdit2();
	CEdit _inZKol;
	afx_msg void OnEnChangeEdit3();
	CEdit _inCylR;
	afx_msg void OnEnChangeEdit4();
	CEdit _countEdgeHard;
	afx_msg void OnEnChangeEdit5();
	CEdit _exCylR;
	
	
	
};
