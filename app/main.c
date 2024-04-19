#include <conio.h>
#include <stdio.h>
#include <windows.h>

#include "goto.h"
#include "create.h"
#include "login_page.h"

int main(void) {
    system("cls");
    int choice;
    gotoxy(20, 3);
    printf("WELCOME TO BANK ACCOUNT SYSTEM\n\n");
    gotoxy(18, 5);
    printf("**********************************");
    gotoxy(25, 7);
    printf("DEVELOPER-Vays Mikhail");
    gotoxy(20, 10);
    printf("1.... CREATE A BANK ACCOUNT");
    gotoxy(20, 12);
    printf("2.... ALREADY A USER? SIGN IN");
    gotoxy(20, 14);
    printf("3.... EXIT\n\n");
    printf("\n\nENTER YOUR CHOICE.. ");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            system("cls");
            printf("\n\n USERNAME 50 CHARACTERS MAX!!");
            printf("\n\n PASSWORD 50 CHARACTERS MAX!!\n\n");
            system("Pause");
            create_account();
            break;
        case 2:
            login_page();
            break;
        case 3:
            exit(0);
            break;
            getch();
        default:
            printf("!!INVALID OPTION!!");
    }
}