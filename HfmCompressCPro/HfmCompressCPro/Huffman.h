#pragma once
#define OK 1
#define SIZE 256

//���ڵ�
struct HTNode{
	int weight;//Ȩֵ
	int parent;//���ڵ�
	int lchild;//����
	int rchild;//�Һ���
};

//Huffman��
typedef HTNode *HuffmanTree;//��̬��������洢 Huffman��
typedef char ** HuffmanCode;//��̬����Huffman�����


//����HuffmanTree�������ڴ���Huffman��
int HuffmanTree_create(HuffmanTree &pHT,int *w,int n);
//����Select��������Ѱ�����ڵ�������Ȩֵ��С�Ľڵ�
int Select(HuffmanTree& pHT, int nSize);
//����HuffmanCoding������������Huffman����
int HuffmanCoding(HuffmanCode& pHC,HuffmanTree &pHT);
//����
void TestHufTree(HuffmanTree pHT);
void TestHufCode(int root, HuffmanTree pHT, HuffmanCode pHC);
void TestHufTreeN(int root, HuffmanTree pHT);
