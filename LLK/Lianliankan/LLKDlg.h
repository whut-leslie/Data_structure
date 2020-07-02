
// LLKDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "GameDlg.h"

class CLianliankanDlgAutoProxy;


// CLLKDlg �Ի���
class CLLKDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLLKDlg);
	friend class CLianliankanDlgAutoProxy;

// ����
public:
	CLLKDlg(CWnd* pParent = NULL);	// ��׼���캯��
	virtual ~CLLKDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LIANLIANKAN_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	CLianliankanDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	HCURSOR OnQueryDragIcon();

	BOOL CanExit();

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnClose();
	virtual void OnCancel();
	DECLARE_MESSAGE_MAP();
	CDC m_dcMem;   // ��ʾ����λͼ�ڴ�
public:
	afx_msg void OnBnClickedBtnBasic();
	afx_msg void OnBnClickedBtnExit();
	afx_msg void OnBnClickedBtnSetting();
	afx_msg void OnBnClickedBtnHelp();
	afx_msg void OnBnClickedBtnRank();
	afx_msg void OnBnClickedBtnRelax();
	afx_msg void OnBnClickedBtnLevel();
private:
	CGameDlg *m_pGameDlg;    //��Ϸ�Ի���
	void InitBackground();     // ��ʼ�������ķ�������λͼѡ��λͼ�ڴ档 
	void UpdateWindow(void);  // ���½���
};