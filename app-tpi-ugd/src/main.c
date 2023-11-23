#include <stdio.h>
#include "user.h"
#include "cuenta.h"
#include "movimientos.h"
#include "utilidades.h"
#include "inputs.h"
#include "transportes.h"
#include "transportes.h"
#include <locale.h>

void ejecutarApp();
int vistaInicio();
int vistaRegistrarUsuario();
int vistaListarUsuarios();
int vistaEspera();
int vistaCargaSaldo();
int vistaUsarSaldo(int tipoDeUso);
int vistaConsultarSaldo();
int vistaMovimientoEntreFechas();
int vistaUsuariosConBenificios();
int vistaListarRecargaPorUsuario();
int vistaCrearChofer();
int vistaCrearUnidad();
int vistaListarUnidades();
int vistaListarChoferes();
int vistaPorcentajePrimerTurno();
int vistaMovimientosPorUsuario();
int vistaChoferConMasPasajeros();

int main() {
    //Para evitar que se rompan las "ñ" en consola
    setlocale(LC_ALL, "");
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
        } else if(vista == 6){
            vista = vistaListarUsuarios();
        } else if(vista == 7){
            vista = vistaMovimientoEntreFechas();
        } else if(vista == 8){
            vista = vistaUsuariosConBenificios();
        } else if (vista==9){
            vista = vistaListarRecargaPorUsuario();
        } else if (vista==10){
            vista = vistaCrearChofer();
        } else if (vista==11){
            vista = vistaCrearUnidad();
        } else if (vista==12){
            vista = vistaListarChoferes();
        } else if(vista == 13){
            vista = vistaListarUnidades();
        } else if (vista==14){
            vista= vistaPorcentajePrimerTurno();
        } else if (vista==15){
            vista = vistaMovimientosPorUsuario();
        } else if(vista == 16){
            vista = vistaChoferConMasPasajeros();
        }
        else {
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
        printf("**************   Elija una opcion  *****************\n");
        printf("*   1 - Registrar Usuario                           *\n");
        printf("*   2 - Consultar Saldo                             *\n");
        printf("*   3 - Cargar Saldo                                *\n");
        printf("*   4 - Usar Tarjeta                                *\n");
        printf("*   5 - Usar Billetera                              *\n");
        printf("*   6 - Listar Usuarios                             *\n");
        printf("*   7 - Ver movimientos, entre fechas               *\n");
        printf("*   8 - Cuenta usuarios con beneficios              *\n");
        printf("*   9 - Listar Recargas por Usuario                 *\n");
        printf("*  10 - Registrar Chofer                            *\n");
        printf("*  11 - Registrar Unidad                            *\n");
        printf("*  12 - Listar Choferes                             *\n");
        printf("*  13 - Listar Unidad                               *\n");
        printf("*  14 - Porcentaje de Movimientos el Primer turno   *\n");
        printf("*  15 - Listar Movimientos de un Usuario            *\n");
        printf("*  16 - Ver chofer con mas pasajeros en un mes      *\n");
        printf("*  0 - Salir                                        *\n");

        nuevaVista = escribirEnteroValido("*:", false);
        int opcionesValidas[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,11, 12 , 13  ,  14 , 15 , 16, 0 , -99};
        opcionEsValida = numberIsFoundIn(nuevaVista, opcionesValidas);

        if(!opcionEsValida) imprimirMensaje("LO SIENTO, vista NO ENCONTRADA", RED_COLOR);
    } while(!opcionEsValida);

    return nuevaVista;
}

