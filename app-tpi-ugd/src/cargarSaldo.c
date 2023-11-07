//
// Created by usuario on 6/11/2023.
//

#include "cargarSaldo.h"


/**
 *
 * @author Thyago
 * @param cargaSaldo
 * @return
 */
int guardarCargaDeSaldo(struct CargaSaldo cargaSaldo){
// DNI, Nro. Control, Monto, Boca de pago, Fecha y hora.
    FILE   * Arch;
    int error=0;
    if((Arch=fopen("assests/Recargas.dat","a+b"))!=NULL){
        fwrite(&cargaSaldo,sizeof(struct CargaSaldo),1,Arch);
        fclose (Arch);
    }else{
        printf("Error al abrir");
        error=1;
    }
    return error;
}