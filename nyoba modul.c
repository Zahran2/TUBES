#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include <pthread.h>

typedef struct
{
    char nama[11];
    char simbol;
    int score;
} Player;

typedef struct
{
    char nama[11];
    int highscore;
} Highscore;

typedef struct
{
    int ukuran;
    int timer;
    Player player1;
    Player player2;
} Game;
Game game;

void *timer();  //  prosedur untuk menampilkan timer
                //  I.S = timer belum muncul
                //  F.S = timer sudah muncul
int gameMenu(); //  function untuk menu game, akan mengembalikkan 1 atau 99
void readUkuran();  //prosedur untuk membaca ukuran dari keyboard
                    //  I.S = ukuran belum terbaca dari keyboard
                    //  F.S = ukuran sudah terbaca dari keyboard
void readNama();    //  prosedur untuk membaca nama dari keyboard
                    //  I.S = nama belum terbaca dari keyboard
                    //  F.S = nama sudah terbaca dari keyboard
void readSimbol();  //  prosedur untuk membaca simbol dari keyboard
                    //  I.S = simbol belum terbaca dari keyboard
                    //  F.S = simbol belum terbaca dari keyboard
void runGame(); //  prosedur menjalankan gameplay
                //  I.S = gameplay belum dijalankan
                //  F.S = gameplay sudah dijalankan
void displayGame(); //  prosedur untuk display game
                    //  I.S = game belum ditampilkan
                    //  F.S = game sudah ditampilkan
void displayPapan1(int p[9]);   //  prosedur display papan 3 x 3
                                //  I.S = papan 3 x 3 belum ditampilkan
                                //  F.S = papan 3 x 3 sudah ditampilkan
void displayPapan2(int p[25]);  //  prosedur display papan 5 x 5
                                // I.S = papan 5 x 5 belum ditampilkan
                                // F.S = papan 5 x 5 sudah ditampilkan
void displayPapan3(int p[49]);  //  prosedur display papan 7 x 7
                                //  I.S = papan 7 x 7 belum ditampilkan
                                //  F.S = papan 7 x 7 sudah ditampilkan
void displayMenu(); //  prosedur display menu
                    //  I.S = menu belum ditampilkan
                    //  F.S = menu sudah ditampilkan
void readMenu(int *menu);   //  prosedur untuk membaca menu dari keyboard
                            //  I.S = menu belum terbaca dari keyboard
                            //  F.S = menu sudah terbaca dari keyboard
void newGame(); //  prosedur untuk menjalankan permulaan game
                //  I.S = game belum dimulai
                //  F.S = game sudah dimulai
void displayBanner();   //  prosedur display banner
                        //  I.S = banner belum ditampilkan
                        //  F.S = banner sudah ditampilkan
void displayGame(int ukuran);   //  prosedur display gameplay
                                //  I.S = game belum ditampilkan
                                //  F.S = game sudah ditampilkan
void gotoxy(int x, int y);  //  prosedur untuk memindahkan cursor sesuai koordinat
                            //  I.S = cursor belum berpindah
                            //  F.S = cursor sudah berpindah
char sign(int x);   //  fungsi untuk mengecek tanda yang harus dikirim ke papan, akan mengembalikan ' ', 'x', atau 'o'
int win1(int p[9]); //  fungsi untuk mengecek kondisi menang papan 3 x 3, akan mengembalikan -1, 0, atau 1
int win2(int p[25]);    //  fungsi untuk mengecek kondisi menang papan 5 x 5, akan mengembalikan -1, 0, atau 1
int win3(int p[49]);    //  fungsi untuk mengecek kondisi menang papan 7 x 7, akan mengembalikan -1, 0, atau 1
void userMove1(int p[9], int ply);  //  prosedur untuk menampung pergerakan pemain dari keyboard papan 3 x 3
                                    //  I.S = pergerakan pemain belum ditampung dari keyboard papan 3 x 3
                                    //  F.S = pergerakan pemain sudah ditampung dari keyboard papan 3 x 3
void userMove2(int p[25], int ply); //  prosedur untuk menampung pergerakan pemain dari keyboard papan 5 x 5
                                    //  I.S = pergerakan pemain belum ditampung dari keyboard papan 5 x 5
                                    //  F.S = pergerakan pemain sudah ditampung dari keyboard papan 5 x 5
void userMove3(int p[49], int ply); //  prosedur untuk menampung pergerakan pemain dari keyboard papan 7 x 7
                                    //  I.S = pergerakan pemain belum ditampung dari keyboard papan 7 x 7
                                    //  F.S = pergerakan pemain sudah ditampung dari keyboard papan 7 x 7
