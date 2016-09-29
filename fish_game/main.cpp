#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <locale>
#include <Windows.h>
#include "mtgex.h"

#define GAME_TITLE		 0
#define GAME_RUNGAME  	 1
#define GAME_EXPLAIN     2
#define GAME_END         3

#define GAME_ENTER		13

#define MY_UP			72
#define MY_DOWN			80
#define MY_LEFT			75
#define MY_RIGHT		77
#define MY_ENTER		13
#define MY_SPACE		32
		

int g_stage = 0;
int g_cursor = 0;
int g_time;
int gg_stage;
long g_t1;
long g_t2;
int g_point = 0;
int g_imsi[20] = { 0 };
int g_flag = 0;
int g_count = 0;
int random;
//물고기 종류, 방향키 수, 물고기 점수 
int g_fish[6][3] = { {0, 8,100},				//쓰레기
					{1,10,150},				//잉어
					{2,12,200},				//고등어
					{3,14,250},				//갈치
					{4,16,300},				//개복치
					{5,18,350} };			//고래

char g_fishName[6][10] = { {"쓰레기"},
						   {"잉어"},
						   {"고등어"},
						   {"갈치"},
						   {"개복치"},
						   {"고래"} };


char g_directionKey[4][4] = { "→","←","↑","↓" };



////////////////////////////////Map///////////////////////////////
#define MAPX 70
#define MAPY 25
void InitMap()
{
	for (int j = 0; j < MAPX; j++)
	{
		_DrawTextColorOrg(j, MAPY, "------", 11);
		_DrawTextColorOrg(j, 0, "------", 11);
	}
	for (int i = 0; i < MAPY; i++)
	{
		_DrawTextColorOrg(0, 1 + i, "||", 11);
		_DrawTextColorOrg(MAPX + 3, 1 + i, "||", 11);
	}
}

void InitMenu()
{
	_DrawTextColorOrg(30, 5, "낚시 게임", 11);
	_DrawTextColorOrg(30, 10, "1. 게임시작", 11);
	_DrawTextColorOrg(30, 13, "2. 도 움 말", 11);
	_DrawTextColorOrg(30, 16, "3. 종    료", 11);
}

void InitCursor(int cursor)
{
	_DrawTextColorOrg(25, 10 + (cursor * 3), "▶", 1);
}

///////////////////////////////////////////////////////////////

////////////////////////////Explain////////////////////////////

void Explain()
{
	_DrawTextColorOrg(5, 5, "1. 물고기가 나타나면 느낌표(!)가 뜹니다.", 7);
	_DrawTextColorOrg(5, 7, "2. 느낌표가 떳을 때 스페이스 바를 누릅니다", 7);
	_DrawTextColorOrg(5, 9, "3. 화살표가 맵밑에 생기면서 게임이 시작됩니다.", 7);
	_DrawTextColorOrg(5, 11, "4-1. 시간내에 누르지 못하면 물고기를 낚지 못하고 점수가 깎입니다.", 7);
	_DrawTextColorOrg(5, 13, "4-2. 시간내에 누르면 물고기를 낚으며 점수가 오릅니다.", 7);
	_DrawTextColorOrg(5, 15, "5. 물고기는 랜덤으로 나타나며 무거울수록 화살표의 갯수가 많아집니다.", 7);
	_DrawTextColorOrg(5, 20, "Space Bar를 누르면 첫화면으로 돌아갑니다.", 7);
}

///////////////////////////////////////////////////////////////


//////////////////////face AND Tool AND Bird///////////////////////////////////


void face()
{
	_DrawTextColorOrg(35, 24, "＠", 10);
	_DrawTextColorOrg(35, 23, "＠", 10);
	_DrawTextColorOrg(37, 22, "＠", 10);
	_DrawTextColorOrg(39, 22, "＠", 10);
	_DrawTextColorOrg(37, 23, "     ", 10);
	_DrawTextColorOrg(37, 23, "* *", 10);
	_DrawTextColorOrg(41, 24, "＠", 10);
	_DrawTextColorOrg(41, 23, "＠", 10);
}

void fishingTool()
{
	for (int i = 0; i < 5; i++)
	{
		_DrawTextColorOrg(44, 24 - i, "| |", 3);
	}
	_DrawTextColorOrg(44, 19, "* *", 3);
	_DrawTextColorOrg(45, 18, "|", 3);
	_DrawTextColorOrg(46, 17, "/", 3);
	_DrawTextColorOrg(47, 16, "/", 3);
}

void Bird(int x, int y)
{
	_DrawTextColorOrg(x, y, "^_^", 10);
}


