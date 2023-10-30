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
    char birthDay[50];
    char cellphone[50];
    char type[20];
};

typedef struct {
    char name[50];
    char lastName[50];
    char dni[50];
    char address[50];
    char birthDay[20];
    char cellphone[50];
    char type[50];
} Account2;

int createUserAccount(struct Account user);
char* getValidStringInput(char* inputName);
char* getValidDate(char* dateName);
struct Account getRegisterValidInput();

bool isDniValid(char* dni);
bool isCellphoneValid(char* cellphone);
bool isNamesValid(char* name, char* nameType);
#endif //APP_TPI_UGD_ACCOUNTS_H