void result(int r); //  prosedur untuk menampilkan pemenang 
                    //  I.S = pemenang belum ditampilkan
                    //  F.S = pemenang sudah ditampilkan
void displayPetunjuk(int ukuran);   //  prosedur untuk menampilkan papan petunjuk
                                    //  I.S = papan petunjuk belum ditampilkan
                                    //  F.S = papan petunjuk sudah ditampilkan

int stopThread; //  var untuk memberhentikan thread timer
int waktuHabis; //  var untuk menentukan timer sudah habis atau belum

pthread_t t;

#define DASH "=========================================="

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
    gotoxy(17, 1);
    printf("___________  ___  _______    ___________  ________  _______   ___________  ________  ________ ");
    gotoxy(16, 2);
    printf("/___   ____/ /  / /  ____/   /___   ____/ /  __   / /  ____/  /___   ____/ /  __   / /  _____/ ");
    gotoxy(19, 3);
    printf("/  /     /  / /  /           /  /     /  /_/  / /  /          /  /     /  / /  / /  /___    ");
    gotoxy(18, 4);
    printf("/  /     /  / /  /           /  /     /  __   / /  /          /  /     /  / /  / /  ____/    ");
    gotoxy(17, 5);
    printf("/  /     /  / /  /___        /  /     /  / /  / /  /___       /  /     /  /_/  / /  /____     ");
    gotoxy(16, 6);
    printf("/__/     /__/ /______/       /__/     /__/ /__/ /______/      /__/     /_______/ /_______/     ");
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
        printf("\nMenu Ukuran Papan");
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

void readNama()
{
    displayBanner();
    printf("\nPlayer 1");
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
        printf("\nPlayer 1");
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
    readNama();
    readSimbol();
}

void runGame()
{
    int ukuran;
    if (game.ukuran == 1)
    {
        int places[9] = {   0, 0, 0, 
                            0, 0, 0, 
                            0, 0, 0};
        ukuran = 3;
        int i;
        for (i = 0; i < 9 && win1(places) == 0; i++)
        {
            displayGame(ukuran);
            displayPapan1(places);
            displayPetunjuk(ukuran);
            if (i % 2 == 0)
            {
                userMove1(places, -1);
            }
            else
            {
                userMove1(places, 1);
            }
            displayPapan1(places);
        }
        displayGame(ukuran);
        displayPapan1(places);
        result(win1(places));
    }
    else if (game.ukuran == 2)
    {
        int places[25] = {  0, 0, 0, 0, 0, 
                            0, 0, 0, 0, 0, 
                            0, 0, 0, 0, 0, 
                            0, 0, 0, 0, 0, 
                            0, 0, 0, 0, 0};
        ukuran = 5;
        int i;
        for (i = 0; i < 25 && win2(places) == 0; i++)
        {
            // system("cls");
            displayGame(ukuran);
            displayPapan2(places);
            displayPetunjuk(ukuran);
            if (i % 2 == 0)
            {
                userMove2(places, -1);
            }
            else
            {
                userMove2(places, 1);
            }
            displayPapan2(places);
        }
        displayGame(ukuran);
        displayPapan2(places);
        result(win2(places));
    }
    else if (game.ukuran == 3)
    {
        int places[49] = {  0, 0, 0, 0, 0, 0, 0, 
                            0, 0, 0, 0, 0, 0, 0, 
                            0, 0, 0, 0, 0, 0, 0, 
                            0, 0, 0, 0, 0, 0, 0, 
                            0, 0, 0, 0, 0, 0, 0, 
                            0, 0, 0, 0, 0, 0, 0, 
                            0, 0, 0, 0, 0, 0, 0};
        ukuran = 7;
        int i;
        for (i = 0; i < 49 && win3(places) == 0; i++)
        {
            // system("cls");
            displayGame(ukuran);
            displayPapan3(places);
            displayPetunjuk(ukuran);
            if (i % 2 == 0)
            {
                userMove3(places, -1);
            }
            else
            {
                userMove3(places, 1);
            }
            displayPapan3(places);
        }
        displayGame(ukuran);
        displayPapan3(places);
        result(win3(places));
    }
}

