
// GameDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "Lianliankan.h"
#include "GameDlg.h"
#include "mmsystem.h"
#define  ProgCtrlMAX 120    //���������ֵ
#define  TimerOne    1      //��ʱ��one

// CGameDlg �Ի���

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(int gModel, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_APP_ICON);
	EnableAutomation();

	m_ptGameTop.Offset(1, 45);   //��Ϸ����ʼ��������
	m_sizeElem.SetSize(40, 40);   //������ϷͼƬ��С
	//������Ϸ����ʼ�����������ϷͼƬԪ�ش�С���㣬������Ϸ����߽�
	m_rtGameRect.left = m_ptGameTop.x;
	m_rtGameRect.top = m_ptGameTop.y;
	m_rtGameRect.bottom = m_ptGameTop.y + m_sizeElem.cy * (CGameControl::s_nRows + 2);
	m_rtGameRect.right = m_ptGameTop.x + m_sizeElem.cx * (CGameControl::s_nCols + 2);
	m_bFirstPoint = true;    //bool��ʼ��
	m_bPlaying = false;      //��Ϸδ�ڽ���״̬
	nRerank = 3;			//����ʣ�������ʼ��Ϊ3��
	extraTime = ProgCtrlMAX;   //ʣ��ʱ���ʼ��Ϊ120s
	gameModel = gModel;			//��Ϸģʽλ��ʼ����Ĭ��Ϊ������ģʽ��
	level = 1;              //�ؿ��ȼ���ʼ��Ϊ1��
}

CGameDlg::~CGameDlg()
{
}

void CGameDlg::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CDialogEx::OnFinalRelease();
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_START, &CGameDlg::OnBnClickedBtnStart)
	ON_WM_CLOSE()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_Rerank, &CGameDlg::OnBnClickedBtnRerank)
	ON_BN_CLICKED(IDC_BTN_Stop, &CGameDlg::OnBnClickedBtnStop)
	ON_BN_CLICKED(IDC_BTN_Tip, &CGameDlg::OnBnClickedBtnTip)
	ON_BN_CLICKED(IDB_BTN_HELP, &CGameDlg::OnBnClickedBtnHelp)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CGameDlg, CDialogEx)
END_DISPATCH_MAP()

// ע��: ������� IID_IGameDlg ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡��� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {F497B997-B536-44C5-830B-FD433615F5F0}
static const IID IID_IGameDlg =
{ 0xF497B997, 0xB536, 0x44C5, { 0x83, 0xB, 0xFD, 0x43, 0x36, 0x15, 0xF5, 0xF0 } };

BEGIN_INTERFACE_MAP(CGameDlg, CDialogEx)
	INTERFACE_PART(CGameDlg, IID_IGameDlg, Dispatch)
END_INTERFACE_MAP()


// CGameDlg ��Ϣ�������


void CGameDlg::OnPaint()
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
		//CPaintDC dc(this);    // ���� CPaintDC ����           
		dc.BitBlt(0, 0, rect.Width(), rect.Height(), &m_dcBG, 0, 0, SRCCOPY);   // ���Ʊ���ͼƬ
		if (m_bPlaying)    //�����Ϸ���ڿ�ʼ״̬������Ҫ�ػ���Ϸ��ͼ����Ҫ��Ϊ�˴�����С����ԭ������Զ��ػ�Ԫ��
			UpdateMap();    //����Ǹս�����Ϸ���棬��û�е������ʼ��Ϸ��������Ҫ������Ϸ��ͼ
		CDialogEx::OnPaint();   //ԭ���Դ��ĸ��ຯ��
	}
}

