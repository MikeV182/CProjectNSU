#ifndef BTREE_H
#define BTREE_H

#include "utilities.h"

// Прототипы функций для работы с B-деревом
struct btree_node *create_node(void);
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

#endif /* BTREE_H */
