#pragma once


// CGameHelp �Ի���

class CGameHelp : public CDialogEx
{
	DECLARE_DYNAMIC(CGameHelp)

public:
	CGameHelp(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGameHelp();

	virtual void OnFinalRelease();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Help_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	
};
