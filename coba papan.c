#include <stdio.h>

#define DASH "\n-------------------\n"

int main()
{
    printf("%s\n", DASH); // print board layout with numbers.
    for (int i = 1; i <= 9; i += 3)
    {
        printf("\t %d | %d | %d \n", i, (i + 1), (i + 2));
    }  
    printf("%s", DASH);
}

