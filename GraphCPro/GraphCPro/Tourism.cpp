#include "Tourism.h"
#include "Graph.h"
#include<fstream>
#include<string>
using namespace std;
static CGraph m_Graph;
void CreateGraph()//��ȡ�ļ���������������ͼ
{
	cout << "======= ������������ͼ ======" << endl;
	char buffer[20];
	fstream inVex;
	inVex.open("Vex.txt", ios::in);		//��Vex�ĵ�
	fstream inEdge;
	inEdge.open("Edge.txt", ios::in);	//��Edge�ĵ�
	inVex.getline(buffer, 3, '\n');		//�����һ�ж�����
	int vexNum = atoi(buffer);
	cout << "��Ŀ��������" << vexNum << endl;
	Vex vex;
	m_Graph.Init();
	cout << "----- ���� -----" << endl;
	for (int i = 0; i < vexNum; i++)
	{
		inVex.getline(buffer, 3, '\n');		//���붥����
		vex.num = atoi(buffer);
		inVex.getline(vex.name, 20, '\n');	//���붥����
		inVex.getline(vex.desc, 1024, '\n');//���붥������
		m_Graph.InsertVex(vex);				//���붥��
		cout << vex.num << "-" << vex.name << endl;
	}
	Edge edge;
	cout << "----- �� -----" << endl;
	while (inEdge.good())
	{
		inEdge.getline(buffer, sizeof(buffer), '\n');//�������Ϣ
		char* p;
		char* buf;
		p=strtok_s(buffer, " \n", &buf);
		edge.vex1 = atoi(p);				//�����һ������
		p = strtok_s(NULL, " \n",&buf);
		edge.vex2 = atoi(p);				//����ڶ�������
		p = strtok_s(NULL, " \n", &buf);
		edge.weight = atoi(p);				//����Ȩ��
		m_Graph.InsertEdge(edge);			//�����
		cout << "<v" << edge.vex1 << ",v" << edge.vex2 << "> " << edge.weight << endl;
	}
	inVex.close();							//�ر���
	inEdge.close();
}
void GetSpotInfo()//��ѯָ��������Ϣ����ʾ�����ھ���ľ���
{
	cout << "=======��ѯ������Ϣ=======" << endl;
	//��ʾ�����б�
	int vexNum = m_Graph.GetVexnum();
	for (int i = 0; i < vexNum; i++) {
		Vex sVex = m_Graph.GetVex(i);
		cout << sVex.num << "--" << sVex.name << endl;
	}
	//��ѯ����
	cout << "��������Ҫ��ѯ�ľ����ţ�";
	int nVex = 0;
	cin >> nVex;
	if (nVex < 0 || nVex >= vexNum) {
		cout << "�������" << endl;
		return;
	}

	Vex sVex = m_Graph.GetVex(nVex);
	cout << "**���**" << endl;
	cout << sVex.name << endl;
	cout << sVex.desc << endl;
	Edge sEdge[20];

	//��ѯ��������
	cout << endl << "**��Χ����**" << endl;
	//����붥����صı�
	int nEdgNum = m_Graph.FindEdge(nVex, sEdge);
	for (int i = 0; i < nEdgNum; i++)
	{
		Vex v1 = m_Graph.GetVex(sEdge[i].vex1);
		Vex v2 = m_Graph.GetVex(sEdge[i].vex2);
		cout << v1.name << "->" << v2.name << " " << sEdge[i].weight << endl << endl;
	}

}
void TravelPath()//��ѯ���ξ���
{
	cout << "=======���ξ��㵼��=======" << endl;

	//��ʾ�����б�
	Vex vex;
	//���ÿ��������Ϣ�����
	for (int i = 0; i < m_Graph.GetVexnum(); i++)
	{
		vex = m_Graph.GetVex(i);
		cout << vex.num << "-" << vex.name << endl;
	}
	cout << "��������ʼ���ţ�";
	int beginNum;
	cin >> beginNum;
	PathList pList = (PathList)malloc(sizeof(Path));
	cout << "����·��Ϊ��" << endl;
	m_Graph.DFSTraverse(beginNum, pList);
}
void FindShortPath()//�����������������·��
{
	cout << "==========�������·��==========" << endl;
	//��Ӧ��ϵ��ʾ	
	for (int i = 0; i < m_Graph.GetVexnum(); i++)
	{
		Vex sVex = m_Graph.GetVex(i);
		cout << i << "-" << sVex.name << endl;
	}

	int start_place, end_place;
	cout << "���������ı�ţ�";
	cin >> start_place;
	cout << "�������յ�ı�ţ�";
	cin >> end_place;

	Edge aPath[20];						//����Ϣ���飬���α�����̵�·��

	//�������·�����������·��������index��ֵ
	int index = m_Graph.FindShortPath(start_place, end_place, aPath);
	int length = 0;						//���·���ܳ���
	Vex sVex = m_Graph.GetVex(aPath[0].vex1);	//������Ϣ��������Ϣ��

	//�����·���������ʾ
	cout << "���·��Ϊ��" << sVex.name;
	for (int i = 0; i < index; i++) {
		sVex = m_Graph.GetVex(aPath[i].vex2);
		cout << "->" << sVex.name;
		length += aPath[i].weight;
	}
	cout << endl;
	cout << "��̾���Ϊ��" << length << endl << endl;

}
void DesignPath()//��ѯ�����·�滮ͼ
{
	cout << "==========�����·�滮==========" << endl;
	Edge aPath[20];
	int length = m_Graph.FindMinTree(aPath);
	cout << "��������������֮�������·��" << endl;
	for (int i = 0; i < m_Graph.GetVexnum() - 1; i++)
	{
		Vex nVex1 = m_Graph.GetVex(aPath[i].vex1);
		Vex nVex2 = m_Graph.GetVex(aPath[i].vex2);
		cout << nVex1.name << "-" << nVex2.name << "    " << aPath[i].weight << "m" << endl;
	}
	cout << "�����·���ܳ����ǣ�" << length << "m" << endl;

}