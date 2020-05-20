#pragma once
>
//树节点
typedef struct HTNode {
	int weight;//权值
	int parent;//父节点
	int lchild;//左孩子
	int rchild;//右孩子
}HuffmanTre[512];

//Huffman树
HTNode HuffmanTre[512]//动态分配数组存储 Huffman树
//定义HuffmanTree函数用于创建Huffman树
int HuffmanTree(HuffmanTree& pHT, int* w, int n)
//定义Select函数用来寻找树节点数组中权值最小的节点
int Select(HuffmanTree pHT, int nSize);
//定义HuffmanCoding函数用力啊生成Huffman编码
int HuffmanCoding(HuffmanCode &pHC，HuffmanTree &pHT);
//字符串数组用来保存Huffman编码表
char HuffmanCode[256];