/////////////////////////////////////////////////////////////

/////////////////////random arrow////////////////////////////

void Random_arrow(int random, int rankey, int i)
{
	_DrawTextColorOrg(38 - g_fish[random][1] / 2 * 3 + i * 3, 5, g_directionKey[rankey], 3);
}

/////////////////////////////////////////////////////////////

///////////////////Paint//////////////////////////////////////
void Paint()
{
	switch (g_stage)
	{
	case GAME_TITLE:

		InitMap();
		InitMenu();
		InitCursor(g_cursor);

		break;

	case GAME_RUNGAME:

		system("cls");
		InitMap();
		face();
		fishingTool();
		_DrawTextColorOrg(50, 24, "Point:", 3);

		if (gg_stage == 100 && g_count == 0)
		{
			g_flag = 1;
			_DrawTextColorOrg(33, 1, "GAME START", 3);
			random = rand() % 6;
			_DrawTextColorOrg(28, 3, g_fishName[random], 3);
			_DrawTextColorOrg(34, 3, "가 낚였습니다.", 3);

			int i;

			for (i = 0; i < g_fish[random][1]; i++)
			{
				int ranKey = rand() % 4;
				//_DrawTextColorOrg(38 - g_fish[random][1]/2*3 + i*3, 5, g_directionKey[ranKey], 3);
				Random_arrow(random, ranKey, i);
				g_imsi[i] = ranKey;
				g_t2 = GetTickCount();
			}
			g_imsi[i] = '\0';
		}
		else if (gg_stage==100 && g_count > 0)
		{
			_DrawTextColorOrg(33, 1, "GAME START", 3);
			_DrawTextColorOrg(28, 3, g_fishName[random], 3);
			_DrawTextColorOrg(34, 3, "가 낚였습니다.", 3);
			for (int i = 0; i < g_fish[random][1]; i++)
			{
				Random_arrow(random, g_imsi[i], i);
			}
		}
		break;

	case GAME_EXPLAIN:

		system("cls");
		InitMap();
		Explain();

		break;

	case GAME_END:

		MTGExit();

		break;

	default:

		break;
	}
}

/////////////////////////////////////////////////////////////


///////////////////////MY_TIME//////////////////////////////


void MyTime(int wparam, int g_stage)
{
	int killtime = 0;
	int temp = 0;

	if (g_stage == 1)
	{
		if (wparam == 1)
		{
			MTGInvalidate();

			for (int i = 0; i < 10; i++)
			{
				int x = rand() % 68 + 2;
				int y = rand() % 10 + 2;

				if (x - temp >= 3 || x - temp <= -3)
				{
					temp = x;
					Bird(x, y);
				}
			}


		}

		if (wparam == 2)
		{
			//MTGInvalidate();
			_DrawTextColorOrg(38, 19, "!!", 4);
			g_t1 = _GetTickCount();
		}
	}
}


///////////////////////////////////////////////////////////