int vistaListarUsuarios(){
    imprimirMensaje("LISTA DE CUENTAS ", AQUAMARINE_COLOR);
    int conteo = 0;
    conteo = listarTodosLosUsuariosRegistrados();
    if(conteo == 0) imprimirMensaje("No hay usuarios registrados", YELLOW_COLOR);
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
        int lastId = obtenerUltimoIdDeCuenta()+1;
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
 * @return
 */
int vistaCargaSaldo(){
    imprimirMensaje("CARGAR SALDO", AQUAMARINE_COLOR);
        printf("Para realizar la recarga verifique su cuenta ingresando los siguientes datos: \n");
        struct Recargas recarga;
        fflush(stdin);

        escribirStringValido("DNI", recarga.DNI);
        recarga.idCuenta = buscarIdCuenta(recarga.DNI);
        if(recarga.idCuenta != 0){
            recarga.monto = escribirMontoValido("Ingrese el monto:", TOPE, 1);
            bool bocaDePagoValida = true;
            do{
                printf("Seleccione la boca de pago de la siguiente lista: \n 1 - Santander Rio\n 2 - Banco Nacion\n 3 - Banco Corrientes\n 4 - Banco Macro\n 5 - Banco Galicia \n 6 - Personal Pay\n 7 - Mercado Pago\n ");
                recarga.bocaDePago =escribirEnteroValido(":", false);
                int opcionesValidas[] = {1, 2, 3, 4, 5, 6, 7, -99};
                bocaDePagoValida = numberIsFoundIn(recarga.bocaDePago, opcionesValidas);
                if(!bocaDePagoValida) imprimirMensaje("No es una opcion valida", RED_COLOR);
            } while(!bocaDePagoValida);
            //
            recuperarFechaActual(recarga.fecha);
            recarga.hora = recuperarHoraActual();
            //Actualizar Saldo de cuenta
            float excedente;
            int actualizo = actualizarSaldoCuenta(recarga.idCuenta,recarga.monto, &excedente);
            if(actualizo == 0){
                imprimirMensaje("SE CARGO HA CARGADO EL SALDO", GREEN_COLOR);
                //Guardar recarga
                guardarRecarga(recarga);

                //Generar comprobante
                char nombreComprobante[40];
                snprintf(nombreComprobante, 40, "comprobante%d%d%s-%s.txt", recarga.idCuenta, recarga.hora, recarga.DNI,recarga.fecha);
                generarComrpobante(nombreComprobante, recarga);
            } else {
                imprimirMensaje("No se ha podido actualizar el saldo.", RED_COLOR);
            }
    } else imprimirMensaje("LO SIENTO, el dni ingresado no se encuentra registrado.", YELLOW_COLOR);
    return -2;
}

int vistaUsarSaldo(int tipoDeUso){
    imprimirMensaje("USAR SALDO", AQUAMARINE_COLOR);
    printf("Dime tus datos:\n");
    char DNI[10];
    fflush(stdin);
    escribirStringValido("DNI", DNI);
    struct Cuenta cuenta = recuperarCuenta(DNI);


    if(cuenta.id != 0) {
        if(cuenta.saldo > -200) {
            struct Movimiento movimiento;
            bool unidadExiste = true;
            do{
                movimiento.idUnidad = escribirEnteroValido("Dime en que unidad viajas:", false);
                unidadExiste = unidadExistePorId(movimiento.idUnidad);

                if(!unidadExiste) imprimirMensaje("Esta unidad no esta registrada.", YELLOW_COLOR);
            } while(!unidadExiste);
            movimiento = crearNuevoMovimiento(tipoDeUso);

            struct Usuario  usuario = recuperarUsuario(DNI);
            strcpy(movimiento.DNI, DNI);
            movimiento.idCuenta = cuenta.id;
            strcpy(movimiento.telefono, usuario.telefono);
            definirPrecio(&movimiento.montoUtilizado, usuario.tipo, movimiento.origen, movimiento.destino, movimiento.hora);
            movimiento.hora = 6;
            int error = guardarMovimientos(movimiento);

            if (error == 0) {
                error = actualizarSaldoCuenta(movimiento.idCuenta, movimiento.montoUtilizado * -1, 0);
                if(error == 0) imprimirMensaje("Has usado tu saldo", GREEN_COLOR);
            }

        } else imprimirMensaje("LO SIENTO, el saldo de su cuenta ha llegado a su limite", YELLOW_COLOR);
    } else imprimirMensaje("LO SIENTO, SU DNI NO ESTA REGISTRADO", RED_COLOR);

    return -2;
}


int vistaConsultarSaldo(){
    float saldo;
    imprimirMensaje("CONSULTAR SALDO.", AQUAMARINE_COLOR);
    printf("Para realizar la consulta verifique su cuenta ingresando los siguientes datos:\n");
    struct Cuenta cuentas;

    fflush(stdin);
    escribirStringValido("DNI",cuentas.DNI);
    saldo= recuperarSaldo(cuentas.DNI);
    char fecha[11];
    recuperarFechaActual(fecha);
    int hora = recuperarHoraActual();

    bool usuarioExiste = usuarioExistePorDNI(cuentas.DNI);
    if (usuarioExiste){
        char mensaje[100];
        snprintf(mensaje, 100, "DNI: %s \nSu saldo es: %.2f\nHora: %d\nFecha: %s",cuentas.DNI, saldo, hora, fecha);
        imprimirMensaje(mensaje, GREEN_COLOR);
    } else imprimirMensaje("Su DNI no esta registrado", YELLOW_COLOR);

    return -2;
}

int vistaMovimientoEntreFechas(){
    imprimirMensaje("VER MOVIMIENTOS", AQUAMARINE_COLOR);
    printf("Ingressa las fechas\n");
    fflush(stdin);
    char fechaInicio[11], fechaFin[11];
    escribirFechaValida("inicio", fechaInicio);
    escribirFechaValida("fin", fechaFin);
    int cuenta =listarMovimientosEntreFechas(fechaInicio, fechaFin);
    if(cuenta == 0) imprimirMensaje("No se ha encontrado movimientos en esas fechas.", YELLOW_COLOR);
    return -2;
}

int vistaUsuariosConBenificios(){
    imprimirMensaje("CUENTA DE USUARIOS CON BENEFICIO.", AQUAMARINE_COLOR);

    int cuenta = contarUsuariosConBeneficio();
    char mensaje[50];
    snprintf(mensaje, 50, "Hay %d usuarios con beneficios.", cuenta);
    imprimirMensaje(mensaje, DARK_GREEN_COLOR);

    return -2;
}

int vistaListarRecargaPorUsuario(){
    imprimirMensaje ("LISTAR RECARGA POR USUARIO", AQUAMARINE_COLOR);
    char DNI[10];
    escribirStringValido("DNI",DNI);
    int existenRecargas;
    bool usuarioExiste = usuarioExistePorDNI(DNI);
    if (usuarioExiste){
        existenRecargas = listarRecargaPorUsuario(DNI);
        if (existenRecargas==0) imprimirMensaje("No existen recargas del Usuario", YELLOW_COLOR);
    } else imprimirMensaje("Su DNI no esta registrado", YELLOW_COLOR);

    return -2;
}

int vistaCrearChofer(){
    imprimirMensaje("REGISTRO DE CHOFER", AQUAMARINE_COLOR);
    struct Chofer chofer = crearNuevoChofer();
    bool elChoferExiste = choferExistePorDNI(chofer.DNI);
    printf("****************************************************\n");
    if(!elChoferExiste){
        int error = guardarChoferes(chofer);
        clearConsole();
        if(error == 1) imprimirMensaje("Error al crear el chofer. ", RED_COLOR);
        if(error == 0) imprimirMensaje("Chofer creado con exito. ", GREEN_COLOR);

    } else imprimirMensaje("LO SIENTO, el dni que ingesaste ya se encuentra registrado.", YELLOW_COLOR);
    return -2;
}

int vistaCrearUnidad(){
    imprimirMensaje("REGISTRO DE UNIDAD.", AQUAMARINE_COLOR);
    struct Unidad unidad = crearNuevaUnidad();
    printf("****************************************************\n");
    int error = guardarUnidad(unidad);
    clearConsole();
    if(error == 1) imprimirMensaje("Error al crear la unidad. ", RED_COLOR);
    if(error == 0) imprimirMensaje("Unidad creada con exito. ", GREEN_COLOR);
    return -2;
}

int vistaListarChoferes(){
    imprimirMensaje("LISTA DE CHOFER", AQUAMARINE_COLOR);

    int cuenta = listarChoferes();
    if(cuenta == 0) imprimirMensaje("No hay choferes registrados", YELLOW_COLOR);

    return -2;
}

int vistaListarUnidades(){
    imprimirMensaje("LISTA DE UNIDAD", AQUAMARINE_COLOR);
    int cuenta = listarUnidades();
    if(cuenta == 0) imprimirMensaje("No hay unidades registradas", YELLOW_COLOR);

    return -2;
}

int vistaPorcentajePrimerTurno() {
    float porcentaje = 0;
    imprimirMensaje("PORCENTAJE USUARIOS EN EL PRIMER TURNO", AQUAMARINE_COLOR);
    char mensaje[50];
    porcentaje = contadorPorcentajePrimerTurno();
    snprintf(mensaje, 50, "El porcentaje es %c %.2f", 37, porcentaje);
    imprimirMensaje(mensaje, DARK_GREEN_COLOR);
    return -2;
}

int vistaEspera(){
    int nuevaVista = 0;
    bool opcionEsValida = true;
    printf("****************************************************\n");
    printf("*           Usuario Hasta aca llegaste.            *\n");
    printf("*   Por Si [1] o por No [0]. Deseas continuar?     *\n");
    nuevaVista = escribirEnteroValido("*:", true);
    return nuevaVista*-1;
}

int vistaMovimientosPorUsuario(){
    char DNI[10], nombre[50], apellido[50];

   imprimirMensaje("LISTAR MOVIMIENTOS DE UN USUARIO", AQUAMARINE_COLOR);
    printf("Ingrese los siguientes datos:\n");
    fflush(stdin);
    escribirStringValido("nombre", nombre);
    escribirStringValido("apellido",apellido);

    int coincidencias = buscarDNIporNombre(nombre,apellido,DNI);
     if(coincidencias>1) {
         printf("\nSe han encontrado varias coincidencias.\n");
         escribirStringValido("DNI",DNI);
     }

     if(coincidencias != 0) listarMovimientoPorUsuario(DNI);
     else imprimirMensaje("No existe el usuario", AQUAMARINE_COLOR);

     return -2;
}

int vistaChoferConMasPasajeros() {
    int mes;
    int idUnidad = 0;
    bool mesEsValido = false;
    imprimirMensaje("CHOFER CON MAS VIAJES", AQUAMARINE_COLOR);
    printf("Ingrese el mes (1 - 12)\n");
    do{
        mes = escribirEnteroValido("*:", false);
        int opcionesValidas[] = {1,2,3,4,5,6,7,8,9,10,11,12, -99};
        mesEsValido = numberIsFoundIn(mes, opcionesValidas);
        if(!mesEsValido) imprimirMensaje("Ese mes no existe,", RED_COLOR);
    } while(!mesEsValido);

    idUnidad = buscarUnidadConMasViajes(mes);
    if(idUnidad != 0){
        char dniChofer[10];
        buscarDNIChoferPorUnidad(idUnidad, dniChofer);
        mostrarChofer(dniChofer);
    } else {
        imprimirMensaje("No se han encontrado viajes en este mes", YELLOW_COLOR);
    }

    return -2;
}

