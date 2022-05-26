#include <stdio.h>
#include <stdlib.h>
#define START_SIZE 2



int isInRect(int maxi, int maxj, int currI, int currJ)
{
    if ((currI >= 0) && (currJ >= 0) 
        && (currI < maxi) && (currJ < maxj))
    {
        return 1;
    }
    return 0;
}

void ouItsAMine(int **A, int maxi, int maxj, int currI, int currJ)
{
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            int realI = currI + i, realJ = currJ + j;
            if (!((i == 0) && (j == 0)) 
                && isInRect(maxi, maxj, realI, realJ)
                && (A[realI][realJ] != 9))
            {
                A[realI][realJ]++;
            }
        }
    }
}

void makeZero(int **A, int maxi, int maxj)
{
    for (int i = 0; i < maxi; i++)
    {
        for (int j = 0; j < maxj; j++)
        {
            if (A[i][j] == '.')
            {
                A[i][j] = 0;
            }
            else
            {
                A[i][j] = 9;
            }
        }
    }
}

void solve(int **A, int maxi, int maxj)
{
    makeZero(A, maxi, maxj);
    for (int i = 0; i < maxi; i++)
    {
        for (int j = 0; j < maxj; j++)
        {
            if (A[i][j] == 9)
            {
                ouItsAMine(A, maxi, maxj, i, j);
            }
        }
    }
}


int main() {
    int currWidthSize = START_SIZE, currW = 0, maxW = 0;
    int currHeightSize = START_SIZE, currH = 0, maxH = 0;

    int **A = 0;
    int *firstRow;    
    firstRow = (int*)malloc(currWidthSize * sizeof(int));

    printf("Zadejte hraci plochu:\n");

    char curr = getchar();
    if ((curr == '\n') || (curr == EOF))
    {
        printf("Nespravny vstup.\n");
        free(firstRow);
        free(A);
        return 1;
    }
    
    while ((curr != '\n') && (curr != EOF))
    {
        if ((curr != '.') && (curr != '*'))
        {
            printf("Nespravny vstup.\n");
            free(firstRow);
            for (int i = 0; i < currHeightSize; i++)
            {
                free(A[i]);
            }
            free(A);
            return 1;
        }
        if (currW >= currWidthSize)
        {
            currWidthSize *= 2;
            firstRow = (int*) realloc (firstRow,currWidthSize * sizeof(int));
        }
        firstRow[currW] = curr;
        curr = getchar();
        currW++;
    }
    maxW = currW;

    A = (int **) realloc(A, currHeightSize * sizeof(*A));
    for (int i = 0; i < currHeightSize; i++)
    {
        A[i] = (int*)malloc(currWidthSize * sizeof(int));
    }
    for (int i = 0; i < maxW; i++)
    {
        A[0][i] = firstRow[i];
    }

    currH++;
    int *currentRow;
    currentRow = (int*)malloc(currWidthSize * sizeof(int));

    while (curr != EOF)
    {
        currW = 0;
        curr = getchar();
        if (curr == EOF){break;}

        while ((curr != '\n') && (curr != EOF))
        {
            if (((curr != '.') && (curr != '*')) 
                || (currW > maxW))
            {
                printf("Nespravny vstup.\n");
                free(firstRow);
                free(currentRow);
                for (int i = 0; i < currHeightSize; i++)
                {
                    free(A[i]);
                }
                free(A);
                return 1;
            }
            currentRow[currW] = curr;
            curr = getchar();
            currW++;
        }

        if (currW != maxW)
        {
            printf("Nespravny vstup.\n");
            free(firstRow);
            free(currentRow);
            for (int i = 0; i < currHeightSize; i++)
            {
                free(A[i]);
            }
            free(A);
            return 1;
        }
        
        if (currH >= currHeightSize)
        {
            currHeightSize *= 2;
            A = (int**) realloc(A, currHeightSize * sizeof(*A));
            for (int i = currH; i < currHeightSize; i++)
            {
                A[i] = (int *)malloc(currWidthSize * sizeof(int));
            }
        }
        for (int i = 0; i < maxW; i++)
        {
            A[currH][i] = currentRow[i];
        }
        
        currH++;
    }
    maxH = currH;
    free(currentRow);
    printf("Vyplnena hraci plocha:\n");

    solve(A, maxH, maxW);

    for (int i = 0; i < maxH; i++)
    {
        for (int j = 0; j < maxW; j++)
        {
            if (A[i][j] == 9)
            {
                printf("*");
            }
            else if(A[i][j] == 0)
            {
                printf(".");
            }
            else
            {
                printf("%c", A[i][j] + '0');
            }
        }
        printf("\n");
    }

    free(firstRow);
    for (int i = 0; i < currHeightSize; i++)
    {
        free(A[i]);
    }
    free(A);
    return 0;
}

