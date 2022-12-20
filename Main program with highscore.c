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
    int score;
} Highscore;

typedef struct
{
    int papan[49];
} Papan;


typedef struct
{
    int ukuran;
    int timer;
    Papan papan;
    Player player1;
    Player player2;
    Player pemenang;
} Game;
Game game;
Highscore data[100];
Highscore score;
FILE *save;
/*
prosedur untuk menjalankan timer
I.S = timer belum berjalan
F.S = timer sudah berjalan
*/
void *timer();

/*
function untuk menu game, akan mengembalikkan 1 untuk memulai game, 2 untuk memunculkan highscore, atau 99 untuk exit
*/
int gameMenu();

/*
prosedur untuk membaca ukuran dari keyboard
I.S = ukuran belum terbaca dari keyboard
F.S = ukuran sudah terbaca dari keyboard
*/
void readUkuran();

/*  
prosedur untuk membaca nama dari keyboard
I.S = nama belum terbaca dari keyboard
F.S = nama sudah terbaca dari keyboard
*/
void readNama();

/*
prosedur untuk membaca simbol dari keyboard
I.S = simbol belum terbaca dari keyboard
F.S = simbol belum terbaca dari keyboard
*/
void readSimbol();

/*
prosedur menjalankan gameplay
I.S = gameplay belum dijalankan
F.S = gameplay sudah dijalankan
*/
void runGame();

/*
prosedur untuk display game
I.S = game belum ditampilkan
F.S = game sudah ditampilkan
*/
void displayGame();

/*
prosedur display papan 3 x 3
I.S = papan 3 x 3 belum ditampilkan
F.S = papan 3 x 3 sudah ditampilkan
*/
void displayPapan1();

/*
prosedur display papan 5 x 5
I.S = papan 5 x 5 belum ditampilkan
F.S = papan 5 x 5 sudah ditampilkan
*/
void displayPapan2();

/*
prosedur display papan 7 x 7
I.S = papan 7 x 7 belum ditampilkan
F.S = papan 7 x 7 sudah ditampilkan
*/
void displayPapan3();

/*
prosedur display menu
I.S = menu belum ditampilkan
F.S = menu sudah ditampilkan
*/
void displayMenu();

/*
prosedur untuk membaca menu dari keyboard
I.S = menu belum terbaca dari keyboard
F.S = menu sudah terbaca dari keyboard
*/
void readMenu(int *menu);

/*
prosedur untuk menjalankan permulaan game
I.S = game belum dimulai
F.S = game sudah dimulai
*/
void newGame();

/*
prosedur display banner
I.S = banner belum ditampilkan
F.S = banner sudah ditampilkan
*/
void displayBanner(); 	

/*
prosedur display gameplay
I.S = game belum ditampilkan
F.S = game sudah ditampilkan
*/
void displayGame();

/*
prosedur untuk memindahkan cursor sesuai koordinat
I.S = cursor belum berpindah
F.S = cursor sudah berpindah
*/
void gotoxy(int x, int y);

/*
fungsi untuk mengecek tanda yang harus dikirim ke papan, akan mengembalikan ' ' jika 0, 'x' jika -1, atau 'o' jika 1
*/
char sign(int tandaAngka);	

/*
fungsi untuk mengecek kondisi menang papan 3 x 3, akan mengembalikan -1 jika 'x' yang menang, 0 untuk tidak terpenuhi kondisi menangnya, atau 1 jika 'o' yang menang
*/
int win1();

/*
fungsi untuk mengecek kondisi menang papan 5 x 5, akan mengembalikan -1 jika 'x' yang menang, 0 untuk tidak terpenuhi kondisi menangnya, atau 1 jika 'o' yang menang
*/
int win2();

/*
fungsi untuk mengecek kondisi menang papan 7 x 7, akan mengembalikan -1 jika 'x' yang menang, 0 untuk tidak terpenuhi kondisi menangnya, atau 1 jika 'o' yang menang
*/
int win3();

/*
prosedur untuk menampung pergerakan pemain dari keyboard untuk papan 3 x 3
I.S = pergerakan pemain belum ditampung dari keyboard untuk papan 3 x 3
F.S = pergerakan pemain sudah ditampung dari keyboard untuk papan 3 x 3
*/
void userMove1(int ply);

