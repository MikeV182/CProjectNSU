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
int id_users;

int main(void);