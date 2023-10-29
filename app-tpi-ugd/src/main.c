#include <stdio.h>

#include "accounts.h"
#include <string.h>

struct Estudiante {
    int matricula;
    char nombre[50];
    int edad;
    float promedio;
};

void runApp();
void screen0();
int screen1();
int screen2();
void screen3();

/*
    TPI:
    Requerimientos:
        - Registro de usuario
            requiere:
            DNI, Nombre y apellido, Fecha de nacimiento, Dirección, Teléfono y Tipo
            *Tipo*: El Tipo de usuario puede ser
                * Normal (sin beneficios).
                * Beneficio Boleto Estudiantil Gratuito.
                * Beneficio por discapacidad, Beneficio de Mayor de Edad.
                * Beneficio Ex-Combatiente de Malvinas.

        - Carga de Saldo
            requiere:
            DNI, Nro. Control, Monto, Boca de pago, Fecha y hora.
            *Generar un comprobante (archivo de texto).

        - Consulta de Saldo
            requiere:
            DNI, Saldo disponible, Fecha y hora.

        - Uso de tarjeta
            requiere:
            DNI, Nro Tarjeta, Nro. unidad, Origen, Destino, Saldo utilizado, Fecha y hora.
            *Genera un movimiento registrando

        - Uso de billetera electronica
            requiere :
            DNI, Nro Celular, Origen, Destino, Nro. unidad, Saldo utilizado, Fecha y hora.

        - Choferes
            requiere:
            DNI, Nombre y apellido, Fecha de nacimiento, Dirección, Teléfono y Correo electrónico (e-mail).

        - Medios de transporte
            requiere:
            De las Unidades (colectivos): Nro. unidad, DNIC, Turno, Marca, Modelo, Cantidad de asiento,
            Kilometraje, Fecha alta y si está adaptado para pasajeros discapacitados.


        Estructura:

        - Vista 0: Pantalla de salida
            Termina la aplicacion

        - Vista 1: Es Pantalla de inicio, re dirije a las otras funciones
                * Registro
                * Cargar Saldo
                * Consulta de Saldo

         - Vista 2: Es pantalla de Registro
            Cuando se termina de registra regresa a la pantalla 1

        - Vista 3: Cargar saldo


 */

int main() {
    //runApp();

    FILE *archivo, *aux;
    int matricula, i=0, id;

    struct Estudiante lista[10];

    //REGISTRO DE MATRICULA

    for (i=0; i<10; i++){
        printf("\n Ingrese la matricula: ");
        scanf("%d", &lista[i].matricula);
    }

    if ((archivo=fopen("estudiantes.dat","wb")) != NULL ) {
        fwrite(lista,sizeof(struct Estudiante),10,archivo);
        fclose(archivo);
    }
    else printf("\n Error de apertura");

//LECURA DE MATRICULAS CARGADAS

    printf("\n\n Lista diseñada: ");


    struct Estudiante student;
    if((archivo=fopen("estudiantes.dat","rb"))!=NULL){
        for (int i = 0; i < 10; i++) {
            fread(&lista[i], sizeof(struct Estudiante), 1, archivo);
            printf("\n Matricula: %d", lista[i].matricula);
        }

        fread(&student, sizeof(struct Estudiante), 1, archivo);
        student.matricula=matricula;

        fwrite(lista,sizeof(struct Estudiante),10,archivo);

        fclose(archivo);
    }
    else printf("\n Error de apertura \n");

    //BUSCAR UNA MATRICULA CARGADA Y CAMBIARLA

    printf("\n\n Modifica la matricula:  ");
    scanf("%d",&id);
    printf("\n ingrese la nueva matricula: ");
    scanf("%d",&matricula);

    if ((archivo=fopen("estudiantes.dat","rb+"))!=NULL) {
        lista[id].matricula=matricula;
        //lista[id].nombre= "Algo";
        fwrite(lista,sizeof(struct Estudiante),10,archivo);

        fclose(archivo);
    } else printf("\n Error de apertura");

    return 0;
}

void runApp(){
    int page = 1;

    do{
        if(page == 1) page = screen1();
        if(page == 2) page = screen2();

    //
    } while(page != 0);

    screen0();
}

int screen1(){
    int updatePage = 0;
    printf("****************************************************\n");
    printf("***** SISTEMA ELECTRONICO PARA TRANSPORTE SUBE *****\n");
    printf("************** Elija una opcion ********************\n");
    printf("*  1 - Iniciar Sesion (Ya tiene una cuenta?)       *\n");
    printf("*  2 - Registrarse                                 *\n");
    printf("*  3 - Salir                                       *\n");
    printf("*:");
    scanf("%d", &updatePage);
    printf("****************************************************\n");
    return updatePage;
}

void screen3(){
//
}

int screen2(){
    return uiRegister();
}
//
void screen0(){
    printf("****************************************************\n");
    printf("*************    GRACIAS POR ENTRAR    *************\n");
    printf("****************************************************\n");
}