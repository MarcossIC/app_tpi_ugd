#include <stdio.h>
#include "user.h"
#include "cuenta.h"
#include "movimientos.h"
#include "utilidades.h"
#include "inputs.h"

void clearConsole();

void ejecutarApp();
int vistaInicio();
int vistaRegistrarUsuario();
int vistaListarUsuarios();
int vistaEspera();
int vistaCargaSaldo();
int vistaUsarSaldo(int tipoDeUso);
int vistaConsultarSaldo();

int main() {
    ejecutarApp();
    return 0;
}

void ejecutarApp(){
    int vista = -1;
    do{
        fflush(stdout);
        if(vista == -1){
            vista = vistaInicio();
            clearConsole();
        } else if(vista == 1){
            vista = vistaRegistrarUsuario();
        } else if(vista == 2){
            vista = vistaConsultarSaldo();
        } else if( vista == 3){
            vista = vistaCargaSaldo();
        } else if( vista == 4 || vista == 5){
            vista = vistaUsarSaldo(vista);
        } else if(vista == 7){
            vista = vistaListarUsuarios();
        } else {
            vista = vistaEspera();
            clearConsole();
        }
    } while(vista != 0);
    imprimirMensaje("GRACIAS POR ENTRAR", GREEN_COLOR);
}

int vistaInicio(){
    int nuevaVista = 0;
    bool opcionEsValida = true;
    do{
        printf("****************************************************\n");
        printf("***** SISTEMA ELECTRONICO PARA TRANSPORTE SUBE *****\n");
        printf("************** Elija una opcion ********************\n");
        printf("*  1 - Registrar Usuario                           *\n");
        printf("*  2 - Consultar Saldo                             *\n");
        printf("*  3 - Cargar Saldo                                *\n");
        printf("*  4 - Usar Tarjeta                               *\n");
        printf("*  5 - Usar Billetera                              *\n");
        printf("*  6 - Gestion de transporte                       *\n");
        printf("*  0 - Salir                                       *\n");
        printf("*:");
        scanf("%d", &nuevaVista);
        int opcionesValidas[] = {1, 2, 3, 4, 5, 7,0, -99};
        opcionEsValida = numberIsFoundIn(nuevaVista, opcionesValidas);
        if(!opcionEsValida) imprimirMensaje("LO SIENTO, vista NO ENCONTRADA", RED_COLOR);
    } while(!opcionEsValida);

    return nuevaVista;
}

int vistaListarUsuarios(){
    imprimirMensaje("LISTA DE CUENTAS ", AQUAMARINE_COLOR);
    int conteo = listarTodosLosUsuariosRegistrados();
    char mensaje[60];
    snprintf(mensaje, 100, "Hay %d cuentas registradas", conteo);
    imprimirMensaje(mensaje, GREEN_COLOR);
    return -2;
}

int vistaRegistrarUsuario(){
    imprimirMensaje("REGISTRO DE CUENTA", AQUAMARINE_COLOR);
    struct Usuario usuario = crearNuevoUsuarioValido();
    bool elUsuarioExiste = usuarioExistePorDNI(usuario.DNI);
    printf("****************************************************\n");
    if(!elUsuarioExiste){
        int error = guardarUsuario(usuario);
        clearConsole();
        if(error == 1) imprimirMensaje("Error al crear el usuario. ", RED_COLOR);
        if(error == 0) imprimirMensaje("Usuario creado con exito. ", GREEN_COLOR);
        int lastId = obtenerUltimoIdDeCuenta();
        struct Cuenta cuenta = {lastId};
        cuenta.saldo = 0;
        cuenta.tipo = usuario.tipo;
        strcpy(cuenta.DNI, usuario.DNI);
        guardarCuenta(cuenta);
    } else {
        imprimirMensaje("LO SIENTO, el dni que ingesaste ya se encuentra registrado.", YELLOW_COLOR);
    }
    return -2;
}

/**
 *
 * @return
 */