int  MTGProc(int msg, int wparam, long lparam)
{
	switch (msg)
	{
	case MTG_CREATE:

		MTGSetTimer(1, 2000);
		g_time = (rand() % 3 + 1) * 1000;
		MTGSetTimer(2, g_time);

		break;

	case MTG_KEYDOWN:

		if (g_stage == GAME_TITLE)					///////////////////////////GAME_TITLE////////////////////////////////////
		{
			switch (wparam)
			{
			case MY_UP:

				MTGPrintColor(25, 10 + (3 * g_cursor), "  ", 11);
				g_cursor = (g_cursor + 2) % 3;
				InitCursor(g_cursor);

				break;

			case MY_DOWN:

				MTGPrintColor(25, 10 + (3 * g_cursor), "  ", 11);
				g_cursor = (g_cursor + 1) % 3;
				InitCursor(g_cursor);

				break;

			case MY_LEFT:


				break;

			case MY_RIGHT:

				break;

			case MY_ENTER:

				if (0 == g_cursor) { g_stage = GAME_RUNGAME; }
				else if (1 == g_cursor) { g_stage = GAME_EXPLAIN; }
				else if (2 == g_cursor) { g_stage = GAME_END; }

				break;

			case MY_SPACE:

				break;

			default:

				break;
			}
		}

		else if (g_stage == GAME_RUNGAME)///////////////////////////GAME_RUNGAME////////////////////////////////////////
		{
			switch (wparam)
			{

			case MY_UP:
				if (gg_stage == 100)
				{
					if (_GetTickCount() - g_t2 < 3000)
					{
						if (strcmp(g_directionKey[g_imsi[g_count]], "↑") == 0)
						{
							g_count++;
							for (int i = 0; i < g_fish[random][1]; i++)
							{
								Random_arrow(random, g_imsi[i], i);
							}
						}
						else
						{
							gg_stage = 0;
							g_flag = 0;
							g_count = 0;
							MTGSetTimer(1, 1000);
							g_time = (rand() % 3 + 1) * 1000;
							MTGSetTimer(2, g_time);
						}
					}
					else
					{
						gg_stage = 0;
						g_flag = 0;
						g_count = 0;
						MTGSetTimer(1, 1000);
						g_time = (rand() % 3 + 1) * 1000;
						MTGSetTimer(2, g_time);
					}
				}
				break;

			case MY_DOWN:
				if (gg_stage == 100)
				{
					if (_GetTickCount() - g_t2 < 3000)
					{
						if (strcmp(g_directionKey[g_imsi[g_count]], "↓") == 0)
						{
							g_count++;
							for (int i = 0; i < g_fish[random][1]; i++)
							{
								Random_arrow(random, g_imsi[i], i);
							}
						}
						else
						{
							gg_stage = 0;
							g_flag = 0;
							g_count = 0;
							MTGSetTimer(1, 1000);
							g_time = (rand() % 3 + 1) * 1000;
							MTGSetTimer(2, g_time);
						}
					}
					else
					{
						gg_stage = 0;
						g_flag = 0;
						g_count = 0;
						MTGSetTimer(1, 1000);
						g_time = (rand() % 3 + 1) * 1000;
						MTGSetTimer(2, g_time);
					}
				}
				break;

			case MY_LEFT:
				if (gg_stage == 100)
				{
					if (_GetTickCount() - g_t2 < 3000)
					{
						if (strcmp(g_directionKey[g_imsi[g_count]], "←") == 0)
						{
							g_count++;
							for (int i = 0; i < g_fish[random][1]; i++)
							{
								Random_arrow(random, g_imsi[i], i);
							}
						}
						else
						{
							gg_stage = 0;
							g_flag = 0;
							g_count = 0;
							MTGSetTimer(1, 1000);
							g_time = (rand() % 3 + 1) * 1000;
							MTGSetTimer(2, g_time);
						}
					}
					else
					{
						gg_stage = 0;
						g_flag = 0;
						g_count = 0;
						MTGSetTimer(1, 1000);
						g_time = (rand() % 3 + 1) * 1000;
						MTGSetTimer(2, g_time);
					}
				}

				break;

			case MY_RIGHT:
				if (gg_stage == 100)
				{
					if (_GetTickCount() - g_t2 < 3000)
					{
						if (strcmp(g_directionKey[g_imsi[g_count]], "→") == 0)
						{
							g_count++;
							for (int i = 0; i < g_fish[random][1]; i++)
							{
								Random_arrow(random, g_imsi[i], i);
							}
						}
						else
						{
							gg_stage = 0;
							g_flag = 0;
							g_count = 0;
							MTGSetTimer(1, 1000);
							g_time = (rand() % 3 + 1) * 1000;
							MTGSetTimer(2, g_time);
						}
					}
					else
					{
						gg_stage = 0;
						g_flag = 0;
						g_count = 0;
						MTGSetTimer(1, 1000);
						g_time = (rand() % 3 + 1) * 1000;
						MTGSetTimer(2, g_time);
					}
				}
				break;
			case MY_SPACE:

				if (_GetTickCount() - g_t1 < 1000 && g_flag == 0) // 1초뒤엔 입력해도 a안나옴.
				{
					gg_stage = 100;
					MTGKillTimer(2);
					MTGKillTimer(1);
				}
				else if (g_flag == 1) {
					g_flag = 0;
					gg_stage = 0;
					MTGSetTimer(1, 1000);
					g_time = (rand() % 3 + 1) * 1000;
					MTGSetTimer(2, g_time);
				}
				break;

			default:
				for (int i = 0; i < g_fish[random][1]; i++)
				{
					Random_arrow(random, g_imsi[i], i);
				}
				break;
			}
		}

		else if (g_stage == GAME_EXPLAIN)					///////////////////////////GAME_EXPLAIN////////////////////////////////////
		{
			switch (wparam)
			{
			case MY_SPACE:

				system("cls");

				g_stage = GAME_TITLE;

				break;

			default:

				break;
			}
		}

		Draw();

		break;

	case MTG_PAINT:

		Paint();

		break;

	case MTG_TIMER:

		MyTime(wparam, g_stage);

		break;

	case MTG_DESTROY:

		break;

	default:

		break;
	}

	return 0;
}


int main()
{

	srand(time(NULL));

	MTGRun();

	return 0;
}