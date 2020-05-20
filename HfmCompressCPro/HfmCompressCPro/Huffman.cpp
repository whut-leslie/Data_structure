#define EXAMPLE_MACRO_NAME
#include "Huffman.h"
#include<iostream>
#include<algorithm>
using namespace std;

//����HuffmanTree_create�������ڴ���Huffman��

int HuffmanTree_create(HuffmanTree &pHT, int * w, int n){

	int m = 2 * n - 1;
	pHT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));
	if (!pHT)
	{
		cerr << "�ڴ����ʧ��! " << endl;
		return -1;
	}
	//��ʼ����
	HuffmanTree p = pHT + 1;//0�ŵ�Ԫ��ʹ��
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
		//��һ����СԪ��
		int s1 = Select(pHT, i - 1);//�ҳ�ǰi-1������СԪ��
		pHT[s1].parent = i;

		//�ڶ�����СԪ��
		int s2 = Select(pHT, i - 1);
		pHT[s2].parent = i;

		pHT[i].weight = pHT[s1].weight + pHT[s2].weight;
		pHT[i].lchild = s1;
		pHT[i].rchild = s2;
	}
	return 0;
}

//����Select��������Ѱ�����ڵ�������Ȩֵ��С�Ľڵ�
int Select(HuffmanTree& pHT, int nSize) {
	int minValue = 0x7FFFFFF;//��Сֵ
	int min = 0;//Ԫ�����
	//�ҵ���СȨֵ��Ԫ�����
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


//����HuffmanCoding������������Huffman����
int HuffmanCoding(HuffmanCode &pHC,HuffmanTree &pHT){
	pHC = (HuffmanCode)malloc((SIZE + 1) * sizeof(char*));
	//��ջ�ǵݹ���� 
	char cd[SIZE] = { '\0' };//��¼����·��
	int cdlen = 0;//��¼��ǰ·������
	for (int i = 1; i < 512; i++)
	{
		pHT[i].weight = 0;//���� Huffman��ʱ�����ڵ��״̬��־
	}

	int p = 2 * SIZE - 1;//���ڵ�
	while (p != 0)
	{
		if (pHT[p].weight == 0)//����
		{
			pHT[p].weight = 1;
			if (pHT[p].lchild != 0)
			{
				p = pHT[p].lchild;
				cd[cdlen++] = '0';
			}
			else if (pHT[p].rchild == 0)//�Ǽ�Ҷ�ӽڵ���ַ�����
			{
				pHC[p] = (char*)malloc((cdlen + 1) * sizeof(char));
				cd[cdlen] = '\0';
				strcpy_s(pHC[p],strlen(cd)+1, cd);//���Ʊ���
			}
		}
		else if (pHT[p].weight == 1)//����
		{
			pHT[p].weight = 2;
			if (pHT[p].rchild != 0)//�Һ���ΪҶ�ӽڵ�
			{
				p = pHT[p].rchild;
				cd[cdlen++] = '1';
			}
		}
		else
		{
			//�˻ظ��ڵ㣬���볤�ȼ�1
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
	cout << "��������ÿ���ڵ���ϢΪ" << endl;
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
	if (pHT[root].lchild)//��������
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