
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