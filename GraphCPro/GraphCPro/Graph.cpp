#include "Graph.h"
#include <iostream>
using namespace std;
static int cnt = 0;//��¼�������·����
//��ͼ���г�ʼ��
void CGraph::Init(void) {
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
		for (int j = 0; j < MAX_VERTEX_NUM; j++)
			m_aAdjMatrix[i][j] = 0;//��ʼ��Ȩ��Ϊ0
	m_nVexNum = 0;//������Ϊ0
}

//��������ӵ�����������
int CGraph::InsertVex(Vex sVex) {
	if (m_nVexNum == MAX_VERTEX_NUM)
	{
		//��������
		return 0;
	}
	m_aVexs[m_nVexNum++] = sVex;//���붥����Ϣ
	return 1;
}

//���߱��浽������
int CGraph::InsertEdge(Edge sEdge) {
	if (sEdge.vex1 < 0 || sEdge.vex1 >= m_nVexNum || sEdge.vex2 < 0 || sEdge.vex2 >= m_nVexNum)
	{//�±�Խ��
		return 0;
	}
	//����ߵ���Ϣ
	m_aAdjMatrix[sEdge.vex1][sEdge.vex2] = sEdge.weight;
	m_aAdjMatrix[sEdge.vex2][sEdge.vex1] = sEdge.weight;
	return 1;
}

//��ѯ������Ϣ
Vex CGraph::GetVex(int nVex)//��ѯָ��������Ϣ
{
	return m_aVexs[nVex];
}

//��ѯ�붥�������ı�
int CGraph::FindEdge(int nVex, Edge aEdge[])
{
	int k = 0;
	for (int i = 0; i < m_nVexNum; i++)
	{
		//�õ������Ϣ
		if (m_aAdjMatrix[m_nVexNum][i] != 0)
		{
			aEdge[k].vex1 = nVex;
			aEdge[k].vex2 = i;
			aEdge[k].weight = m_aAdjMatrix[nVex][i];
			k++;
		}
	}
	return k;
}

//��ȡ��ǰ������
int CGraph::GetVexnum()
{
	return m_nVexNum;

}

