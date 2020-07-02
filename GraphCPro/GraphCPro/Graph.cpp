#include "Graph.h"
#include <iostream>
using namespace std;
static int cnt = 0;//记录已输出的路径数
//对图进行初始化
void CGraph::Init(void) {
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
		for (int j = 0; j < MAX_VERTEX_NUM; j++)
			m_aAdjMatrix[i][j] = 0;//初始化权重为0
	m_nVexNum = 0;//顶点数为0
}

//将顶点添加到顶点数组中
int CGraph::InsertVex(Vex sVex) {
	if (m_nVexNum == MAX_VERTEX_NUM)
	{
		//顶点已满
		return 0;
	}
	m_aVexs[m_nVexNum++] = sVex;//插入顶点信息
	return 1;
}

//将边保存到矩阵中
int CGraph::InsertEdge(Edge sEdge) {
	if (sEdge.vex1 < 0 || sEdge.vex1 >= m_nVexNum || sEdge.vex2 < 0 || sEdge.vex2 >= m_nVexNum)
	{//下标越界
		return 0;
	}
	//插入边的信息
	m_aAdjMatrix[sEdge.vex1][sEdge.vex2] = sEdge.weight;
	m_aAdjMatrix[sEdge.vex2][sEdge.vex1] = sEdge.weight;
	return 1;
}

//查询顶点信息
Vex CGraph::GetVex(int nVex)//查询指定顶点信息
{
	return m_aVexs[nVex];
}

//查询与顶点相连的边
int CGraph::FindEdge(int nVex, Edge aEdge[])
{
	int k = 0;
	for (int i = 0; i < m_nVexNum; i++)
	{
		//得到变得消息
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

//获取当前顶点数
int CGraph::GetVexnum()
{
	return m_nVexNum;

}

//根据输入的编号得到访问结果
void CGraph::DFSTraverse(int nVex, PathList& List)
{
	int nIndex = 0;
	bool aVisited[MAX_VERTEX_NUM] = { false };//将访问标志设置为未访问状态
	DFS(nVex, aVisited, nIndex, List);

}
//根据迪杰特斯拉求最短路径
int CGraph::FindShortPath(int nVexStart, int nVexEnd, Edge aPath[])
{
	int nShortPath[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//最短路径
	int nShortDistance[MAX_VERTEX_NUM];//最短距离
	bool bVisited[MAX_VERTEX_NUM];//判断某顶点是否已经加入到最短路径中
	int v;//表示每一次找到的可以加入集合的顶点，即已经找到了从起点到该顶点的最短路径
	//初始化最短距离和两点间的距离
	for (int v = 0; v < m_nVexNum; v++)
	{
		//设置该点的状态
		bVisited[v] = false;
		if (m_aAdjMatrix[nVexStart][v] != 0)
		{
			nShortDistance[v] = m_aAdjMatrix[nVexStart][v];//有边的时候设置为边的长度
		}
		else
		{
			nShortDistance[v] = INT_MAX;//无边的时候设置为最大整数
		}
		nShortPath[v][0] = nVexStart;//起点为NVexStart
		//初始化最短路径
		for (int w = 1; w < m_nVexNum; w++)
		{
			nShortPath[v][w] = -1;
		}
	}
	//初始化，将nVexStart顶点加入到集合中
	bVisited[nVexStart] = true;
	int min;//路径最小值
	for (int i = 0; i < m_nVexNum; i++)
	{
		min = 0x7FFFFFFF;
		bool badd = false;//判断是否还有顶点可以加入
		for (int w = 0; w < m_nVexNum; w++)
		{
			if (!bVisited[w] && nShortDistance[w] < min)
			{
				v = w;//w顶点距离nVexStart距离最近
				min = nShortDistance[w];//w到nVexStart的最短距离为min
				badd = true;
			}
		}
		//若没有顶点可以加入集合，则跳出循环
		if (!badd)break;
		bVisited[v] = true;//将w顶点加入到集合
		nShortPath[v][i] = v;//每次找到最短路径后，就相当于从原点出发到终点
		for (int w = 0; w < m_nVexNum; w++)
		{
			//将w作为过渡顶点计算距离
			if (!bVisited[w] && (min + m_aAdjMatrix[v][w] < nShortDistance[w]) && (m_aAdjMatrix[v][w] > 0))
			{
				//更新当前最短路径及距离
				nShortDistance[w] = min + m_aAdjMatrix[v][w];
				for (int i = 0; i < m_nVexNum; i++) {
					//如果通过w达到顶点i的距离比较短，则将w的最短路径复制给i
					nShortPath[w][i] = nShortPath[v][i];
				}
			}
		}
	}
	int nIndex = 0;
	int nVex1 = nVexStart;
	//将最短路径保存为边的结构体数组
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
	int lowcost[MAX_VERTEX_NUM] = { 0 };	//最短距离
	bool addVexNew[MAX_VERTEX_NUM] = { true };//已获得最短距离的点
	int prev[MAX_VERTEX_NUM] = { 0 };		//之前点
	int length = 0;
	//初始化数组并默认起始顶点为0点
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
			//保存路径信息
			aPath[p].vex1 = prev[v];
			aPath[p].vex2 = v;
			aPath[p].weight = lowcost[v];
			addVexNew[v] = true;                                      //将v加Vnew中
			length += lowcost[v];                             //计算路径长度之和
			for (int i = 0; i < m_nVexNum; i++)
			{
				if ((!addVexNew[i]) && (m_aAdjMatrix[v][i] < lowcost[i]) && (m_aAdjMatrix[i][v] != 0))
				{
					lowcost[i] = m_aAdjMatrix[v][i];                     //此时v点加入Vnew 需要更新lowcost
					prev[i] = v;										//存储上一个点
				}
			}
		}
	}
	return length;

}

void CGraph::DFS(int nVex, bool aVisited[], int& nIndex, PathList& List)
{//改进的图的深度优先遍历算法
	aVisited[nVex] = true;				//改为已访问
	List->vex[nIndex++] = nVex;		//访问顶点nVex并赋值给链表，然后索引值自加
	if (nIndex == m_nVexNum)
	{
		//输出当前满足条件的路线
		cout << "路线" << ++cnt << ":";
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
				aVisited[i] = false;		//退回上一顶点恢复之前信息
				nIndex--;
			}
		}
	}
}