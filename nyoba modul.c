#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>

typedef struct
{
    char nama[100];
    char simbol;
    int score;
    int highscore;
} Player;

typedef struct
{
    int ukuran;
    int ronde;
    int giliran;
    Player player1;
    Player player2;
} Game;
Game game;

int gameMenu();
void readUkuran();
void readRonde();
void readNama();
void readSimbol();
void runGame();
void displayGame();
void displayPlayer();
void displayPapan1(int p[9]);
void displayPapan2(int p[25]);
void displayPapan3(int p[49]);
void saveFile();
void displayMenu();
void readMenu(int *menu);
void newGame();
void highScore();
void displayBanner();
void displayGame(int ukuran, int ronde);
void gotoxy(int x, int y);
char sign(int x);

#define DASH "\n==========================================\n"

int main()
{
    int menu;
    menu = gameMenu();
    if (menu == 1)
    {
        newGame();
        runGame();
    }
    /*if (menu == 2)
    {
        highScore();
    }
    */
    printf("%d", menu);
    printf("%d %d", game.ukuran, game.ronde);
    printf("%c %c", game.player1.simbol, game.player2.simbol);
    printf("%s", game.player1.nama);
    printf("%s", game.player2.nama);
    return 0;
}

int gameMenu()
{
    int menu;
    menu = 1;
    do
    {
        displayMenu();
        readMenu(&menu);
        system("cls");
    } while ((menu < 1 || menu > 2) && menu != 99);
    return menu;
}

void displayBanner()
{
    printf("\n\t\t ___________  ___  _______    ___________  ________  _______   ___________  ________  ________ ");
    printf("\n\t\t/___   ____/ /  / /  ____/   /___   ____/ /  __   / /  ____/  /___   ____/ /  __   / /  _____/ ");
    printf("\n\t\t   /  /     /  / /  /           /  /     /  /_/  / /  /          /  /     /  / /  / /  /___    ");
    printf("\n\t\t  /  /     /  / /  /           /  /     /  __   / /  /          /  /     /  / /  / /  ____/    ");
    printf("\n\t\t /  /     /  / /  /___        /  /     /  / /  / /  /___       /  /     /  /_/  / /  /____     ");
    printf("\n\t\t/__/     /__/ /______/       /__/     /__/ /__/ /______/      /__/     /_______/ /_______/     \n");
}

void displayMenu()
{
    displayBanner();
    printf("\n\t\t\t\t\t _   _   __     __    _   _   __  __       ");
    printf("\n\t\t\t\t\t| |_| | |__| | |  |  | |_| | |_  |  | |  | ");
    printf("\n\t\t\t\t\t|     | |  | | |  |  |     | |__ |  | |__| \n");
    printf("\n\t\t\t\t\t\t\t(1)  GAME  ");
    printf("\n\t\t\t\t\t\t\t(2)  HIGH SCORE");
    printf("\n\t\t\t\t\t\t\t(99) QUIT GAME ");
}

void readMenu(int *menu)
{
    if ((*menu < 1 || *menu > 2) && *menu != 99)
    {
        printf("\nInputan salah!");
    }
    printf("\nSilahkan masukkan input: ");
    scanf("%d", &(*menu));
}

void readUkuran()
{
    system("cls");
    game.ukuran = 1;
    do
    {
        displayBanner();
        printf("Menu Ukuran Papan");
        printf("\n(1) 3 x 3");
        printf("\n(2) 5 x 5");
        printf("\n(3) 7 x 7");
        if (game.ukuran < 1 || game.ukuran > 3)
        {
            printf("\nInputan salah!");
        }
        printf("\nSilahkan masukkan ukuran papan: ");
        scanf("%i", &game.ukuran);
        system("cls");
    } while (game.ukuran < 1 || game.ukuran > 3);
}

void readRonde()
{
    game.ronde = 1;
    do
    {
        displayBanner();
        printf("Menu Ronde");
        printf("\n(1) Best of 1");
        printf("\n(2) Best of 3");
        if (game.ronde < 1 || game.ronde > 2)
        {
            printf("\nInputan salah!");
        }
        printf("\nSilahkan masukkan pilihan ronde: ");
        scanf("%i", &game.ronde);
        system("cls");
    } while (game.ronde < 1 || game.ronde > 2);
}

void readNama()
{
    displayBanner();
    printf("Player 1");
    printf("\nSilahkan masukkan nama anda: ");
    scanf(" %[^\n]%*c", game.player1.nama);
    printf("Player 2");
    printf("\nSilahkan masukkan nama anda: ");
    scanf(" %[^\n]%*c", game.player2.nama);
    system("cls");
}

void readSimbol()
{
    game.player1.simbol = 'x';
    do
    {
        displayBanner();
        printf("Player 1");
        if (game.player1.simbol == 'x')
        {
            game.player2.simbol = 'o';
        }
        else if (game.player1.simbol == 'o')
        {
            game.player2.simbol = 'x';
        }
        else
        {
            printf("\nInputan salah");
        }
        printf("\nSilahkan masukkan simbol pilihan anda (x/o): ");
        scanf(" %c", &game.player1.simbol);
        game.player1.simbol = tolower(game.player1.simbol);
        system("cls");
    } while (tolower(game.player1.simbol) != 'x' && tolower(game.player1.simbol) != 'o');
}

void newGame()
{
    readUkuran();
    readRonde();
    readNama();
    readSimbol();
}

