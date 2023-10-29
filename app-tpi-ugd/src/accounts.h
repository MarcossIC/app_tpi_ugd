//
// Created by usuario on 28/10/2023.
//

#ifndef APP_TPI_UGD_ACCOUNTS_H
#define APP_TPI_UGD_ACCOUNTS_H
#include <stdbool.h>

struct Account{
    char name[50];
    char lastName[50];
    char dni[20];
    char address[20];
    char birthDay[20];
    char cellphone[20];
    char type[20];
};

int createUserAccount(struct Account user);
int uiRegister();
struct Account getRegisterValidInput();
#endif //APP_TPI_UGD_ACCOUNTS_H
