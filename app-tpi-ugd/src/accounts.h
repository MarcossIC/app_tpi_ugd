//
// Created by usuario on 28/10/2023.
//

#ifndef APP_TPI_UGD_ACCOUNTS_H
#define APP_TPI_UGD_ACCOUNTS_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Account{
    char name[50];
    char lastName[50];
    char dni[50];
    char address[50];
    char birthDay[11];
    char cellphone[50];
    int type;
};

int saveAccount(struct Account user);
int listAllRegisteredAccounts();
void getValidStringInput(const char* inputName, char* input);
void getValidDate(const char* dateName, char* date);
int readIntegerInput(const char* prompt);
struct Account getAccountValidInput();

bool isDniValid(const char* dni);
bool isCellphoneValid(const char* cellphone);
bool isNamesValid(const char* name, const char* nameType);
#endif //APP_TPI_UGD_ACCOUNTS_H
