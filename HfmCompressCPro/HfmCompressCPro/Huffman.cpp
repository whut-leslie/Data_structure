#define EXAMPLE_MACRO_NAME
#include "Huffman.h"
#include<iostream>
#include<algorithm>
using namespace std;

//定义HuffmanTree_create函数用于创建Huffman树

int HuffmanTree_create(HuffmanTree &pHT, int * w, int n){

	int m = 2 * n - 1;
	pHT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));
	if (!pHT)
	{
		cerr << "内存分配失败! " << endl;
		return -1;
	}
	//初始化树
	HuffmanTree p = pHT + 1;//0号单元不使用
	for (int i = 0; i < m; i++)
	{
		p->weight = (i < n) ? w[i] : 0;
		p->parent = 0;
		p->lchild = 0;
		p->rchild = 0;
		p++;
	}
	for (int i = n + 1; i <= m; i++)
	{
		//第一个最小元素
		int s1 = Select(pHT, i - 1);//找出前i-1个中最小元素
		pHT[s1].parent = i;

		//第二个最小元素
		int s2 = Select(pHT, i - 1);
		pHT[s2].parent = i;

		pHT[i].weight = pHT[s1].weight + pHT[s2].weight;
		pHT[i].lchild = s1;
		pHT[i].rchild = s2;
	}
	return 0;
}

//定义Select函数用来寻找树节点数组中权值最小的节点
int Select(HuffmanTree& pHT, int nSize) {
	int minValue = 0x7FFFFFF;//最小值
	int min = 0;//元素序号
	//找到最小权值的元素序号
	for (int i = 1; i < nSize; i++)
	{
		if (pHT[i].parent == 0 && pHT[i].weight < minValue)
		{
			minValue = pHT[i].weight;
			min = i;
		}
	}
	return min;
}


//定义HuffmanCoding函数用来生成Huffman编码
int HuffmanCoding(HuffmanCode &pHC,HuffmanTree &pHT){
	pHC = (HuffmanCode)malloc((SIZE + 1) * sizeof(char*));
	//无栈非递归遍历 
	char cd[SIZE] = { '\0' };//记录访问路径
	int cdlen = 0;//记录当前路径长度
	for (int i = 1; i < 512; i++)
	{
		pHT[i].weight = 0;//遍历 Huffman树时用作节点的状态标志
	}

	int p = 2 * SIZE - 1;//根节点
	while (p != 0)
	{
		if (pHT[p].weight == 0)//向左
		{
			pHT[p].weight = 1;
			if (pHT[p].lchild != 0)
			{
				p = pHT[p].lchild;
				cd[cdlen++] = '0';
			}
			else if (pHT[p].rchild == 0)//登记叶子节点的字符编码
			{
				pHC[p] = (char*)malloc((cdlen + 1) * sizeof(char));
				cd[cdlen] = '\0';
				strcpy_s(pHC[p],strlen(cd)+1, cd);//复制编码
			}
		}
		else if (pHT[p].weight == 1)//向右
		{
			pHT[p].weight = 2;
			if (pHT[p].rchild != 0)//右孩子为叶子节点
			{
				p = pHT[p].rchild;
				cd[cdlen++] = '1';
			}
		}
		else
		{
			//退回父节点，编码长度减1
			pHT[p].weight = 0;
			p = pHT[p].parent;
			--cdlen;
		}
		//		printf("*");
	}
	return OK;
}
void TestHufTree(HuffmanTree pHT)
{
	cout << "哈夫曼树每个节点信息为" << endl;
	cout << " Byte  Weight  Parent  lchild   Rchild" << endl;
	for (int i = 1; i < 2 * SIZE; i++)
	{
		printf("pHT[%d]\t%d\t%d\t%d\t%d\n", i, pHT[i].weight, pHT[i].parent, pHT[i].lchild, pHT[i].rchild);
	}
}

void TestHufCode(int root, HuffmanTree pHT, HuffmanCode pHC)
{
	if (pHT[root].lchild == 0 && pHT[root].rchild == 0)
	{
		printf("0x%02X %s\n", root - 1, pHC[root]);
	}
	if (pHT[root].lchild)//访问左孩子
	{
		TestHufCode(pHT[root].lchild, pHT, pHC);
	}
	if (pHT[root].rchild)
	{
		TestHufCode(pHT[root].rchild, pHT, pHC);
	}
}

void TestHufTreeN(int root, HuffmanTree pHT)
{
	cout << pHT[root].weight << "\t" << pHT[root].lchild << "\t" << pHT[root].rchild << "\t" << pHT[root].parent << "\n";
	if (pHT[root].lchild != 0)
	{
		TestHufTreeN(pHT[root].lchild, pHT);
	}
	if (pHT[root].rchild != 0)
	{
		TestHufTreeN(pHT[root].rchild, pHT);
	}
}