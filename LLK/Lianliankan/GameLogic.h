
#pragma once
#include "global.h"
#include "GameException.h"
#define PathLen 4

/*���ݲ�ͬ�����ݽṹ����������߼����жϹ���*/
class CGameLogic
{
private: 
	Vertex m_avPath[PathLen];  // �����ڽ��������ж�ʱ�������Ĺؼ�����
	int m_nVexNum;       // ������
protected:
	bool LinkInRow(int** pGameMap, Vertex v1, Vertex v2);	 // �жϺ����Ƿ���ͨ 
	bool LinkInCol(int** pGameMap, Vertex v1, Vertex v2);	 // �ж������Ƿ���ͨ

	bool LineX(int** pGameMap, int nRow, int nCol1, int nCol2);  // ֱ����ͨ X ��
	bool LineY(int** pGameMap, int nRow1, int nRow2, int nCol);  // ֱ����ͨ Y ��
	bool OneCornerLink(int** pGameMap, Vertex v1, Vertex v2);    // һ���յ�2������ͨ�ж�
	bool TwoCornerLink(int** pGameMap, Vertex v1, Vertex v2);    // 2���յ�3��ֱ�������ж�
	

	void PushVertex(Vertex v);		// ���һ��·������ 
	Vertex PopVertex();			    // ȡ��һ������
	void ClearStack();				// ���ջ
public:
	CGameLogic();
	~CGameLogic();
	int** InitMap();         // ��ʼ����Ϸ��ͼ 
	void ReleaseMap(int** &pGameMap);  // �ͷŵ�ͼ
	void RerankGraph(int** pGameMap);         //���ŵ�ͼԪ������

	bool IsLink(int** pGameMap, Vertex v1, Vertex v2);  // �ж��Ƿ���ͨ
	void Clear(int** pGameMap, Vertex v1, Vertex v2);   // ���� 

	int GetVexPath(Vertex avPath[PathLen]);		 // �õ�·�������ص��Ƕ�����
	//bool IsBlank(int** pGameMap);              // �ж�ͼ�ж����ǲ���ȫΪ�գ���Ҫ������ά��ͼ���飬Ч�ʵ�
};