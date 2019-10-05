#include "Turboc.h" //������� �߰��Ұ�. 
#include <ctype.h>


#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define MAXSTAGE 4
#define putchxy(x,y,c) {gotoxy(x,y);putch(c);}
#define SCREANX 21
#define SCREANY 14 
void DrawScreen();
BOOL TestEnd();
void Move(int dir);

char ns[SCREANY][SCREANX];
int nStage;
int nx, ny;
int nMove;

char arStage[MAXSTAGE][SCREANY][SCREANX] = {
		{
			"                    ",
			"                    ",
			"                    ",
			"      #####         ",
			"      #   #         ",
			"      #   ###       ",
			"      #OOOX #       ",
			"      #...  #       ",
			"      #######       ",
			"                    ",
			"                    ",
			"                    ",
			"                    ",
			"                    "
		},
		{
			"                    ",
			"                    ",
			"                    ",
			"        #####       ",
			"       ##   ##      ",
			"       # .O. #      ",
			"       # O#O #      ",
			"       # .O. #      ",
			"       #  X ##      ",
			"       ##  ##       ",
			"        ####        ",
			"                    ",
			"                    ",
			"                    "
		},
		{
			"                    ",
			"                    ",
			"                    ",
			"    ######          ",
			"    #    #          ",
			"    # OO ###        ",
			"    ### X  #        ",
			"      #  . #        ",
			"      ## .##        ",
			"       ####         ",
			"                    ",
			"                    ",
			"                    ",
			"                    "
		},
		{
			"                    ",
			"                    ",
			"    #####           ",
			"   ## X ####        ",
			"   #  #  . ##       ",
			"   # #      #       ",
			"   # OO #.  #       ",
			"   ##    ####       ",
			"    ##   #          ",
			"     #####          ",
			"                    ",
			"                    ",
			"                    ",
			"                    "
		},

};
void main()
{
	int ch;
	int x, y;
	setcursortype(NOCURSOR);
	gotoxy(20, 4);
	printf("Push Push Game");
	gotoxy(12, 5);
	printf("Made by Kim JiAe, Boo Jae Hyuck");
	gotoxy(12, 12);
	printf("������ ���������� ������[ 1 - %d ] : ", MAXSTAGE);
	scanf("%d", &nStage);
	nStage--;
	for (; 1;) {
		memcpy(ns, arStage[nStage], sizeof(ns));
		for (y = 0; y<SCREANY; y++) {
			for (x = 0; x<SCREANX - 1; x++) {
				if (ns[y][x] == 'X') {
					nx = x;
					ny = y;
					ns[y][x] = ' ';
				}
			}
		}
		clrscr();
		nMove = 0;
		for (; 2;) {
			DrawScreen();
			ch = getch();
			if (ch == 0xE0 || ch == 0) {
				ch = getch();
				switch (ch) {
				case LEFT:
				case RIGHT:
				case UP:
				case DOWN:
					Move(ch);
					break;
				}
			}
			else {
				ch = tolower(ch);
				if (ch == 'c' || ch == 'C') {
					break;
				}
				if (ch == 'n' || ch == 'N') {
					if (nStage < MAXSTAGE - 1) {
						nStage++;
					}
					break;
				}
				if (ch == 'p' || ch == 'P') {
					if (nStage > 0) {
						nStage--;
					}
					break;
				}
				if (ch == 'q' || ch == 'Q') {
					setcursortype(NORMALCURSOR);
					exit(0);
				}
			}

			if (TestEnd()) {
				clrscr();
				gotoxy(10, 10);
				printf("%d ���������� Ǯ�����ϴ�. ���� ���������� �̵��մϴ�", nStage + 1);
				delay(2000);
				if (nStage < MAXSTAGE - 1) {
					nStage++;
				}
				break;
			}
		}
	}
}

void DrawScreen()
{
	int x, y;
	for (y = 0; y<SCREANY; y++) {
		for (x = 0; x<SCREANX - 1; x++) {
			putchxy(x, y, ns[y][x]);
		}
	}

	putchxy(nx, ny, 'X');
	gotoxy(30, 1); puts("��������������������������");
	gotoxy(30, 2); puts("��                      ��");
	gotoxy(30, 3); puts("��    PUSHPUSH GAME     ��");
	gotoxy(30, 4); puts("��                      ��");
	gotoxy(30, 5); puts("��  Q:����, C:�ٽ� ���� ��");
	gotoxy(30, 6); puts("��  P:���� N:����       ��");
	gotoxy(30, 7); puts("��                      ��");
	gotoxy(30, 8); printf("��  �������� : %d        ��", nStage + 1);
	gotoxy(30, 9); puts("��                      ��");
	gotoxy(30, 10); printf("��  �̵�Ƚ�� : %-4d     ��", nMove);
	gotoxy(30, 11); puts("��                      ��");
	gotoxy(30, 12); puts("��  0 : ��  X  : ����� ��");
	gotoxy(30, 13); puts("�� .���� ���� �ű⼼��  ��");
	gotoxy(30, 14); puts("��                      ��");
	gotoxy(30, 15); puts("��������������������������");

}

BOOL TestEnd()
{
	int x, y;
	for (y = 0; y<SCREANY; y++) {
		for (x = 0; x<SCREANX - 1; x++) {
			if (arStage[nStage][y][x] == '.' && ns[y][x] != 'O') {
				return FALSE;
			}
		}
	}
	return TRUE;
}

void Move(int dir)
{
	int dx = 0, dy = 0;
	switch (dir) {
	case LEFT:
		dx = -1;
		break;
	case RIGHT:
		dx = 1;
		break;
	case UP:
		dy = -1;
		break;
	case DOWN:
		dy = 1;
		break;
	}
	if (ns[ny + dy][nx + dx] != '#') {
		if (ns[ny + dy][nx + dx] == 'O') {
			if (ns[ny + dy * 2][nx + dx * 2] == ' ' || ns[ny + dy * 2][nx + dx * 2] == '.') {
				if (arStage[nStage][ny + dy][nx + dx] == '.') {
					ns[ny + dy][nx + dx] = '.';
				}
				else {
					ns[ny + dy][nx + dx] = ' ';
				}
				ns[ny + dy * 2][nx + dx * 2] = 'O';
			}
			else {
				return;
			}
		}
		nx += dx;
		ny += dy;
		nMove++;
	}
}
