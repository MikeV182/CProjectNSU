#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "utilities.h"

// Прототипы функций для работы с аккаунтом
void create_account(void);
void account_created(void);
void login_page(void);
void infoPage(struct data* userData);
void logout(void);
void self_moneyAdd(struct data* userData); 

#endif /* ACCOUNT_H */
