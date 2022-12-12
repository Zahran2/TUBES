#include<stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
void gotoxy(int x, int y);
int main(){
    int ukuran,ronde;
    scanf("%d",&ukuran);
if (ukuran == 3)
    {
        gotoxy(53,6);printf("PAPAN x -  ROUND");
        gotoxy(40,8);printf("SKOR : 0                           SKOR : 0");
        gotoxy(56,9);printf(" x | o | x ");
        gotoxy(40,10);printf("Player 1        ---|---|---        Player 2");
        gotoxy(40,11);printf("   x             o | x | x            o   ");
        gotoxy(56,12);printf("---|---|---                ");
        gotoxy(56,13);printf(" x | o | o                 ");
    }
    else if (ukuran == 5)
    {
        gotoxy(49,6);printf("PAPAN x - 1 ROUND");
        gotoxy(35,8);printf("SKOR : 0                             SKOR : 0");
        gotoxy(48,9);printf(" o | x | o | x | o ");
        gotoxy(48,10);printf("---|---|---|---|---");
        gotoxy(48,11);printf(" x | o | x | o | x ");
        gotoxy(35,12);printf("Player 1     ---|---|---|---|---     Player 2");
        gotoxy(38,13);printf("x          o | x | o | o | x         o   ");
        gotoxy(48,14);printf("---|---|---|---|---");
        gotoxy(48,15);printf(" o | x | o | x | x ");
        gotoxy(48,16);printf("---|---|---|---|---");
        gotoxy(48,17);printf(" x | o | x | x | o ");
    }
    else if (ukuran == 7)
    {
        gotoxy(50,6);printf("PAPAN x - 1 ROUND");
        gotoxy(33,8);printf("SKOR : 0                                     SKOR : 0");
        gotoxy(46,10);printf(" x | o | x | o | x | o | x  ");
        gotoxy(46,11);printf("---|---|---|---|---|---|---");
        gotoxy(46,12);printf(" o | o | o | x | o | x | o ");
        gotoxy(46,13);printf("---|---|---|---|---|---|---");
        gotoxy(46,14);printf(" x | o | x | o | o | x | x ");
        gotoxy(33,15);printf("Player 1     ---|---|---|---|---|---|---     Player 2 ");
        gotoxy(36,16);printf("x          o | o | x | x | x | x | o         o    ");
        gotoxy(46,17);printf("---|---|---|---|---|---|---");
        gotoxy(46,18);printf(" x | x | o | x | x | o | x ");
        gotoxy(46,19);printf("---|---|---|---|---|---|---");
        gotoxy(46,20);printf(" x | x | o | x | o | x | o ");
        gotoxy(46,21);printf("---|---|---|---|---|---|---");
        gotoxy(46,22);printf(" o | x | x | o | x | o | x ");
    }
    return 0;
}
void gotoxy(int x, int y)
{
	COORD pos = {x, y}; // sets co-ordinates in(x,y)
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
