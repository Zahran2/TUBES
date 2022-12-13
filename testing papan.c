// testing papan
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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

char player1, player2;
int giliran;

int main()
{
    printf("Silahkan masukkan giliran (x/o): ");
    scanf("%c", &player1);
    if (player1 == 'x')
    {
        player2 = 'o';
    }
    runGame();
}

void runGame()
{
    int places[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
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
    for (i = giliran; i < (9 + giliran) && win(places) == 0; i++)
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
    result(win(places));
}

int win(int p[9]) //  return current game state.
{
    int chance[8][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}}; // winning patterns
    for (int i = 0; i < 8; i++)
        if (p[chance[i][0]] != 0 && p[chance[i][0]] == p[chance[i][1]] && p[chance[i][0]] == p[chance[i][2]])
            return p[chance[i][0]];
    return 0;
}

void board(int p[9]) //  print tic tac toe board.
{
    for (int i = 0; i < 9; i += 3)
        printf("\n\t %c | %c | %c ", sign(p[i]), sign(p[i + 1]), sign(p[i + 2]));
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

void user_move(int p[9], int ply) // player moves
{
    int position;
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

void result(int r) //  write game results.

{
    if (r != 0)
    {
        if (r == -1)
        {
            printf("%c IS THE WINNER!", player1);
        }
        else
        {
            printf("%c IS THE WINNER!", player2);
        }
    }
    else
    {
        printf("DRAW!");
    }
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