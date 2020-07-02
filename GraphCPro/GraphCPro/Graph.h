#pragma once
#define MAX_VERTEX_NUM 20
//����ṹ��
struct Vex {
	int num;//������
	char name[20];//��������
	char desc[1024];//�������
};

//�߽ṹ��
struct Edge {
	int vex1;//�ߵĵ�һ������
	int vex2;//�ߵĵڶ�������
	int weight;//Ȩֵ
};

//��������PathList����������·��
typedef struct Path {
	int vex[20];//����һ��·��
	Path* next=nullptr;//��һ��·��
}*PathList;


class CGraph{
private:
	int m_aAdjMatrix[20][20];//�ڽӾ���
	Vex m_aVexs[20];//��������
	int m_nVexNum;//�������
public:
	void Init(void);//��ʼ��ͼ�ṹ
	int InsertVex(Vex sVex);//��������ӵ�����������
	int InsertEdge(Edge sEdge);//���߱��浽�ڽӾ�����
	Vex GetVex(int nVex);//��ѯָ��������Ϣ
	int FindEdge(int v, Edge aEdge[]);//��ѯ��ָ�����������ı�
	int GetVexnum();//��ȡ��ǰ������
	void DFSTraverse(int nVex,PathList &List);//��ñ������
	int FindShortPath(int nVexStart, int nVexEnd, Edge aPath[]);//��Ѱ����֮�����̾���
	int FindMinTree(Edge aPath[]);//������С������
	void DFS(int nVex, bool aVisited[], int& nIndex, PathList& List);//���������������ͼ

};