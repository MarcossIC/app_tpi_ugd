//
// Created by usuario on 28/10/2023.
//

#ifndef APP_TPI_UGD_VALIDATEDATA_H
#define APP_TPI_UGD_VALIDATEDATA_H
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int calcUserAge(int year);
bool isNameOrLastNameValid(char *nameOrLastname, char* type);
bool isBirthDateValid(int day, int month, int year);
bool isDniValid(char *dni);
bool isAddressValid(char *address);
bool isCellphoneValid(char *cellphone);
bool isLeapYear(int year);


#endif //APP_TPI_UGD_VALIDATEDATA_H