BOOL CGameDlg::OnInitDialog()
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
	SetIcon(m_hIcon, TRUE);	    // ���ô�ͼ��
	SetIcon(m_hIcon, TRUE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	InitBackground();   //���ر���ͼƬ
	InitElement();     //��ʼ����ϷͼƬԪ��
	// ��ʼ��������
	pProgCtrl = (CProgressCtrl*)GetDlgItem(IDC_PROGRESS_TIME);
	pProgCtrl->SetRange(0, ProgCtrlMAX);    //���ý�������Χ  
	//pProgCtrl->SetPos(ProgCtrlMAX);			//���ý�������ǰλ��Ϊ���ֵ
	//��̬�ı�ָ�붨λ
	pStaticTime = (CStatic*)GetDlgItem(IDC_extraTimeText);	  
	pStaticLevel = (CStatic*)GetDlgItem(IDC_STATIC_Level);    
	CString title;    //�Ի�������ı�
	//����ģʽ������ʱ���������ʱ����ʾ�ı�,�޸ĶԻ������
	if (gameModel == 1)
	{
		pProgCtrl->ShowWindow(SW_HIDE);
		pStaticTime->ShowWindow(SW_HIDE);
		title = "��ͨ������-����ģʽ";
		SetWindowText(title);
	}
	else if (gameModel == 2)
	{
		title = "��ͨ������-�ؿ�ģʽ";
		SetWindowText(title);
		LevelModelSupt();	    //�ؿ�ģʽ����ؿ���֧��
	}
		
	return TRUE;    // ���ǽ��������õ��ؼ������򷵻� TRUE
}

/* �رնԻ��򣬵���ȷ�Ͽ� */
void CGameDlg::OnClose()
{
	if (MessageBox(_T("ȷʵҪ�˳���"), _T("��ʾ"), MB_OKCANCEL | MB_ICONWARNING) == IDOK)
	{
		m_GameC.s_nPicNum = 20;     //�˳���Ϸ����ʱ��ɵ�ͼĬ�����ݻָ�
		CDialog::OnClose();
	}
}