int vistaCargaSaldo(){
    int p;
    imprimirMensaje("CARGAR SALDO", AQUAMARINE_COLOR);
        // Pedir DNI, monto, boca de pago
        printf("Para realizar la recarga verifique su cuenta ingresando los siguientes datos: \n");
        struct Recargas recarga;
        fflush(stdin);
        escribirStringValido("DNI", recarga.DNI);
        recarga.idCuenta = buscarIdCuenta(recarga.DNI);
        if(recarga.idCuenta != 0){

            printf("Ingrese el monto:");
            scanf("%f",&recarga.monto);
            printf("Seleccione la boca de pago de la siguiente lista: \n 1 Santander Rio\n 2 Banco Nacion\n 3 Banco Corrientes\n 4 Banco Macro\n 5 Personal Pay\n 6 Mercado Pago\n ");
            recarga.bocaDePago =escribirEnteroValido(":");
            //Fecha y hora se puede hacer con time.h
            recuperarFechaActual(recarga.fecha);
            int hora = recuperarHoraActual();
            snprintf(recarga.hora, 10, "%d", hora);
            //Actualizar Saldo de cuenta
             actualizarSaldoCuenta(recarga.idCuenta,recarga.monto, &p);
            //Guardar recarga
            guardarRecarga(recarga);

            //Generar comprobante
            FILE *Comprobante;
            if ((Comprobante=fopen("assets/comprobantes/Comprobantes.txt","w+"))!=NULL){
                fputs("*****************************COMPROBANTE****************************",Comprobante);
                fputs("\n DNI: ",Comprobante); fputs(recarga.DNI,Comprobante);
                char monto[20], idCuenta[10];
                sscanf(monto, "%f", recarga.monto);
                sscanf(idCuenta, "%d", recarga.idCuenta);
                fputs("\n Monto Ingresado: ",Comprobante); fputs(monto, Comprobante);
                fputs("\n Nr. Unidad: ",Comprobante); fputs(idCuenta, Comprobante);
                fputs("\n Fecha: ",Comprobante); fputs(recarga.fecha,Comprobante);
                fputs("******************************************************************",Comprobante);
                fclose(Comprobante);
            }else imprimirMensaje("Error de apertura de archivo.", RED_COLOR);
    } else imprimirMensaje("LO SIENTO, el dni que ingesaste ya se encuentra registrado.", YELLOW_COLOR);
    return -2;
}

int vistaUsarSaldo(int tipoDeUso){
    imprimirMensaje("USAR SALDO", AQUAMARINE_COLOR);
    printf("Dime tus datos:\n");
    char DNI[10];
    fflush(stdin);
    escribirStringValido("DNI", DNI);
    struct Cuenta cuenta = recuperarCuenta(DNI);

    if(cuenta.id != NULL && cuenta.id != 0){
        if(cuenta.saldo > -200){
            struct Movimiento movimiento = crearNuevoMovimiento(tipoDeUso);
            struct Usuario  usuario = recuperarUsuario(DNI);
            fflush(stdin);
            strcpy(movimiento.DNI, DNI);
            movimiento.idCuenta = cuenta.id;
            strcpy(movimiento.telefono, usuario.telefono);
            movimiento.montoUtilizado = escribirMontoValido("Ingrese el monto que utilizara:", cuenta.saldo+200, 200.00);
            int error = guardarMovimientos(movimiento);
            if (error == 0) {
                error = actualizarSaldoCuenta(movimiento.idCuenta, movimiento.montoUtilizado * -1, 0);
                if(error == 0) imprimirMensaje("Has usado tu saldo", GREEN_COLOR);
            }

        } else imprimirMensaje("LO SIENTO, el saldo de su cuenta ha llegado a su limite", RED_COLOR);
    } else imprimirMensaje("LO SIENTO, SU DNI NO ESTA REGISTRADO", RED_COLOR);

    return -2;
}


int vistaConsultarSaldo(){
    float saldo;
    bool flag= false;
    imprimirMensaje("CONSULTAR SALDO", AQUAMARINE_COLOR);
    printf("Para realizar la consulta verifique su cuenta ingresando los siguientes datos: \n");
    struct Cuenta cuentas;
    int hora = recuperarHoraActual();
    fflush(stdin);
    escribirStringValido("DNI",cuentas.DNI);
    saldo= recuperarSaldo(cuentas.DNI);
    flag = usuarioExistePorDNI(cuentas.DNI);
    char fecha[11];
    recuperarFechaActual(fecha);
    if (flag){
        char mensaje[100];
        snprintf(mensaje, 100, "DNI: %s \nSu saldo es : %.2f\nHora: %d\nFecha: %s",cuentas.DNI, saldo, hora, fecha);
        imprimirMensaje(mensaje, GREEN_COLOR);
        flag = false;
    }

    return -2;
}


int vistaEspera(){
    int nuevavista = 0;
    bool opcionEsValida = true;
    do{
        printf("\n*************    Que desea realizar?   *************\n");
        printf("* -1 - Continuar                \n");
        printf("*  0 - Salir                     \n");
        printf("*:");
        scanf("%d", &nuevavista);
        int opcionesValidas[] = {0,-1, -99};
        opcionEsValida = numberIsFoundIn(nuevavista, opcionesValidas);
        if(!opcionEsValida) imprimirMensaje("LO SIENTO, OPCION NO VALIDA", RED_COLOR);
    } while(!opcionEsValida);
    return nuevavista;
}
