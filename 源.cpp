#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>
#include  <Windows.h>
#include <graphics.h>
#include <mmsystem.h>
#pragma comment (lib,"winmm.lib")

#define W 50
#define B 50

int n = 0;
IMAGE wall,space,end,box,boxend,peo;


// 0space  1wall  2end  3box  4peo
int map[4][8][8] = {
    {{1,1,1,1,1,1,1,0},
	 {1,0,0,0,0,0,1,0},
	 {1,4,0,1,0,0,1,1},
	 {1,1,0,1,0,3,0,1},
	 {1,1,0,1,2,0,0,1},
	 {1,2,0,0,3,3,0,1},
	 {1,0,1,1,0,2,0,1},
	 {1,1,1,1,1,1,1,1}},

	{{0,0,1,1,1,0,0,0},
	 {0,0,1,2,1,1,0,0},
	 {0,0,1,0,2,1,1,1},
	 {1,1,1,3,3,3,2,1},
	 {1,2,0,3,4,1,1,1},
	 {1,1,1,1,3,1,0,0},
	 {0,0,0,1,2,1,0,0},
	 {0,0,0,1,1,1,0,0}},
 
    {{0,1,1,1,1,1,1,0}, 
     {0,1,2,2,3,0,1,0},
     {0,1,1,1,0,0,1,1},
     {1,1,0,0,0,3,0,1},
     {1,1,0,0,2,0,0,1},
     {1,0,0,0,3,3,0,1},
     {1,0,1,0,4,2,0,1},
     {1,1,1,1,1,1,1,1}},

	{{1,1,1,1,1,1,1,1},
	 {1,0,0,0,0,0,0,1},
	 {1,0,1,0,1,3,2,1},
	 {1,0,3,0,0,0,2,1},
	 {1,0,1,0,1,3,2,1},
	 {1,0,0,0,1,0,0,1},
	 {1,0,4,0,0,0,0,1},
	 {1,1,1,1,1,1,1,1}}
};

void InitGame() {
	wall, space, end, box, boxend, peo;
	loadimage(&wall,  "wall.PNG" , W, B, false);
	loadimage(&space, "space.PNG", W, B, false);
	loadimage(&end, "end.PNG", W, B, false);
	loadimage(&box, "box.PNG", W, B, false);
	loadimage(&boxend, "boxend.PNG", W, B, false);
	loadimage(&peo, "peo.PNG", W, B, false);
}

void ShowMap() {
	
	system("cls");
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			//printf_s("%d ", map[i][j]);
			switch (map[n][i][j])
			{
			case 0:
				printf_s("  ");
				putimage(j * W, i * B, &space);
				break;

			case 1:
				printf_s("■");
				putimage(j * W, i * B, &wall);
				break;

			case 2:
				printf_s("○");
				putimage(j * W, i * B, &end);
				break;

			case 3:
				printf_s("●");
				putimage(j * W, i * B, &box);
				break;

			case 4:
				printf_s("人");
				putimage(j * W, i * B, &peo);
				break;
            // box+end      not exsite wall+peo
			case 5:
				printf_s("★");
				putimage(j * W, i * B, &boxend);
				break;
			//end+peo
			case 6:
				printf_s("人");
				putimage(j * W, i * B, &peo);
				break;
			default:
				break;
			}
		}
		printf_s("\n");
	}
}

void PlayGame() {
	int r, c;
	char  walk;
	for (r = 0; r < 8; r++)
	{
		for (c = 0; c < 8; c++)
		{
			if (map[n][r][c] == 4|| map[n][r][c] == 6)
			{
				goto next;
			}
		}
	 }
next:
	// 0space  1wall  2end  3box  4peo  
	walk = _getch();
	switch (walk)
	{
	case 'W':
	case 'w':       //上 下 左 右
	case 72:        //72 80 75 77 
		if (map[n][r - 1][c] == 0 || map[n][r - 1][c] == 2)//前面是空地或者终点
		{
			map[n][r - 1][c] += 4;
			map[n][r][c] -= 4;
		}
		if ((map[n][r - 1][c] == 3 || map[n][r - 1][c] == 5)&&(map[n][r - 2][c] == 0 || map[n][r - 2][c] == 2))//前面是箱子或者终点的箱子
		{
			map[n][r - 2][c] += 3;
			map[n][r - 1][c] += 1;
            map[n][r][c] -= 4;
			
		}
		break;
	case 'S':
	case 's':
	case 80 :
		if (map[n][r + 1][c] == 0 || map[n][r + 1][c] == 2)
		{
			map[n][r + 1][c] += 4;
			map[n][r][c] -= 4;
		}
		if ((map[n][r + 1][c] == 3 || map[n][r + 1][c] == 5) && (map[n][r + 2][c] == 0 || map[n][r + 2][c] == 2))
		{
			map[n][r + 2][c] += 3;
			map[n][r + 1][c] += 1;
			map[n][r][c] -= 4;
		}
		break;
	case 'A':
	case 'a':
	case 75 :
		if (map[n][r][c - 1] == 0 || map[n][r][c - 1] == 2)
		{
			map[n][r][c - 1] += 4;
			map[n][r][c] -= 4;
		}
		if ((map[n][r][c - 1] == 3 || map[n][r][c - 1] == 5) && (map[n][r][c - 2] == 0 || map[n][r][c - 2] == 2))
		{
			map[n][r][c - 2] += 3;
			map[n][r][c - 1] += 1;
			map[n][r][c] -= 4;
		}
		break;
	case 'D':
	case 'd':
	case 77 :
		if (map[n][r][c + 1] == 0 || map[n][r][c + 1] == 2)
		{
			map[n][r][c + 1] += 4;
			map[n][r][c] -= 4;
		}
		if ((map[n][r][c + 1] == 3 || map[n][r][c + 1] == 5) && (map[n][r][c + 2] == 0 || map[n][r][c + 2] == 2))
		{
			map[n][r][c + 2] += 3;
			map[n][r][c + 1] += 1;
			map[n][r][c] -= 4;
		}
		break;
	default:
		break;
	}
}

int main() {     
	initgraph(400, 400);
	//initgraph(400, 400, SHOWCONSOLE);
	InitGame();
	system("color 3f");
	system("mode con: cols=78 lines=20");
	PlaySound("The O'Neill Brothers - Canon In D (Piano).wav",NULL,SND_LOOP|SND_FILENAME | SND_ASYNC);//SND_ASYNC 异步
	BOOL gameover;
	while (1) {	

		ShowMap();
        PlayGame();
		gameover = 1;
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (map[n][i][j] == 3 )
				{
					gameover = 0;
				}
			}
		}
		if (gameover)
		{
			ShowMap();
			n++;
		}
		if (n > 3)
		{
			break;
		}
	}
	return 0;
}
