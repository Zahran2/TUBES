#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

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
    else if (menu == 2)
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
    game.player1.simbol = 'X';
    do
    {
        displayBanner();
        printf("Player 1");
        if (game.player1.simbol == 'X')
        {
            game.player2.simbol = 'O';
        }
        else if (game.player1.simbol == 'O')
        {
            game.player2.simbol = 'X';
        }
        else
        {
            printf("\nInputan salah");
        }
        printf("\nSilahkan masukkan simbol pilihan anda (X/O): ");
        scanf(" %c", &game.player1.simbol);
        game.player1.simbol = toupper(game.player1.simbol);
        system("cls");
    } while (toupper(game.player1.simbol) != 'X' && toupper(game.player1.simbol) != 'O');
}

void newGame()
{
    readUkuran();
    readRonde();
    readNama();
    readSimbol();
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