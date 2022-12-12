#include <stdio.h>

typedef struct
{
    FILE *save;
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

void readisi(Player *ply);
void saveFile(Player ply);
void readFile(Player ply);
int main(){
    Player ply;
    
 //   readisi(&ply);
 //   saveFile(ply);
    readFile(ply);
    printf("%s",ply.nama);
    return 0;
}
void readisi(Player *ply){
     printf("Nama : ");
     scanf("%[^\n]%*c",&(*ply).nama);
     printf("Score : ");
     scanf("%d",&(*ply).score);
}

void saveFile(Player ply){
    FILE *save = fopen("Data_Highscore.txt","a");
    fprintf(save,"\nNama : %s\nHighscore : %d", &ply.nama, ply.score);
    fclose(save);
}

void readFile(Player ply){
	char a,b;
    FILE *save = fopen("Data_Highscore.txt","r");
    if (NULL == save) {
        printf("file kosong \n");
    }
 
    printf("isi dari file : \n");
 
    while (!feof(save)) {
        a = fgetc(save);
        ply.nama = a;
    }
    fclose(save);
}