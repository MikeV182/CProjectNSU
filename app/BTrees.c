#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

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

struct BTreeNode {
    struct KeyValue {
        char *key;
        long long int money;
    } keyValue[MAX_KEYS];

    struct BTreeNode *children[MAX_KEYS + 1];
    int is_leaf;
    int count;
};

struct UserData {
    char username[50];
    long long int money;
};

struct data users[MAX_USERS];
int id_users = 0;
struct UserData topUsers[MAX_USERS]; // Объявляем topUsers здесь

void create_account(void);
void account_created(void);
void login_page(void);
void infoPage(struct data* userData);
void logout(struct data* userData);
void self_moneyAdd(struct data* userData); 
struct BTreeNode *createNode(void);
void insert(struct BTreeNode **root, char *key, long long int money);
void insertNonFull(struct BTreeNode *node, char *key, long long int money);
void splitChild(struct BTreeNode** parent, int childIndex);
void buildBTree(struct BTreeNode **root);
struct KeyValue* findMaxMoneyUser(struct BTreeNode *root);
void updateTopUsers(struct BTreeNode *node);
void printMaxMoneyUser(struct KeyValue *maxMoneyUser, struct data *userData);
void btree(struct data *userData);
void printTopUsers(struct UserData *topUsers, int n, struct data *userData);
void printUsersByBirthDate(struct BTreeNode *root, int start_year, int end_year, struct data *userData);
int compareMoney(struct KeyValue *a, struct KeyValue *b); // Объявляем функцию сравнения

void gotoxy(int x, int y) {
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

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
    printf("\n\nEnter your first name: ");
    scanf("%s", &userData.first_name);
    printf("\n\nEnter your last name: ");
    scanf("%s", &userData.last_name);
    printf("\n\nEnter your date of birth(dd/mm/year): ");
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
            printf("!!!LOGIN SUCCESSFULLY!!! (Any key to enter the bank system)");
            getch();
            infoPage(&users[i]);
            break;
        }
    }
    if (!found) {
        gotoxy(25,11);
        printf("Invalid username or password. Try again.\n\n");
        Sleep(2000);
        login_page();
    }
}

void infoPage(struct data* userData) {
    system("cls");
    printf("\n\n==WELCOME TO THE USER INFO PAGE==\n\n");
    printf("Hello, %s %s!\n", userData->first_name, userData->last_name);
    printf("1. View account balance\n");
    printf("2. Add money to your account\n");
    printf("3. B-Tree options\n");
    printf("4. Logout\n");
    printf("Choose an option: ");
    int choice;
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            printf("Your account balance: %lld$\n", userData->money);
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
            logout(userData);
            break;
        default:
            printf("Invalid option. Please try again.\n");
            break;
    }
}

void self_moneyAdd(struct data* userData) {
    system("cls");
    printf("Enter the amount of money to add: ");
    long long int amount;
    scanf("%lld", &amount);
    userData->money += amount;
    printf("Money added successfully.\n");
    printf("Press any key to return to the user info page...");
    getch();
    infoPage(userData);
}

void logout(struct data* userData) {
    system("cls");
    printf("Logging out...\n");
    Sleep(1500);
    main();
}

