#include <conio.h>
#include <stdio.h>
#include <windows.h>

#include "main.h"
#include "login_page.h"
#include "create.h"

void create_account(void) {
    struct data userData;
    char ch;
    system("cls");
    printf("\n\n!!!CREATE ACCOUNT!!!");
    printf("\n\nEnter your username.. ");
    scanf("%s", userData.username);
    printf("\n\nEnter your password.. ");
    for (int i = 0; i < 50; i++) {
        ch = getch();
        if (ch != 13) {
            userData.password[i] = ch;
            ch = '*';
            printf("%c", ch);
        }
        else break;
    }
    printf("\n\nEnter your first name.. ");
    scanf("%s", userData.first_name);
    printf("\n\nEnter your last name.. ");
    scanf("%s", userData.last_name);
    printf("\n\nEnter your gender.. ");
    scanf("%s", userData.gender);
    printf("\n\nEnter your contact number.. ");
    scanf("%s", userData.contact_number);
    printf("\n\nEnter your date of birth(dd/mm/year).. ");
    scanf("%d/%d/%d", &userData.day, &userData.month, &userData.year);
    userData.money = 0;
    users[id_users++] = userData;
    account_created();
}

void account_created(void) {
    system("cls");
    printf("\n\n__YOUR DATA IS PROCESSING__");
    Sleep(1500);
    printf("\n\nCOMPLETED SUCCESSFULLY. Press any key to continue... ");
    getch();

    login_page();
}