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

void gameMenu();
void readUkuran();
void readRonde();
void readNama();
void readSimbol();
void runGame();
void displayGame();
void displayPlayer();
void displayPapan();
void saveFile();
void runGame();

int main()
{
    gameMenu();
    /* printf("%i %i", game.ukuran, game.ronde);
    printf("\n%s", game.player1.nama);
    printf("\n%s", game.player2.nama);
    printf("\n%c", game.player1.simbol);
    printf("\n%c", game.player2.simbol);
    */
}

void gameMenu()
{
    readUkuran();
    readRonde();
    readNama();
    readSimbol();
}

void readUkuran()
{
    game.ukuran = 1;
    do
    {
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
    } while (toupper(game.player1.simbol) != 'X');
}