struct BTreeNode *createNode(void) {
    struct BTreeNode *newNode = (struct BTreeNode*)malloc(sizeof(struct BTreeNode));
    newNode->is_leaf = 1;
    newNode->count = 0;
    for (int i = 0; i < MAX_KEYS; i++) {
        newNode->keyValue[i].key = NULL;
        newNode->keyValue[i].money = 0;
    }
    for (int i = 0; i < MAX_KEYS + 1; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

void insert(struct BTreeNode **root, char *key, long long int money) {
    if ((*root)->count == MAX_KEYS) {
        struct BTreeNode *newRoot = createNode();
        newRoot->is_leaf = 0;
        newRoot->children[0] = *root;
        splitChild(&newRoot, 0);
        *root = newRoot;
    }
    insertNonFull(*root, key, money);
}

void insertNonFull(struct BTreeNode *node, char *key, long long int money) {
    int i = node->count - 1;
    if (node->is_leaf) {
        while (i >= 0 && strcmp(key, node->keyValue[i].key) < 0) {
            node->keyValue[i+1].key = node->keyValue[i].key;
            node->keyValue[i+1].money = node->keyValue[i].money;
            --i; 
        }
        node->keyValue[i+1].key = strdup(key);
        node->keyValue[i+1].money = money;
        node->count++;
    } else {
        while (i >= 0 && strcmp(key, node->keyValue[i].key) < 0) {
            --i;
        }
        i++;
        if (node->children[i]->count == MAX_KEYS) {
            splitChild(&node, i);
            if (strcmp(key, node->keyValue[i].key) > 0) {
                i++;
            }
        }
        insertNonFull(node->children[i], key, money);
    }
}

void splitChild(struct BTreeNode** parent, int childIndex) {
    struct BTreeNode* child = (*parent)->children[childIndex];
    struct BTreeNode* newChild = createNode();
    newChild->is_leaf = child->is_leaf;
    newChild->count = MAX_KEYS / 2;

    for (int i = 0; i < MAX_KEYS / 2; i++) {
        newChild->keyValue[i] = child->keyValue[i + MAX_KEYS / 2];
    }

    if (!child->is_leaf) {
        for (int i = 0; i < MAX_KEYS / 2 + 1; i++) {
            newChild->children[i] = child->children[i + MAX_KEYS / 2];
        }
    }

    child->count = MAX_KEYS / 2;

    for (int i = (*parent)->count; i >= childIndex + 1; i--) {
        (*parent)->children[i + 1] = (*parent)->children[i];
    }
    (*parent)->children[childIndex + 1] = newChild;

    for (int i = (*parent)->count - 1; i >= childIndex; i--) {
        (*parent)->keyValue[i + 1] = (*parent)->keyValue[i];
    }
    (*parent)->keyValue[childIndex] = child->keyValue[MAX_KEYS / 2 - 1];
    (*parent)->count++;
}

void buildBTree(struct BTreeNode **root) {
    for (int i = 0; i < id_users; i++) {
        insert(root, users[i].username, users[i].money);
    }
}

struct KeyValue* findMaxMoneyUser(struct BTreeNode *root) {
    while (!root->is_leaf) {
        root = root->children[root->count];
    }
    return &(root->keyValue[root->count - 1]);
}

void updateTopUsers(struct BTreeNode *node) {
    struct BTreeNode *temp = node;
    while (!temp->is_leaf) {
        temp = temp->children[temp->count];
    }

    int count = 0;
    for (int i = temp->count - 1; i >= 0; i--) {
        if (count >= MAX_USERS) {
            break;
        }
        strcpy(topUsers[count].username, temp->keyValue[i].key);
        topUsers[count].money = temp->keyValue[i].money;
        count++;
    }
}

void printMaxMoneyUser(struct KeyValue *maxMoneyUser, struct data *userData) {
    system("cls");
    gotoxy(25,3);
    printf("===THE RICHEST USER IS===");
    gotoxy(20, 6);
    printf("USERNAME: %s", maxMoneyUser->key);
    gotoxy(20,8);
    printf("AMOUNT OF MONEY ON ACCOUNT: %lld$", maxMoneyUser->money);

    gotoxy(25, 18);
    printf("Press any key and you will return to a B-Tree page\n\n");
    system("Pause");
    btree(userData);
}

void btree(struct data *userData) {
    system("cls");
    int choice;
    struct BTreeNode *bTreeRoot = createNode();
    buildBTree(&bTreeRoot);
    updateTopUsers(bTreeRoot); // Обновление списка пользователей с наибольшим количеством денег
    gotoxy(25,3);
    printf("=== THIS IS IMPLEMENTATION OF B-TREES ALGORITHM IN C ===");
    gotoxy(20,5);
    printf("Here are some options:");
    gotoxy(20,7);
    printf("1. User with maximum money on account");
    gotoxy(20,9);
    printf("2. Top 15 users with top money on account");
    gotoxy(20,11);
    printf("3. Users born in period between two ages");
    gotoxy(20,13);
    printf("4. Return to the login info page");
    gotoxy(20, 15);
    printf("Your choice is: ");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            printMaxMoneyUser(findMaxMoneyUser(bTreeRoot), userData);
            break;

        case 2:
            gotoxy(25,17);
            printTopUsers(topUsers, id_users > MAX_USERS ? MAX_USERS : id_users, userData);
            break;

        case 3:
            gotoxy(25,17);
            int age_to, age_from;
            printf("Enter two years you want to search users between: ");
            scanf("%d %d", &age_from, &age_to);
            printUsersByBirthDate(bTreeRoot, age_from, age_to, userData);
            break;

        case 4:
            gotoxy(25,17);
            printf("RETURNING TO THE LOGIN INFO PAGE...");
            Sleep(1500);
            infoPage(userData);
            break;

        default:
            gotoxy(25,19);
            printf("You entered a wrong number, dummy!\n\n");
            system("Pause");
            btree(userData);
            break;
    }
}

void printTopUsers(struct UserData *topUsers, int n, struct data *userData) {
    system("cls");
    if (n <= 0) {
        printf("B-tree is empty.\n");
        printf("\nPress any key and you will return to a B-Tree page\n\n");
        system("Pause");
        btree(userData);
        return;
    }

    for (int i = 0; i < n; i++) {
        printf("Username: %s, Money: %lld\n", topUsers[i].username, topUsers[i].money);
    }

    printf("\nPress any key and you will return to a B-Tree page\n\n");
    system("Pause");
    btree(userData);
}

void printUsersByBirthDate(struct BTreeNode *root, int start_year, int end_year, struct data *userData) {
    system("cls");
    if (root == NULL) {
        printf("B-tree is empty.\n");
        printf("\nPress any key and you will return to a B-Tree page\n\n");
        system("Pause");
        btree(userData);
        return;
    }

    if (!root->is_leaf) {
        for (int i = 0; i < root->count; i++) {
            printUsersByBirthDate(root->children[i], start_year, end_year, userData);
        }
    } else {
        for (int i = 0; i < root->count; i++) {
            for (int j = 0; j < id_users; j++) {
                if (strcmp(root->keyValue[i].key, users[j].username) == 0) {
                    if (users[j].year >= start_year && users[j].year <= end_year) {
                        printf("Username: %s, Birth Date: %d/%d/%d\n", users[j].username, users[j].day, users[j].month, users[j].year);
                    }
                    break;
                }
            }
        }
    }
    printf("\nPress any key and you will return to a B-Tree page\n\n");
    system("Pause");
    btree(userData);
}
