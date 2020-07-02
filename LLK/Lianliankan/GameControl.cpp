
#include "stdafx.h"
#include "GameControl.h"


//��̬��Ա������ʼ��
int CGameControl::s_nRows = 10;
int CGameControl::s_nCols = 12;
int CGameControl::s_nPicNum = 20;

CGameControl::CGameControl()
{
	clearPic = 0;
}

CGameControl::~CGameControl()
{
	m_GameLogic.ReleaseMap(m_pGameMap);   //�ͷ���Ϸ��ͼ����ָ��
	//delete m_pGameMap; 
}

/*��ʼ��Ϸ*/
void CGameControl::StartGame(void)
{
	m_pGameMap = m_GameLogic.InitMap();    //��ʼ����Ϸ��ͼ

}

int CGameControl::GetElement(int nRow, int nCol)
{
	return m_pGameMap[nRow][nCol];   //������ϷͼƬ��
}

/* ���ŵ�ͼԪ�� */
void CGameControl::Rerank()
{
	m_GameLogic.RerankGraph(m_pGameMap);    //�Ե�ͼ�����������ţ������ص�ַ
}

/*���õ�һ��ѡ�еĵ���Ϣ*/
void CGameControl::SetFirstPoint(int nRow, int nCol)
{
	m_svSelFst.row = nRow;
	m_svSelFst.col = nCol;
	m_svSelFst.info = m_pGameMap[nRow][nCol];
}

/*���õڶ���ѡ�еĵ���Ϣ*/
void CGameControl::SetSecPoint(int nRow, int nCol)
{
	m_svSelSec.row = nRow;
	m_svSelSec.col = nCol;
	m_svSelSec.info = m_pGameMap[nRow][nCol];
}

/*�����ж�*/
bool CGameControl::Link(Vertex *avPath, int &nVexnum)
{
	// �ж��Ƿ�ͬһ��ͼƬ  
	if(m_svSelFst.row == m_svSelSec.row && m_svSelFst.col == m_svSelSec.col) 
	{  
		return false;  
	}  
	// �ж�ͼƬ�Ƿ���ͬ 
	if(m_pGameMap[m_svSelFst.row][m_svSelFst.col]!=m_pGameMap[m_svSelSec.row][m_svSelSec.col])
	{ 
		return false;  
	}  

	// �ж��Ƿ���ͨ 
	if (m_GameLogic.IsLink(m_pGameMap, m_svSelFst, m_svSelSec))
	{ 
		// ����ʵ�� 
		m_GameLogic.Clear(m_pGameMap, m_svSelFst, m_svSelSec);
		clearPic += 2;     //�Դ�����2��ͼƬ����������2
		// ����·��������  
		nVexnum = m_GameLogic.GetVexPath(avPath);
		return true;
	}
	return false;
}

/* Ѱ�ҿ����ӵ���Ч·�� */
bool CGameControl::SearchValidPath(Vertex *avPath, int &nVexnum)
{
	// �ж��Ƿ���ͨ 
	if (m_GameLogic.IsLink(m_pGameMap, m_svSelFst, m_svSelSec))
	{
		nVexnum = m_GameLogic.GetVexPath(avPath);	 // ����·��������  
		return true;
	}
	return false;
}

/* ����������Ԫ�أ������Ƿ����������ʾ */
bool CGameControl::Help(Vertex *avPath, int &nVexnum)
{
	int x1, y1, x2, y2;
	for(x1 = 0; x1 < s_nRows; x1++)
		for (y1 = 0; y1 < s_nCols; y1++)
		{
			if (m_pGameMap[x1][y1] != BLANK)
			{
				SetFirstPoint(x1, y1);			  //���õ�һ����
				for (x2 = x1; x2 < s_nRows; x2++)   //��������ʣ���ͼԪ�أ�Ѱ�ҵڶ�����
					for (y2 = y1+1; y2 < s_nCols; y2++)
					{
						if (m_pGameMap[x2][y2] == m_pGameMap[x1][y1])  //����������ͼƬ��ͬ
						{
							SetSecPoint(x2, y2);        //���õڶ�����
							if (SearchValidPath(avPath, nVexnum))   //���������ͨ
								return true;
						}
					}
			}
		}

	return false;   //ѭ����ɺ�û�ҵ�����������ͼƬ�򷵻�false������һ�������о�
}

/*����������ͼƬ���ж�ʤ��*/
bool CGameControl::IsWin(void)
{
	/*���������ͼƬ����ԭ��ͼƬ����ȣ����ж����ȡʤ���Ż���ÿ�α�����ά��ͼ���������ʱ�ո��Ӷ�*/
	if (clearPic == s_nRows*s_nCols)
	{
		clearPic = 0;   //���ü�������Ϊ��һ����׼��
		return true;
	}
	else
		return false;
}
