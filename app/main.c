#include "main.h"

int main(void) {
    //delete this later, only for testing purposes
    struct data user0 = {"user0", "password0", "John", "Doe", 1, 1, 1990, 1000};
    struct data user1 = {"user1", "password1", "Jane", "Doe", 2, 2, 1991, 2000};
    struct data user2 = {"user2", "password2", "Alice", "Smith", 3, 3, 1992, 15000};
    struct data user3 = {"Mike", "Mike", "Michail", "Vays", 13, 7, 2005, 0};
    struct data user4 = {"Damn", "Damn", "Mike", "Wazowsky", 3, 3, 2000, -200};
    users[0] = user0;
    users[1] = user1;
    users[2] = user2;
    users[3] = user3;
    users[4] = user4;
    id_users = 5;
    
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
            printf("!!INVALID OPTION!!");
            main();
            break;
    }
}