void CGameDlg::InitElement()
{
	// ��õ�ǰ�Ի������Ƶ�ڴ�     
	CClientDC dc(this);
	// ���� BMP ͼƬ��Դ     
	HANDLE hBmp = ::LoadImageW(NULL, _T("res\\theme\\picture\\fruit_element.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	// ��������Ƶ�ڴ���ݵ��ڴ� DC 
	m_dcElement.CreateCompatibleDC(&dc); 
	// ��λͼ��Դѡ�� DC     
	m_dcElement.SelectObject(hBmp);

	// �������� BMP ͼƬ��Դ   
	HANDLE hMask = ::LoadImageW(NULL, _T("res\\theme\\picture\\fruit_mask.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	// ��������Ƶ�ڴ���ݵ��ڴ� DC     
	m_dcMask.CreateCompatibleDC(&dc);
	// ��λͼ��Դѡ�� DC     
	m_dcMask.SelectObject(hMask);
}

// ��ʼ�������ķ�������λͼѡ��λͼ�ڴ档
void CGameDlg::InitBackground()
{
	UpdateWindow();
	/* ��̬������Ϸ����
	// ��õ�ǰ�Ի������Ƶ�ڴ�    
	CClientDC dc(this);
	// ��������Ƶ�ڴ���ݵ��ڴ� DC     
	m_dcBG.CreateCompatibleDC(&dc);
	CBitmap bmpGameBG;
	bmpGameBG.LoadBitmap(IDB_GAME_BG1);
	// ��λͼ��Դѡ�� DC    
	m_dcBG.SelectObject(bmpGameBG);
	*/

	//������Ϸģʽѡ����صı���ͼƬ
	CString bkgPath("res\\theme\\fruit_bg.bmp");
	if (gameModel == 1)
		bkgPath = "res\\theme\\fruit_bg.bmp";
	else if (gameModel == 2)
		bkgPath = "res\\theme\\fruit_bg.bmp";
	// ��̬����
	// ��õ�ǰ�Ի������Ƶ�ڴ�    
	CClientDC dc(this);
	// ��̬����������Ϸ����ͼƬ��Դ   
	HANDLE hBackG = ::LoadImageW(NULL, bkgPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	// ��������Ƶ�ڴ���ݵ��ڴ� DC     
	m_dcBG.CreateCompatibleDC(&dc);
	// ��λͼ��Դѡ�� DC     
	m_dcBG.SelectObject(hBackG);
}

/*�ػ���Ϸ���򱳾������ڽ���ˢ��*/
void CGameDlg::UpdateGameRect()
{
	// ��õ�ǰ�Ի������Ƶ�ڴ�    
	CClientDC dc(this);
	//�ػ������Ϸ���򱳾�
	dc.StretchBlt(m_ptGameTop.x, m_ptGameTop.y, m_rtGameRect.right- m_rtGameRect.left, m_rtGameRect.bottom- m_rtGameRect.top, &m_dcBG, m_rtGameRect.left, m_rtGameRect.top, m_rtGameRect.right - m_rtGameRect.left, m_rtGameRect.bottom - m_rtGameRect.top, SRCCOPY);  
}

// ���´���
void CGameDlg::UpdateWindow()
{
	// �������ڴ�С     
	CRect rtWin;    
	CRect rtClient;     
	this->GetWindowRect(rtWin);       // ��ô��ڴ�С 
	this->GetClientRect(rtClient);    // ��ÿͻ�����С 

	// ����������߿�Ĵ�С     
	int nSpanWidth = rtWin.Width() - rtClient.Width();     
	int nSpanHeight = rtWin.Height() - rtClient.Height(); 

	// ���ô��ڴ�С     
	MoveWindow(0, 0, 860 + nSpanWidth, 660 + nSpanHeight); 

	// ���öԻ�����ʾ�� windows ���������롣
	CenterWindow();
}

// ������Ϸ��ͼ
void CGameDlg::UpdateMap()
{
	UpdateGameRect();   //�ػ������Ϸ���򱳾�

	// ��ȡ��ͼ������������ͼƬ��  
	int nRows = CGameControl::s_nRows;
	int nCols = CGameControl::s_nCols;
	int nPicNum = CGameControl::s_nPicNum;

	// ����ͼƬ�Ķ���������ͼƬ��С
	int nLeft = m_ptGameTop.x, nTop = m_ptGameTop.y;	 //��Ϸ����ʼ��������
	int nElemW = m_sizeElem.cx, nElemH = m_sizeElem.cy;   //ͼƬ�߶ȺͿ������
	
	CClientDC dcGame(this);
	for (int i = 1; i < nRows + 1; i++) {
		for (int j = 1; j < nCols + 1; j++) {   
			// �õ�ͼƬ��ŵ�ֵ   
			int nElemVal = m_GameC.GetElement(i, j); 
			if (nElemVal != BLANK)    //����ѱ���ΪBLANK(-1)��������
			{
				// ��������������򣬱߱�����ͼ������Ϊ 1            
				//dcGame.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcMask, 0, nElemVal * nElemH, SRCPAINT); 
				dcGame.StretchBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcMask, 0, nElemVal * nElemH, nElemW, nElemH, SRCPAINT);

				// ��Ԫ��ͼƬ���룬�߱�����ͼ������ΪԪ��ͼƬ           
				//dcGame.BitBlt(nLeft + j * nElemW, nTop + i * nElemH , nElemW, nElemH, &m_dcElement, 0, nElemVal * nElemH, SRCAND);
				dcGame.StretchBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcElement, 0, nElemVal * nElemH, nElemW, nElemH, SRCAND);
			}
		}
	} 
}

//�������¼�
void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (!m_bPlaying)    //�����Ϸδ�ڽ��У�����Ӧ����¼�
		return;
	// �ж������������  
	if(point.y < m_rtGameRect.top + m_sizeElem.cy || point.y > m_rtGameRect.bottom - m_sizeElem.cy || point.x < m_rtGameRect.left + m_sizeElem.cx || point.x > m_rtGameRect.right - m_sizeElem.cx)
	{  
		return CDialogEx::OnLButtonUp(nFlags, point); 
	} 
	int nRow = (int)(point.y - m_rtGameRect.top) / m_sizeElem.cy;    //���λ�������к�
	int nCol = (int)(point.x - m_rtGameRect.left) / m_sizeElem.cx;   //���λ�������к�

	if (m_GameC.GetElement(nRow, nCol) != BLANK)   // ��δ��������ѡ��
	{
		if (m_bFirstPoint)  // ��һ����  
		{
			DrawTipFrame(nRow, nCol);     //���Ƶ�һ��������ʾ��
			m_GameC.SetFirstPoint(nRow, nCol);   //����ѡ�еĵ�һ����ļ�¼
			m_bFirstPoint = false;
		}
		else               // �ڶ�����
		{
			DrawTipFrame(nRow, nCol);     //���Ƶڶ���������ʾ��
			m_GameC.SetSecPoint(nRow, nCol);   //����ѡ�еĵڶ�����ļ�¼

			// �����ж�  
			Vertex avPath[PathLen];
			int nVexnum = 0;
			bool bSuc = m_GameC.Link(avPath, nVexnum);
			if (bSuc == true)
			{
				DrawTipLine(avPath, nVexnum);    // ����ʾ��  
				Sleep(200);     //��ͣ200ms������һ������
				extraTime += 3;      //����һ�Ժ�ʣ��ʱ���10s
				//PlaySound(_T("res\\music\\cut2.wav"), NULL, SND_FILENAME | SND_ASYNC );   // ������������
				if (m_GameC.IsWin())
				{
					CButton *pBtn = (CButton*)GetDlgItem(IDC_BTN_START);   //��ťָ��ָ��IDC_BTN_START�����ť 
					pBtn->EnableWindow(TRUE);    // "��ʼ��Ϸ"��ť��Ϊ����
					KillTimer(TimerOne);
					if(gameModel!=2)
						MessageBox(_T("��ϲ��Ӯ��!!!"), _T("ʤ����"), MB_OK);   //�����������ʤ����
					else           
					{
						level++;      //�ؿ���1
						LevelModelSupt();      //�����һ�ؿ���׼������
						//�ؿ�ģʽ�£�����������Ҽ�����
						MessageBox(_T("��ϲ��ͨ�����أ���\n �������һ��!"), _T("������"), MB_OK);
					}
				}
			}
			UpdateMap();      // ���µ�ͼ
			m_bFirstPoint = !m_bFirstPoint;   //����
		}
	}
}

/*���ƾ�����ʾ�� */
void CGameDlg::DrawTipFrame(int nRow, int nCol)
{
	int recX = nCol*m_sizeElem.cx + m_rtGameRect.left;   //�������Ͻ�X����
	int recY = nRow*m_sizeElem.cy + m_rtGameRect.top;    //�������Ͻ�Y����
	CPoint topLeft(recX, recY);     //���ƾ��ε����Ͻ�����
	CPoint rightBottom(recX + m_sizeElem.cx, recY + m_sizeElem.cy);   //���ƾ��ε����½�����
	CClientDC dc(this);
	CPen pen(PS_SOLID, 1, RGB(233, 43, 43));    //����ֱ����ԡ���ɫ����ɫ��
	CPen *pOldPen = dc.SelectObject(&pen);
	CBrush *pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
	CBrush *pOldBrush = dc.SelectObject(pBrush);
	dc.Rectangle(CRect(topLeft, rightBottom));
	dc.SelectObject(pOldPen);
	dc.SelectObject(pOldBrush);
}

/* ������ʾLine */
void CGameDlg::DrawTipLine(Vertex asvPath[PathLen], int nVexnum)
{
	CClientDC dc(this);   //��õ�ǰ��Ƶ�ڴ�
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));   //���廭�����ԡ���ɫ��ǳ��ɫ��
	CPen* pOldPen = dc.SelectObject(&penLine);   //������ѡ����Ƶ�ڴ�

	dc.MoveTo(m_ptGameTop.x + asvPath[0].col * m_sizeElem.cx + m_sizeElem.cx / 2, m_ptGameTop.y + asvPath[0].row * m_sizeElem.cy + m_sizeElem.cy / 2);  //���ʶ�λ

	for (int i = 1; i < nVexnum; i++)    // ����ʼ��������㻭���������յ�
	{
		dc.LineTo(m_ptGameTop.x + asvPath[i].col * m_sizeElem.cx + m_sizeElem.cx / 2, m_ptGameTop.y + asvPath[i].row * m_sizeElem.cy + m_sizeElem.cy / 2);
	}
	dc.SelectObject(pOldPen);
}

