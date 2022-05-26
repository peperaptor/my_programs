#include <stdio.h>

#ifndef PROGTEST
#include <stdio.h>
#include <assert.h>

#endif /* PROGTEST */

int dayInMonth(int month, int isLp)
{
    if (month == 1)
    {
        return 31;
    } else
    if (month == 2)
    {
        if (isLp)
        {
            return 29;
        }
        return 28;
    } else
    if (month == 3)
    {
        return 31;
    } else
    if (month == 4)
    {
        return 30;
    } else
    if (month == 5)
    {
        return 31;
    } else
    if (month == 6)
    {
        return 30;
    } else
    if (month == 7)
    {
        return 31;
    } else
    if (month == 8)
    {
        return 31;
    } else
    if (month == 9)
    {
        return 30;
    } else
    if (month == 10)
    {
        return 31;
    } else
    if (month == 11)
    {
        return 30;
    } else
    
    return 31;
    
}

int isLeap(int year){
    if ((((year % 4 == 0) && (year % 100 != 0)) 
        || (year % 400 == 0))
            && (year % 4000 != 0))
    {
        return 1;
    }
    return 0;
}

int kontrolaVstupu(int day, int month, int year){
    if ((year < 2000) 
        || (month < 1) || (month > 12) 
            || (day > dayInMonth(month, isLeap(year)))
                || (day <= 0))
    {
        return 1;
    }
    return 0;
}   



int dateToIndex(int day, int month, int year, int *idx) {
    if (kontrolaVstupu(day, month, year))
    {
        return 0;
    }
    int isLp = isLeap(year);
    int res = 0;
    if (month != 1)
    {
        for (int i = 1; i < month; i++)
        {
            res += dayInMonth(i, isLp);
        }
    }
    res += day;
    *idx = res;
    return 1;
}

#ifndef PROGTEST
int main (int argc, char * argv []) {
    int idx;

    assert(dateToIndex( 1,  1, 2000, &idx) == 1 && idx == 1);
    assert(dateToIndex( 1,  2, 2000, &idx) == 1 && idx == 32);
    assert(dateToIndex(29,  2, 2000, &idx) == 1 && idx == 60);
    assert(dateToIndex(29,  2, 2001, &idx) == 0);
    assert(dateToIndex( 1, 12, 2000, &idx) == 1 && idx == 336);
    assert(dateToIndex(31, 12, 2000, &idx) == 1 && idx == 366);
    assert(dateToIndex( 1,  1, 1999, &idx) == 0);
    assert(dateToIndex( 6,  7, 3600, &idx) == 1 && idx == 188);
    assert(dateToIndex(29,  2, 3600, &idx) == 1 && idx == 60);
    assert(dateToIndex(29,  2, 4000, &idx) == 0);
    
    assert(dateToIndex(0, 1, 2022, &idx) == 0);
    return 0;
}
#endif /* PROGTEST */
