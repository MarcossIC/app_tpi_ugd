#include "cuenta.h"
#include "utilidades.h"

/**
 *<
 * @author Thyago
 * @return
 */
int obtenerUltimoIdDeCuenta(){
    //Se busca la ultima id
    FILE *CuentaArch;
    int lastId = 1; // Variable que va a tener la ultima id
    if((CuentaArch=fopen("assets/Cuenta.dat","ab"))!=NULL){
        fseek(CuentaArch, -sizeof(struct Cuenta), SEEK_END);
        struct Cuenta Cuentas;
        if(fread(&Cuentas, sizeof(struct Cuenta),1,CuentaArch)) lastId=Cuentas.id;
        fclose(CuentaArch);
    }
    return lastId;
}

/**
 *
 * @author Matias
 * @param DNI
 * @return
 */
int buscarIdCuenta(char* DNI) {
    FILE *Cuenta;
    int id = 0;
    struct Cuenta cuentas;
    bool encontroElId = false;
    if ((Cuenta = fopen("assets/Cuenta.dat", "rb")) != NULL) {
        while (!encontroElId && fread(&cuentas, sizeof(struct Cuenta), 1, Cuenta)) {
            if (areStringsEqual(DNI, cuentas.DNI)) {
                id = cuentas.id;
                encontroElId = true;
            }
        }
    }
    return id;
}

/**
 *
 * @author Matias
 * @param cuenta
 * @return
 */
int guardarCuenta(struct Cuenta cuenta){
    FILE *Cuenta;
    int error=0;
    if((Cuenta=fopen("assets/Cuenta.dat","a+b"))!=NULL){
        fwrite(&cuenta,sizeof(struct Cuenta),1,Cuenta);
        fclose(Cuenta);
    } else{
        printf("\n Error de apertura");
        error = 1;
    }
    return error;
}

/**
 * Actualiza el saldo de una cuentra registrada por un DNI como referencia
 *
 * @author Matias y Thiago
 * @param idCuenta
 * @param saldoExtra
 * @param excedente
 * @return
 */
int actualizarSaldoCuenta(int idCuenta, float saldoExtra, float *excedente){
    struct Cuenta cuentas;
    FILE *Arch;
    int error=0;
    bool bandera = false;

    if((Arch=fopen("assets/Cuenta.dat","r+b"))!=NULL){
        while(!bandera && fread(&cuentas, sizeof(struct Cuenta), 1, Arch) == 1){

            if(cuentas.id==idCuenta){
                cuentas.saldo+=saldoExtra;//
                if(cuentas.saldo > TOPE){
                    *excedente = cuentas.saldo - TOPE;
                    cuentas.saldo = TOPE;
                    setColorOutput(YELLOW_COLOR);
                    printf("El saldo excede el limite de $%d, le devolveremos $%.2f \n ", TOPE, *excedente);
                    resetColor();
                }
                fseek(Arch, -sizeof(struct Cuenta), SEEK_CUR);
                fwrite(&cuentas,sizeof(struct Cuenta),1,Arch);
                bandera = true;
            } else error = 2;
        }
        fclose(Arch);
    }else{
        printf ("erorr al abrir\n");
        error=1;
    }
    return error;
}



/**
 * Consulta el saldo de una cuenta registra por un DNI como referencia
 *
 * @author Thyago
 * @param DNI
 * @return float
 */
float recuperarSaldo(const char* DNI){
    struct Cuenta cuentas;
    FILE *Arch;
    bool encontroElDNI = false;
    float saldo = 0;
    if((Arch=fopen("assets/Cuenta.dat","rb"))!=NULL){
        while (!encontroElDNI && fread(&cuentas, sizeof(struct Cuenta), 1, Arch)) {
            if (areStringsEqual(DNI, cuentas.DNI)) {
                encontroElDNI = true;
            }
        }
        fclose(Arch);
    } else {
        printf ("Error al abrir el archivo Cuenta en consultar saldo.\n");
    }
    return saldo;
}

/**
 * Busca un struct de cuenta en el archivo por un DNI como referencia
 *
 * @author Marcos
 * @param DNI
 * @return
 */
struct Cuenta recuperarCuenta(const char* DNI){
    struct Cuenta cuenta;
    FILE* cuentaArch;
    bool encontreLaCuenta = false;
    if((cuentaArch=fopen("assets/Cuenta.dat", "rb")) != NULL){
        while (!encontreLaCuenta && fread(&cuenta, sizeof(struct Cuenta), 1, cuentaArch)) {
            if (areStringsEqual(DNI, cuenta.DNI)) encontreLaCuenta = true;
        }
        fclose(cuentaArch);
    } else printf ("Error al abrir el archivo.\n");

    if(!encontreLaCuenta) cuenta.id = 0;

    return cuenta;
}


void definirPrecio(float* precio, int tipoCuenta, int origen, int destino, int hora){
    if(origen == destino) *precio = 170;
    else *precio = 200;

    if(tipoCuenta == 2) {
        if(hora >= 5 && hora < 23)  *precio = 0;
    } else if(tipoCuenta == 3 || tipoCuenta == 4 || tipoCuenta == 5){
        *precio -= (*precio * 55 / 100);
    }
}