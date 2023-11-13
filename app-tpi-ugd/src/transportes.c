#include "transportes.h"


/**
 * @author Marcos
 * @return
 */
struct Chofer crearNuevoChofer(){
    struct Chofer chofer = {"", "", "", "", "", "", 0};
    fflush(stdin);
    escribirStringValido("DNI", chofer.DNI);
    escribirStringValido("nombre", chofer.nombre);
    escribirStringValido("apellido", chofer.apellido);
    fflush(stdin);
    escribirFechaValida("nacimiento", chofer.fechaNacimiento);
    fflush(stdin);
    escribirStringValido("telefono", chofer.telefono);
    fflush(stdin);
    escribirStringValido("email", chofer.email);
    chofer.direccion = escribirDireccionValida("direccion");

    return chofer;
}

/**
 * @author Thyago
 * @return
 */
struct Unidad crearNuevaUnidad(){
    struct Unidad unidad;
    bool choferExiste = false;
    fflush (stdin);
    do{
        printf("Primero necesito datos del chofer.\n");
        escribirStringValido("DNI",unidad.dniChofer);
        choferExiste = choferExistePorDNI(unidad.dniChofer);
        if (!choferExiste) imprimirMensaje("El DNI del chofer no existe", YELLOW_COLOR);
    } while(!choferExiste);
    unidad.idUnidad=buscarUltimoIdUnidad()+1;
    escribirStringValido("Marca",unidad.marca);
    escribirStringValido("Modelo",unidad.modelo);
    unidad.cantidadDeAsientos = escribirEnteroValido("Ingresar la cantidad de asientos que dispone la Unidad: ", false);
    unidad.kilometraje = escribirEnteroValido("Ingresar el kilometraje la Unidad: ", false);
    escribirFechaValida("alta: ", unidad.fechaAlta);
    unidad.turno = escribirEnteroValido("Ingresar el turno de la Unidad \n[1] Tarde \n[0] Ma\xf1\x61na\n: ", true);
    unidad.aptoDiscapacitados= escribirEnteroValido ("Es apto para discapacitados \n[1] SI \n[0] NO\n:", true);
    return unidad;
}

/**
 * @author Thyago
 * @param DNI
 * @return
 */
bool choferExistePorDNI(const char* DNI){
    struct Chofer chofferAtmp;
    bool choferExiste = false;
    FILE* choferArch;
    if( (choferArch = fopen("assets/Chofer.dat", "rb")) != NULL){
        while(!choferExiste && fread(&chofferAtmp, sizeof(struct Chofer), 1, choferArch)){
            if(areStringsEqual(DNI, chofferAtmp.DNI)) choferExiste = true;
        }
        fclose(choferArch);
    }
    return choferExiste;
}

/**
 * @author Thyago
 * @return
 */
int buscarUltimoIdUnidad(){
    //Se busca la ultima id
    struct Unidad unidad;
    FILE *Arch;
    int lastId = 0; // Variable que va a tener la ultima id
    if((Arch=fopen("assets/Unidades.dat","a+b"))!=NULL){
        fseek(Arch, -sizeof(struct Unidad), SEEK_END);
        if(fread(&unidad, sizeof(struct Unidad),1,Arch)) lastId= unidad.idUnidad;

        fclose(Arch);
    } else imprimirMensaje("Error al abrir el archivo", RED_COLOR);
    return lastId;
}

/**
 * @author Marcos
 * @param chofer
 * @return
 */
int guardarChoferes(struct Chofer chofer){
    int error = 0;
    FILE* choferArch;
    if( (choferArch = fopen("assets/Chofer.dat", "a+b")) != NULL ){
        fwrite(&chofer, sizeof(struct Chofer), 1, choferArch);
        fclose(choferArch);
    } else error = 1;
    return error;
}

/**
 * @author Thyago
 * @param unidad
 * @return
 */
int guardarUnidad(struct Unidad unidad){
    int error = 0;
    FILE* Arch;

    if((Arch = fopen("assets/Unidades.dat", "a+b")) != NULL){
        fwrite(&unidad, sizeof(struct Unidad), 1, Arch);
        fclose(Arch);
    } else error = 1;
    return error;
}

/**
 * @author Thyago
 * @param idUnidad
 * @return
 */
bool unidadExistePorId(const int idUnidad) {
    struct Unidad unidad;
    bool unidadExiste = false;
    FILE* unidadArch;
    if ((unidadArch = fopen("assets/Unidades.dat", "rb")) != NULL) {
        fseek(unidadArch, 0, SEEK_SET);
        while (!unidadExiste && fread(&unidad, sizeof(struct Unidad), 1, unidadArch) == 1) {
            if (idUnidad == unidad.idUnidad) unidadExiste = true;
        }
        fclose (unidadArch);
    }
    return unidadExiste;
}

/**
 * @author Thuago
 * @return
 */
int listarChoferes(){
    FILE* Arch;
    struct Chofer chofer;
    int cuentaDeUsuariosRegistrados = 0;
    if((Arch = fopen("assets/Chofer.dat", "rb")) != NULL) {
        while (fread(&chofer, sizeof(struct Chofer), 1, Arch)) {
            printf("*                               CHOFER                                        *\n");
            printf("%s %s, %s\n", chofer.nombre, chofer.apellido, chofer.DNI);
            printf("Fecha nacimiento: %s \n", chofer.fechaNacimiento);
            printf("Telefono: %s \n", chofer.telefono);
            printf("Email: %s \n", chofer.email);
            printf("Direccion: %s \n", recuperarDireccion( chofer.direccion ));
            printf("*******************************************************************************\n\n");
            cuentaDeUsuariosRegistrados++;
        }
        fclose(Arch);
    }

    return cuentaDeUsuariosRegistrados;
}

/**
 * @author Marcos
 * @return
 */
int listarUnidades(){
    FILE* unidadesArch;
    struct Unidad unidad;
    int cuentaUnidades = 0;
    if((unidadesArch = fopen("assets/Unidades.dat", "rb")) != NULL) {
        while (fread(&unidad, sizeof(struct Unidad), 1, unidadesArch) == 1) {
            printf("*                                 Unidad                                    *\n");
            printf("DNI Chofer: %s\n", unidad.dniChofer);
            printf("Nro Unidad: %d\n", unidad.idUnidad);
            printf("Fecha Alta: %s\n", unidad.fechaAlta);
            if(unidad.turno == 1) printf("Turno: Tarde\n");
            else printf("Turno: Ma%sna\n", "\xf1");

            printf("Marca: %s\n", unidad.marca);
            printf("Modelo: %s\n", unidad.modelo);
            printf("Cantidad de asientos: %d\n", unidad.cantidadDeAsientos);
            printf("Kilometraje: %d\n", unidad.kilometraje);

            if(unidad.aptoDiscapacitados == 1) printf("Si es apto para discapacitados.\n");
            else printf("No es apto para discapacitados.\n");

            printf("*******************************************************************************\n");
            cuentaUnidades++;
        }
        fclose(unidadesArch);
    }

    return cuentaUnidades;
}




