#include <stdio.h>
#include <windows.h>

#include "main.h"
#include "info_page.h"
#include "logout.h"

void logout(struct data* userData) {
    system("cls");
    char ch;
    printf("YOU SURE YOU WANT TO LOG OUT? (y/n).. ");
    scanf("%c", &ch);
    switch (ch) {
        case 'y':
            printf("\n\n");
            for (int i = 3; i > 0; i--) {
                system("cls");
                printf("RETURNING TO THE MAIN PAGE IN..%d", i);
                Sleep(1000);
            }
            main();
        case 'n':
            infoPage(userData);
        default:
            printf("\n\n!!INVALID OPTION!!\n\n");
            system("Pause");
            logout(userData);
    }
}