// testing papan
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>

#define ERROR printf("\n Error! Can't create the log.\n") // Error Message
#define DASH "\n______________________________________\n"

typedef struct // Structure to hold global variables
{
    FILE *logs;
    char player_1;
    char player_2;
    int mode;
    int start;
} Game;
Game game;

void board(int p[9]);
char sign(int x);
void user_move(int p[9], int ply);
int win(int p[9]);
void runGame();
void gotoxy(int x, int y);

char player1, player2;
int giliran;

int main()
{
    printf("Silahkan masukkan giliran (x/o): ");
    scanf("%c", &player1);
    runGame();
}

void runGame()
{
    int places[25] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int i;
    /*if (player1 == 'x')
    {
        player2 = 'o';
        giliran = 0;
        giliranPlayer2 = 1;
    }
    else
    {
        player2 = 'x';
        giliran = 1;
        giliranPlayer2 = 0;
    }*/
    giliran = 0;
    board(places);
    for (i = giliran; i < (25 + giliran) && win(places) == 0; i++)
    {
        if (i % 2 == 0)
        {
            user_move(places, -1);
        }
        else
        {
            user_move(places, 1);
        }
        board(places);
    }
}

int win(int p[25]) //  return current game state.
{
    int chance[28][4] = {   {0, 1, 2, 3}, {1, 2, 3, 4}, {5, 6, 7, 8}, {6, 7, 8, 9}, {10, 11, 12, 13}, {11, 12, 13, 14}, {15, 16, 17, 18}, {16, 17, 18, 19}, {20, 21, 22, 23}, {21, 22, 23, 24},
                            {0, 5, 10, 15}, {5, 10, 15, 20}, {1, 6, 11, 16}, {6, 11, 16, 21}, {2, 7, 12, 17}, {7, 12, 17, 22}, {3, 8, 13, 18}, {8, 13, 18, 23}, {4, 9, 14, 19}, {9, 14, 19, 24},
                            {0, 6, 12, 18}, {6, 12, 18, 24}, {4, 8, 12, 16}, {8, 12, 16, 20}, {1, 7, 13, 19}, {5, 11, 17, 23}, {3, 7, 11, 15}, {9, 13, 17, 21}}; // winning patterns
    for (int i = 0; i < 28; i++)
        if (p[chance[i][0]] != 0 && p[chance[i][0]] == p[chance[i][1]] && p[chance[i][0]] == p[chance[i][2]] && p[chance[i][0]] == p[chance[i][3]])
            return p[chance[i][0]];
    return 0;
}

void board(int p[25]) //  print tic tac toe board.
{
    int i, j;
    j = 0;
    for (i = 0; i < 25; i += 5)
    {
        gotoxy(48, 10 + j);
        printf("\n\t %c | %c | %c | %c | %c", sign(p[i]), sign(p[i + 1]), sign(p[i + 2]), sign(p[i + 3]), sign(p[i + 4]));
        j++;
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

void user_move(int p[25], int ply) // player moves
{
    int position;
    printf("\n Player %c Move : ", sign(ply));
        scanf("%d", &position);
        if (position >= 1 && position <= 25 && p[position - 1] == 0)
        {
            
            if (ply == -1)
            {
                p[position-1] = -1;
            }
            else
            {
                p[position - 1] = 1;
            }
        }
        else
        {
            printf("\n Position is already occupied\n or a Wrong position number.\n");
        }
    /*while (1)
    {
        printf("\n Player %c Move : ", sign(ply));
        scanf("%d", &position);
        if (position >= 1 && position <= 9 && p[position - 1] == 0)
        {
            
            if (ply == -1)
            {
                p[position-1] = -1;
            }
            else
            {
                p[position - 1] = 1;
            }
            //(ply == -1) ? (p[position - 1] = -1) : (p[position - 1] = 1); // make moves based on the player.
            break;
        }
        printf("\n Position is already occupied\n or a Wrong position number.\n");
    }*/
}

void gotoxy(int x, int y)
{
    COORD pos = {x, y}; // sets co-ordinates in(x,y)
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

/*
int main()
{
    int places[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    int s = game.start - 1;

    for (int i = s; i < (9 + s) && win(places) == 0; i++)
    {
        if (i % 2 == 0)
            user_move(places, -1);
        else if (game.mode != 3)
            auto_move(places, ((game.mode == 1) ? 1 : 2), i);
        else
            user_move(places, 1);
        board(places);
    }
}

void board(int p[9]) //  print tic tac toe board.
{
    for (int i = 0; i < 9; i += 3)
        printf("\n\t %c | %c | %c ", sign(p[i]), sign(p[i + 1]), sign(p[i + 2]));
    printf("\n");
}

char sign(int x) //  return ' ', 'X', 'O' for 0, -1 , 1.
{
    return (x == 0) ? ' ' : ((x == -1) ? game.player_1 : game.player_2);
}

void user_move(int p[9], int ply) // player moves
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
}

int win(int p[9]) //  return current game state.
{
    int chance[8][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}}; // winning patterns
    for (int i = 0; i < 8; i++)
        if (p[chance[i][0]] != 0 && p[chance[i][0]] == p[chance[i][1]] && p[chance[i][0]] == p[chance[i][2]])
            return p[chance[i][0]];
    return 0;
}*/