void displayGame(int ukuran)
{
    displayBanner();
    if (ukuran == 3)
    {
        gotoxy(55, 8);
        printf("PAPAN %d x %d", ukuran, ukuran);
        if (game.player1.simbol == 'x')
        {
            gotoxy(40, 11);
            printf("%s", game.player1.nama);
            gotoxy(75, 11);
            printf("%s", game.player2.nama);
        }
        else
        {
            gotoxy(40, 11);
            printf("%s", game.player2.nama);
            gotoxy(75, 11);
            printf("%s", game.player1.nama);
        }
        
        gotoxy(40, 12);
        printf("   x                                  o   ");
    }
    else if (ukuran == 5)
    {
        gotoxy(52, 8);
        printf("PAPAN %d x %d", ukuran, ukuran);
        if (game.player1.simbol == 'x')
        {
            gotoxy(35, 13);
            printf("%s", game.player1.nama);
            gotoxy(72, 13);
            printf("%s", game.player2.nama);
        }
        else
        {
            gotoxy(35, 13);
            printf("%s", game.player2.nama);
            gotoxy(72, 13);
            printf("%s", game.player1.nama);
        }
        gotoxy(38, 14);
        printf("x                                    o   ");
    }
    else if (ukuran == 7)
    {
        gotoxy(54, 9);
        printf("PAPAN %d x %d", ukuran, ukuran);
        if (game.player1.simbol == 'x')
        {
            gotoxy(33, 16);
            printf("%s", game.player1.nama);
            gotoxy(78, 16);
            printf("%s", game.player2.nama);
        }
        else
        {
            gotoxy(33, 16);
            printf("%s", game.player2.nama);
            gotoxy(78, 16);
            printf("%s", game.player1.nama);
        }
        gotoxy(36, 17);
        printf("x                                            o    ");
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
        j++;

        if (i < 6)
        {
            gotoxy(56, 10 + j);
            printf("---|---|---");
        }
        j++;
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
        j++;
        if (i < 20)
        {
            gotoxy(48, 10 + j);
            printf("---|---|---|---|---");
        }
        j++;
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
        j++;
        if (i < 36)
        {
            gotoxy(46, 11 + j);
            printf("---|---|---|---|---|---|---");
        }
        j++;
    }
    printf("\n");
}

char sign(int x) //  return ' ', 'X', 'O' if 0, -1 , 1.
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

int win1(int p[9])
{
    int chance[8][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};
    for (int i = 0; i < 8; i++)
        if (p[chance[i][0]] != 0 && p[chance[i][0]] == p[chance[i][1]] && p[chance[i][0]] == p[chance[i][2]])
            return p[chance[i][0]];
    return 0;
}

int win2(int p[25])
{
    int chance[28][4] = {   {0, 1, 2, 3}, {1, 2, 3, 4}, {5, 6, 7, 8}, {6, 7, 8, 9}, {10, 11, 12, 13}, {11, 12, 13, 14}, {15, 16, 17, 18}, {16, 17, 18, 19}, {20, 21, 22, 23}, {21, 22, 23, 24}, 
                            {0, 5, 10, 15}, {5, 10, 15, 20}, {1, 6, 11, 16}, {6, 11, 16, 21}, {2, 7, 12, 17}, {7, 12, 17, 22}, {3, 8, 13, 18}, {8, 13, 18, 23}, {4, 9, 14, 19}, {9, 14, 19, 24}, 
                            {0, 6, 12, 18}, {6, 12, 18, 24}, {4, 8, 12, 16}, {8, 12, 16, 20}, {1, 7, 13, 19}, {5, 11, 17, 23}, {3, 7, 11, 15}, {9, 13, 17, 21}};
    for (int i = 0; i < 28; i++)
        if (p[chance[i][0]] != 0 && p[chance[i][0]] == p[chance[i][1]] && p[chance[i][0]] == p[chance[i][2]] && p[chance[i][0]] == p[chance[i][3]])
            return p[chance[i][0]];
    return 0;
}

