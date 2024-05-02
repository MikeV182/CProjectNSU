#include "utilities.h"
#include <windows.h>
#include <conio.h>

void gotoxy(int x, int y) {
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

int calculate_age(int day, int month, int year) {
    time_t now;
    struct tm *current_time;
    time(&now);
    current_time = localtime(&now);
    int current_year = current_time->tm_year + 1900;
    int current_month = current_time->tm_mon + 1;
    int current_day = current_time->tm_mday;

    int age = current_year - year;
    if (current_month < month || (current_month == month && current_day < day)) {
        age--;
    }
    return age;
}

int leap_year(int year) {
    if (year % 4 != 0) {
        return 0;
    }

    else if (year % 100 != 0) {
        return 1;
    }

    else if (year % 400 != 0) {
        return 0;
    }
    
    else {
        return 1;
    }
}

int data_check(int day, int month, int year) {
    if (year < 1900 || year > 9999) {
        return 0;
    }

    if (month < 1 || month > 12) {
        return 0;
    }

    if (day < 1 || day > 31) {
        return 0;
    }

    if (month == 2) {
        if (leap_year(year)) {
            if (day > 29) {
                return 0;
            }
        } else {
            if (day > 28) {
                return 0;
            }
        }
    }

    else if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30) {
            return 0;
        }
    }

    return 1;
}