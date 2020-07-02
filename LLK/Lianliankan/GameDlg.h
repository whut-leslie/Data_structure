
#pragma once
#include "afxwin.h"
#include "GameControl.h"
#include "GameHelp.h"


// CGameDlg �Ի���

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(int gModel, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGameDlg();

	virtual void OnFinalRelease();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif

protected:
	HICON m_hIcon;       // �Ի���ͼ��
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg void OnPaint();        // WM_PAINT ��Ϣ���� 
	virtual BOOL OnInitDialog();   // ���ڳ�ʼ������ 
	void InitElement(void);        // ��ʼ��Ԫ��ͼƬ��DC
	void DrawTipFrame(int nRow, int nCol);   // ���ƾ�����ʾ��
	void DrawTipLine(Vertex asvPath[PathLen], int nVexnum);   //������ʾLine

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
private:
	CDC m_dcMem;         // �ڴ�DC
	CDC m_dcBG;          // ����DC
	CDC m_dcElement;     // Ԫ���ڴ�DC
	CDC m_dcMask;        // �����ڴ�DC
	CPoint m_ptGameTop;   // ��Ϸ����ʼ�㣨��Ϸ��һ��ͼƬ�Ķ�������, ��������ڴ��ڿͻ����� 
	CSize m_sizeElem;     // Ԫ��ͼƬ�Ĵ�С
	CRect m_rtGameRect;     // ��Ϸ�����С(������Ϊ��Ϸ���������С�����ǵ����滭���ߣ����ܻᳬ��ͼƬ����һ����Χ)
	CGameControl m_GameC;   // ��Ϸ���������
	CProgressCtrl *pProgCtrl;   //������ָ��
	CStatic *pStaticTime;       // "ʣ��ʱ��"��̬�ı�ָ��
	CStatic *pStaticLevel;      // "��ǰ�ؿ�"��̬�ı�ָ��
	bool m_bFirstPoint;     // �Ƿ��ǵ�һ��ѡ�еĵ�
	bool m_bPlaying;		// ��Ϸ״̬��ʶ
	int nRerank;			// ���Ŵ���
	int extraTime;          // ��Ϸʣ��ʱ��
	int gameModel;          // ��Ϸģʽλ��0=����ģʽ��1=����ģʽ��2=�ؿ�ģʽ
	int level;				//�ؿ��ȼ�

	void InitBackground();  // ��ʼ�����ڱ���
	void UpdateGameRect();     //������Ϸ���򱳾�
	void UpdateWindow();    // ���½���
	void UpdateMap();       // ������Ϸ��ͼ
	void LevelModelSupt();  // �ؿ�ģʽ����֧��
public:
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnClose();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnStop();
	afx_msg void OnBnClickedBtnTip();
	afx_msg void OnBnClickedBtnRerank();
	afx_msg void OnBnClickedBtnHelp();
};
