#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "main.h"
#include "info_page.h"
#include "goto.h"

void login_page(void) {
    system("cls");
    char name_user[50];
    char pass_user[50];
    char ch;
    gotoxy(25,3);
    printf("==LOGIN PAGE==");
    gotoxy(20,5);
    printf("Enter your username: ");
    scanf("%s", name_user);
    gotoxy(20,7);
    printf("Enter your password: ");
    for (int i = 0; i < 50; i++) {
        ch = getch();
        if (ch != 13) {
            pass_user[i] = ch;
            ch = '*';
            printf("%c", ch);
        }
        else break;
    }
    int found = 0;
    for (int i = 0; i < id_users; i++) {
        if (strcmp(name_user, users[i].username) == 0 && strcmp(pass_user, users[i].password) == 0) {
            gotoxy(25,11);
            found = 1;
            printf("!!!LOGIN SUCCESSFULLY!!! (Any key to enter the account info page) ");
            getch();
            infoPage(&users[i]);
        }
    }
    if (!found) {
        printf("\n\nYour username or password is incorrect.. Any key to retry..");
        getch();
        login_page();
    }
}