#pragma once
#define EXAMPLE_MACRO_NAME
#include "Huffman.h"
struct HEAD {
	char type[4];//�ļ�����
	int length; //ԭ�ļ�����
	int weight[256];//Ȩֵ��ֵ
};
typedef unsigned  char* BUFFER;
//ʵ���ļ�ѹ��
int Compress(const char*pFilename);
//��ȡԭ�ļ�����ʼ���ļ�ͷ������Ϣ
int InitHead(const char*pFilename,HEAD &sHead);
//����Huffman����ʵ���ļ�ѹ��
int Encode(const char *pFilename,const HuffmanCode pHC,BUFFER &pBuffer,const int nSize);
//���ڽ���01010101����ʽ���ַ����ֽ�
unsigned char Str2byte(const char*pBinStr);
//���ڽ�ѹ���������д�����ļ�
int WriteFile(const char*pFilename,const HEAD sHead,unsigned char* pBuffer,const int nSize );
