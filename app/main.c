#include "main.h"

int main(void) {
    struct data user0 = {"Blink182", "Blink182", "Travis", "Barker", 14, 11, 1975, 1000};
    struct data user1 = {"Prodigy", "Prodigy", "Keith", "Flint", 17, 9, 1969, 3800};
    struct data user2 = {"Aerosmith", "Aerosmith", "Steven", "Tyler", 26, 3, 1948, 15000};
    struct data user3 = {"Mike", "Mike", "Michail", "Vays", 13, 7, 2005, 35};
    users[0] = user0;
    users[1] = user1;
    users[2] = user2;
    users[3] = user3;
    id_users = 4;

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
            create_account();
            break;

        case 2:
            login_page();
            break;

        case 3:
            exit(0);
            break;

        default:
            gotoxy(25, 20);
            printf("!!INVALID OPTION!!");
            gotoxy(25, 21);
            printf("Any key to retry...");
            getch();
            main();
            break;
    }
}