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
	//以二进制打开文件
	FILE* in;
	fopen_s(&in,pFilename, "rb");
	if (in == NULL)
	{
		cout << "Failed to open the file!" << endl;
		exit(0);
	}
	cout << "成功打开文件 " << pFilename << endl;
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
	cout << "成功生成哈夫曼树" << endl;
	//	TestHufTree(hfmt);
		//	TestHufTreeN(511, hfmt);
	HuffmanCode hfmc = (HuffmanCode)malloc((SIZE + 1) * sizeof(char*));
	//	for (int i = 1; i <= SIZE; i++)
	//		hfmt[i].weight = weight[i - 1]
		//根据哈夫曼树进行编码
	HuffmanCoding(hfmc, hfmt);
	cout << "成功完成哈夫曼编码" << endl;
	//	cout << "先序遍历哈夫曼树输出编码信息：" << endl;
	//	TestHufCode(2 * SIZE - 1, hfmt, hfmc);//测试哈夫曼编码
	//	cout << "压缩后的文件编码：" << endl;

		//计算编码缓冲区大小
	int nSize = 0;
	for (int i = 0; i < 256; i++)
	{
		nSize += weight[i] * strlen(hfmc[i + 1]);
	}
	nSize = (nSize % 8) ? nSize / 8 + 1 : nSize / 8;

	//	cout <<"nSize = "<<nSize << endl << endl;

		//对原文件进行压缩编码
	unsigned char* pBuffer = NULL;
	pBuffer = (unsigned char*)malloc(nSize * sizeof(unsigned char));
	memset(pBuffer, 0, (nSize) * sizeof(unsigned char));
	//	cout << "begin: " << strlen(pBuffer) << endl;
	////	cout << "----";
	//	int n;
	//	cout << "input n:";
	//	cin >> n;
		//将编码写入缓冲区
	Encode(pFilename, hfmc, pBuffer, nSize);
	//	cout << "after: " << strlen(pBuffer) << endl;
	//	cout << "len of puf  = " << strlen(pBuffer) << endl;
	//	cout << "!pBuffer = " << !pBuffer << endl;
	if (!pBuffer)
	{
		cout << "!pBuffer = " << !pBuffer << endl;
		return -1;
	}
	cout << "\n压缩完毕" << endl;
	//for (int i = 1; i < nSize; i++)
	//{
	//	printf("%X\n", pBuffer[i]);
	//}

	HEAD sHead;
	InitHead(pFilename, sHead);
	cout << "原文件" << pFilename << "大小为：" << sHead.length << "Byte" << endl;
	int len_after = WriteFile(pFilename, sHead, pBuffer, nSize);
	cout << "大小为：" << len_after << "Byte \n头文件sHead大小为：" << sizeof(sHead) << "Byte" << endl;
	cout << "压缩比率：" << (double)len_after * 100 / sHead.length << "%" << endl;
	free(hfmt);
	free(hfmc);
	free(pBuffer);
	return OK;
}


int Encode(const char* pFilename, const HuffmanCode pHC, BUFFER& pBuffer, const int nSize)
{
	//开辟缓冲区
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
		cerr << "开辟缓冲区失败" << endl;
		return -1;
	}
	cout << "loading";
	int sign = 0;//用于控制小数点输出
	char cd[SIZE] = { 0 };//工作区
	int pos = 0;//缓冲区指针
	int ch;
	//扫描文件，根据huffmman编码表对其进行压缩，压缩结果暂存到缓冲区中
	while ((ch = getc(in)) != EOF)
	{
		if (sign % 1000 == 1)
			printf(".");
		sign++;
		strcat(cd, pHC[ch + 1]);//从HC复制编码串到cd


		//打印压缩后的文件编码
//		printf("%s", pHC[ch + 1]);


		//压缩编码
		while (strlen(cd) >= 8)
		{
			//截取字符串左边的8个字符，编码成字节
			pBuffer[pos++] = Str2byte(cd);
			//字符串整体左移8个字节
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
	//初始化文件头
	strcpy_s(sHead.type, "HUF");//文件类型
	sHead.length = 0;//原文件长度
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
	//生成文件名
	char filename[256] = { 0 };
	strcpy_s(filename, pFilename);
	strcat_s(filename, ".huf");
	//以二进制流形式打开文件
	FILE* out;
	fopen_s(&out,filename, "wb");
	//写文件头
	fwrite(&sHead, sizeof(sHead), 1, out);
	//写压缩后的编码
	fwrite(pBuffer, sizeof(char), nSize, out);
	//关闭文件，释放文件指针
	fclose(out);
	out = NULL;
	cout << "生成压缩文件：" << filename << endl;
	int len = sizeof(HEAD) + strlen(pFilename) + 1 + nSize;
	return len;
}