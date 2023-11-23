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
    if((Arch=fopen("assets/Recargas.dat","a+b"))!=NULL){
        fwrite(&recarga,sizeof(struct Recargas),1,Arch);
        fclose (Arch);
    }else{
        printf("Error al abrir.\n");
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

/**
 *
 * @author Marcos
 * @param tipoDeUso
 * @return
 */
struct Movimiento crearNuevoMovimiento(int tipoDeUso){
    struct Movimiento movimiento;
    fflush(stdin);
    movimiento.origen = escribirDireccionValida("origen");
    movimiento.destino = escribirDireccionValida("destino");
    movimiento.hora = recuperarHoraActual();
    recuperarFechaActual(movimiento.fecha);

    if(tipoDeUso == 4 )movimiento.esTarjeta = 1;
    else movimiento.esTarjeta = 0;

    return movimiento;
}

/**
 * @author Marcos
 * @param tipoDeUso
 * @return
 */
int listarMovimientosEntreFechas(const char* fechaInicio, const char* fechaFin){
    FILE* movimientoArch;
    struct Movimiento movimiento;
    int cuentaMovimientos = 0;
    if((movimientoArch = fopen("assets/Movimientos.dat", "rb")) != NULL) {
        while (fread(&movimiento, sizeof(struct Movimiento), 1, movimientoArch) == 1){
            if( dateIsBetween(movimiento.fecha, fechaInicio, fechaFin) ){
                printf("*                  Movimiento                      *\n");
                if(movimiento.esTarjeta == 1) printf("Tipo de movimiento: Tarjeta.\n");
                else printf("Tipo de movimiento: Billetera virtual.\n");
                printf("DNI: %s\n", movimiento.DNI);
                printf("Telefono: %s\n", movimiento.telefono);
                printf("Nro de cuenta: %d\n", movimiento.idCuenta);
                printf("Origen: %s\n", recuperarDireccion(movimiento.origen));
                printf("Destino: %s\n", recuperarDireccion(movimiento.destino));
                printf("Monto: %.2f\n", movimiento.montoUtilizado);
                printf("Fecha: %s\n", movimiento.fecha);
                printf("Hora: %d\n", movimiento.hora);
                printf("****************************************************\n");
                cuentaMovimientos++;
            }
        }
        fclose(movimientoArch);
    }
    return cuentaMovimientos;
}

/**
 *
 * @author Matias
 * @param tipoDeUso
 * @return
 */
void generarComrpobante(const char* name, struct Recargas recarga) {
    FILE *Comprobante;
    char filePath[80];
    snprintf(filePath, 80, "assets/comprobantes/%s",name);
    if ((Comprobante=fopen(filePath,"w+"))!=NULL){
        fputs("*****************************COMPROBANTE****************************",Comprobante);
        fputs("\n DNI: ",Comprobante); fputs(recarga.DNI,Comprobante);
        char monto[20], idCuenta[10], hora[10];
        itoa(recarga.monto, monto, 10);

        itoa(recarga.idCuenta, idCuenta, 10);
        itoa(recarga.hora, hora, 10);

        fputs("\n Monto Ingresado: ",Comprobante); fputs(monto, Comprobante);
        fputs("\n Nr. Unidad: ",Comprobante); fputs(idCuenta, Comprobante);
        fputs("\n Fecha: ",Comprobante); fputs(recarga.fecha,Comprobante);
        fputs("\n Hora: ",Comprobante); fputs(hora,Comprobante);
        fputs("\n******************************************************************",Comprobante);
        fclose(Comprobante);
    }  else imprimirMensaje("Error de apertura de archivo.", RED_COLOR);
}

/**
 *
 * @author Thyago
 * @param tipoDeUso
 * @return
 */
int listarRecargaPorUsuario(const char *DNI){

    FILE *Arch;
    struct Recargas recarga;
    int cont=0;
    if((Arch=fopen("assets/Recargas.dat","rb"))!=NULL){
        while (fread(&recarga, sizeof(struct Recargas), 1, Arch)){
            if (areStringsEqual(recarga.DNI,DNI)){
                cont++;
                printf("*                  Recarga                        *\n");
                printf ("DNI: %s\n",recarga.DNI);
                printf ("ID de Cuenta: %d\n", recarga.idCuenta);
                printf ("Monto Cargado: %.2f\n", recarga.monto);
                printf ("Boca de pago: %s\n",recuperarTipoBocaPago(recarga.bocaDePago));
                printf ("Fecha: %s\n", recarga.fecha);
                printf ("Hora: %d\n", recarga.hora);
                printf("****************************************************\n");
            }
        }
        fclose(Arch);
    }else{
        imprimirMensaje("Error al abrir el acrhivo de ListarRecargaPorUsuario", RED_COLOR);
    }

    return cont;
}

/**
 * @author Thyago
 * @return
 */
float contadorPorcentajePrimerTurno(){
    FILE* movimientoArch;
    struct Movimiento movimiento;
    int contadorPrimTurno = 0;
    int cuentaMovimientos = 0;
    int  anho = getCurrentYear();
    float porc = 0;

    if((movimientoArch = fopen("assets/Movimientos.dat", "rb")) != NULL) {
        while (fread(&movimiento, sizeof(struct Movimiento), 1, movimientoArch) == 1){
            if (movimiento.hora >= 0 && movimiento.hora < 12 && desComponerFecha(movimiento.fecha).anho == anho) contadorPrimTurno++;

            cuentaMovimientos++;
        }
        porc = contadorPrimTurno * 100 / cuentaMovimientos;
        fclose(movimientoArch);
    }

    return porc;
}

/**
 * @author Matias
 * @param DNI
 * @return
 */
int listarMovimientoPorUsuario(const char* DNI){
    FILE* movimientoArch;
    struct Movimiento movimiento;
    int cuentaMovimientos = 0;
    if((movimientoArch = fopen("assets/Movimientos.dat", "rb")) != NULL) {
        while (fread(&movimiento, sizeof(struct Movimiento), 1, movimientoArch) == 1){
            if(areStringsEqual(DNI, movimiento.DNI)){
                printf("*                  Movimiento                      *\n");
                if(movimiento.esTarjeta == 1) printf("Tipo de movimiento: Tarjeta");
                else printf("Tipo de movimiento: Billetera virtual");
                printf("DNI: %s\n", movimiento.DNI);
                printf("Telefono: %s\n", movimiento.telefono);
                printf("Nro de cuenta: %d\n", movimiento.idCuenta);
                printf("Origen: %s\n", recuperarDireccion(movimiento.origen));
                printf("Destino: %s\n", recuperarDireccion(movimiento.destino));
                printf("Monto: %.2f\n", movimiento.montoUtilizado);
                printf("Fecha: %s\n", movimiento.fecha);
                printf("Hora: %d\n", movimiento.hora);
                printf("****************************************************\n");
                cuentaMovimientos++;
            }
        }
        fclose(movimientoArch);
    }
    return cuentaMovimientos;
}


int buscarUnidadConMasViajes(const int mes){
    FILE* movimientoArch;
    FILE* movimientoCopyArch;
    struct Movimiento movimientoRef;
    struct Movimiento movimiento;
    struct Fecha fecha;
    int attpCount = 0;
    int maxCont = 0;
    int attpId = 0;
    int maxId = 0;
    duplicarArchivo("assets/Movimientos.dat", "assets/CopyMovimientos.dat");

    if((movimientoArch = fopen("assets/Movimientos.dat", "rb")) != NULL && (movimientoCopyArch = fopen("assets/CopyMovimientos.dat", "rb")) != NULL) {
        while (fread(&movimientoRef, sizeof(struct Movimiento), 1, movimientoArch) == 1) {
            if(desComponerFecha(movimientoRef.fecha).mes == mes) {
                rewind(movimientoCopyArch);
                while (fread(&movimiento, sizeof(struct Movimiento), 1, movimientoCopyArch) == 1) {
                    if(movimientoRef.idUnidad == movimiento.idUnidad && desComponerFecha(movimiento.fecha).mes == mes){

                        attpId = movimiento.idUnidad;
                        attpCount++;
                    }
                }

                if(attpCount > maxCont) {
                    maxCont = attpCount;
                    maxId = attpId;
                }
                maxCont = 0;
            }
        }

        fclose(movimientoCopyArch);
        fclose(movimientoArch);
    } else imprimirMensaje("No se pudo abrir el archivo.", RED_COLOR);

    borrarArchivo("assets/CopyMovimientos.dat");

    return maxId;
}