int win3(int p[49])
{
    int chance[60][5] = { {0, 1, 2, 3, 4}, {1, 2, 3, 4, 5}, {2, 3, 4, 5, 6}, {7, 8, 9, 10, 11}, {8, 9, 10, 11, 12}, {9, 10, 11, 12, 13}, {14, 15, 16, 17, 18}, {15, 16, 17, 18, 19}, {16, 17, 18, 19, 20}, {21, 22, 23, 24, 25}, {22, 23, 24, 25, 26}, {23, 24, 25, 26, 27}, {28, 29, 30, 31, 32}, {29, 30, 31, 32, 33}, {30, 31, 32, 33, 34}, {35, 36, 37, 38, 39}, {36, 37, 38, 39, 40}, {37, 38, 39, 40, 41}, {42, 43, 44, 45, 46}, {43, 44, 45, 46, 47}, {44, 45, 46, 47, 48},
                        {0, 7, 14, 21, 28}, {7, 14, 21, 28, 35}, {14, 21, 28, 35, 42}, {1, 8, 15, 22, 29}, {8, 15, 22, 29, 36}, {15, 22, 29, 36, 43}, {2, 9, 16, 23, 30}, {9, 16, 23, 30, 37}, {16, 23, 30, 37, 44}, {3, 10, 17, 24, 31}, {10, 17, 24, 31, 38}, {17, 24, 31, 38, 45}, {4, 11, 18, 25, 32}, {11, 18, 25, 32, 39}, {18, 25, 32, 39, 46}, {5, 12, 19, 26, 33}, {12, 19, 26, 33, 40}, {19, 26, 33, 40, 47}, {6, 13, 20, 27, 34}, {13, 20, 27, 34, 41}, {20, 27, 34, 41, 48},
                        {0, 8, 16, 24, 32}, {8, 16, 24, 32, 40}, {16, 24, 32, 40, 48}, {6, 12, 18, 24, 30}, {12, 18, 24, 30, 36}, {18, 24, 30, 36, 42}, {7, 15, 23, 31, 39}, {15, 23, 31, 39, 47}, {14, 22, 30, 38, 46}, {1, 9, 17, 25, 33}, {9, 17, 25, 33, 41}, {2, 10, 18, 26, 34}, {5, 11, 17, 23, 29}, {11, 17, 23, 29, 35}, {4, 10, 16, 22, 28}, {13, 19, 25, 31, 37}, {19, 25, 31, 37, 43}, {20, 26, 32, 38, 44}};
    for (int i = 0; i < 60; i++)
        if (p[chance[i][0]] != 0 && p[chance[i][0]] == p[chance[i][1]] && p[chance[i][0]] == p[chance[i][2]] && p[chance[i][0]] == p[chance[i][3]] && p[chance[i][0]] == p[chance[i][4]])
            return p[chance[i][0]];
    return 0;
}

void *timer()
{
	while (game.timer >= 0 && stopThread == 0)
	{
		sleep(1);
		if (game.ukuran == 1)
		{
			gotoxy(30, 18);
			printf("   Silahkan masukkan input[%d]: ", game.timer);
		}
		else if (game.ukuran == 2)
		{
			gotoxy(30, 22);
			printf("   Silahkan masukkan input[%d]: ", game.timer);
		}
		else if (game.ukuran == 3)
		{
			gotoxy(30, 27);
			printf("   Silahkan masukkan input[%d]: ", game.timer);
		}
		game.timer--;
	}
	if (stopThread == 1)
	{
		return NULL;
	}
	else
	{
		waktuHabis = 1;
        system("cls");
		printf("\n\n\t\t\t\tWaktu habis! Ketik 0 untuk berganti giliran! ");
		return NULL;
	}
	
}

void userMove1(int p[9], int ply)
{
    int position;
    int salah;
	game.timer = 10;

    do
    {
        waktuHabis = 0;
		stopThread = 0;
        gotoxy(55, 16);
        printf("Player %c Move", sign(ply));
		pthread_create(&t, NULL, &timer, NULL);
        scanf("%d", &position);
		stopThread = 1;
		pthread_join(t,NULL);

		if (waktuHabis == 1)
		{
			break;
		}

        if (position >= 1 && position <= 9 && p[position - 1] == 0)
        {

            if (ply == -1)
            {
            p[position - 1] = -1;
            }
            else
            {
            p[position - 1] = 1;
            }
            salah = 0;
            system("cls");
        }
        else
        {
            salah = 1;
            printf("\n\t\t\t\t\tPOSISI SUDAH DIISI ATAU SALAH INPUT POSISI!");
        }
    } while (salah == 1);
    
    
}

void userMove2(int p[25], int ply)
{
    int position;
    int salah;
	game.timer = 10;
    do
    {
        waktuHabis = 0;
		stopThread = 0;
        gotoxy(51, 20);
        printf("Player %c Move", sign(ply));
		pthread_create(&t, NULL, &timer, NULL);
        scanf("%d", &position);
		stopThread = 1;
		pthread_join(t, NULL);

		if (waktuHabis == 1)
		{
			break;
		}

        if (position >= 1 && position <= 25 && p[position - 1] == 0)
        {

            if (ply == -1)
            {
            p[position - 1] = -1;
            }
            else
            {
            p[position - 1] = 1;
            }
            salah = 0;
            system("cls");
        }
        else
        {
            salah = 1;
            printf("\n\t\t\t\t\tPOSISI SUDAH DIISI ATAU SALAH INPUT POSISI!");
        }
    } while (salah == 1);
}

