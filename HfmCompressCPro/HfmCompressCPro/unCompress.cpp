#include"unCompress.h"
#include<iostream>
using namespace std;
//解压函数
int UnCompress(const char* pFilename)
{
	char outputfile[255];
	FILE* ifp, * ofp;
	fopen_s(&ifp,pFilename, "rb");//打开.huf文件
	if (!ifp)
	{
		cerr << "Failed to open this file!" << endl;
		return -1;
	}
	cout << "输入解压后的文件名,(原文件名为" << pFilename << "): " << endl;
	cin >> outputfile;
	//	strcpy(outputfile, "d:\\aaa.png");
	 fopen_s(&ofp,outputfile, "wb");
	if (!ofp)
	{
		cerr << "Failed to open this file!" << endl;
		return -1;
	}
	HEAD sHead;
	//读文件头
	fread(&sHead, sizeof(HEAD), 1, ifp);
	HuffmanTree hfmt = NULL;
	HuffmanTree_create(hfmt, sHead.weight, 256);
	HuffmanCode hfmc = NULL;
	HuffmanCoding(hfmc, hfmt);
	int max = 0;
	for (int k = 1; k <= 256; k++) {
		if (strlen(hfmc[k]) > max) {
			max = strlen(hfmc[k]);
		}//找出最长的编码
	}
	//
	int nSize = 0;
	for (int i = 0; i < 256; i++)
	{
		nSize += sHead.weight[i] * strlen(hfmc[i + 1]);
	}
	nSize = (nSize % 8) ? nSize / 8 + 1 : nSize / 8;
	cout << "nsize =  " << nSize << endl;
	//	unsigned char *pBuffer = NULL;
	unsigned char* pBuffer = NULL;
	pBuffer = (unsigned char*)malloc(nSize * sizeof(unsigned char));
	memset(pBuffer, 0, (nSize) * sizeof(unsigned char));
	//	pBuffer = (unsigned char*)malloc(nSize*sizeof(unsigned char));
	fread(pBuffer, sizeof(unsigned char), nSize, ifp);
	//for (int i = 0; i < nSize; i++)
	//{
	//	printf("%x\n", pBuffer[i]);
	//}
	char ch[SIZE] = { 0 };
	unsigned char c;
	for (int i = 0; i < nSize; i++)
	{
		//		printf("%x\n", pBuffer[i]);
		char s[SIZE] = { 0 };
		char buf[SIZE] = { 0 };
		_itoa_s(pBuffer[i], buf, 2);

		for (int k = 8; k > strlen(buf); k--)
		{
			strcat_s(s, "0");
		}
		strcat_s(s, buf);
		strcat_s(ch, s);
		//		cout << "ch = " << ch << endl;
		int m = 2 * SIZE - 1;
		while (strlen(ch) >= max)
		{
			//			cout << "**";
			int j = 0;
			while (ch[j] != '\0')
			{
				//				cout << "....";
				int t = m;
				while (hfmt[t].lchild != 0 && hfmt[t].rchild != 0)
				{
					if (ch[j] == '0')
					{
						t = hfmt[t].lchild;
					}
					else
					{
						t = hfmt[t].rchild;
					}
					j++;
				}
				c = (unsigned char)(t - 1);
				//				cout << (t - 1) << endl;
				fwrite(&c, 1, 1, ofp);

				for (int b = 0; b < SIZE - j; b++)
				{
					ch[b] = ch[b + j];
				}
				break;
			}
			//			cout << "::::";
		}
	}
	cout << "解压成功" << endl;
	fclose(ifp);
	fclose(ofp);

	return OK;
}