/*��ʼ��Ϸ��ť�¼�*/
void CGameDlg::OnBnClickedBtnStart()  
{
	m_GameC.StartGame();
	/*��ʼ����ϷͼƬԪ�أ����ܷ�������ظ��������ʼ��Ϸ����ť���ظ�
	 *����CDCλͼ�ڴ棬�����жϡ�����֪��ԭ�� */
	UpdateMap();     //���µ�ͼ��������ϷͼƬ
	pProgCtrl->SetPos(extraTime);    //���ý�������ʼλ��
	m_bPlaying = true;                 //��Ϸ����״̬
	if (gameModel != 1)             //ֻҪ��������ģʽ���趨��ʱ��
		SetTimer(TimerOne, 1000, NULL);     //��ʱ����ÿ1s����һ��OnTimer()
	nRerank = 3;                    //���Ŵ�����Ϊ3��
	 //���á���ʼ��Ϸ����ť����
	CButton *pBtn = (CButton*)GetDlgItem(IDC_BTN_START);   //��ťָ��ָ��IDC_BTN_START�����ť 
	if (pBtn != NULL)
	{
		pBtn->EnableWindow(FALSE);  // True or False 
	}
}

/* ����ͣ/������Ϸ����ť�¼� */
void CGameDlg::OnBnClickedBtnStop()
{
	m_bPlaying = !m_bPlaying;     //��Ϸ״̬�л�
	CButton *pBtn = (CButton*)GetDlgItem(IDC_BTN_Stop);   //��ťָ��ָ��IDC_BTN_Stop�����ť 
	//������Ϸ״̬���ð�ť����ʾ���ı�
	if (m_bPlaying)
		pBtn->SetWindowTextW(_T("��ͣ��Ϸ"));
	else
		pBtn->SetWindowTextW(_T("������Ϸ"));
}

