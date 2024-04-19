#include <conio.h>
#include <stdio.h>
#include <windows.h>

#include "main.h"
#include "info_page.h"

void self_moneyAdd(struct data* userData) {
    system("cls");
    printf("ADD AMOUNT MONEY TO ADD: ");
    long long int amount;
    scanf("%lld", &amount);
    userData->money = userData->money + amount;
    printf("\n\nMONEY IS SENT ON YOUR ACCOUNT. RETURNING TO ACCOUNT INFORMATION PAGE");
    Sleep(1500);
    infoPage(userData);
}