
// DlgProxy.h: ͷ�ļ�
//

#pragma once

class CLLKDlg;


// CLianliankanDlgAutoProxy ����Ŀ��

class CLianliankanDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CLianliankanDlgAutoProxy)

	CLianliankanDlgAutoProxy();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��

// ����
public:
	CLLKDlg* m_pDialog;

// ����
public:

// ��д
	public:
	virtual void OnFinalRelease();

// ʵ��
protected:
	virtual ~CLianliankanDlgAutoProxy();

	// ���ɵ���Ϣӳ�亯��

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CLianliankanDlgAutoProxy)

	// ���ɵ� OLE ����ӳ�亯��

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

