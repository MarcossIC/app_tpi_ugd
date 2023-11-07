#ifndef APP_TPI_UGD_UTILIDADES_H
#define APP_TPI_UGD_UTILIDADES_H
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define GREEN_OUTPUT 32
#define DEFAULT_COLOR 39
#define DEFAULT_BG 40

#define BLACK_COLOR "0"
#define RED_COLOR 4
#define GREEN_COLOR 2
#define WHITE_COLOR "7"


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
bool encontrarCoincidencia(int number, const int numbers[]);

bool isWindowsOS();
void clearConsole();
void setColorOutput(int foregroundColor);
void resetColor();

#endif //APP_TPI_UGD_UTILIDADES_H
