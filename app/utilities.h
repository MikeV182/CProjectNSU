#ifndef UTILITIES_H
#define UTILITIES_H

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
int id_users;

void gotoxy(int x, int y);
int calculate_age(int day, int month, int year);
int leap_year(int year);
int data_check(int day, int month, int year);

#endif /* UTILITIES_H */

