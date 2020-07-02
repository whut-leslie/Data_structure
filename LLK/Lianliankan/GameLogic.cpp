
#include "stdafx.h"
#include "GameLogic.h"
#include "GameControl.h"

CGameLogic::CGameLogic()
{
	m_nVexNum = 0;
}


CGameLogic::~CGameLogic()
{
}

/* ��ʼ����Ϸ��ͼ */
int** CGameLogic::InitMap()
{
	// ��ȡ��ͼ��С�ͻ�ɫ  
	int nRows = CGameControl::s_nRows; 
	int nCols = CGameControl::s_nCols;  
	int nPicNum = CGameControl::s_nPicNum; 

	// ��Ϸ��ͼ�����ڴ�ռ�   
	int** pGameMap = new int*[nRows + 2];  
	if(NULL == pGameMap)  
	{   
		throw new CGameException(_T("�ڴ�����쳣��"));  
	} 
	else  
	{
		for (int i = 0; i < nRows + 2; i++)   
		{    
			pGameMap[i] = new int[nCols + 2]; 
			if(NULL == pGameMap) 
			{     
				throw new CGameException(_T("�ڴ�����쳣��"));   
			}   
			memset(pGameMap[i], BLANK, sizeof(int) * (nCols + 2));  //��ʼ������ΪBLANK(-1)
		}  
	}
	
	// ���ٻ�ɫ, ���ݻ�ɫ����������ÿ�ֻ�ɫ��ͼƬ��ƽ�����������θ����鸳ֵ��   
	if ((nRows * nCols) % (nPicNum * 2) != 0)  
	{  
		ReleaseMap(pGameMap);   
		throw new CGameException(_T("��Ϸ��ɫ����Ϸ��ͼ��С��ƥ�䣡"));
	}  
	int nRepeatNum = nRows * nCols / nPicNum;
	int nCount = 0; 
	for(int i = 0; i < nPicNum; i++) 
	{   
		for(int j = 0; j < nRepeatNum; j++)  // �ظ���
		{    
			pGameMap[nCount / nCols + 1][nCount % nCols + 1] = i;   
			nCount++; 
		}
	} 

	/* ����ҵ�����λ�õ�ͼƬ�����н��� */

	srand((int)time(NULL));   // ��������  

	// ������⽻����������  
	int nVertexNum = nRows * nCols;  
	for(int i = 0; i < nVertexNum; i++)  
	{  
		// ����õ���������  
		int nIndex1 = rand() % nVertexNum; 
	    int nIndex2 = rand() % nVertexNum;

		// ����������ֵ   
		int nTmp = pGameMap[nIndex1 / nCols + 1][nIndex1 % nCols + 1];   
		pGameMap[nIndex1 / nCols + 1][nIndex1 % nCols + 1] = pGameMap[nIndex2 / nCols + 1][nIndex2 % nCols + 1];  
		pGameMap[nIndex2 / nCols + 1][nIndex2 % nCols + 1] = nTmp;  
	} 

	return pGameMap;
}

/* �ͷ���Ϸ��ͼָ�� */
void CGameLogic::ReleaseMap(int**& pGameMap)
{ 
	for (int i = 0; i < CGameControl::s_nRows + 2; i++) 
	{ 
			delete[] pGameMap[i]; 
	} 
	delete[] pGameMap;
	
	//delete pGameMap;
}

/* ������Ϸ��ͼ���ݣ��������������ǿյĵ�ͼԪ��100�� */
void CGameLogic::RerankGraph(int** pGameMap)
{
	// ��ȡ��ͼ��С
	int nRows = CGameControl::s_nRows;
	int nCols = CGameControl::s_nCols;

	/* ����ҵ�����λ�õ�ͼƬ�����н��� */

	srand((int)time(NULL));   // ��������  

	// ������⽻����������  
	int nVertexNum = nRows * nCols;
	for (int i = 0; i < 100; i++)     //����100��
	{
		int x1, y1, x2, y2;     //x,y����
	
		//�������2����ͼԪ������
		int nIndex1 = rand() % nVertexNum;
		int nIndex2 = rand() % nVertexNum;
		x1 = nIndex1 / nCols + 1; y1 = nIndex1 % nCols + 1;
		x2 = nIndex2 / nCols + 1; y2 = nIndex2 % nCols + 1;

		int nTmp = pGameMap[x1][y1];
		pGameMap[x1][y1] = pGameMap[x2][y2];
		pGameMap[x2][y2] = nTmp;
	}
}

