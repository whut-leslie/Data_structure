
// DlgProxy.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Lianliankan.h"
#include "DlgProxy.h"
#include "LLKDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLianliankanDlgAutoProxy

IMPLEMENT_DYNCREATE(CLianliankanDlgAutoProxy, CCmdTarget)

CLianliankanDlgAutoProxy::CLianliankanDlgAutoProxy()
{
	EnableAutomation();
	
	// ΪʹӦ�ó������Զ��������ڻ״̬ʱһֱ���� 
	//	���У����캯������ AfxOleLockApp��
	AfxOleLockApp();

	// ͨ��Ӧ�ó����������ָ��
	//  �����ʶԻ���  ���ô�����ڲ�ָ��
	//  ָ��Ի��򣬲����öԻ���ĺ���ָ��ָ��
	//  �ô���
	ASSERT_VALID(AfxGetApp()->m_pMainWnd);
	if (AfxGetApp()->m_pMainWnd)
	{
		ASSERT_KINDOF(CLLKDlg, AfxGetApp()->m_pMainWnd);
		if (AfxGetApp()->m_pMainWnd->IsKindOf(RUNTIME_CLASS(CLLKDlg)))
		{
			m_pDialog = reinterpret_cast<CLLKDlg*>(AfxGetApp()->m_pMainWnd);
			m_pDialog->m_pAutoProxy = this;
		}
	}
}

CLianliankanDlgAutoProxy::~CLianliankanDlgAutoProxy()
{
	// Ϊ������ OLE �Զ����������ж������ֹӦ�ó���
	//	������������ AfxOleUnlockApp��
	//  ���������������⣬�⻹���������Ի���
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CLianliankanDlgAutoProxy::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CLianliankanDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CLianliankanDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// ע��: ��������˶� IID_ILianliankan ��֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {2FFE508F-46E5-49AC-AFCE-245C24812F75}
static const IID IID_ILianliankan =
{ 0x2FFE508F, 0x46E5, 0x49AC, { 0xAF, 0xCE, 0x24, 0x5C, 0x24, 0x81, 0x2F, 0x75 } };

BEGIN_INTERFACE_MAP(CLianliankanDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CLianliankanDlgAutoProxy, IID_ILianliankan, Dispatch)
END_INTERFACE_MAP()

// IMPLEMENT_OLECREATE2 ���ڴ���Ŀ�� StdAfx.h �ж���
// {BDC3A4DA-E97E-49F0-9184-F8A386CFBF52}
IMPLEMENT_OLECREATE2(CLianliankanDlgAutoProxy, "Lianliankan.Application", 0xbdc3a4da, 0xe97e, 0x49f0, 0x91, 0x84, 0xf8, 0xa3, 0x86, 0xcf, 0xbf, 0x52)


// CLianliankanDlgAutoProxy ��Ϣ�������
