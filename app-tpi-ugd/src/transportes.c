#include "transportes.h"

struct Chofer crearNuevoChofer(){
    struct Chofer chofer;
    fflush(stdin);
    escribirStringValido("DNI", chofer.DNI);
    escribirStringValido("nombre", chofer.nombre);
    escribirStringValido("apellido", chofer.apellido);
    escribirFechaValida("nacimiento", chofer.fechaNacimiento);
    escribirStringValido("telefono", chofer.telefono);
    escribirStringValido("email", chofer.email);
    escribirStringValido("direccion", chofer.direccion);
    return chofer;
}


struct Unidad crearNuevaUnidad(){
    struct Unidad unidad;
    bool choferExiste = false;
    fflush (stdin);
    do{
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

    unidad.turno = escribirEnteroValido("Ingresar el turno de la Unidad [1] Tarde [0] Mañana ", true);
    unidad.aptoDiscapacitados= escribirEnteroValido ("Es apto para discapacitados [1] SI [0] NO", true);
    return unidad;
}

bool choferExistePorDNI(const char* DNI){
    struct Chofer chofer;
    bool choferExiste = false;
    FILE* choferArch;
    if( (choferArch = fopen("assets/Chofer.dat", "rb")) != NULL){
        while(!choferExiste && fread(&chofer, sizeof(struct Chofer), 1, choferArch)){
            if(areStringsEqual(DNI, chofer.DNI)) choferExiste = true;
        }
    }
    return choferExiste;
}

/**
 *
 * @author Thyago
 * @return
 */
int buscarUltimoIdUnidad(){
    //Se busca la ultima id
    struct Unidad unidad;
    FILE *Arch;
    int lastId = 1; // Variable que va a tener la ultima id
    if((Arch=fopen("assets/Unidades.dat","ab"))!=NULL){
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
    } error = 1;
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
    FILE *Arch;
    if ((Arch = fopen("assets/Chofer.dat", "rb")) != NULL) {
        while (!unidadExiste && fread(&unidad,sizeof(struct Unidad), 1, Arch)) {
            if (areIntegersEqual(idUnidad, unidad.idUnidad)) unidadExiste = true;
        }
    }
}

/**
 * @author Thuago
 * @return
 */
int listarChoferes(){
    FILE* Arch;
    struct Chofer chofer;
    int cuentaDeUsuariosRegistrados = 0;
    if((Arch = fopen("assets/Usuarios.dat", "rb")) != NULL) {
        while (fread(&chofer, sizeof(struct Chofer), 1, Arch) == 1) {
            printf("*                               CHOFER                                        *\n");
            printf("%s %s, %s\n", chofer.nombre, chofer.apellido, chofer.DNI);
            printf("Nacio: %s\n", chofer.fechaNacimiento);
            printf("Telefono: %s\n", chofer.telefono);
            printf("Email: %d\n", chofer.email);
            printf("Direccion: %d\n", chofer.direccion);
            printf("*******************************************************************************\n");
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
            if(unidad.turno == 1) printf("Turno: Tarde\n", unidad.idUnidad);
            else printf("Turno: Mañana\n", unidad.idUnidad);

            printf("Marca: %s\n", unidad.marca);
            printf("Modelo: %s\n", unidad.modelo);
            printf("Cantidad de asientos: %d\n", unidad.cantidadDeAsientos);
            printf("Kilometraje: %d\n", unidad.kilometraje);

            if(unidad.aptoDiscapacitados == 1) printf("Si es apto para discapacitados");
            else printf("No es apto para discapacitados");

            printf("*******************************************************************************\n");
            cuentaUnidades++;
        }
        fclose(unidadesArch);
    }

    return cuentaUnidades;
}