//��������ı�ŵõ����ʽ��
void CGraph::DFSTraverse(int nVex, PathList& List)
{
	int nIndex = 0;
	bool aVisited[MAX_VERTEX_NUM] = { false };//�����ʱ�־����Ϊδ����״̬
	DFS(nVex, aVisited, nIndex, List);

}
//���ݵϽ���˹�������·��
int CGraph::FindShortPath(int nVexStart, int nVexEnd, Edge aPath[])
{
	int nShortPath[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//���·��
	int nShortDistance[MAX_VERTEX_NUM];//��̾���
	bool bVisited[MAX_VERTEX_NUM];//�ж�ĳ�����Ƿ��Ѿ����뵽���·����
	int v;//��ʾÿһ���ҵ��Ŀ��Լ��뼯�ϵĶ��㣬���Ѿ��ҵ��˴���㵽�ö�������·��
	//��ʼ����̾���������ľ���
	for (int v = 0; v < m_nVexNum; v++)
	{
		//���øõ��״̬
		bVisited[v] = false;
		if (m_aAdjMatrix[nVexStart][v] != 0)
		{
			nShortDistance[v] = m_aAdjMatrix[nVexStart][v];//�бߵ�ʱ������Ϊ�ߵĳ���
		}
		else
		{
			nShortDistance[v] = INT_MAX;//�ޱߵ�ʱ������Ϊ�������
		}
		nShortPath[v][0] = nVexStart;//���ΪNVexStart
		//��ʼ�����·��
		for (int w = 1; w < m_nVexNum; w++)
		{
			nShortPath[v][w] = -1;
		}
	}
	//��ʼ������nVexStart������뵽������
	bVisited[nVexStart] = true;
	int min;//·����Сֵ
	for (int i = 0; i < m_nVexNum; i++)
	{
		min = 0x7FFFFFFF;
		bool badd = false;//�ж��Ƿ��ж�����Լ���
		for (int w = 0; w < m_nVexNum; w++)
		{
			if (!bVisited[w] && nShortDistance[w] < min)
			{
				v = w;//w�������nVexStart�������
				min = nShortDistance[w];//w��nVexStart����̾���Ϊmin
				badd = true;
			}
		}
		//��û�ж�����Լ��뼯�ϣ�������ѭ��
		if (!badd)break;
		bVisited[v] = true;//��w������뵽����
		nShortPath[v][i] = v;//ÿ���ҵ����·���󣬾��൱�ڴ�ԭ��������յ�
		for (int w = 0; w < m_nVexNum; w++)
		{
			//��w��Ϊ���ɶ���������
			if (!bVisited[w] && (min + m_aAdjMatrix[v][w] < nShortDistance[w]) && (m_aAdjMatrix[v][w] > 0))
			{
				//���µ�ǰ���·��������
				nShortDistance[w] = min + m_aAdjMatrix[v][w];
				for (int i = 0; i < m_nVexNum; i++) {
					//���ͨ��w�ﵽ����i�ľ���Ƚ϶̣���w�����·�����Ƹ�i
					nShortPath[w][i] = nShortPath[v][i];
				}
			}
		}
	}
	int nIndex = 0;
	int nVex1 = nVexStart;
	//�����·������Ϊ�ߵĽṹ������
	for (int i = 1; i < m_nVexNum; i++)
	{
		if (nShortPath[nVexEnd][i] != -1)
		{
			aPath[nIndex].vex1 = nVex1;
			aPath[nIndex].vex2 = nShortPath[nVexEnd][i];
			aPath[nIndex].weight = m_aAdjMatrix[nVex1][aPath[nIndex].vex2];
			nVex1 = nShortPath[nVexEnd][i];
			nIndex++;
		}
	}

	return nIndex;
}
int CGraph::FindMinTree(Edge aPath[]) 
{
	int lowcost[MAX_VERTEX_NUM] = { 0 };	//��̾���
	bool addVexNew[MAX_VERTEX_NUM] = { true };//�ѻ����̾���ĵ�
	int prev[MAX_VERTEX_NUM] = { 0 };		//֮ǰ��
	int length = 0;
	//��ʼ�����鲢Ĭ����ʼ����Ϊ0��
	for (int i = 1; i < m_nVexNum; i++)
	{
		if (m_aAdjMatrix[0][i] != 0)
			lowcost[i] = m_aAdjMatrix[0][i];
		else
			lowcost[i] = INT_MAX;
		addVexNew[i] = false;
	}
	for (int p = 0; p < m_nVexNum - 1; p++)
	{
		int min = INT_MAX;
		int v = 0;
		for (int i = 1; i < m_nVexNum; i++)
		{
			if ((!addVexNew[i]) && lowcost[i] < min)
			{
				min = lowcost[i];
				v = i;
			}
		}
		if (v != 0)
		{
			//����·����Ϣ
			aPath[p].vex1 = prev[v];
			aPath[p].vex2 = v;
			aPath[p].weight = lowcost[v];
			addVexNew[v] = true;                                      //��v��Vnew��
			length += lowcost[v];                             //����·������֮��
			for (int i = 0; i < m_nVexNum; i++)
			{
				if ((!addVexNew[i]) && (m_aAdjMatrix[v][i] < lowcost[i]) && (m_aAdjMatrix[i][v] != 0))
				{
					lowcost[i] = m_aAdjMatrix[v][i];                     //��ʱv�����Vnew ��Ҫ����lowcost
					prev[i] = v;										//�洢��һ����
				}
			}
		}
	}
	return length;

}

void CGraph::DFS(int nVex, bool aVisited[], int& nIndex, PathList& List)
{//�Ľ���ͼ��������ȱ����㷨
	aVisited[nVex] = true;				//��Ϊ�ѷ���
	List->vex[nIndex++] = nVex;		//���ʶ���nVex����ֵ������Ȼ������ֵ�Լ�
	if (nIndex == m_nVexNum)
	{
		//�����ǰ����������·��
		cout << "·��" << ++cnt << ":";
		for (int i = 0; i < this->GetVexnum(); i++) {
			cout << this->GetVex(List->vex[i]).name;
			if (i < this->GetVexnum() - 1)
				cout << "->";
		}
		cout << endl;
	}
	else
	{
		for (int i = 0; i < m_nVexNum; i++)
		{
			if ((m_aAdjMatrix[nVex][i] != 0) && (!aVisited[i]))
			{
				DFS(i, aVisited, nIndex, List);
				aVisited[i] = false;		//�˻���һ����ָ�֮ǰ��Ϣ
				nIndex--;
			}
		}
	}
}