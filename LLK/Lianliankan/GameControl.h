#pragma once
#include "GameLogic.h"


/* ������Ϸ���ݣ�ͳһЭ���͵��ø��߼��������Ӧ�Ĺ��� */
class CGameControl
{
private:
	int** m_pGameMap;		// ��Ϸ��ͼ����ָ�� 
    CGameLogic m_GameLogic;  // ��Ϸ�߼���������
	int clearPic;           //��¼��������ͼƬ���������ж�ʤ��

	Vertex m_svSelFst;     // ѡ�еĵ�һ����
	Vertex m_svSelSec;     // ѡ�еĵڶ�����
public:
	static int s_nRows;    // ��Ϸ���� 
	static int s_nCols;    // ��Ϸ���� 
	static int s_nPicNum;  // ͼƬ��

	CGameControl();     //���캯��
	~CGameControl();    //�����������ͷŵ�ͼָ��
	void StartGame(void);   // ��ʼ��Ϸ 
	int GetElement(int nRow, int nCol);   // �õ�ĳһ��Ԫ��
	void Rerank();		//��ʣ��ͼƬԪ������
	void SetFirstPoint(int nRow, int nCol);     // ���õ�һ���� 
	void SetSecPoint(int nRow, int nCol);       // ���õڶ�����
	bool Link(Vertex *avPath, int &nVexnum);   // �����ж�(·���ݶ�Ϊ4������)
	bool SearchValidPath(Vertex *avPath, int &nVexnum); //Ѱ�ҿ����ӵ���Ч·��
	bool Help(Vertex *avPath, int &nVexnum);   //��Ϸ������ʾ
	bool IsWin(void);						  // �ж��Ƿ��ʤ
};