/*
prosedur untuk menampung pergerakan pemain dari keyboard untuk papan 5 x 5
I.S = pergerakan pemain belum ditampung dari keyboard untuk papan 5 x 5
F.S = pergerakan pemain sudah ditampung dari keyboard untuk papan 5 x 5
*/
void userMove2(int ply);

/*
prosedur untuk menampung pergerakan pemain dari keyboard untuk papan 7 x 7
I.S = pergerakan pemain belum ditampung dari keyboard untuk papan 7 x 7
F.S = pergerakan pemain sudah ditampung dari keyboard untuk papan 7 x 7
*/
void userMove3(int ply);

/*
prosedur untuk menentukan hasil permainan 
I.S = hasil permainan belum ditentukan
F.S = hasil permainan sudah ditentukan 
*/
void result(int statusMenang);

/*
prosedur untuk menampilkan papan petunjuk
I.S = papan petunjuk belum ditampilkan
F.S = papan petunjuk sudah ditampilkan
*/
void displayPetunjuk();

/*
proedur untuk membaca dan menambahkan score pemain
I. S = nilai score pemain belum terbaca
F. S = nilai score pemain sudah terbaca dan jika pernah bermain sebelumnya kemudian score ditambah
*/
void readHighScore();

/*
prosedur untuk mengambil data pemain dari file
I. S = data dari file belum terambil
F. S = data dari file sudah diambil dan dimasukkan kedalam array
*/
void readDataHighscore();

/*
prosedur untuk menyimpan data pemain kedalam file
I. S = data belum disimpan kedalam file
F. S = data sudah disimpan kedalam file
*/
void saveFile();

/*
prosedur untuk menampilkan highscore dari pemain yang sudah main sebelumnya
I. S = highscore dari pemain belum ditampilkan 
F. S = highscore dari pemain sudah ditampilkan
*/
void displayhighScore();

/*
prosedur untuk mensorting data pemain berdasarkan score secara descending
I. S = data pemain belum terurut
F. S = data pemain sudah terurut
*/
void sortdata();

/*
prosedur untuk menampilkan how to play
I.S = how to play belum ditampilkan
F.S = how to play sudah ditampilkan
*/
void displayHowToPlay();

// var untuk menghentikan thread timer
int stopThread;
// var untuk menentukan timer sudah habis atau belum
int waktuHabis; 
// var untuk thread baru
pthread_t t; 

#define DASH "=========================================="

int main()
{
    int menu;
    while(menu != 99){
    menu = gameMenu();
    if (menu == 1)
    {
        newGame();
        runGame();
        system("pause");
        system("cls");
    }
    else if (menu == 2)
    {
        readDataHighscore();
        sortdata();
        // for(int i = 0; i<100; i++){
        //     printf("%s %d\n", data[i].pemenang.nama, data[i].pemenang.highscore);
        // }
        displayhighScore();
        system("pause");
        system("cls");
    }
    else if (menu == 3)
    {
        displayHowToPlay();
        system("pause");
        system("cls");
    }}
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
    gotoxy(39,7);printf(" _   _   __     __    _   _   __  __       ");
    gotoxy(39,8);printf("| |_| | |__| | |  |  | |_| | |_  |  | |  | ");
    gotoxy(39,9);printf("|     | |  | | |  |  |     | |__ |  | |__| \n");
    gotoxy(53,11);printf("(1)  GAME  ");
    gotoxy(53,12);printf("(2)  HIGH SCORE");
    gotoxy(53,13);printf("(3)  HOW TO PLAY");
    gotoxy(53,14);printf("(99) QUIT GAME ");
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
    int ukuran;
    ukuran = 1;
    do
    {
        displayBanner();
        printf("\nMenu Ukuran Papan");
        printf("\n(1) 3 x 3");
        printf("\n(2) 5 x 5");
        printf("\n(3) 7 x 7");
        if (ukuran < 1 || ukuran > 3)
        {
            printf("\nInputan salah!");
        }
        printf("\nSilahkan masukkan ukuran papan: ");
        scanf("%i", &ukuran);
        system("cls");
    } while (ukuran < 1 || ukuran > 3);
    if (ukuran == 1)
    {
        game.ukuran = 3;
    }
    else if (ukuran == 2)
    {
        game.ukuran = 5;
    }
    else if (ukuran == 3)
    {
        game.ukuran = 7;
    }
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
    int draw;
    for (int i = 0; i < 49; i++)
    {
        game.papan.papan[i] = 0;
    }
    draw = 1;
    if (game.ukuran == 3)
    {
        int i;
        for (i = 0; i < 9 && win1() == 0; i++)
        {
            displayGame();
            displayPapan1();
            displayPetunjuk();
            if (i % 2 == 0)
            {
                userMove1(-1);
            }
            else
            {
                userMove1(1);
            }
            displayPapan1();
        }
        displayGame();
        displayPapan1();
        result(win1());
        if (win1() != 0)
        {
            draw = 0;
        }
    }
    else if (game.ukuran == 5)
    {
        int i;
        for (i = 0; i < 25 && win2() == 0; i++)
        {
            displayGame();
            displayPapan2();
            displayPetunjuk();
            if (i % 2 == 0)
            {
                userMove2(-1);
            }
            else
            {
                userMove2(1);
            }
            displayPapan2();
        }
        displayGame();
        displayPapan2();
        result(win2());
        if (win2() != 0)
        {
            draw = 0;
        }
    }
    else if (game.ukuran == 7)
    {
        
        int i;
        for (i = 0; i < 49 && win3() == 0; i++)
        {
            displayGame();
            displayPapan3();
            displayPetunjuk();
            if (i % 2 == 0)
            {
                userMove3(-1);
            }
            else
            {
                userMove3(1);
            }
            displayPapan3();
        }
        displayGame();
        displayPapan3();
        result(win3());
        if (win3() != 0)
        {
            draw = 0;
        }
    }
    if (draw == 0)
    {
        readHighScore();
        saveFile();
    }
}

