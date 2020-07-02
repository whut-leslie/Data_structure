#pragma once
#define MAX_VERTEX_NUM 20
//顶点结构体
struct Vex {
	int num;//景点编号
	char name[20];//景点名字
	char desc[1024];//景点介绍
};

//边结构体
struct Edge {
	int vex1;//边的第一个顶点
	int vex2;//边的第二个顶点
	int weight;//权值
};

//定义链表PathList来保存所有路径
typedef struct Path {
	int vex[20];//保存一条路径
	Path* next=nullptr;//下一条路径
}*PathList;


class CGraph{
private:
	int m_aAdjMatrix[20][20];//邻接矩阵
	Vex m_aVexs[20];//顶点数组
	int m_nVexNum;//顶点个数
public:
	void Init(void);//初始化图结构
	int InsertVex(Vex sVex);//将顶点添加到顶点数组中
	int InsertEdge(Edge sEdge);//将边保存到邻接矩阵中
	Vex GetVex(int nVex);//查询指定顶点信息
	int FindEdge(int v, Edge aEdge[]);//查询与指定顶点相连的边
	int GetVexnum();//获取当前顶点数
	void DFSTraverse(int nVex,PathList &List);//获得遍历结果
	int FindShortPath(int nVexStart, int nVexEnd, Edge aPath[]);//搜寻两点之间的最短距离
	int FindMinTree(Edge aPath[]);//构造最小生成树
	void DFS(int nVex, bool aVisited[], int& nIndex, PathList& List);//深度优先搜索遍历图

};