// GameHelp.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Lianliankan.h"
#include "GameHelp.h"
#include "afxdialogex.h"


// CGameHelp �Ի���

IMPLEMENT_DYNAMIC(CGameHelp, CDialogEx)

CGameHelp::CGameHelp(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_Help_DIALOG, pParent)
{

	EnableAutomation();

}

CGameHelp::~CGameHelp()
{
}

void CGameHelp::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CDialogEx::OnFinalRelease();
}

void CGameHelp::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGameHelp, CDialogEx)

END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CGameHelp, CDialogEx)
END_DISPATCH_MAP()

// ע��: ������� IID_IGameHelp ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {8D810658-D053-4FF9-AA10-AE6AEE92AC9F}
static const IID IID_IGameHelp =
{ 0x8D810658, 0xD053, 0x4FF9, { 0xAA, 0x10, 0xAE, 0x6A, 0xEE, 0x92, 0xAC, 0x9F } };

BEGIN_INTERFACE_MAP(CGameHelp, CDialogEx)
	INTERFACE_PART(CGameHelp, IID_IGameHelp, Dispatch)
END_INTERFACE_MAP()


// CGameHelp ��Ϣ�������

