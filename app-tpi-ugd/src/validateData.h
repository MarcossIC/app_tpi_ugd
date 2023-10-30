#ifndef APP_TPI_UGD_VALIDATEDATA_H
#define APP_TPI_UGD_VALIDATEDATA_H
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

int calcUserAge(int year);

bool isLeapYear(int year);
bool isValidDate(int day, int month, int year);
bool isGreaterThan(int birthdayYear, int olderAge);
bool isStringOnlyHasNumber(char *string, char* stringName);
bool stringEquals(char* firstString, char* secondString);
bool stringSizeLessThan(char* string, char* stringName, int number);
bool stringSizeIsBetween(char* string, char* stringName, int firstNumber, int secondNumber);
bool stringSizeGreaterThan(char* string, char* stringName, int number);
bool stringNotContainNumber(char* string, char* stringName);
bool stringSizeIsEqualsTo(char *string, char* stringName, int size);

#endif //APP_TPI_UGD_VALIDATEDATA_H
