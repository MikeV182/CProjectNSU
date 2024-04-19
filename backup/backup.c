#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_USERS 100

struct data {
    char username[50];
    char password[50];
    char first_name[30];
    char last_name[30];
    int day, month, year;
    char contact_number[15];
    char gender[10];
    long long int money;
};



struct data users[MAX_USERS];
int id_users = 0;

void gotoxy(int x, int y) {
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void create_account(void);
void account_created(void);
void login_page(void);
void infoPage(struct data* userData);
void transfer_money(struct data* userFrom);
void logout(struct data* userData);
void self_moneyAdd(struct data* userData); 

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

void create_account(void) {
    struct data userData;
    char ch;
    system("cls");
    printf("\n\n!!!CREATE ACCOUNT!!!");
    printf("\n\nEnter your username.. ");
    scanf("%s", &userData.username);
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
    scanf("%s", &userData.first_name);
    printf("\n\nEnter your last name.. ");
    scanf("%s", &userData.last_name);
    printf("\n\nEnter your gender.. ");
    scanf("%s", &userData.gender);
    printf("\n\nEnter your contact number.. ");
    scanf("%s", &userData.contact_number);
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

void transfer_money(struct data* userFrom) {
    system("cls");
    char name[50];
    gotoxy(25,3);
    printf("===TRANSFER MONEY===");
    gotoxy(20, 5);
    printf("ENTER A NICKNAME OF A PERSON YOU WANT TO TRANSFER MONEY TO: ");
    scanf("%s", &name);
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