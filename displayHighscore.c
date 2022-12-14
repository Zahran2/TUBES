#include<stdio.h>
#include<windows.h>

void displayHighscore();
void gotoxy();

int main(){
    displayHighscore();
    return 0;
}

void displayHighscore(){
    gotoxy(20,10);
    printf("========================");
    gotoxy(20,11);
    printf("|      HIGH SCORE      |");
    gotoxy(20,12);
    printf("========================");
    gotoxy(20,13);
    printf("| 1 |                  |");
    gotoxy(20,14);
    printf("========================");
    gotoxy(20,15);
    printf("| 2 |                  |");
    gotoxy(20,16);
    printf("========================");
    gotoxy(20,17);
    printf("| 3 |                  |");
    gotoxy(20,18);
    printf("========================");
}
       
    void gotoxy(int x, int y)
    {
    COORD pos = {x, y}; // sets co-ordinates in(x,y)
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    }
                