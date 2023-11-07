//
// Created by usuario on 6/11/2023.
//

#ifndef APP_TPI_UGD_INPUTS_H
#define APP_TPI_UGD_INPUTS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void escribirStringValido(const char* inputName, char* input);
int escribirEnteroValido(const char* prompt);
void escribirFechaValida(const char* dateName, char* date);
bool esValidoElDNI(const char* dni);
bool esValidoElTelefono(const char* cellphone);
bool esValidoElNombre(const char* name, const char* nameType);

#endif //APP_TPI_UGD_INPUTS_H

