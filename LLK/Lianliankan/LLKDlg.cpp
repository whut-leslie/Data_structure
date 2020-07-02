/*
@title:LLK.cpp
@author:Frank Liu
@time:2017-6-7
*/

// LLKDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Lianliankan.h"
#include "LLKDlg.h"
#include "DlgProxy.h"
#include "afxdialogex.h"
#include "GameDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CLLKDlg �Ի���

IMPLEMENT_DYNAMIC(CLLKDlg, CDialogEx);

CLLKDlg::CLLKDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LIANLIANKAN_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_APP_ICON);
	m_pAutoProxy = NULL;

}

CLLKDlg::~CLLKDlg()
{
	
	//  ���˴���ָ��öԻ���ĺ���ָ������Ϊ NULL���Ա�
	//  �˴���֪���öԻ����ѱ�ɾ����
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
	// �����ģ̬�Ի����Ѿ�������ɾ����   
	if (!m_pGameDlg)
	{
		// ɾ����ģ̬�Ի������   
		delete m_pGameDlg;
	}
}

void CLLKDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLLKDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_BASIC, &CLLKDlg::OnBnClickedBtnBasic)
	ON_BN_CLICKED(IDC_BTN_RELAX, &CLLKDlg::OnBnClickedBtnRelax)
	ON_BN_CLICKED(IDC_BTN_LEVEL, &CLLKDlg::OnBnClickedBtnLevel)
	ON_BN_CLICKED(IDB_BTN_SETTING, &CLLKDlg::OnBnClickedBtnSetting)
	ON_BN_CLICKED(IDB_BTN_HELP, &CLLKDlg::OnBnClickedBtnHelp)
	ON_BN_CLICKED(IDB_BTN_RANK, &CLLKDlg::OnBnClickedBtnRank)
	ON_BN_CLICKED(IDC_BTN_EXIT, &CLLKDlg::OnBnClickedBtnExit)
END_MESSAGE_MAP()


// CLLKDlg ��Ϣ�������

BOOL CLLKDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�
	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	InitBackground();       //���ر���ͼ

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CLLKDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CLLKDlg::OnPaint()
{
	CPaintDC dc(this); // ���ڻ��Ƶ��豸������
	CRect rect;
	GetClientRect(&rect);
	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);

		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{          
		dc.BitBlt(0, 0, rect.Width(), rect.Height(), &m_dcMem, 0, 0, SRCCOPY);   // ���Ʊ���ͼƬ 

		CDialogEx::OnPaint();   //ԭ���Դ��ĸ��ຯ��
	}
}

// ��ʼ�������ķ�������λͼѡ��λͼ�ڴ档
void CLLKDlg::InitBackground()
{
	UpdateWindow();   //���´��ڴ�С��λ��

	// ��õ�ǰ�Ի������Ƶ�ڴ�    
	CClientDC dc(this);
	// ��������Ƶ�ڴ���ݵ��ڴ� DC     
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpBackgrd;
	bmpBackgrd.LoadBitmap(IDB_MAIN_BG0);
	// ��λͼ��Դѡ�� DC    
	m_dcMem.SelectObject(bmpBackgrd);
	
}

void CLLKDlg::UpdateWindow(void)
{
	// �������ڴ�С    
	CRect rtWin;
	CRect rtClient;

	this->GetWindowRect(rtWin);       // ��ô��ڴ�С     
	this->GetClientRect(rtClient);    // ��ÿͻ�����С  

	// ����������߿�Ĵ�С     
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();

	MoveWindow(0, 0, 800 + nSpanWidth, 600 + nSpanHeight);  // ���ô��ڴ�С  
	CenterWindow();     // ���öԻ�����ʾ����������

}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR CLLKDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CLLKDlg::OnClose()
{
	/*
	if (CanExit())
		CDialogEx::OnClose();
	*/
	if (CanExit() && MessageBox(_T("ȷʵҪ�˳���"), _T("��ʾ"), MB_OKCANCEL | MB_ICONWARNING) == IDOK)
	{
		CDialog::OnClose();
	}
}

void CLLKDlg::OnCancel()
{
	if (CanExit())
		CDialogEx::OnCancel();
}

BOOL CLLKDlg::CanExit()
{
	// �����������Ա�����������Զ���
	//  �������Իᱣ�ִ�Ӧ�ó���
	//  ʹ�Ի���������������� UI ����������
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}


void CLLKDlg::OnBnClickedBtnBasic()    //����ģʽ
{
	
	// ������ģ̬�Ի���ʵ�� 
	m_pGameDlg = new CGameDlg(0, this);
	m_pGameDlg->Create(IDD_GAME_DIALOG, this);
	// ��ʾ��ģ̬�Ի��� 
	m_pGameDlg->ShowWindow(SW_SHOW);
}

void CLLKDlg::OnBnClickedBtnRelax()  //����ģʽ
{;
	// ������ģ̬�Ի���ʵ�� 
	m_pGameDlg = new CGameDlg(1, this);     //ģʽλ��Ϊ1������ģʽ��
	m_pGameDlg->Create(IDD_GAME_DIALOG, this);	
	// ��ʾ��ģ̬�Ի��� 
	m_pGameDlg->ShowWindow(SW_SHOW);
}

void CLLKDlg::OnBnClickedBtnLevel()  //�ؿ�ģʽ
{
	// ������ģ̬�Ի���ʵ�� 
	m_pGameDlg = new CGameDlg(2, this);	  //ģʽλ��Ϊ2���ؿ�ģʽ��
	m_pGameDlg->Create(IDD_GAME_DIALOG, this);

	//���ֹؿ�ģʽ�µĽ�������ͳ�ʼ��

	// ��ʾ��ģ̬�Ի��� 
	m_pGameDlg->ShowWindow(SW_SHOW);
}

void CLLKDlg::OnBnClickedBtnExit()  //�˳���Ϸ
{
	if (MessageBox(_T("ȷʵҪ�˳���"), _T("��ʾ"), MB_OKCANCEL | MB_ICONWARNING) == IDOK)
	{
		CDialog::OnCancel();
	}
}


void CLLKDlg::OnBnClickedBtnRank()  //���а�ť
{

}

void CLLKDlg::OnBnClickedBtnSetting()  //���ð�ť
{

}

void CLLKDlg::OnBnClickedBtnHelp()   //������ť
{
	//������ģ̬��ʾ���������Ի���
	CGameHelp gameHelpDlg;
	gameHelpDlg.DoModal();
}