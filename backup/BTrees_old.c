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
    char contact_number[15];
    char gender[10];
    long long int money;
};

struct BTreeNode {
    char *keys[MAX_KEYS];
    struct data *users[MAX_KEYS];
    struct BTreeNode *children[MAX_KEYS + 1];
    int is_leaf;
    int count;
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
struct BTreeNode *createNode(void);
void insert(struct BTreeNode **root, char *key, struct data *userData);
void insertNonFull(struct BTreeNode *node, char *key, struct data *userData);
void splitChild(struct BTreeNode** parent, int childIndex);
void buildBTree(struct BTreeNode **root);
struct data *findMaxMoneyUser(struct BTreeNode *root);
void printMaxMoneyUser(struct data *maxMoneyUser, struct data *userData);
void btree(struct data *userData);

void printTopUsers(struct BTreeNode *root, int n, struct data *userData);
void printUsersByBirthDate(struct BTreeNode *root, int start_year, int end_year, struct data *userData);

struct BTreeNode *createNode(void) {
    struct BTreeNode *newNode = (struct BTreeNode*)malloc(sizeof(struct BTreeNode));
    newNode->is_leaf = 1;
    newNode->count = 0;
    for (int i = 0; i < MAX_KEYS; i++) {
        newNode->keys[i] = NULL;
        newNode->users[i] = NULL;
    }
    for (int i = 0; i < MAX_KEYS + 1; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

void insert(struct BTreeNode **root, char *key, struct data *userData) {
    if ((*root)->count == MAX_KEYS) {
        struct BTreeNode *newRoot = createNode();
        newRoot->is_leaf = 0;
        newRoot->children[0] = *root;
        splitChild(&newRoot, 0);
        *root = newRoot;
    }
    insertNonFull(*root, key, userData);
}

void insertNonFull(struct BTreeNode *node, char *key, struct data *userData) {
    int i = node->count - 1;
    if (node->is_leaf) {
        while (i >= 0 && strcmp(key, node->keys[i]) < 0) {
            node->keys[i+1] = node->keys[i];
            node->users[i+1] = node->users[i];
            --i; 
        }
        node->keys[i+1] = strdup(key);
        node->users[i+1] = userData;
        node->count++;
    } else {
        while (i >= 0 && strcmp(key, node->keys[i]) < 0) {
            --i;
        }
        i++;
        if (node->children[i]->count == MAX_KEYS) {
            splitChild(&node, i);
            if (strcmp(key, node->keys[i]) > 0) {
                i++;
            }
        }
        insertNonFull(node->children[i], key, userData);
    }
}

void splitChild(struct BTreeNode** parent, int childIndex) {
    struct BTreeNode* child = (*parent)->children[childIndex];
    struct BTreeNode* newChild = createNode();
    newChild->is_leaf = child->is_leaf;
    newChild->count = MAX_KEYS / 2;

    for (int i = 0; i < MAX_KEYS / 2; i++) {
        newChild->keys[i] = child->keys[i + MAX_KEYS / 2];
        newChild->users[i] = child->users[i + MAX_KEYS / 2];
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
        (*parent)->keys[i + 1] = (*parent)->keys[i];
        (*parent)->users[i + 1] = (*parent)->users[i];
    }
    (*parent)->keys[childIndex] = child->keys[MAX_KEYS / 2 - 1];
    (*parent)->users[childIndex] = child->users[MAX_KEYS / 2 - 1];
    (*parent)->count++;
}

void buildBTree(struct BTreeNode **root) {
    for (int i = 0; i < id_users; i++) {
        insert(root, users[i].username, &users[i]);
    }
}

struct data* findMaxMoneyUser(struct BTreeNode *root) {
    while (!root->is_leaf) {
        root = root->children[root->count];
    }
    return root->users[root->count - 1];
}

void printMaxMoneyUser(struct data *maxMoneyUser, struct data *userData) {
    system("cls");
    gotoxy(25,3);
    printf("===THE RICHEST USER IS===");
    gotoxy(20, 6);
    printf("USERNAME: %s", maxMoneyUser->username);
    gotoxy(20,8);
    printf("FIRST AND SECOND NAME: %s %s", maxMoneyUser->first_name, maxMoneyUser->last_name);
    gotoxy(20,10);
    printf("AMOUNT OF MONEY ON ACCOUNT: %lld$", maxMoneyUser->money);

    gotoxy(25, 18);
    printf("Press any key and you will return to a B-Tree page\n\n");
    system("Pause");
    btree(userData);
}

void btree(struct data *userData) {
    system("cls");
    int choice;
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
    struct BTreeNode *bTreeRoot = createNode();
    struct data *maxMoneyUser;
    buildBTree(&bTreeRoot);
    switch (choice) {
        case 1:
            maxMoneyUser = findMaxMoneyUser(bTreeRoot);
            printMaxMoneyUser(maxMoneyUser, userData);
            break;

        case 2:
            gotoxy(25,17);
            printTopUsers(bTreeRoot, 15, userData);
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
            system("Sleep");
            btree(userData);
            break;
    }
}

void printTopUsers(struct BTreeNode *root, int n, struct data *userData) {
    system("cls");
    if (root == NULL) {
        printf("B-tree is empty.\n");
        printf("\nPress any key and you will return to a B-Tree page\n\n");
        system("Pause");
        btree(userData);
    }

    while (!root->is_leaf) {
        root = root->children[root->count];
    }

    for (int i = root->count - 1; i >= root->count - n && i >= 0; i--) {
        printf("Username: %s, Money: %lld\n", root->users[i]->username, root->users[i]->money);
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
    }

    if (!root->is_leaf) {
        for (int i = 0; i < root->count; i++) {
            printUsersByBirthDate(root->children[i], start_year, end_year, userData);
        }
    } else {
        for (int i = 0; i < root->count; i++) {
            if (root->users[i]->year >= start_year && root->users[i]->year <= end_year) {
                printf("Username: %s, Birth Date: %d/%d/%d\n", root->users[i]->username,
                       root->users[i]->day, root->users[i]->month, root->users[i]->year);
            }
        }
    }
    printf("\nPress any key and you will return to a B-Tree page\n\n");
    system("Pause");
    btree(userData);
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
    printf("2. B-TREES FEATURES");
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
            btree(userData);
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
    scanf(" %c", &ch);
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