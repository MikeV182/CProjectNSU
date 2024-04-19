#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "main.h"
#include "info_page.h"
#include "goto.h"

void transfer_money(struct data* userFrom) {
    system("cls");
    char name[50];
    gotoxy(25,3);
    printf("===TRANSFER MONEY===");
    gotoxy(20, 5);
    printf("ENTER A NICKNAME OF A PERSON YOU WANT TO TRANSFER MONEY TO: ");
    scanf("%s", name);
    int found = 0, i=0;
    for (i; i < id_users; i++) {
        if (strcmp(name, users[i].username) == 0) {
            found = 1;
            printf("\n\nUSER FOUND");
            break;
        }
    }
    if (!found) {
        printf("\n\nUSER IS NOT FOUND. RETURNING TO ACCOUNT INFO PAGE.\n\n");
        system("Pause");
        infoPage(userFrom);
    }
    long long int amount=0;
    printf("\n\nENTER AMOUNT OF MONEY TO TRANSFER: ");
    scanf("%lld", &amount);
    userFrom->money -= amount;
    users[i].money += amount;
    printf("\n\nMONEY TRANSFERED SUCCESSFULLY. RETURNING TO THE ACCOUNT INFO PAGE");
    Sleep(1500);
    infoPage(userFrom);
}