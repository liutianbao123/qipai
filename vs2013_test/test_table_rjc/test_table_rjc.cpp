#include <iostream>
#include <windows.h>
#include <vector>
#include <algorithm>

#include "Define.h"
//#include "DefineHuTip.h"
//#include "PlayerHuTips.h"
#include "PlayerHuTips2.h"

using namespace std;

void print_cards(char* cards)
{
	for (int i = 0; i<9; ++i)
	{
		printf("%d,", cards[i]);
	}
	printf("  ");

	for (int i = 9; i<18; ++i)
	{
		printf("%d,", cards[i]);
	}
	printf("  ");
	for (int i = 18; i<27; ++i)
	{
		printf("%d,", cards[i]);
	}
	printf("  ");
	for (int i = 27; i<34; ++i)
	{
		printf("%d,", cards[i]);
	}
	printf("\n");
}

#define GUI_NUM 4
#define MAX_COUNT (1000 * 10000)
static BYTE g_HuCardAll[136];

CPlayerHuTips2 stTssss;

void test_repeat()
{
	char cards[] = {
		2, 0, 0, 0, 0, 0, 0, 1, 0,
		0, 1, 0, 1, 3, 2, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 4
	};
	int hu = 0;
	stCardData2 stData2;

	DWORD dwTimeBegin = GetTickCount();
	for (int i = 0; i < MAX_COUNT; i++){
		stData2.byNum = 14;
		memcpy(stData2.byCardNum, cards, sizeof(cards));
		hu += stTssss.CheckCanHu(stData2, 33);
	}

	cout << "rjc���������ͬ���ͣ��ܴ���: " << MAX_COUNT / 10000 << "���" << endl;
	cout << "time: " << GetTickCount() - dwTimeBegin << "ms" << endl;
	cout << "hu:" << hu << endl;
}

void main()
{
	stTssss.TrainAll();

	test_repeat();
	
	for (int i = 0; i < 34; i++)
	{
		g_HuCardAll[i * 4] = i;
		g_HuCardAll[i * 4+1] = i;
		g_HuCardAll[i * 4+2] = i;
		g_HuCardAll[i * 4+3] = i;
	}
	
	int gui_index = 33;
	int hu = 0;
	char cards[34] = { 0 };

	// rjc�����
	stCardData2 stData2;
	srand(1);
	DWORD dwTimeBegin = GetTickCount();
	for (int n = 0; n<MAX_COUNT; ++n)
	{
		random_shuffle(g_HuCardAll, g_HuCardAll + 126);		// ��������Լ�����Ӱ��
		for (int i = 0; i<9; ++i)	// 136/14 -> 9
		{
			stData2.byNum = 14;
			memset(cards, 0, sizeof(cards));
			for (int j = i * 14; j < i * 14 + 14 - GUI_NUM; j++)
				++cards[g_HuCardAll[j]];
			cards[33] = GUI_NUM;
			memcpy(stData2.byCardNum, cards, sizeof(cards));

			if (stTssss.CheckCanHu(stData2, gui_index))
			{
				hu++;
			}
		}
	}
	cout << "rjc���������:" << 9 * MAX_COUNT << "  time:" << GetTickCount() - dwTimeBegin << "ms" << endl;
	cout << "Hu: " << hu << endl;
	cin >> hu;
}