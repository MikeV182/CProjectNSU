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


void insert(struct btree_node *root, struct data *user);
void split_child(struct btree_node *parent, int index, struct btree_node *child);
void insert_nonfull(struct btree_node *node, struct data *user);
void print_max_money_users(struct btree_node *root);
void find_max_money_user(struct btree_node *node, struct data **max_user, long long int *max_money);
void print_users_with_age(struct btree_node *root, int from_age, int to_age);
void print_users_with_money(struct btree_node *root, long long int starting_money, long long int ending_money);
void print_users_starting_with_letter(struct btree_node *root, char letter);
void free_btree(struct btree_node *node);

int main(void) {
    system("cls");
    struct btree_node *root = create_node();

    // Пример добавления пользователей
    struct data user1 = {"user1", "password1", "John", "Doe", 1, 1, 1990, 1000};
    struct data user2 = {"user2", "password2", "Jane", "Doe", 2, 2, 1991, 2000};
    struct data user3 = {"user3", "password3", "Alice", "Smith", 3, 3, 1992, 15000};
    struct data user4 = {"user4", "password4", "Michail", "Vays", 13, 7, 2005, 0};
    struct data user5 = {"user5", "password5", "Mike", "Wazowsky", 3, 3, 2000, -200};

    insert(root, &user1);
    insert(root, &user2);
    insert(root, &user3);
    insert(root, &user4);
    insert(root, &user5);

    int choice;
    printf("1. User with maximum money on account\n");
    printf("2. Users with age [from] [to]\n");
    printf("3. Users with amount of money [starting] [ending]\n");
    printf("4. Users with nickname starting on [letter]\n");
    printf("Enter your choice: ");
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
        default:
            printf("Invalid choice.\n");
            break;
    }

    free_btree(root);
    return 0;
}

// Вставка данных о пользователе в B-дерево
void insert(struct btree_node *root, struct data *user) {
    // Проверка, есть ли место в корневом узле
    if (root->num_keys < MAX_KEYS) {
        int i = root->num_keys - 1;
        // Находим место для вставки, сдвигая ключи
        while (i >= 0 && strcmp(user->username, root->keys[i]->username) < 0) {
            root->keys[i + 1] = root->keys[i];
            i--;
        }
        // Вставляем пользователя в найденное место
        root->keys[i + 1] = user;
        root->num_keys++;
    } else {
        // Если корневой узел полон, разделяем его
        struct btree_node *new_root = create_node();
        new_root->child[0] = root;
        split_child(new_root, 0, root);
        // Вставляем нового пользователя
        insert_nonfull(new_root, user);
    }
}

// Разделение полного узла
void split_child(struct btree_node *parent, int index, struct btree_node *child) {
    struct btree_node *new_child = create_node();
    new_child->num_keys = MAX_KEYS / 2;

    // Переносим ключи и детей из полного узла в новый
    for (int i = 0; i < MAX_KEYS / 2; i++) {
        new_child->keys[i] = child->keys[i + MAX_KEYS / 2];
        new_child->child[i] = child->child[i + MAX_KEYS / 2];
    }
    new_child->child[MAX_KEYS / 2] = child->child[MAX_KEYS];

    // Уменьшаем количество ключей в родительском узле
    for (int i = parent->num_keys; i > index; i--) {
        parent->child[i + 1] = parent->child[i];
    }
    parent->child[index + 1] = new_child;

    // Переносим средний ключ в родительский узел
    for (int i = parent->num_keys - 1; i >= index; i--) {
        parent->keys[i + 1] = parent->keys[i];
    }
    parent->keys[index] = child->keys[MAX_KEYS / 2];
    parent->num_keys++;
    child->num_keys = MAX_KEYS / 2;
}

// Вставка в неполный узел
void insert_nonfull(struct btree_node *node, struct data *user) {
    int i = node->num_keys - 1;
    if (node->child[0] == NULL) {
        // Если это листовой узел, просто вставляем новый ключ
        while (i >= 0 && strcmp(user->username, node->keys[i]->username) < 0) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = user;
        node->num_keys++;
    } else {
        // Если это не листовой узел, находим дочерний узел для вставки
        while (i >= 0 && strcmp(user->username, node->keys[i]->username) < 0) {
            i--;
        }
        i++;
        if (node->child[i]->num_keys == MAX_KEYS) {
            // Если дочерний узел полный, разделяем его
            split_child(node, i, node->child[i]);
            if (strcmp(user->username, node->keys[i]->username) > 0) {
                i++;
            }
        }
        // Рекурсивно вставляем ключ в соответствующий дочерний узел
        insert_nonfull(node->child[i], user);
    }
}

// Вывод пользователей с максимальным количеством денег
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

// Поиск пользователя с максимальным количеством денег
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

// Освобождение памяти, выделенной под B-дерево
void free_btree(struct btree_node *node) {
    if (node == NULL) return;
    for (int i = 0; i < node->num_keys; i++) {
        free(node->keys[i]);
    }
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

// Пользователи с указанным возрастом
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

// Пользователи с указанной суммой денег на счете
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

// Пользователи с никнеймом, начинающимся на указанную букву
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