void userMove3(int p[49], int ply)
{
    int position;
    int salah;
	game.timer = 10;
    do
    {
        waktuHabis = 0;
		stopThread = 0;
        gotoxy(53, 25);
        printf("Player %c Move", sign(ply));
		pthread_create(&t, NULL, &timer, NULL);
        scanf("%d", &position);
		stopThread = 1;
		pthread_join(t, NULL);

		if (waktuHabis == 1)
		{
			break;
		}

        if (position >= 1 && position <= 49 && p[position - 1] == 0)
        {
            if (ply == -1)
            {
            p[position - 1] = -1;
            }
            else
            {
            p[position - 1] = 1;
            }
            salah = 0;
            system("cls");
        }
        else
        {
            salah = 1;
            printf("\n\t\t\t\t\tPOSISI SUDAH DIISI ATAU SALAH INPUT POSISI!");
        }
    } while (salah == 1);
}

void result(int r)

{
    if (r != 0)
    {
        if (r == -1)
        {
            if (game.player1.simbol == 'x')
            {
                printf("\n\t\t\t\t\t\t%s IS THE WINNER!", game.player1.nama);
            }
            else
            {
                printf("\n\t\t\t\t\t\t%s IS THE WINNER!", game.player2.nama);
            }
        }
        else
        {
            if (game.player1.simbol == 'o')
            {
                printf("\n\t\t\t\t\t\t%s IS THE WINNER!", game.player1.nama);
            }
            else
            {
                printf("\n\t\t\t\t\t\t%s IS THE WINNER!", game.player2.nama);
            }
        }
    }
    else
    {
        printf("\n\t\t\t\t\t\tDRAW!");
    }
}

void displayPetunjuk(int ukuran)
{
    if (ukuran == 3)
    {
        printf("\n\n\n\n\n\n\n\t\t\t\t\t%s\n", DASH);
        for (int i = 1; i <= 9; i += 3)
        {
            printf("\t\t\t\t\t\t\t %d | %d | %d \n", i, (i + 1), (i + 2));
        }
        printf("\t\t\t\t\t%s\n", DASH);
    }
    else if (ukuran == 5)
    {
        printf("\n\n\n\n\n\n\n\t\t\t\t      %s\n", DASH);
        for (int i = 1; i <= 25; i += 5)
        {
            if ( i < 10)
            {
                printf("\t\t\t\t\t\t%d  | %d  | %d  | %d  | %d\n", i, (i + 1), (i + 2), (i + 3), (i + 4));
            }
            else
            {
                printf("\t\t\t\t\t\t%d | %d | %d | %d | %d\n", i, (i + 1), (i + 2), (i + 3), (i + 4));
            }
            
        }
        printf("\t\t\t\t      %s\n", DASH);
    }
    else if (ukuran == 7)
    {
        printf("\n\n\n\n\n\n\n\t\t\t\t      %s\n", DASH);
        for (int i = 1; i <= 49; i += 7)
        {
            if (i < 15)
            {
                if (i < 8)
                {
                    printf("\t\t\t\t\t   %d  | %d  | %d  | %d  | %d  | %d  | %d\n", i, (i + 1), (i + 2), (i + 3), (i + 4), (i + 5), (i + 6));
                }
                else
                {
                    printf("\t\t\t\t\t   %d  | %d  | %d | %d | %d | %d | %d\n", i, (i + 1), (i + 2), (i + 3), (i + 4), (i + 5), (i + 6));
                }
            }   
            else
            {
                printf("\t\t\t\t\t   %d | %d | %d | %d | %d | %d | %d\n", i, (i + 1), (i + 2), (i + 3), (i + 4), (i + 5), (i + 6));
            }
            
        }
        printf("\t\t\t\t      %s\n", DASH);
    }
}

/*int main(int argc, char *argv[])
{
	pthread_t t1;
	int test;
	
	pthread_create(&t1, NULL, &routine, NULL);
	printf("Silahkan masukkan input: ");
	scanf("%d", &test);
	printf("%d", test);
	pthread_join(t1, NULL);
	
	gotoxy(1, 1);
	printf("masuk");
	gotoxy(1, 1);
	printf("keluar");
	return 0;
}
*/