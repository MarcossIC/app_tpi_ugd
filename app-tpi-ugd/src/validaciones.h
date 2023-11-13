#ifndef APP_TPI_UGD_VALIDACIONES_H
#define APP_TPI_UGD_VALIDACIONES_H

#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "utilidades.h"

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
bool numberIsFoundIn(int number, const int numbers[]);
bool isWindowsOS();
bool isValidDNI(const char* dni);
bool isCellphoneValid(const char* cellphone);
bool isAddressValid(const char* address);
bool isNameValid(const char* name, const char* nameType);
bool dateIsBetween(const char *date, const char *startDate, const char *endDate);
bool validarOpciones(const int opcion, const int* opcionesValidas);
bool isLessThan(int birthdayYear, int olderAge);

#endif //APP_TPI_UGD_VALIDACIONES_H

