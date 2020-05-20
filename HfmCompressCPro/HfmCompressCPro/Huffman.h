#pragma once
#define OK 1
#define SIZE 256

//树节点
struct HTNode{
	int weight;//权值
	int parent;//父节点
	int lchild;//左孩子
	int rchild;//右孩子
};

//Huffman树
typedef HTNode *HuffmanTree;//动态分配数组存储 Huffman树
typedef char ** HuffmanCode;//动态分配Huffman编码表


//定义HuffmanTree函数用于创建Huffman树
int HuffmanTree_create(HuffmanTree &pHT,int *w,int n);
//定义Select函数用来寻找树节点数组中权值最小的节点
int Select(HuffmanTree& pHT, int nSize);
//定义HuffmanCoding函数用来生成Huffman编码
int HuffmanCoding(HuffmanCode& pHC,HuffmanTree &pHT);
//测试
void TestHufTree(HuffmanTree pHT);
void TestHufCode(int root, HuffmanTree pHT, HuffmanCode pHC);
void TestHufTreeN(int root, HuffmanTree pHT);
