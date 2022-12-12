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
void displayPapan();
void saveFile();
void displayMenu();
void readMenu(int *menu);
void newGame();
void loadGame();
void highScore();
void displayBanner();
void displayGame(int ukuran, int ronde);
void gotoxy(int x, int y);

#define DASH "\n==========================================\n"
int main()
{
    int menu;
    menu = gameMenu();
    if (menu == 1)
    {
        newGame();
        menu = 2;
    }
    if (menu == 2)
    {
        runGame();
    }
    /*
    else if (menu == 3)
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
    } while ((menu < 1 || menu > 3) && menu != 99);
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
    printf("\n\t\t\t\t\t\t\t(1)  NEW GAME  ");
    printf("\n\t\t\t\t\t\t\t(2)  LOAD GAME ");
    printf("\n\t\t\t\t\t\t\t(3)  HIGH SCORE");
    printf("\n\t\t\t\t\t\t\t(99) QUIT GAME ");
}

void readMenu(int *menu)
{
    if ((*menu < 1 || *menu > 3) && *menu != 99)
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
    if (game.ukuran == 1)
    {
        int places[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        ukuran = 3;
    }
    else if (game.ukuran == 2)
    {
        int places[25] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        ukuran = 5;
    }
    else if (game.ukuran == 3)
    {
        int places[49] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        ukuran = 7;
    }
    if (game.ronde == 1)
    {
        ronde = 1;
    }
    else if (game.ronde == 2)
    {
        ronde = 3;
    }
    displayGame(ukuran, ronde);
}

void displayGame(int ukuran, int ronde)
{
    displayBanner();
    if (ukuran == 3)
    {
        printf("\n\t\t\t\t\t\t   PAPAN %dx%d - %d ROUND\n\n", ukuran, ukuran, ronde);
        printf("\n\t\t\t\t\tSKOR : 0                           SKOR : 0\n");
        printf("\n\t\t\t\t\t                 x | o | x                 ");
        printf("\n\t\t\t\t\tPlayer 1        ---|---|---        Player 2");
        printf("\n\t\t\t\t\t   %c             o | x | x            %c   ", game.player1.simbol, game.player2.simbol);
        printf("\n\t\t\t\t\t                ---|---|---                ");
        printf("\n\t\t\t\t\t                 x | o | o                 ");
    }
    else if (ukuran == 5)
    {
        printf("\n\t\t\t\t\t\t PAPAN %dx%d - %d ROUND\n\n", ukuran, ukuran, ronde);
        printf("\n\t\t\t\t    SKOR : 0                             SKOR : 0\n");
        printf("\n\t\t\t\t                  o | x | o | x | o              ");
        printf("\n\t\t\t\t                 ---|---|---|---|---             ");
        printf("\n\t\t\t\t                  x | o | x | o | x              ");
        printf("\n\t\t\t\t    Player 1     ---|---|---|---|---     Player 2");
        printf("\n\t\t\t\t       %c          o | x | o | o | x         %c   ", game.player1.simbol, game.player2.simbol);
        printf("\n\t\t\t\t                 ---|---|---|---|---             ");
        printf("\n\t\t\t\t                  o | x | o | x | x              ");
        printf("\n\t\t\t\t                 ---|---|---|---|---             ");
        printf("\n\t\t\t\t                  x | o | x | x | o              ");
    }
    else if (ukuran == 7)
    {
        printf("\n\t\t\t\t\t\t  PAPAN %dx%d - %d ROUND\n\n", ukuran, ukuran, ronde);
        printf("\n\t\t\t\tSKOR : 0                                       SKOR : 0 \n");
        printf("\n\t\t\t\t               x | o | x | o | x | o | x                ");
        printf("\n\t\t\t\t              ---|---|---|---|---|---|---               ");
        printf("\n\t\t\t\t               o | o | o | x | o | x | o                ");
        printf("\n\t\t\t\t              ---|---|---|---|---|---|---	            ");
        printf("\n\t\t\t\t               x | o | x | o | o | x | x                ");
        printf("\n\t\t\t\tPlayer 1      ---|---|---|---|---|---|---      Player 2 ");
        printf("\n\t\t\t\t   %c           o | o | x | x | x | x | o          %c    ", game.player1.simbol, game.player2.simbol);
        printf("\n\t\t\t\t              ---|---|---|---|---|---|---               ");
        printf("\n\t\t\t\t               x | x | o | x | x | o | x                ");
        printf("\n\t\t\t\t              ---|---|---|---|---|---|---               ");
        printf("\n\t\t\t\t               x | x | o | x | o | x | o                ");
        printf("\n\t\t\t\t              ---|---|---|---|---|---|---               ");
        printf("\n\t\t\t\t               o | x | x | o | x | o | x                ");
    }
    displayPapan();
}

void displayPapan()
{
    if (game.ukuran == 1)
    {
        printf("%s\n", DASH); // print board layout with numbers.
        for (int i = 1; i <= 9; i += 3)
        {
            printf("\t %d | %d | %d \n", i, (i + 1), (i + 2));
            if (i < 9)
            {
                printf("\t---|---|--- \n");
            }
        }
        printf("%s", DASH);
    }
    else if (game.ukuran == 2)
    {
        printf("%s\n", DASH); // print board layout with numbers.
        for (int i = 1; i <= 25; i += 5)
        {

            if (i < 10)
            {
                printf("\t  %d  |  %d  |  %d  |  %d  |  %d  \n", i, (i + 1), (i + 2), (i + 3), (i + 4));
            }
            else if (i > 10)
            {
                printf("\t  %d |  %d |  %d |  %d |  %d \n", i, (i + 1), (i + 2), (i + 3), (i + 4));
            }
            if (i < 25)
            {
                printf("\t-----|-----|-----|-----|----- \n");
            }
        }
        printf("%s", DASH);
    }
    else if (game.ukuran == 3)
    {
        printf("%s\n", DASH); // print board layout with numbers.
        for (int i = 1; i <= 49; i += 7)
        {
            if (i < 8)
            {
                printf("\t  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  \n", i, (i + 1), (i + 2), (i + 3), (i + 4), (i + 5), (i + 6));
            }
            else if (i == 8)
            {
                printf("\t  %d  |  %d  |  %d |  %d |  %d |  %d |  %d \n", i, (i + 1), (i + 2), (i + 3), (i + 4), (i + 5), (i + 6));
            }

            else if (i > 8)
            {
                printf("\t  %d |  %d |  %d |  %d |  %d |  %d |  %d \n", i, (i + 1), (i + 2), (i + 3), (i + 4), (i + 5), (i + 6));
            }

            if (i < 49)
            {
                printf("\t-----|-----|-----|-----|-----|-----|----- \n");
            }
        }
        printf("%s", DASH);
    }
}

void gotoxy(int x, int y)
{
	COORD pos = {x, y}; // sets co-ordinates in(x,y)
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
/*void user_move(int p[9], int ply) // player moves
{
    int position;
    while (1)
    {
        printf("\n Player %c Move : ", sign(ply));
        scanf("%d", &position);
        if (position >= 1 && position <= 9 && p[position - 1] == 0)
        {
            (ply == -1) ? (p[position - 1] = -1) : (p[position - 1] = 1); // make moves based on the player.
            break;
        }
        printf("\n Position is already occupied\n or a Wrong position number.\n");
    }
    (!game.logs) ? ERROR : fprintf(game.logs, "\nPlayer %c Moved to %d.", sign(ply), position);
}*/