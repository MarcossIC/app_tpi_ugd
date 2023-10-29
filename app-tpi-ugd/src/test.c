//
// Created by usuario on 28/10/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Estudiante {
    int matricula;
    char nombre[50];
    int edad;
    float promedio;
};

int main() {
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