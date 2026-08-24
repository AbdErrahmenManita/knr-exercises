#include <stdio.h>
#include <stdlib.h>
int day_of_year(int, int, int);
void month_day(int, int, int *, int *);
int main() {
    int pmonth;
    int pday;
    int pyear;
    printf("year: ");
    scanf("%d", &pyear);
    printf("month: ");
    scanf("%d", &pmonth);
    printf("day: ");
    scanf("%d", &pday);
    printf("%d\n", day_of_year(pyear, pmonth, pday));
    printf("year day: ");
    int pyearday;
    scanf("%d", &pyearday);
    month_day(pyear, pyearday, &pmonth, &pday);
    printf("month: %d\nday: %d\n", pmonth, pday);
    return 0;
}
static char notleap[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static char leap[] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static char *daytab[2] = {notleap, leap};
#define INVALID_MONTH (month <= 0 || month > 12)
#define INVALID_DAY (day <= 0 || day > daytab[leap][month])
/*day_of_year: set day of year from month & day*/
int day_of_year(int year, int month, int day) {
    int i, leap;
    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    if (INVALID_MONTH) {
        printf("Invalid Month");
        return -1;
    }
    if (INVALID_DAY) {
        printf("Invalid Day");
        return -1;
    }
    for (i = 1; i < month; i++)
        day += *(*(daytab + leap) + i);
    return day;
}
static int dayssum[2] = {365, 366};
#define INVALID_YEARDAY (yearday <= 0 || yearday > dayssum[leap])
/*month_day: set month, day from day of year*/
void month_day(int year, int yearday, int *pmonth, int *pday) {
    int i, leap;
    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    if (INVALID_YEARDAY) {
        printf("Wrong year day");
        exit(1);
    }
    for (i = 1; yearday > *(*(daytab + leap) + i); i++) {
        yearday -= *(*(daytab + leap) + i);
    }
    *pmonth = i;
    *pday = yearday;
}
