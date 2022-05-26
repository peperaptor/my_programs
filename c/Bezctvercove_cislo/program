#include <stdio.h>
#define SIZE_NUMB 199999

typedef struct
{
    char touched;
    char isSquarefree;
} Numb;

int RemoveAllCurr(Numb *numb, int step)
{
    for (int i = 2*step; i < SIZE_NUMB; i+=step)
    {
        if (!numb[i].touched)
        {
            numb[i].isSquarefree = 0;
        }
        numb[i].touched = 0;
    }
    return 0;
}

int ReplaceAllCurr(Numb *numb, int step)
{
    for (int i = step; i < SIZE_NUMB; i+=step)
    {
        if (!numb[i].isSquarefree)
        {
            numb[i].isSquarefree = 1;
            numb[i].touched = 1;
        }
    }
    return 0;
}

int GetSquarefree(Numb *numb)
{
    RemoveAllCurr(numb, 2);
    for (int i = 3; i < SIZE_NUMB; i++)
    {
        if (numb[i].isSquarefree)
        {
            ReplaceAllCurr(numb, i);
            RemoveAllCurr(numb, i);
        }
    }
    return 0;
}

int GetArrayOfSquarefree(Numb *numb, int *cisla)
{
    for (int i = 0; i < SIZE_NUMB; i++)
    {
        numb[i].touched = 0;
        numb[i].isSquarefree = 1;
    }
    numb[2].isSquarefree = 1;
    numb[2].touched = 1;
    
    GetSquarefree(numb);
    int a = 1;

    for (int i = 1; i < SIZE_NUMB; i++)
    {
        if (numb[i].isSquarefree)
        {
            cisla[a] = i;
            a++;
        }
    }
    return 0;
}

int main() {
    int cisla[SIZE_NUMB];
    Numb numb[SIZE_NUMB];
    GetArrayOfSquarefree(numb, cisla);
    printf("Poradi:\n");
    while (1)
    {
        int curr;
        int h = scanf("%d", &curr);
        if (h == EOF)
        {
            return 0;
        }
        if ((h != 1) || (curr < 1))
        {
            printf("Nespravny vstup.\n");
            return 1;
        }
        
        
        printf("= %d\n", cisla[curr]);
    }
    return 0;
}