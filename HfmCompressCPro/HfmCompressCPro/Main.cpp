
#include <iostream>
#include <stdlib.h>
#include"Compress.h"
#include"unCompress.h"
using namespace std;
int main() 
{
	cout << "= = = = = = = =Huffman �ļ�ѹ��= = = = = = = =" << endl;
	cout << "**1.ѹ���ļ�" << endl;
	cout << "**2.��ѹ�ļ�" << endl;
	cout << "= = = = = = = = = =  = = = = = = = = = = = = =" << endl;
	int choose = 0;
	cout << "----ѡ���ܣ�";
	cin >> choose;
	while (choose == 1 || choose == 2)
	{
		if (choose == 1)
		{
			cout << "�������ļ�����";
			char filename[256];
			cin >> filename;
			Compress(filename);
		}
		else if (choose == 2)
		{
			cout << "������Ҫ��ѹ���ļ���(.huf��׺): ";
			char newfilename[SIZE] = { 0 };
			cin >> newfilename;
			//	strcpy(newfilename, "d:\\t.png.huf");
			UnCompress(newfilename);
		}
		else
			break;
		cout << "----ѡ���ܣ�";
		cin >> choose;
	}


	//	system("pause");
	return 0;
}
