#include"Huffman.h"
#include"Compress.h"
#include<iostream>
#pragma warning( disable : 4996)
using namespace std;


unsigned char Str2byte(const char* pBinStr)
{
	unsigned char b = 0x00;
	for (int i = 0; i < 8; i++)
	{
		b = b << 1;
		if (pBinStr[i] == '1')
		{
			b = b | 0x01;
		}
	}
	return b;
}

int Compress(const char* pFilename)
{
	int weight[256] = { 0 };
	//�Զ����ƴ��ļ�
	FILE* in;
	fopen_s(&in,pFilename, "rb");
	if (in == NULL)
	{
		cout << "Failed to open the file!" << endl;
		exit(0);
	}
	cout << "�ɹ����ļ� " << pFilename << endl;
	int ch;
	while ((ch = getc(in)) != EOF)
	{
		weight[ch]++;
	}
	fclose(in);
	//cout << "Byte Weight" << endl;
	//for (int i = 0; i < SIZE; i++)
	//{
	//	printf("0x%02X %d\n", i, weight[i]);
	//}

	HuffmanTree hfmt;
	HuffmanTree_create(hfmt, weight, SIZE);
	cout << "�ɹ����ɹ�������" << endl;
	//	TestHufTree(hfmt);
		//	TestHufTreeN(511, hfmt);
	HuffmanCode hfmc = (HuffmanCode)malloc((SIZE + 1) * sizeof(char*));
	//	for (int i = 1; i <= SIZE; i++)
	//		hfmt[i].weight = weight[i - 1]
		//���ݹ����������б���
	HuffmanCoding(hfmc, hfmt);
	cout << "�ɹ���ɹ���������" << endl;
	//	cout << "������������������������Ϣ��" << endl;
	//	TestHufCode(2 * SIZE - 1, hfmt, hfmc);//���Թ���������
	//	cout << "ѹ������ļ����룺" << endl;

		//������뻺������С
	int nSize = 0;
	for (int i = 0; i < 256; i++)
	{
		nSize += weight[i] * strlen(hfmc[i + 1]);
	}
	nSize = (nSize % 8) ? nSize / 8 + 1 : nSize / 8;

	//	cout <<"nSize = "<<nSize << endl << endl;

		//��ԭ�ļ�����ѹ������
	unsigned char* pBuffer = NULL;
	pBuffer = (unsigned char*)malloc(nSize * sizeof(unsigned char));
	memset(pBuffer, 0, (nSize) * sizeof(unsigned char));
	//	cout << "begin: " << strlen(pBuffer) << endl;
	////	cout << "----";
	//	int n;
	//	cout << "input n:";
	//	cin >> n;
		//������д�뻺����
	Encode(pFilename, hfmc, pBuffer, nSize);
	//	cout << "after: " << strlen(pBuffer) << endl;
	//	cout << "len of puf  = " << strlen(pBuffer) << endl;
	//	cout << "!pBuffer = " << !pBuffer << endl;
	if (!pBuffer)
	{
		cout << "!pBuffer = " << !pBuffer << endl;
		return -1;
	}
	cout << "\nѹ�����" << endl;
	//for (int i = 1; i < nSize; i++)
	//{
	//	printf("%X\n", pBuffer[i]);
	//}

	HEAD sHead;
	InitHead(pFilename, sHead);
	cout << "ԭ�ļ�" << pFilename << "��СΪ��" << sHead.length << "Byte" << endl;
	int len_after = WriteFile(pFilename, sHead, pBuffer, nSize);
	cout << "��СΪ��" << len_after << "Byte \nͷ�ļ�sHead��СΪ��" << sizeof(sHead) << "Byte" << endl;
	cout << "ѹ�����ʣ�" << (double)len_after * 100 / sHead.length << "%" << endl;
	free(hfmt);
	free(hfmc);
	free(pBuffer);
	return OK;
}


int Encode(const char* pFilename, const HuffmanCode pHC, BUFFER& pBuffer, const int nSize)
{
	//���ٻ�����
//	cout << "+++++";
	FILE* in;
	fopen_s(&in,pFilename, "rb");
	if (in == NULL)
	{
		cout << "Failed to open the file!" << endl;
		exit(0);
	}
	pBuffer = (unsigned char*)malloc(nSize * sizeof(unsigned char));
	if (!pBuffer)
	{
		cerr << "���ٻ�����ʧ��" << endl;
		return -1;
	}
	cout << "loading";
	int sign = 0;//���ڿ���С�������
	char cd[SIZE] = { 0 };//������
	int pos = 0;//������ָ��
	int ch;
	//ɨ���ļ�������huffmman�����������ѹ����ѹ������ݴ浽��������
	while ((ch = getc(in)) != EOF)
	{
		if (sign % 1000 == 1)
			printf(".");
		sign++;
		strcat(cd, pHC[ch + 1]);//��HC���Ʊ��봮��cd


		//��ӡѹ������ļ�����
//		printf("%s", pHC[ch + 1]);


		//ѹ������
		while (strlen(cd) >= 8)
		{
			//��ȡ�ַ�����ߵ�8���ַ���������ֽ�
			pBuffer[pos++] = Str2byte(cd);
			//�ַ�����������8���ֽ�
			for (int i = 0; i < SIZE - 8; i++)
			{
				cd[i] = cd[i + 8];
			}
		}
	}
	if (strlen(cd) > 0)
	{
		pBuffer[pos++] = Str2byte(cd);
	}
	fclose(in);
	//	printf("%", pBuffer);
	return OK;
}

int InitHead(const char* pFilename, HEAD& sHead)
{
	//��ʼ���ļ�ͷ
	strcpy_s(sHead.type, "HUF");//�ļ�����
	sHead.length = 0;//ԭ�ļ�����
	for (int i = 0; i < SIZE; i++)
	{
		sHead.weight[i] = 0;
	}
	FILE* in;
	fopen_s(&in,pFilename, "rb");
	int ch;
	while ((ch = fgetc(in)) != EOF)
	{
		sHead.weight[ch]++;
		sHead.length++;
	}
	fclose(in);
	in = NULL;
	return OK;
}

int WriteFile(const char* pFilename, const HEAD sHead, unsigned char* pBuffer, const int nSize)
{
	//�����ļ���
	char filename[256] = { 0 };
	strcpy_s(filename, pFilename);
	strcat_s(filename, ".huf");
	//�Զ���������ʽ���ļ�
	FILE* out;
	fopen_s(&out,filename, "wb");
	//д�ļ�ͷ
	fwrite(&sHead, sizeof(sHead), 1, out);
	//дѹ����ı���
	fwrite(pBuffer, sizeof(char), nSize, out);
	//�ر��ļ����ͷ��ļ�ָ��
	fclose(out);
	out = NULL;
	cout << "����ѹ���ļ���" << filename << endl;
	int len = sizeof(HEAD) + strlen(pFilename) + 1 + nSize;
	return len;
}