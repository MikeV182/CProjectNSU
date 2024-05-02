#include "account.h"
#include "utilities.h"
#include "btree.h"
#include "main.h"

void create_account(void) {
    system("cls");
    struct data userData;
    char ch;
    gotoxy(25, 4);
    printf("!!!CREATE ACCOUNT!!!");
    gotoxy(20, 6);
    printf("Enter your username: ");
    scanf("%s", &userData.username);
    gotoxy(20, 8);
    printf("Enter your password: ");
    for (int i = 0; i < 50; i++) {
        ch = getch();
        if (ch != 13) {
            userData.password[i] = ch;
            ch = '*';
            printf("%c", ch);
        }
        else break;
    }
    gotoxy(20, 10);
    printf("Enter your first name: ");
    scanf("%s", &userData.first_name);
    gotoxy(20, 12);
    printf("Enter your last name: ");
    scanf("%s", &userData.last_name);
    gotoxy(20, 14);
    printf("Enter your date of birth(dd/mm/year): ");
    scanf("%d/%d/%d", &userData.day, &userData.month, &userData.year);
    if (!data_check(userData.day, userData.month, userData.year)) {
        gotoxy(20,16);
        printf("Your date of birth is incorrect, try again");
        gotoxy(20,17);
        printf("Any key to retry...");
        getch();
        create_account();
    }
    userData.money = 0;
    users[id_users++] = userData;
    account_created();
}

void account_created(void) {
    system("cls");
    gotoxy(25, 4);
    printf("__YOUR DATA IS PROCESSING__");
    Sleep(1500);
    gotoxy(25, 6);
    printf("COMPLETED SUCCESSFULLY. Press any key to continue... ");
    getch();

    login_page();
}

void login_page(void) {
    system("cls");
    char name_user[50];
    char pass_user[50];
    char ch;
    struct data userData;

    gotoxy(25,3);
    printf("==LOGIN PAGE==");
    gotoxy(20,5);
    printf("Enter your username: ");
    scanf("%s", &name_user);
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

    int found = 0; // should add some kind of a quicker search there
    for (int i = 0; i < id_users; i++) {
        if (strcmp(name_user, users[i].username) == 0 && strcmp(pass_user, users[i].password) == 0) {
            gotoxy(25,10);
            found = 1;
            printf("!!!LOGIN SUCCESSFULLY!!! (Any key to enter the bank system)");
            getch();

            infoPage(&users[i]);
            break;
        }
    }
    if (!found) {
        gotoxy(25, 10);
        printf("Invalid username or password. Try again.");
        Sleep(1500);

        login_page();
    }
}

void infoPage(struct data* userData) {
    system("cls");
    gotoxy(25, 3);
    printf("==WELCOME TO THE USER INFO PAGE==");
    gotoxy(25, 6);
    printf("Hello, %s %s!", userData->first_name, userData->last_name);
    gotoxy(25, 8);
    printf("1. View account balance");
    gotoxy(25, 9);
    printf("2. Add money to your account");
    gotoxy(25, 10);
    printf("3. B-Tree options");
    gotoxy(25, 11);
    printf("4. Logout");
    gotoxy(25, 14);
    printf("Choose an option: ");
    int choice;
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            gotoxy(25, 16);
            printf("Your account balance: %lld$\n", userData->money);
            gotoxy(25, 17);
            printf("Press any key to return to the user info page...");
            getch();
            infoPage(userData);
            break;

        case 2:
            self_moneyAdd(userData);
            break;

        case 3:
            btree(userData);
            break;

        case 4:
            logout();
            break;

        default:
            gotoxy(25, 20);
            printf("Invalid option. Please try again.\n");
            break;
    }
}

void self_moneyAdd(struct data* userData) {
    system("cls");
    gotoxy(20, 4);
    printf("Enter the amount of money to add: ");
    long long int amount;
    scanf("%lld", &amount);
    userData->money += amount;
    gotoxy(20, 6);
    printf("Money added successfully.\n");
    gotoxy(20, 7);
    printf("Press any key to return to the user info page...");
    getch();

    infoPage(userData);
}

void logout(void) {
    system("cls");
    gotoxy(20, 4);
    printf("Logging out...");
    Sleep(1500);

    main();
}