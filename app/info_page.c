#include <conio.h>
#include <stdio.h>
#include <windows.h>

#include "main.h"
#include "transfer.h"
#include "logout.h"
#include "selfAdd.h"
#include "goto.h"

void infoPage(struct data* userData) {
    system("cls");
    gotoxy(25, 3);
    printf("===ACCOUNT INFORMATION PAGE===");
    int choice;
    gotoxy(20, 6);
    printf("\nYour username: %s", userData->username);
    printf("\nYour first and last name: %s %s", userData->first_name, userData->last_name);
    printf("\nYour date of birth: %d/%d/%d", userData->day, userData->month, userData->year);
    printf("\nYour gender: %s", userData->gender);
    printf("\nYour contact number: +%c (%c%c%c) %c%c%c-%c%c-%c%c", 
    userData->contact_number[0],
    userData->contact_number[1], userData->contact_number[2], userData->contact_number[3],
    userData->contact_number[4], userData->contact_number[5], userData->contact_number[6],
    userData->contact_number[7], userData->contact_number[8],
    userData->contact_number[9], userData->contact_number[10]);
    printf("\nAmmount of money: %lld$", userData->money);
    gotoxy(60, 6);
    printf("OPTIONS:");
    gotoxy(60,8);
    printf("1. TRANSFER MONEY");
    gotoxy(60,10);
    printf("2. this is for databases purposes");
    gotoxy(60,12);
    printf("3. LOGOUT");
    gotoxy(60,14);
    printf("4. ADD MONEY ON YOUR ACCOUNT");
    gotoxy(30, 20);
    printf("\nYOUR CHOICE:");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            transfer_money(userData);
            break;
        case 2:
            printf("THIS IS NOT WORKING... FOR NOW");
            break;
        case 3:
            logout(userData);
            break;
        case 4:
            self_moneyAdd(userData);
            break;
        default:
            printf("!!INVAlID OPTION!!");
    }
}