#ifndef APP_TPI_UGD_VALIDATEDATA_H
#define APP_TPI_UGD_VALIDATEDATA_H
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

int calcUserAge(int year);

bool isLeapYear(int year);
bool isValidDate(int day, int month, int year);
bool isOlderThan(int birthdayYear, int olderAge);
bool isStringOnlyHasNumber(const char *string, const char* stringName);
bool areStringsEqual(const char* firstString, const char* secondString);
bool areIntegersEqual(int firstNumber, int secondNumber);
bool isStringLengthLessThan(const char* string, const char* stringName, int minSize);
bool isStringLengthBetween(const char* string, const char* stringName, int minSize, int maxSize);
bool isStringLengthGreaterThan(const char* string, const char* stringName, int maxSize);
bool doesStringNotContainDigits(const char* string, const char* stringName);
bool isStringLengthEqualTo(const char *string, const char* stringName, int size);

#endif //APP_TPI_UGD_VALIDATEDATA_H
