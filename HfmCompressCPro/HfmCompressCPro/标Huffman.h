#pragma once
>
//���ڵ�
typedef struct HTNode {
	int weight;//Ȩֵ
	int parent;//���ڵ�
	int lchild;//����
	int rchild;//�Һ���
}HuffmanTre[512];

//Huffman��
HTNode HuffmanTre[512]//��̬��������洢 Huffman��
//����HuffmanTree�������ڴ���Huffman��
int HuffmanTree(HuffmanTree& pHT, int* w, int n)
//����Select��������Ѱ�����ڵ�������Ȩֵ��С�Ľڵ�
int Select(HuffmanTree pHT, int nSize);
//����HuffmanCoding��������������Huffman����
int HuffmanCoding(HuffmanCode &pHC��HuffmanTree &pHT);
//�ַ���������������Huffman�����
char HuffmanCode[256];