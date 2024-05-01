#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#define MAX_USERS 100
#define MAX_KEYS 5

struct data {
    char username[50];
    char password[50];
    char first_name[30];
    char last_name[30];
    int day, month, year;
    long long int money;
};

struct btree_node {
    int num_keys;
    struct data *keys[MAX_KEYS];
    struct btree_node *child[MAX_KEYS + 1];
};

struct data users[MAX_USERS];
int id_users = 0;

void create_account(void);
void account_created(void);
void login_page(void);
void infoPage(struct data* userData);
void logout(void);
void self_moneyAdd(struct data* userData); 

void btree(struct data *userData);
void insert(struct btree_node *root, struct data *user);
void split_child(struct btree_node *parent, int index, struct btree_node *child);
void insert_nonfull(struct btree_node *node, struct data *user);
void print_max_money_users(struct btree_node *root);
void find_max_money_user(struct btree_node *node, struct data **max_user, long long int *max_money);
void print_users_with_age(struct btree_node *root, int from_age, int to_age);
void print_users_with_money(struct btree_node *root, long long int starting_money, long long int ending_money);
void print_users_starting_with_letter(struct btree_node *root, char letter);
void free_btree(struct btree_node *node);

void gotoxy(int x, int y) {
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

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

struct btree_node *create_node() {
    struct btree_node *new_node = (struct btree_node *)malloc(sizeof(struct btree_node));
    new_node->num_keys = 0;
    for (int i = 0; i < MAX_KEYS; i++) {
        new_node->keys[i] = NULL;
        new_node->child[i] = NULL;
    }
    new_node->child[MAX_KEYS] = NULL;
    return new_node;
}

void btree(struct data *userData) {
    system("cls");

    struct btree_node *root = create_node();
    for (int i = 0; i < id_users; ++i) {
        insert(root, &users[i]);
    }

    gotoxy(25,4);
    printf("=== THIS IS IMPLEMENTATION OF B-TREES ALGORITHM IN C ===");
    gotoxy(20,6);
    printf("Here are some options:");
    gotoxy(20,8);
    printf("1. User with maximum money on account");
    gotoxy(20,9);
    printf("2. Users with age [from] [to]");
    gotoxy(20,10);
    printf("3. Users with amount of money [starting] [ending]");
    gotoxy(20,11);
    printf("4. Users with nickname starting on [letter]");
    gotoxy(20, 12);
    printf("5. Return to login info page");

    int choice, flag = 1;
    while (flag) {
        printf("\n\nYour choice is: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                print_max_money_users(root);
                break;

            case 2:
                printf("Enter from age: ");
                int from_age;
                scanf("%d", &from_age);
                printf("Enter to age: ");
                int to_age;
                scanf("%d", &to_age);
                printf("Users with age between %d and %d:\n", from_age, to_age);
                print_users_with_age(root, from_age, to_age);
                break;

            case 3:
                printf("Enter starting money: ");
                long long int starting_money;
                scanf("%lld", &starting_money);
                printf("Enter ending money: ");
                long long int ending_money;
                scanf("%lld", &ending_money);
                printf("Users with money between %lld and %lld:\n", starting_money, ending_money);
                print_users_with_money(root, starting_money, ending_money);
                break;

            case 4:
                printf("Enter starting letter: ");
                char starting_letter;
                scanf(" %c", &starting_letter); // Пробел перед %c для пропуска пробелов и символов новой строки
                printf("Users with username starting with '%c':\n", starting_letter);
                print_users_starting_with_letter(root, starting_letter);
                break;

            case 5:
                printf("\nRETURNING TO THE LOGIN INFO PAGE...");
                Sleep(1500);
                flag = 0;
                break;

            default:
                printf("You entered a wrong number, dummy!\n\n");
                break;
        }
    }
    free_btree(root);
    infoPage(userData);
}

void insert(struct btree_node *root, struct data *user) {
    if (root->num_keys < MAX_KEYS) {
        int i = root->num_keys - 1;
        while (i >= 0 && strcmp(user->username, root->keys[i]->username) < 0) {
            root->keys[i + 1] = root->keys[i];
            i--;
        }
        root->keys[i + 1] = user;
        root->num_keys++;
    } else {
        struct btree_node *new_root = create_node();
        new_root->child[0] = root;
        split_child(new_root, 0, root);
        insert_nonfull(new_root, user);
    }
}

void split_child(struct btree_node *parent, int index, struct btree_node *child) {
    struct btree_node *new_child = create_node();
    new_child->num_keys = MAX_KEYS / 2;

    for (int i = 0; i < MAX_KEYS / 2; i++) {
        new_child->keys[i] = child->keys[i + MAX_KEYS / 2];
        new_child->child[i] = child->child[i + MAX_KEYS / 2];
    }
    new_child->child[MAX_KEYS / 2] = child->child[MAX_KEYS];

    for (int i = parent->num_keys; i > index; i--) {
        parent->child[i + 1] = parent->child[i];
    }
    parent->child[index + 1] = new_child;

    for (int i = parent->num_keys - 1; i >= index; i--) {
        parent->keys[i + 1] = parent->keys[i];
    }
    parent->keys[index] = child->keys[MAX_KEYS / 2];
    parent->num_keys++;
    child->num_keys = MAX_KEYS / 2;
}

void insert_nonfull(struct btree_node *node, struct data *user) {
    int i = node->num_keys - 1;
    if (node->child[0] == NULL) {
        while (i >= 0 && strcmp(user->username, node->keys[i]->username) < 0) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = user;
        node->num_keys++;
    } else {
        while (i >= 0 && strcmp(user->username, node->keys[i]->username) < 0) {
            i--;
        }
        i++;
        if (node->child[i]->num_keys == MAX_KEYS) {
            split_child(node, i, node->child[i]);
            if (strcmp(user->username, node->keys[i]->username) > 0) {
                i++;
            }
        }
        insert_nonfull(node->child[i], user);
    }
}

void print_max_money_users(struct btree_node *root) {
    if (root == NULL) return;
    struct data *max_user = NULL;
    long long int max_money = 0;
    find_max_money_user(root, &max_user, &max_money);
    if (max_user != NULL) {
        printf("User with maximum money on account:\n");
        printf("Username: %s\n", max_user->username);
        printf("Money: %lld\n", max_user->money);
    } else {
        printf("No users found.\n");
    }
}

void find_max_money_user(struct btree_node *node, struct data **max_user, long long int *max_money) {
    if (node == NULL) return;
    for (int i = 0; i < node->num_keys; i++) {
        if (node->keys[i]->money > *max_money) {
            *max_money = node->keys[i]->money;
            *max_user = node->keys[i];
        }
    }
    if (node->child[0] != NULL) {
        find_max_money_user(node->child[node->num_keys], max_user, max_money);
    }
}

void free_btree(struct btree_node *node) {
    if (node == NULL) return;
    for (int i = 0; i <= node->num_keys; i++) {
        free_btree(node->child[i]);
    }
    free(node);
}

int calculate_age(int day, int month, int year) {
    time_t now;
    struct tm *current_time;
    time(&now);
    current_time = localtime(&now);
    int current_year = current_time->tm_year + 1900;
    int current_month = current_time->tm_mon + 1;
    int current_day = current_time->tm_mday;

    int age = current_year - year;
    if (current_month < month || (current_month == month && current_day < day)) {
        age--;
    }
    return age;
}

void print_users_with_age(struct btree_node *root, int from_age, int to_age) {
    if (root == NULL) return;
    for (int i = 0; i < root->num_keys; i++) {
        int user_age = calculate_age(root->keys[i]->day, root->keys[i]->month, root->keys[i]->year);
        if (user_age >= from_age && user_age <= to_age) {
            printf("Username: %s, Age: %d\n", root->keys[i]->username, user_age);
        }
    }
    for (int i = 0; i <= root->num_keys; i++) {
        print_users_with_age(root->child[i], from_age, to_age);
    }
}

void print_users_with_money(struct btree_node *root, long long int starting_money, long long int ending_money) {
    if (root == NULL) return;
    for (int i = 0; i < root->num_keys; i++) {
        if (root->keys[i]->money >= starting_money && root->keys[i]->money <= ending_money) {
            printf("Username: %s, Money: %lld\n", root->keys[i]->username, root->keys[i]->money);
        }
    }
    for (int i = 0; i <= root->num_keys; i++) {
        print_users_with_money(root->child[i], starting_money, ending_money);
    }
}

void print_users_starting_with_letter(struct btree_node *root, char letter) {
    if (root == NULL) return;
    for (int i = 0; i < root->num_keys; i++) {
        if (root->keys[i]->username[0] == letter) {
            printf("Username: %s\n", root->keys[i]->username);
        }
    }
    for (int i = 0; i <= root->num_keys; i++) {
        print_users_starting_with_letter(root->child[i], letter);
    }
}