/* ����ʾ����ť�¼���Ѱ�ҿ����ӣ�������ʾ�����ʾ�� */
void CGameDlg::OnBnClickedBtnTip()
{
	if (!m_bPlaying)   //��Ϸ����ʱ����Ч
		return;
	Vertex avPath[PathLen];
	int nVexnum = 0;
	bool bSuc = m_GameC.Help(avPath, nVexnum);   
	if (bSuc == true)    	//�������������ʾ
	{
		extraTime -= 30;         //���򣺳ɹ�ʹ��һ����ʾʣ��ʱ���30s
		DrawTipLine(avPath, nVexnum);    // ����ʾ�ߣ�1�� 
		Sleep(300);     //��ͣ300ms������ҹ۲�
		UpdateMap();    //ˢ�µ�ͼ
		Sleep(300);     //��ͣ300ms������ҹ۲�
		DrawTipLine(avPath, nVexnum);    // ����ʾ�ߣ�2��
		Sleep(300);     //��ͣ300ms������ҹ۲�
		UpdateMap();    //ˢ�µ�ͼ
	}
	else
	{
		MessageBox(_T("Sorry,there are not links! \n May you have failured!"));   //������ʾ�Ҳ�����������ͼƬ
	}
}

/* �����š���ť�¼���ִ��ʣ���ͼԪ�ص����Ų�ˢ�µ�ͼ */
void CGameDlg::OnBnClickedBtnRerank()
{
	if (m_bPlaying && nRerank > 0)   //ֻ����Ϸ��ʼ�������Ŵ���ǰ���²�������
	{
		m_GameC.Rerank();   //���ŵ�ͼԪ��
		UpdateMap();		//ˢ�µ�ͼ
		nRerank--;          //���Ŵ�����1
		CButton *pBtn = (CButton*)GetDlgItem(IDC_BTN_Rerank);   //��ťָ��ָ��IDC_BTN_Rerank�����ť 
		CString rankStr;
		rankStr.Format(_T("�� �� %d"), nRerank);
		pBtn->SetWindowTextW(rankStr);    //���á����š���ť�ı�
	}
}