/*�ؼ�����ջ*/
void CGameLogic::PushVertex(Vertex v)
{
	if(m_nVexNum <= PathLen)
		m_avPath[m_nVexNum++] = v;
}

/*�ؼ����ջ*/
Vertex CGameLogic::PopVertex()
{
	Vertex retPop = { BLANK,BLANK,BLANK };
	if (m_nVexNum > 0)
	{
		retPop = m_avPath[m_nVexNum];
		m_avPath[m_nVexNum--] = { BLANK,BLANK,BLANK };
	}
	return retPop;
}

/*���ջ*/
void CGameLogic::ClearStack()
{
	for (; m_nVexNum > 0; m_nVexNum--)
	{
		m_avPath[m_nVexNum - 1] = { BLANK,BLANK,BLANK };
	}
}

/* �к���ͬʱ���жϺ����Ƿ���ͨ
 * �㷨���� nCol1 + 1 ������ nCol2���ж�����ֱ�����Ƿ�Ϊ�հ��������ȫΪ�հ������������ͨ��
*/
bool CGameLogic::LinkInRow(int **pGameMap, Vertex v1, Vertex v2)
{
	int nCol1 = v1.col; 
	int nCol2 = v2.col; 
	int nRow = v1.row;
	//�����Ԫ�ش��ڱ�Ե�У������ֱ�������������ж��Ƿ����ֱͨ
	//if (nRow == 0 || nRow == CGameControl::s_nRows-1)
		//return true;
	//��֤ nCol1 ��ֵС�� nCol2 
	if(nCol1 > nCol2) 
	{   //���ݽ���   
		int nTemp = nCol1;   
		nCol1 = nCol2;  
		nCol2 = nTemp; 
	} 
	 //ֱͨ   
	for(int i = nCol1 + 1; i <= nCol2; i++)  
	{  
		if(i == nCol2) 
			return true;  
		if(pGameMap[nRow][i] != BLANK)  
			break;  
	}
	return false;
}

/* �к���ͬʱ���ж��ܷ�������ͨ
 * �㷨���� nRow1 + 1 ������ nRow2���ж�����ֱ�����Ƿ�ȫΪ�հ��������ȫΪ�հ� ������������ͨ�� 
 */
bool CGameLogic::LinkInCol(int** pGameMap, Vertex v1, Vertex v2)
{
	int nRow1 = v1.row;
	int nRow2 = v2.row; 
	int nCol = v1.col; 
	//�����Ԫ�ش��ڱ�Ե�У������ֱ�������������ж��Ƿ����ֱͨ
	//if (nCol == 0 || nCol == CGameControl::s_nCols-1)
		//return true;
	//��֤nRow1��ֵС��nRow2
	if (nRow1 > nRow2)
	{ 
		int nTemp = nRow1;  
		nRow1 = nRow2;  
		nRow2 = nTemp; 
	} 
	//ֱͨ  
	for(int i = nRow1+1; i <= nRow2; i++)
	{   
		if(i == nRow2)  
			return true;
		if(pGameMap[i][nCol] != BLANK)
			break;  
	} 
	return false;
}

/*�жϺ����Ƿ���ͨ*/
bool CGameLogic::LineX(int** pGameMap, int nRow, int nCol1, int nCol2)
{
	//��֤ nCol1 ��ֵС�� nCol2 
	if (nCol1 > nCol2)
	{   //���ݽ���   
		int nTemp = nCol1;
		nCol1 = nCol2;
		nCol2 = nTemp;
	}
	//ֱͨ   
	for (int i = nCol1 + 1; i <= nCol2; i++)
	{
		if (i == nCol2)
			return true;
		if (pGameMap[nRow][i] != BLANK)
			break;
	}
	return false;
}

bool CGameLogic::LineY(int** pGameMap, int nRow1, int nRow2, int nCol)
{
	//��֤ nRow1 ��ֵС�� nRow2 
	if (nRow1 > nRow2)
	{
		int nTemp = nRow1;
		nRow1 = nRow2;
		nRow2 = nTemp;
	}
	//ֱͨ  
	for (int i = nRow1 + 1; i <= nRow2; i++)
	{
		if (i == nRow2)
			return true;
		if (pGameMap[i][nCol] != BLANK)
			break;
	}
	return false;
}

