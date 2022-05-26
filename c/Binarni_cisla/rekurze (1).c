#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int maxRepeat = 0;
int pocetCifr = 0;
int pocetReseni = 0;

void printNumb(int currRepeat, int currPos, char *currStr)
{
    currStr[currPos] = '\0';
    printf("%s\n", currStr);
    pocetReseni++;
    currStr[currPos] = '0';
    if (currPos != pocetCifr)
    {
        if (currRepeat < maxRepeat)
        {
            currStr[currPos] = currStr[currPos - 1];
            printNumb(currRepeat + 1, currPos + 1, currStr);
        }
        if (currStr[currPos - 1] == '0')
        {
            currStr[currPos] = '1';
            printNumb(1, currPos + 1, currStr);
        }
        else
        {
            currStr[currPos] = '0';
            printNumb(1, currPos + 1, currStr);
        }
    }
}

int main() 
{
    printf("Pocet cifer:\n");
    if ((scanf("%d", &pocetCifr) != 1))
    {
        printf("Nespravny vstup.\n");
        return 1;
    }
    if ((pocetCifr <= 0) || (pocetCifr > 64))
    {
        printf("Nespravny vstup.\n");
        return 1;
    }
    char str[100];
    str[0] = '1';
    printf("Max. stejnych po sobe:\n");
    if ((scanf("%d", &maxRepeat) != 1))
    {
        printf("Nespravny vstup.\n");
        return 1;
    }
    if ((maxRepeat <= 0))
    {
        printf("Nespravny vstup.\n");
        return 1;
    }
    int currRep = 1;
    printNumb(currRep, 1, str);

    printf("Celkem: %d\n", pocetReseni);
    return 0;
}