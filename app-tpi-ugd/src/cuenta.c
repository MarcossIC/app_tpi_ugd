//
// Created by usuario on 6/11/2023.
//

#include "cuenta.h"
#include "utilidades.h"

/**
 *
 * @author Thyago
 * @return
 */
int obtenerUltimoIdDeCuenta(){
    //Se busca la ultima id

    FILE *Users;
    struct Cuenta Cuentas;
    int lastId = 0; // Variable que va a tener la ultima id
    if((Users=fopen("assets/Cuenta.dat","rb"))!=NULL){
        fread (&Cuentas, sizeof(struct Cuenta),1,Users);
        while (!feof(Users)){
            fread (&Cuentas, sizeof(struct Cuenta),1,Users);
            if (lastId<=Cuentas.id){
                lastId=Cuentas.id;
            }
        }
        fclose(Users);
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
    int id;
    struct Cuenta cuentas;
    if ((Cuenta = fopen("assets/Cuenta.dat", "rb")) != NULL) {
        rewind(Cuenta);
        fread(&cuentas, sizeof(struct Cuenta), 1, Cuenta);
        while (!feof(Cuenta)) {
            if (strcmp(DNI, cuentas.DNI) == 0) {
                id = cuentas.id;
            } else fread(&cuentas, sizeof(struct Cuenta), 1, Cuenta);

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
 *
 * @author
 * @param idCuenta
 * @param saldoExtra
 * @return
 */
int actualizarSaldoCuenta(int idCuenta, int saldoExtra){
    struct Cuenta cuentas;
    FILE *Arch;
    int error=0;
    int tope=1000;
    bool bandera = false;
    if((Arch=fopen("assests/Cuenta.dat","r+b"))!=NULL){
        while(!bandera && fread(&cuentas, sizeof(struct Cuenta), 1, Arch) == 1){
            if(cuentas.id==idCuenta){
                cuentas.saldo+=saldoExtra;
                if(cuentas.saldo <= tope){
                    fseek(Arch, -sizeof(struct Cuenta), SEEK_CUR);
                    fwrite(&cuentas,sizeof(struct Cuenta),1,Arch);
                    bandera = true;
                } else error = 2;
            } else error = 2;
        }
        fclose(Arch);
    }else{
        printf ("erorr al abrir");
        error=1;
    }
    return error;
}