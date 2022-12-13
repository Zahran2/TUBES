#include<stdio.h>
#include <windows.h>
void gotoxy(int x, int y);
int main(){
	gotoxy(17,2);printf("___________  ___  _______    ___________  ________  _______   ___________  ________  ________ ");
	gotoxy(16,3);printf("/___   ____/ /  / /  ____/   /___   ____/ /  __   / /  ____/  /___   ____/ /  __   / /  _____/ ");
	gotoxy(19,4);printf("/  /     /  / /  /           /  /     /  /_/  / /  /          /  /     /  / /  / /  /___    ");
	gotoxy(18,5);printf("/  /     /  / /  /           /  /     /  __   / /  /          /  /     /  / /  / /  ____/    ");
	gotoxy(17,6);printf("/  /     /  / /  /___        /  /     /  / /  / /  /___       /  /     /  /_/  / /  /____     ");
	gotoxy(16,7);printf("/__/     /__/ /______/       /__/     /__/ /__/ /______/      /__/     /_______/ /_______/     ");
	return 0;
}
void gotoxy(int x, int y)
{
	COORD pos = {x, y}; // sets co-ordinates in(x,y)
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
