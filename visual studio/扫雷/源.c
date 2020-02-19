#define _CRT_SECURE_NO_WARNINGS 0
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>.
#define COL 9
#define ROW 9
#define COLS COL+2
#define ROWS ROW+2
#define easymine 10
int menu()
{
	int choice;
	printf("■■■■■■■■■■■■■■■■■■\n");
	printf("■        欢迎玩扫雷游戏          ■\n");
	printf("■■■■■■■■■■■■■■■■■■\n");
	printf("■                                ■\n");
	printf("■         1：开始游戏            ■\n");
	printf("■         2：结束游戏            ■\n");
	printf("■                                ■\n");
	printf("■■■■■■■■■■■■■■■■■■\n");
	scanf("%d", &choice);
	return choice;
}
void print()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0;  j < 10;  j++)
		{
			printf("■");
		}
		printf("\n");
	}
} 
void init(char map[COLS][ROWS], int cols, int rows, char set)
{
	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			map[i][j] = set;
		}
	}
}
void ShowMap(char map[COLS][ROWS], int cols, int rows)
{
	for (int i = 0; i <= 9; i++)
		printf("%d ", i);
	printf("\n");
	for (int i = 0; i <= 9; i++)
		printf("- ");
	printf("\n");
	for (int i = 1; i <=cols; i++)
	{
		printf("%d|", i);
		for (int j = 1; j <= rows; j++)
		{
			printf("%c ", map[i][j]);
		}
		printf("\n");
	}
}
void SetMine(char map[COLS][ROWS], int col, int row)
{
	int a = easymine;
	while(a)
	{
		int x = rand() %col+1;
		int y = rand() %row+1;
		if (map[x][y] == '0')
		{
			map[x][y] = '1';
			a--;
		}
	}
}
int CountMine(char mine[COLS][ROWS], int cols, int rows, int x, int y)
{
	return mine[x - 1][y - 1] +
		mine[x - 1][y] +
		mine[x - 1][y + 1] +
		mine[x][y + 1] +
		mine[x + 1][y + 1] +
		mine[x + 1][y] +
		mine[x + 1][y - 1] +
		mine[x][y - 1] - 8 * '0';
}
void BreakMap(char map[COLS][ROWS], char mine[COLS][ROWS], int x, int y)
{
	if (CountMine(mine, COLS, ROWS, x, y) != 0)
	{
		map[x][y] = CountMine(mine, COLS, ROWS, x, y) + '0';
	}
	else {
		while (mine[x][y] != 1 && (CountMine(mine, COLS, ROWS, x, y) == 0) && map[x][y] == '#')
		{
			map[x][y] = '0';
			BreakMap(map, mine, x - 1, y - 1);
			BreakMap(map, mine, x - 1, y);
			BreakMap(map, mine, x - 1, y + 1);
			BreakMap(map, mine, x, y + 1);
			BreakMap(map, mine, x + 1, y + 1);
			BreakMap(map, mine, x + 1, y);
			BreakMap(map, mine, x + 1, y - 1);
			BreakMap(map, mine, x, y - 1);
		}
	}
	
}
void SwapMine(char map[COLS][ROWS], char mine[COLS][ROWS], int col, int row)
{
	int posion = 0;
	while (posion<row*col-easymine)
	{
		int x=0, y=0;
		printf("输入坐标");
		scanf("%d %d", &x, &y);
		if (x >= 1 && x <= COL && y >= 1 && y <= ROW)
		{
			if (mine[x][y] == '1')
			{
				printf("扫雷失败\n");
				ShowMap(mine, COL, ROW);
				break;
			}
			else 
			{
				BreakMap(map, mine, x, y);
				map[x][y] = CountMine(mine, COLS, ROWS, x, y) + '0';
				ShowMap(map, COL, ROW); 
				posion++;
			}
		}
		else print("输入错误");
	}
	if (posion == row * col - easymine)
	{
		printf("排雷成功");
	}
}
void game()
{
	char map[COLS][ROWS];
	char mine[COLS][ROWS];
	srand((unsigned int)time(NULL));
	init(map,COLS,ROWS,'#');
	init(mine, COLS, ROWS, '0');
	ShowMap(map, COL, ROW);
	SetMine(mine, COL, ROW);
	//ShowMap(mine, COL, ROW);
	SwapMine(map, mine, COL, ROW);
	//print();
}
int main()
{
	int ret=menu();
	switch (ret)
	{
	case 1:game(); break;
	case 2:printf("再见"); break;
	default:
		break;
	}
	
	return 0;
}