/*��ʱ���¼�����*/
void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (!m_bPlaying)    //�����Ϸ����ֹͣ״̬���򲻽��н���������
		return;
	int m_nStep = 1;      //����
	//extraTime = pProgCtrl->StepIt();		//ȡ�ø���ǰλ��,����ǰʣ��ʱ�� 
	extraTime -= m_nStep;         //ʣ��ʱ��ݼ�
	pProgCtrl->SetPos(extraTime);    //���½���λ��
	CString timeStr;              //ʣ��ʱ���ַ�������
	timeStr.Format(_T("ʣ��ʱ��:%ds"), extraTime);   //��ʽ���޸ľ�̬�ı�
	pStaticTime->SetWindowTextW(timeStr);       //���þ�̬�ı�����

	if (extraTime <= 0)
	{
		KillTimer(TimerOne);      //ж�ض�ʱ��
		CButton *pBtn = (CButton*)GetDlgItem(IDC_BTN_START);   //��ťָ��ָ��IDC_BTN_START�����ť 
		pBtn->EnableWindow(TRUE);    // "��ʼ��Ϸ"��ť��Ϊ����
		if (MessageBox(_T("There is no time! \n Please again."), _T("Failure"), MB_OK) == IDOK)   //����������ҳ�ʱ��
		{
			m_bPlaying = false;    //��Ϸ��Ϊֹͣ״̬
			level = 1;            //���ùؿ��ȼ�
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}

/* �ؿ�ģʽ����֧�� */
void CGameDlg::LevelModelSupt()
{
	// �ؿ��ı���ʾ����
	pStaticLevel->ShowWindow(SW_SHOW);    //��ʾ�ؿ���̬�ı�
	CString levelStr;            //�ؿ��ַ�������
	levelStr.Format(_T("�ؿ�:%d"), level);   //��ʽ���޸ľ�̬�ı�
	pStaticLevel->SetWindowTextW(levelStr);       //���þ�̬�ı�����

	// ���ݹؿ��趨��������ʾ����
	//���ݹؿ����ý�����ʱ��
	if (ProgCtrlMAX - level * 5 > 24)
		extraTime = ProgCtrlMAX - level * 5;
	else
		extraTime = 24;
	pProgCtrl->SetRange(0, extraTime);    //���ý�������Χ
	
	// ���ݹؿ��趨��Ϸ��ͼͼƬ����
	/*
	if (level == 1)
	{
		m_GameC.s_nRows = 5;
		m_GameC.s_nCols = 6;
		m_GameC.s_nPicNum = 3;
	}
	else if (level <= 9)
	{
		if (level % 2 == 1 || level % 4 == 0)
			m_GameC.s_nRows = 6 + level / 2;
		else
			m_GameC.s_nRows = 7 + level / 2;
		m_GameC.s_nCols = 6 + level;
		m_GameC.s_nPicNum = level + 6;
	}
	else if(level == 15)
	{
		m_GameC.s_nRows = 10;
		m_GameC.s_nCols = 16;
		m_GameC.s_nPicNum = 20;
	}
		//����Ĭ�ϼ���...
	*/
	if (level == 1 || level == 2)
		m_GameC.s_nPicNum = 2;
	else if (level >= 3 || level <= 5)
		m_GameC.s_nPicNum = 4;
	else if (level >= 6 || level <= 9)
		m_GameC.s_nPicNum = 8;
	else if (level >= 10 || level <= 12)
		m_GameC.s_nPicNum = 10;
	else if (level >= 13 || level <= 15)
		m_GameC.s_nPicNum = 16;
	else
		m_GameC.s_nPicNum = 20;
}

/* ����������ť�¼������������Ի��� */
void CGameDlg::OnBnClickedBtnHelp()
{
	//������ģ̬��ʾ���������Ի���
	CGameHelp gameHelpDlg;
	gameHelpDlg.DoModal();
}
