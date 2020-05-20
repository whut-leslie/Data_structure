
#include <iostream>
#include <stdlib.h>
#include"Compress.h"
#include"unCompress.h"
using namespace std;
int main() 
{
	cout << "= = = = = = = =Huffman 文件压缩= = = = = = = =" << endl;
	cout << "**1.压缩文件" << endl;
	cout << "**2.解压文件" << endl;
	cout << "= = = = = = = = = =  = = = = = = = = = = = = =" << endl;
	int choose = 0;
	cout << "----选择功能：";
	cin >> choose;
	while (choose == 1 || choose == 2)
	{
		if (choose == 1)
		{
			cout << "请输入文件名：";
			char filename[256];
			cin >> filename;
			Compress(filename);
		}
		else if (choose == 2)
		{
			cout << "输入你要解压的文件名(.huf后缀): ";
			char newfilename[SIZE] = { 0 };
			cin >> newfilename;
			//	strcpy(newfilename, "d:\\t.png.huf");
			UnCompress(newfilename);
		}
		else
			break;
		cout << "----选择功能：";
		cin >> choose;
	}


	//	system("pause");
	return 0;
}
