#pragma once
#define EXAMPLE_MACRO_NAME
#include "Huffman.h"
struct HEAD {
	char type[4];//文件类型
	int length; //原文件长度
	int weight[256];//权值数值
};
typedef unsigned  char* BUFFER;
//实现文件压缩
int Compress(const char*pFilename);
//读取原文件，初始化文件头数据信息
int InitHead(const char*pFilename,HEAD &sHead);
//利用Huffman编码实现文件压缩
int Encode(const char *pFilename,const HuffmanCode pHC,BUFFER &pBuffer,const int nSize);
//用于将“01010101”形式的字符串字节
unsigned char Str2byte(const char*pBinStr);
//用于将压缩后的数据写入新文件
int WriteFile(const char*pFilename,const HEAD sHead,unsigned char* pBuffer,const int nSize );
