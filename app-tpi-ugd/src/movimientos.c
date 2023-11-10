//
// Created by usuario on 9/11/2023.
//

#include "movimientos.h"

/**
 *
 * @author Thyago
 * @param cargaSaldo
 * @return
 */
int guardarRecarga(struct Recargas recarga){
    FILE* Arch;
    int error=0;
    if((Arch=fopen("assests/Recargas.dat","a+b"))!=NULL){
        fwrite(&recarga,sizeof(struct Recargas),1,Arch);
        fclose (Arch);
    }else{
        printf("Error al abrir");
        error=1;
    }
    return error;
}

/**
 *
 * @author Marcos
 * @param movimiento
 * @return
 */
int guardarMovimientos(struct Movimiento movimiento){
    FILE* movimientosArch;
    int errors = 0;
    if((movimientosArch = fopen("assets/Movimientos.dat", "a+b")) != NULL){
        fwrite(&movimiento, sizeof(struct Movimiento), 1, movimientosArch);
        fclose(movimientosArch);
    } else errors = 1;
    return errors;
}

struct Movimiento crearNuevoMovimiento(int tipoDeUso){
    struct Movimiento movimiento;
    fflush(stdin);
    movimiento.idUnidad = escribirEnteroValido("Dime en que unidad viajas:");
    escribirStringValido("origen", movimiento.origen);
    escribirStringValido("destino", movimiento.destino);
    movimiento.hora = recuperarHoraActual();
    recuperarFechaActual(movimiento.fecha);

    if(tipoDeUso == 4 )movimiento.esTarjeta = 1;
    else movimiento.esTarjeta = 0;

    return movimiento;
}