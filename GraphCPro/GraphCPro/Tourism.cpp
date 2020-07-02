#include "Tourism.h"
#include "Graph.h"
#include<fstream>
#include<string>
using namespace std;
static CGraph m_Graph;
void CreateGraph()//读取文件，创建景区景点图
{
	cout << "======= 创建景区景点图 ======" << endl;
	char buffer[20];
	fstream inVex;
	inVex.open("Vex.txt", ios::in);		//打开Vex文档
	fstream inEdge;
	inEdge.open("Edge.txt", ios::in);	//打开Edge文档
	inVex.getline(buffer, 3, '\n');		//读入第一行顶点数
	int vexNum = atoi(buffer);
	cout << "项目顶点数：" << vexNum << endl;
	Vex vex;
	m_Graph.Init();
	cout << "----- 顶点 -----" << endl;
	for (int i = 0; i < vexNum; i++)
	{
		inVex.getline(buffer, 3, '\n');		//读入顶点编号
		vex.num = atoi(buffer);
		inVex.getline(vex.name, 20, '\n');	//读入顶点名
		inVex.getline(vex.desc, 1024, '\n');//读入顶点描述
		m_Graph.InsertVex(vex);				//插入顶点
		cout << vex.num << "-" << vex.name << endl;
	}
	Edge edge;
	cout << "----- 边 -----" << endl;
	while (inEdge.good())
	{
		inEdge.getline(buffer, sizeof(buffer), '\n');//读入边信息
		char* p;
		char* buf;
		p=strtok_s(buffer, " \n", &buf);
		edge.vex1 = atoi(p);				//读入第一个顶点
		p = strtok_s(NULL, " \n",&buf);
		edge.vex2 = atoi(p);				//读入第二个顶点
		p = strtok_s(NULL, " \n", &buf);
		edge.weight = atoi(p);				//读入权重
		m_Graph.InsertEdge(edge);			//插入边
		cout << "<v" << edge.vex1 << ",v" << edge.vex2 << "> " << edge.weight << endl;
	}
	inVex.close();							//关闭流
	inEdge.close();
}
void GetSpotInfo()//查询指定景点信息，显示到相邻景点的距离
{
	cout << "=======查询景点信息=======" << endl;
	//显示景点列表
	int vexNum = m_Graph.GetVexnum();
	for (int i = 0; i < vexNum; i++) {
		Vex sVex = m_Graph.GetVex(i);
		cout << sVex.num << "--" << sVex.name << endl;
	}
	//查询景点
	cout << "请输入您要查询的景点编号：";
	int nVex = 0;
	cin >> nVex;
	if (nVex < 0 || nVex >= vexNum) {
		cout << "输入错误" << endl;
		return;
	}

	Vex sVex = m_Graph.GetVex(nVex);
	cout << "**简介**" << endl;
	cout << sVex.name << endl;
	cout << sVex.desc << endl;
	Edge sEdge[20];

	//查询附近景点
	cout << endl << "**周围景点**" << endl;
	//获得与顶点相关的边
	int nEdgNum = m_Graph.FindEdge(nVex, sEdge);
	for (int i = 0; i < nEdgNum; i++)
	{
		Vex v1 = m_Graph.GetVex(sEdge[i].vex1);
		Vex v2 = m_Graph.GetVex(sEdge[i].vex2);
		cout << v1.name << "->" << v2.name << " " << sEdge[i].weight << endl << endl;
	}

}
void TravelPath()//查询旅游景点
{
	cout << "=======旅游景点导航=======" << endl;

	//显示景点列表
	Vex vex;
	//获得每个顶点信息并输出
	for (int i = 0; i < m_Graph.GetVexnum(); i++)
	{
		vex = m_Graph.GetVex(i);
		cout << vex.num << "-" << vex.name << endl;
	}
	cout << "请输入起始点编号：";
	int beginNum;
	cin >> beginNum;
	PathList pList = (PathList)malloc(sizeof(Path));
	cout << "导游路线为：" << endl;
	m_Graph.DFSTraverse(beginNum, pList);
}
void FindShortPath()//搜索两个景点间的最短路径
{
	cout << "==========搜索最短路径==========" << endl;
	//对应关系显示	
	for (int i = 0; i < m_Graph.GetVexnum(); i++)
	{
		Vex sVex = m_Graph.GetVex(i);
		cout << i << "-" << sVex.name << endl;
	}

	int start_place, end_place;
	cout << "请输入起点的编号：";
	cin >> start_place;
	cout << "请输入终点的编号：";
	cin >> end_place;

	Edge aPath[20];						//边信息数组，依次保存最短的路径

	//查找最短路径，并给最短路径的条数index赋值
	int index = m_Graph.FindShortPath(start_place, end_place, aPath);
	int length = 0;						//最短路径总长度
	Vex sVex = m_Graph.GetVex(aPath[0].vex1);	//顶点信息（景点信息）

	//将最短路径输出，显示
	cout << "最短路径为：" << sVex.name;
	for (int i = 0; i < index; i++) {
		sVex = m_Graph.GetVex(aPath[i].vex2);
		cout << "->" << sVex.name;
		length += aPath[i].weight;
	}
	cout << endl;
	cout << "最短距离为：" << length << endl << endl;

}
void DesignPath()//查询铺设电路规划图
{
	cout << "==========铺设电路规划==========" << endl;
	Edge aPath[20];
	int length = m_Graph.FindMinTree(aPath);
	cout << "在以下两个景点之间铺设电路：" << endl;
	for (int i = 0; i < m_Graph.GetVexnum() - 1; i++)
	{
		Vex nVex1 = m_Graph.GetVex(aPath[i].vex1);
		Vex nVex2 = m_Graph.GetVex(aPath[i].vex2);
		cout << nVex1.name << "-" << nVex2.name << "    " << aPath[i].weight << "m" << endl;
	}
	cout << "铺设电路的总长度是：" << length << "m" << endl;

}