/*һ���յ㣬2����ʵ�����ж�*/
bool CGameLogic::OneCornerLink(int** pGameMap, Vertex v1, Vertex v2)
{
	// ֱ���ܹ����ӣ���ô����һ��������������к����ཻ�ĵ㣬ֻ����������Ϊ�գ����п���ʵ�ֶ���ֱ������ 
	if (pGameMap[v1.row][v2.col] == BLANK)
	{ 
		if (LineY(pGameMap, v1.row, v2.row, v2.col) && LineX(pGameMap, v1.row, v1.col, v2.col))
		{
			Vertex v = { v1.row, v2.col, BLANK };   
			PushVertex(v);   
			return true; 
		}
	}    
	if (pGameMap[v2.row][v1.col] == BLANK)
	{
		if (LineY(pGameMap, v1.row, v2.row, v1.col) && LineX(pGameMap, v2.row, v1.col, v2.col))
		{
			Vertex v = { v2.row, v1.col, BLANK };  
			PushVertex(v);  
			return true;
		}
	}
	return false;
}

/*2���յ㣬3���������ж�*/
bool CGameLogic::TwoCornerLink(int** pGameMap, Vertex v1, Vertex v2)
{
	for (int nCol = 0; nCol < CGameControl::s_nCols + 2; nCol++)
	{
		// �ҵ�һ���� Y ��ƽ�е���ͨ�߶�  
		if (pGameMap[v1.row][nCol] == BLANK && pGameMap[v2.row][nCol] == BLANK)
		{
			if (LineY(pGameMap, v1.row, v2.row, nCol))
			{
				if (LineX(pGameMap, v1.row, v1.col, nCol) && LineX(pGameMap, v2.row, v2.col, nCol))
				{
					// ����ڵ�     
					Vertex vx1 = { v1.row, nCol, BLANK };
					Vertex vx2 = { v2.row, nCol, BLANK };
					PushVertex(vx1);
					PushVertex(vx2);
					return true;
				}
			}
		}
	}
	for (int nRow = 0; nRow < CGameControl::s_nRows + 2; nRow++)
	{  
		// �ҵ�һ���� X ��ƽ�е���ͨ�߶�  
		if(pGameMap[nRow][v1.col] == BLANK && pGameMap[nRow][v2.col] == BLANK)  
		{ 
			if(LineX(pGameMap, nRow, v1.col, v2.col))  
			{  
				if(LineY(pGameMap, nRow, v1.row, v1.col) && LineY(pGameMap, nRow, v2.row, v2.col)) 
				{   
					// ����ڵ�      
					Vertex vx1 = { nRow, v1.col, BLANK };
					Vertex vx2 = { nRow, v2.col, BLANK };
					PushVertex(vx1);    
					PushVertex(vx2);    
					return true;    
				}  
			}  
		} 
	} 
	return false;
}

/* �ж��Ƿ�������� */
bool CGameLogic::IsLink(int** pGameMap, Vertex v1, Vertex v2)
{
	ClearStack();	// ���ջ
	PushVertex(v1);

	bool isLink = false;
	if (v1.row == v2.row)
	{
		if (LinkInRow(pGameMap, v1, v2))  // X ֱ����ʽ  
			isLink = true;
		else if (TwoCornerLink(pGameMap, v1, v2))
			isLink = true;
	}
	else if (v1.col == v2.col)  // Y ֱ����ʽ 
	{
		if (LinkInCol(pGameMap, v1, v2))
			isLink = true;
		else if (TwoCornerLink(pGameMap, v1, v2))
			isLink = true;
	}
	else if (OneCornerLink(pGameMap, v1, v2))   //һ�յ㣬2����
	{
		isLink = true;
	}
	else if (TwoCornerLink(pGameMap, v1, v2))   //2�յ㣬3����
	{
		isLink = true;
	}
	PushVertex(v2);
	return isLink;
}

/* ���ӣ�����ͼ�����Ӧ����ΪBLANK��-1��*/
void CGameLogic::Clear(int** pGameMap, Vertex v1, Vertex v2)
{
	pGameMap[v1.row][v1.col] = BLANK;
	pGameMap[v2.row][v2.col] = BLANK;
}

/* ��ȡ����·����ͨ����������·����ͨ������ֵ����������ʵ��Ԫ�ظ��� */
int CGameLogic::GetVexPath(Vertex avPath[PathLen])
{
	for (int i = 0; i < m_nVexNum; i++)
	{
		avPath[i] = m_avPath[i];
	}
	return m_nVexNum;
}
