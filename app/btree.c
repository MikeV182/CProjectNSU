#include "btree.h"
#include "utilities.h"
#include "account.h"

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
        struct btree_node *root = create_node();
        printf("\n\nYour choice is: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                for (int i = 0; i < id_users; ++i) {
                    insert(root, &users[i], "money");
                }
                print_max_money_users(root);
                free_btree(root);
                break;

            case 2:
                printf("Enter from age: ");
                int from_age;
                scanf("%d", &from_age);
                printf("Enter to age: ");
                int to_age;
                scanf("%d", &to_age);
                if (from_age > to_age) {
                    printf("Ages are incorrect, try again...\n");
                    break;
                }

                for (int i = 0; i < id_users; ++i) {
                    insert(root, &users[i], "age");
                }
                printf("Users with age between %d and %d:\n", from_age, to_age);
                print_users_with_age(root, from_age, to_age);
                free_btree(root);
                break;

            case 3:
                printf("Enter starting money: ");
                long long int starting_money;
                scanf("%lld", &starting_money);
                printf("Enter ending money: ");
                long long int ending_money;
                scanf("%lld", &ending_money);
                if (starting_money > ending_money) {
                    printf("Values are incorrect, try again...\n");
                    break;

                }

                for (int i = 0; i < id_users; ++i) {
                    insert(root, &users[i], "money");
                }
                printf("Users with money between %lld and %lld:\n", starting_money, ending_money);
                print_users_with_money(root, starting_money, ending_money);
                free_btree(root);
                break;

            case 4:
                printf("Enter starting letter: ");
                char starting_letter;
                scanf(" %c", &starting_letter);
                for (int i = 0; i < id_users; ++i) {
                    insert(root, &users[i], "username");
                }
                printf("Users with username starting with '%c':\n", starting_letter);
                print_users_starting_with_letter(root, starting_letter);
                free_btree(root);
                break;

            case 5:
                printf("\nRETURNING TO THE LOGIN INFO PAGE...");
                Sleep(1500);
                flag = 0;
                free_btree(root);
                break;

            default:
                printf("You entered a wrong number, dummy!\n\n");
                free_btree(root);
                break;
        }
    }
    infoPage(userData);
}

void insert(struct btree_node *root, struct data *user, char *key) {
    if (root->num_keys == MAX_KEYS) { // Check if the root is full
        struct btree_node *new_root = create_node(); // Create a new root
        new_root->child[0] = root; // Make the current root a child of the new root
        split_child(new_root, 0, root); // Split the full root
        insert_nonfull(new_root, user, key); // Insert the user into the newly created root
    } else {
        insert_nonfull(root, user, key); // Insert the user into the non-full root
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

void insert_nonfull(struct btree_node *node, struct data *user, char *key) {
    int i = node->num_keys - 1;
    if (strcmp(key, "username") == 0) {
        if (node->child[0] == NULL) {
            while (i >= 0 && strcmp(user->username, node->keys[i]->username) < 0) {
                node->keys[i + 1] = node->keys[i];
                i--;
            }
            node->keys[i + 1] = user;
            node->num_keys++;
        } 
        
        else {
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
            insert_nonfull(node->child[i], user, key);
        }
    } 
    
    else if (strcmp(key, "money") == 0) {
        if (node->child[0] == NULL) {
            while (i >= 0 && user->money < node->keys[i]->money) {
                node->keys[i + 1] = node->keys[i];
                i--;
            }
            node->keys[i + 1] = user;
            node->num_keys++;
        } 
        
        else {
            while (i >= 0 && user->money < node->keys[i]->money) {
                i--;
            }
            i++;
            if (node->child[i]->num_keys == MAX_KEYS) {
                split_child(node, i, node->child[i]);
                if (user->money > node->keys[i]->money) {
                    i++;
                }
            }
            insert_nonfull(node->child[i], user, key);
        }
    } 
    
    else if (strcmp(key, "age") == 0) {
        if (node->child[0] == NULL) {
            while (i >= 0 && calculate_age(user->day, user->month, user->year) < calculate_age(node->keys[i]->day, node->keys[i]->month, node->keys[i]->year)) {
                node->keys[i + 1] = node->keys[i];
                i--;
            }
            node->keys[i + 1] = user;
            node->num_keys++;
        } 
        
        else {
            while (i >= 0 && calculate_age(user->day, user->month, user->year) < calculate_age(node->keys[i]->day, node->keys[i]->month, node->keys[i]->year)) {
                i--;
            }
            i++;
            if (node->child[i]->num_keys == MAX_KEYS) {
                split_child(node, i, node->child[i]);
                if (calculate_age(user->day, user->month, user->year) > calculate_age(node->keys[i]->day, node->keys[i]->month, node->keys[i]->year)) {
                    i++;
                }
            }
            insert_nonfull(node->child[i], user, key);
        }
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
    } 
    
    else {
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

// for testing purposes
void print_btree(struct btree_node *root, int level) {
    if (root != NULL) {
        int i;
        for (i = 0; i < root->num_keys; i++) {
            print_btree(root->child[i], level + 1);
            printf("\n");
            for (int j = 0; j < level; j++) {
                printf("    ");
            }
            printf("%s\n", root->keys[i]->username);
        }
        print_btree(root->child[i], level + 1);
    }
}