void displayGame()
{
    displayBanner();
    if (game.ukuran == 3)
    {
        gotoxy(55, 8);
        printf("PAPAN %d x %d", game.ukuran, game.ukuran);
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
    else if (game.ukuran == 5)
    {
        gotoxy(52, 8);
        printf("PAPAN %d x %d", game.ukuran, game.ukuran);
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
    else if (game.ukuran == 7)
    {
        gotoxy(54, 9);
        printf("PAPAN %d x %d", game.ukuran, game.ukuran);
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

void displayPapan1()
{
    int i, j;
    j = 0;
    for (i = 0; i < 9; i += 3)
    {
        gotoxy(56, 10 + j);
        printf(" %c | %c | %c ", sign(game.papan.papan[i]), sign(game.papan.papan[i + 1]), sign(game.papan.papan[i + 2]));
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

void displayPapan2()
{
    int i, j;
    j = 0;
    for (i = 0; i < 25; i += 5)
    {
        gotoxy(48, 10 + j);
        printf(" %c | %c | %c | %c | %c ", sign(game.papan.papan[i]), sign(game.papan.papan[i + 1]), sign(game.papan.papan[i + 2]), sign(game.papan.papan[i + 3]), sign(game.papan.papan[i + 4]));
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

void displayPapan3()
{
    int i, j;
    j = 0;
    for (i = 0; i < 49; i += 7)
    {
        gotoxy(46, 11 + j);
        printf(" %c | %c | %c | %c | %c | %c | %c ", sign(game.papan.papan[i]), sign(game.papan.papan[i + 1]), sign(game.papan.papan[i + 2]), sign(game.papan.papan[i + 3]), sign(game.papan.papan[i + 4]), sign(game.papan.papan[i + 5]), sign(game.papan.papan[i + 6]));
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

char sign(int tandaAngka)
{
    char tanda;
    if (tandaAngka == 0)
    {
        tanda = ' ';
    }
    else if (tandaAngka == -1)
    {
        tanda = 'x';
    }
    else if (tandaAngka == 1)
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

int win1()
{
    int chance[8][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};
    for (int i = 0; i < 8; i++)
    {
        if (game.papan.papan[chance[i][0]] != 0 && game.papan.papan[chance[i][0]] == game.papan.papan[chance[i][1]] && game.papan.papan[chance[i][0]] == game.papan.papan[chance[i][2]])
        {
            return game.papan.papan[chance[i][0]];
        }
    }
    return 0;
}

int win2()
{
    int chance[28][4] = {   {0, 1, 2, 3}, {1, 2, 3, 4}, {5, 6, 7, 8}, {6, 7, 8, 9}, {10, 11, 12, 13}, {11, 12, 13, 14}, {15, 16, 17, 18}, {16, 17, 18, 19}, {20, 21, 22, 23}, {21, 22, 23, 24}, 
                            {0, 5, 10, 15}, {5, 10, 15, 20}, {1, 6, 11, 16}, {6, 11, 16, 21}, {2, 7, 12, 17}, {7, 12, 17, 22}, {3, 8, 13, 18}, {8, 13, 18, 23}, {4, 9, 14, 19}, {9, 14, 19, 24}, 
                            {0, 6, 12, 18}, {6, 12, 18, 24}, {4, 8, 12, 16}, {8, 12, 16, 20}, {1, 7, 13, 19}, {5, 11, 17, 23}, {3, 7, 11, 15}, {9, 13, 17, 21}};
    for (int i = 0; i < 28; i++)
    {
        if (game.papan.papan[chance[i][0]] != 0 && game.papan.papan[chance[i][0]] == game.papan.papan[chance[i][1]] && game.papan.papan[chance[i][0]] == game.papan.papan[chance[i][2]] && game.papan.papan[chance[i][0]] == game.papan.papan[chance[i][3]])
        {
            return game.papan.papan[chance[i][0]];
        }
    }
    return 0;
}

int win3()
{
    int chance[60][5] = { {0, 1, 2, 3, 4}, {1, 2, 3, 4, 5}, {2, 3, 4, 5, 6}, {7, 8, 9, 10, 11}, {8, 9, 10, 11, 12}, {9, 10, 11, 12, 13}, {14, 15, 16, 17, 18}, {15, 16, 17, 18, 19}, {16, 17, 18, 19, 20}, {21, 22, 23, 24, 25}, {22, 23, 24, 25, 26}, {23, 24, 25, 26, 27}, {28, 29, 30, 31, 32}, {29, 30, 31, 32, 33}, {30, 31, 32, 33, 34}, {35, 36, 37, 38, 39}, {36, 37, 38, 39, 40}, {37, 38, 39, 40, 41}, {42, 43, 44, 45, 46}, {43, 44, 45, 46, 47}, {44, 45, 46, 47, 48},
                        {0, 7, 14, 21, 28}, {7, 14, 21, 28, 35}, {14, 21, 28, 35, 42}, {1, 8, 15, 22, 29}, {8, 15, 22, 29, 36}, {15, 22, 29, 36, 43}, {2, 9, 16, 23, 30}, {9, 16, 23, 30, 37}, {16, 23, 30, 37, 44}, {3, 10, 17, 24, 31}, {10, 17, 24, 31, 38}, {17, 24, 31, 38, 45}, {4, 11, 18, 25, 32}, {11, 18, 25, 32, 39}, {18, 25, 32, 39, 46}, {5, 12, 19, 26, 33}, {12, 19, 26, 33, 40}, {19, 26, 33, 40, 47}, {6, 13, 20, 27, 34}, {13, 20, 27, 34, 41}, {20, 27, 34, 41, 48},
                        {0, 8, 16, 24, 32}, {8, 16, 24, 32, 40}, {16, 24, 32, 40, 48}, {6, 12, 18, 24, 30}, {12, 18, 24, 30, 36}, {18, 24, 30, 36, 42}, {7, 15, 23, 31, 39}, {15, 23, 31, 39, 47}, {14, 22, 30, 38, 46}, {1, 9, 17, 25, 33}, {9, 17, 25, 33, 41}, {2, 10, 18, 26, 34}, {5, 11, 17, 23, 29}, {11, 17, 23, 29, 35}, {4, 10, 16, 22, 28}, {13, 19, 25, 31, 37}, {19, 25, 31, 37, 43}, {20, 26, 32, 38, 44}};
    for (int i = 0; i < 60; i++)
    {
        if (game.papan.papan[chance[i][0]] != 0 && game.papan.papan[chance[i][0]] == game.papan.papan[chance[i][1]] && game.papan.papan[chance[i][0]] == game.papan.papan[chance[i][2]] && game.papan.papan[chance[i][0]] == game.papan.papan[chance[i][3]] && game.papan.papan[chance[i][0]] == game.papan.papan[chance[i][4]])
        {
            return game.papan.papan[chance[i][0]];
        }
    }
    return 0;
}

void *timer()
{
	while (game.timer >= 0 && stopThread == 0)
	{
		sleep(1);
		if (game.ukuran == 3)
		{
			gotoxy(33, 18);
			printf("Silahkan masukkan input[%d]: ", game.timer);
		}
		else if (game.ukuran == 5)
		{
			gotoxy(33, 22);
			printf("Silahkan masukkan input[%d]: ", game.timer);
		}
		else if (game.ukuran == 7)
		{
			gotoxy(33, 27);
			printf("Silahkan masukkan input[%d]: ", game.timer);
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

void userMove1(int ply)
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

        if (position >= 1 && position <= 9 && game.papan.papan[position - 1] == 0)
        {

            if (ply == -1)
            {
            game.papan.papan[position - 1] = -1;
            }
            else
            {
            game.papan.papan[position - 1] = 1;
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

void userMove2(int ply)
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

        if (position >= 1 && position <= 25 && game.papan.papan[position - 1] == 0)
        {

            if (ply == -1)
            {
            game.papan.papan[position - 1] = -1;
            }
            else
            {
            game.papan.papan[position - 1] = 1;
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

void userMove3(int ply)
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

        if (position >= 1 && position <= 49 && game.papan.papan[position - 1] == 0)
        {
            if (ply == -1)
            {
            game.papan.papan[position - 1] = -1;
            }
            else
            {
            game.papan.papan[position - 1] = 1;
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

void result(int statusMenang)

{
    game.player1.score = 0;
    game.player2.score = 0;
    game.pemenang.score = 0;
    if (statusMenang != 0)
    {
        if (statusMenang == -1)
        {
            if (game.player1.simbol == 'x')
            {
                printf("\n\t\t\t\t\t\t%s IS THE WINNER!", game.player1.nama);
                game.player1.score++;
                game.pemenang.score = game.player1.score;
                strcpy(game.pemenang.nama, game.player1.nama);
            }
            else if (game.player1.simbol == 'o')
            {
                printf("\n\t\t\t\t\t\t%s IS THE WINNER!", game.player2.nama);
                game.player2.score++;
                game.pemenang.score = game.player2.score;
                strcpy(game.pemenang.nama, game.player2.nama);
            }
        }
        else
        {
            if (game.player1.simbol == 'o')
            {
                printf("\n\t\t\t\t\t\t%s IS THE WINNER!", game.player1.nama);
                game.player1.score++;
                game.pemenang.score = game.player1.score;
                strcpy(game.pemenang.nama, game.player1.nama);
            }
            else if (game.player1.simbol == 'x')
            {
                printf("\n\t\t\t\t\t\t%s IS THE WINNER!", game.player2.nama);
                game.player2.score++;
                game.pemenang.score = game.player2.score;
                strcpy(game.pemenang.nama, game.player2.nama);
            }
        }
    }
    else
    {
        printf("\n\t\t\t\t\t\tDRAW!");
    }
}

void displayPetunjuk()
{
    if (game.ukuran == 3)
    {
        printf("\n\n\n\n\n\n\n\t\t\t\t\t%s\n", DASH);
        for (int i = 1; i <= 9; i += 3)
        {
            printf("\t\t\t\t\t\t\t %d | %d | %d \n", i, (i + 1), (i + 2));
        }
        printf("\t\t\t\t\t%s\n", DASH);
    }
    else if (game.ukuran == 5)
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
    else if (game.ukuran == 7)
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

void readHighScore(){
    int i=0,sama;

    strcpy(score.nama, game.pemenang.nama);
    score.score = game.pemenang.score;
    readDataHighscore();
    for(i = 0; i < 100; i++){
        if(strcmp(score.nama, data[i].nama)==0){
            data[i].score = data[i].score + 1;
            i=100;
        }
    }
    if(i==100){
    strcpy(data[20].nama, score.nama);
    data[20].score = score.score;
    }
}

void saveFile(){
    FILE *save = fopen("Data_Highscore.txt","w");
    sortdata();
    for(int i=0;i<100;i++){
    fprintf(save,"%s %d\n", &(data[i]).nama, data[i].score);
    }
    fclose(save);
}

void readDataHighscore(){
    FILE *save;
    int i=0;
    char ch;
    save = fopen("Data_Highscore.txt", "r");
    if(NULL == save) {
        printf("File kosong \n"); 
    }

    while (ch!=EOF){
        fscanf(save," %s %d", &data[i].nama, &data[i].score);
        ch=fgetc(save);
        i++;
    }
    fclose(save);
}

void displayhighScore(){
    int i=0,k=13;
    displayBanner();
    gotoxy(46,10);
    printf("=====================");
    gotoxy(46,11);
    printf("|\t    HIGH SCORE\t  |");
    gotoxy(46,12);
    printf("=====================");
    gotoxy(46,13);
    printf("| 1 |               |");
    gotoxy(46,14);
    printf("=====================");
    // gotoxy(46,15);
    // printf("| 2 |               |");
    // gotoxy(46,16);
    // printf("=====================");
    // gotoxy(46,17);
    // printf("| 3 |               |");
    // gotoxy(46,18);
    // printf("=====================");
    // gotoxy(46,19);
    // printf("| 4 |               |");
    // gotoxy(46,20);
    // printf("=====================");
    // gotoxy(46,21);
    // printf("| 5 |               |");
    // gotoxy(46,22);
    // printf("=====================");
    // while(i < 5)
    // {
        i=0;
        gotoxy(48,k);
        printf("%d | %s  %d",i+1,data[i].nama, data[i].score);
        // i++;
        // k=k+2;
    //}
    printf("\n\n");
}

void sortdata(){
    Highscore temp;
    for (int i=0; i < (100-1); i++){
        for (int j=0 ; j< (99-i);j++){
            if ((data[j].score < data[j+1].score)&& (data[j+1].score != 0)){
                strcpy(temp.nama, data[j].nama);
                temp.score = data[j].score;
                strcpy(data[j].nama, data[j+1].nama);
                data[j].score = data[j+1].score;
                strcpy(data[j+1].nama, temp.nama);
                data[j+1].score = temp.score;
            }
        }
    }
}

void displayHowToPlay()
{
    displayBanner();
    gotoxy(37,7);printf("      __            ___  __     __       __        ");
    gotoxy(37,8);printf("|__| |  | |  _  |    |  |  |   |__| |   |__| |__|  ");
    gotoxy(37,9);printf("|  | |__| |_| |_|    |  |__|   |    |__ |  |  __| \n");
    gotoxy(10,11);printf("1. Untuk memulai permainan, pada display menu pilihlah new game.");
    gotoxy(10,12);printf("2. Setelah memilih new game, pilihlah  ukuran papan permainan yang akan dimainkan (3x3,5x5,7x7).");
    gotoxy(10,13);printf("3. Input nama dari kedua pemain sebagai petunjuk pemain pertama dan kedua akan memakai simbol apa saat");
    gotoxy(13,14);printf("bermain.");
    gotoxy(10,15);printf("4. Mulailah bermain dengan ketentuan permainan Tic-Tac-Toe.");
    gotoxy(10,16);printf("5. Permainan Tic-Tac-Toe adalah permainan yang memberikan kondisi menang Ketika ada beberapa simbol sejajar");
    gotoxy(13,17);printf("dengan ketentuan tertentu sesuai jenis ukuran papan yang dipilih");
    gotoxy(10,18);printf("6. Pada papan 3x3, maka pemain harus membubat simbol berderet 3 bidang secara horizontal,vertical, atau");
    gotoxy(13,19);printf("diagonal.");
    gotoxy(10,20);printf("7. Pada papan 5x5, maka pemain harus membubat simbol berderet 4 bidang secara horizontal,vertical,diagonal.");
    gotoxy(10,21);printf("8. Pada papan 7x7, maka pemain harus membubat simbol berderet 5 bidang secara horizontal,vertical,diagonal.");
    gotoxy(10,22);printf("9. Jika kondisi pada nomer 6-8 terpenuhi pada ukuran papan yang sesuai maka kondisi menang ada di tangan anda.");
    gotoxy(10,23);printf("10. Sebaliknya jika lawan bisa lebih cepat, maka pihak lawan yang akan memenangkan permainan.");
    gotoxy(10,24);printf("11. Jika menang dalam satu ronde, nama akan dicatat dan diberi poin 1(bersifat kumulatif).");
    gotoxy(10,25);printf("12. Jika terjadi kondisi seri, maka kedua pemain tidak mendapatkan poin (0 poin).");
    gotoxy(10,26);printf("13. Jika kalah dalam satu ronde, pemain tidak akan mendapatkan poin (0 poin");
    gotoxy(10,27);printf("14. Terdapat fitur highscore, sehingga nama pemain yang memiliki poin lebih tinggi akan dicatat dan terlihat");
    gotoxy(13,28);printf("di program.");
    gotoxy(10,29);printf("15. Jika ingin melihat highscore keseluruhan bisa memilih di bagian main menu game pada awal program.");
    gotoxy(10,30);printf("16. Jika ingin exit saat bermain dapat memilih quit game di main menu game.");
    gotoxy(50,32);printf("SELAMAT BERMAIN!!!!!");
    gotoxy(50,33);
}
