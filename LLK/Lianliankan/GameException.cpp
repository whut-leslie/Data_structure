#include "stdafx.h"
#include "CString"
#include "GameException.h"

CGameException::CGameException(wchar_t *excp)
{
	info.Format(excp);
	MessageBox(NULL, info, _T("Error!"), MB_OK | MB_ICONERROR);   //����쳣��Ϣ
}


CGameException::~CGameException()
{
	delete info;   //�ͷ�ָ��
}