void runGame()
{
    int ukuran;
    int ronde;
    int i;

    if (game.ronde == 1)
    {
        ronde = 1;
    }
    else if (game.ronde == 2)
    {
        ronde = 3;
    }

    for (i = 1; i <= ronde; i++)
    {
        if (game.ukuran == 1)
        {
            int places[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
            ukuran = 3;
            system("cls");
            displayGame(ukuran, ronde);
            displayPapan1(places);
            
        }
        else if (game.ukuran == 2)
        {
            int places[25] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
            ukuran = 5;
            system("cls");
            displayGame(ukuran, ronde);
            displayPapan2(places);
            
        }
        else if (game.ukuran == 3)
        {
            int places[49] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
            ukuran = 7;
            system("cls");
            displayGame(ukuran, ronde);
            displayPapan3(places);
            
        }
    }
    
}

void displayGame(int ukuran, int ronde)
{
    displayBanner();
    if (ukuran == 3)
    {
        gotoxy(53, 7);
        printf("PAPAN %d x %d - %d ROUND", ukuran, ukuran, ronde);
        gotoxy(40, 9);
        printf("SKOR : 0                           SKOR : 0");
        gotoxy(56, 10);
        printf(" x | o | x ");
        gotoxy(40, 11);
        printf("Player 1        ---|---|---        Player 2");
        gotoxy(40, 12);
        printf("   x             o | x | x            o   ");
        gotoxy(56, 13);
        printf("---|---|---                ");
        gotoxy(56, 14);
        printf(" x | o | o                 ");
    }
    else if (ukuran == 5)
    {
        gotoxy(49, 7);
        printf("PAPAN %d x %d - %d ROUND", ukuran, ukuran, ronde);
        gotoxy(35, 9);
        printf("SKOR : 0                             SKOR : 0");
        gotoxy(48, 10);
        printf(" o | x | o | x | o ");
        gotoxy(48, 11);
        printf("---|---|---|---|---");
        gotoxy(48, 12);
        printf(" x | o | x | o | x ");
        gotoxy(35, 13);
        printf("Player 1     ---|---|---|---|---     Player 2");
        gotoxy(38, 14);
        printf("x          o | x | o | o | x         o   ");
        gotoxy(48, 15);
        printf("---|---|---|---|---");
        gotoxy(48, 16);
        printf(" o | x | o | x | x ");
        gotoxy(48, 17);
        printf("---|---|---|---|---");
        gotoxy(48, 18);
        printf(" x | o | x | x | o ");
    }
    else if (ukuran == 7)
    {
        gotoxy(50, 7);
        printf("PAPAN %d x %d - %d ROUND", ukuran, ukuran, ronde);
        gotoxy(33, 9);
        printf("SKOR : 0                                     SKOR : 0");
        gotoxy(46, 11);
        printf(" x | o | x | o | x | o | x  ");
        gotoxy(46, 12);
        printf("---|---|---|---|---|---|---");
        gotoxy(46, 13);
        printf(" o | o | o | x | o | x | o ");
        gotoxy(46, 14);
        printf("---|---|---|---|---|---|---");
        gotoxy(46, 15);
        printf(" x | o | x | o | o | x | x ");
        gotoxy(33, 16);
        printf("Player 1     ---|---|---|---|---|---|---     Player 2 ");
        gotoxy(36, 17);
        printf("x          o | o | x | x | x | x | o         o    ");
        gotoxy(46, 18);
        printf("---|---|---|---|---|---|---");
        gotoxy(46, 19);
        printf(" x | x | o | x | x | o | x ");
        gotoxy(46, 20);
        printf("---|---|---|---|---|---|---");
        gotoxy(46, 21);
        printf(" x | x | o | x | o | x | o ");
        gotoxy(46, 22);
        printf("---|---|---|---|---|---|---");
        gotoxy(46, 23);
        printf(" o | x | x | o | x | o | x ");
    }
}

void displayPapan1(int p[9])
{
    int i, j;
    j = 0;
    for (i = 0; i < 9; i += 3)
    {
        gotoxy(56, 10 + j);
        printf(" %c | %c | %c ", sign(p[i]), sign(p[i + 1]), sign(p[i + 2]));
        j += 2;
    }
    printf("\n");
}

void displayPapan2(int p[25])
{
    int i, j;
    j = 0;
    for (i = 0; i < 25; i += 5)
    {
        gotoxy(48, 10 + j);
        printf(" %c | %c | %c | %c | %c ", sign(p[i]), sign(p[i + 1]), sign(p[i + 2]), sign(p[i + 3]), sign(p[i + 4]));
        j += 2;
    }
    printf("\n");
}

void displayPapan3(int p[49])
{
    int i, j;
    j = 0;
    for (i = 0; i < 49; i += 7)
    {
        gotoxy(46, 11 + j);
        printf(" %c | %c | %c | %c | %c | %c | %c ", sign(p[i]), sign(p[i + 1]), sign(p[i + 2]), sign(p[i + 3]), sign(p[i + 4]), sign(p[i + 5]), sign(p[i + 6]));
        j += 2;
    }
    printf("\n");
}

char sign(int x) //  return ' ', 'X', 'O' for 0, -1 , 1.
{
    char tanda;
    if (x == 0)
    {
        tanda = ' ';
    }
    else if (x == -1)
    {
        tanda = 'x';
    }
    else if (x == 1)
    {
        tanda = 'o';
    }

    return tanda;
}

void gotoxy(int x, int y)
{
    COORD pos = {x, y}; // sets co-ordinates in(x,y)
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}