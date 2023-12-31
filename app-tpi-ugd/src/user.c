#include "user.h"

/**
 * Arma el struct de Usuario con todos los datos
 *
 * @author Marcos
 * @return Retorna el struct de account
 */
struct Usuario crearNuevoUsuarioValido(){
    struct Usuario cuenta;
    fflush(stdin);
    escribirStringValido("nombre", cuenta.nombre);
    escribirStringValido("apellido", cuenta.apellido);
    escribirStringValido("DNI", cuenta.DNI);
    escribirStringValido("telefono", cuenta.telefono);
    escribirFechaValida("nacimiento", cuenta.fechaNacimiento);
    bool esValido = false;
    cuenta.direccion = escribirDireccionValida("direccion");
    do {
        printf("Dime cual es su tipo de cuenta.\n");
        printf("1 - Normal(Sin beneficio).\n");
        printf("2 - Beneficio estudiantil.\n");
        printf("3 - Beneficio de discapacidad.\n");
        printf("4 - Beneficio de tercera edad.\n");
        printf("5 - Beneficio ex combatiente de malvinas.\n");
        cuenta.tipo = escribirEnteroValido(":", false);
        int opcionesValidas[] = {1, 2,3,4,5,-99};
        esValido = validarOpciones(cuenta.tipo, opcionesValidas);
        if(esValido) esValido = validarTipoCuenta(cuenta.tipo, cuenta.direccion, cuenta.fechaNacimiento);

    } while(!esValido);

    return cuenta;
}

/**
 * @author Marcos y Matias
 * @param tipo
 * @param origen
 * @param fechaNacimiento
 * @return
 */
bool validarTipoCuenta(const int tipo, const int origen, const char* fechaNacimiento){
    int result = 1;
    int edad = 0;
    struct Fecha fechaNacimientoS = desComponerFecha(fechaNacimiento);
    bool cumpleConEdad = true;

    if(tipo == 2){
        result = escribirEnteroValido("Cuentas con los siguientes documentos para presentar:\n- constancia BEG \n- DNI Original\n- Copia DNI Original\n[1] - Si \n[0] - No\n:", true);
        edad = 6;
    }
    if(tipo == 3){
        result = escribirEnteroValido("Cuentas con los siguientes documentos para presentar:\n- Certificado \n- DNI Original\n[1] - Si \n[0] - No\n:", true);
        edad = 7;
    }
    if(tipo == 4){
        int sexo = escribirEnteroValido("Dime tu genero biologico. \n[1] - Maculino \n[0] - Femenino\n:", true);

        if(origen == 1){
            result = escribirEnteroValido("Cuentas con los siguientes documentos para presentar:\n- DNI Original \n- Copia Original\n[1] - Si \n[0] - No\n:", true);
            edad = 70;
        } else {
            if(sexo == 1) edad = 65;
            else edad = 60;
            char mensaje[220];
            snprintf(mensaje, 220, "Cuentas con los siguientes documentos para presentar:\n- DNI Original \n- Copia Original\n-Carnet de la tercera edad Original\n- Edad %d\n[1] - Si \n[0] - No\n:", edad);
            result = escribirEnteroValido(mensaje, true);
        }
    }
    if(tipo == 5){
        result = escribirEnteroValido("Cuentas con las siguientes documentos para presentar:\n- DNI Original\n- Copia DNI Original\n- Certificado de ex combatiente de malvina\n-Copia de certificado\n [1]- Si\n [0]- No\n:", true);
        edad = 53;
    }
    setColorOutput(RED_COLOR);
    cumpleConEdad = isOlderThan(fechaNacimientoS.anho, edad);
    if(result != 1) printf("Lo siento, no cuenta con los requisitios para este beneficio.\n");
    resetColor();
    return result == 1 && cumpleConEdad;
}

/**
 * Guarda un account en el archivo "Usuarios.dat"
 *
 * @author Marcos
 * @param user struct account con los datos para guardar
 * @return Estado del resultado (1 hubo error / 0 no hubo error)
 */
int guardarUsuario(struct Usuario usuario) {
    FILE* usuarioArch;
    int errors = 0;
    if((usuarioArch = fopen("assets/Usuarios.dat", "a+b")) != NULL){
        fwrite(&usuario, sizeof(struct Usuario), 1, usuarioArch);
        fclose(usuarioArch);
    } else errors = 1;
    return errors;
}

/**
 * Lista todos las cuentas guardadas en el archivo Usuarios.dat
 *<
 * @author Marcos
 * @return El numero de cuentas que listo
 */
int listarTodosLosUsuariosRegistrados(){
    FILE* usuarioArch;
    struct Usuario usuario;
    int cuentaDeUsuariosRegistrados = 0;
    if((usuarioArch = fopen("assets/Usuarios.dat", "rb")) != NULL) {
        while (fread(&usuario, sizeof(struct Usuario), 1, usuarioArch) == 1){
            printf("*                     Usuario                      *\n");
            printf("%s %s, %s\n", usuario.nombre, usuario.apellido, usuario.DNI);
            printf("Fecha nacimiento: %s\n",usuario.fechaNacimiento);
            printf("Direccion: %s\n", recuperarDireccion( usuario.direccion ));
            printf("Telefono: %s\n", usuario.telefono);
            printf("Tipo: %s\n", recuperarTipoCuenta( usuario.tipo) );
            printf("****************************************************\n");
            cuentaDeUsuariosRegistrados++;
        }
        fclose(usuarioArch);
    }
    return cuentaDeUsuariosRegistrados;
}
/**
 *
 * @author Marcos
 * @param DNI
 * @return
 */
bool usuarioExistePorDNI(const char* DNI){
    FILE* usuarioArch;
    struct Usuario usuario;
    bool usuarioExiste = false;
    if((usuarioArch = fopen("assets/Usuarios.dat", "rb")) != NULL) {
        while (!usuarioExiste && fread(&usuario, sizeof(struct Usuario), 1, usuarioArch)){
            if(areStringsEqual(DNI, usuario.DNI)) usuarioExiste = true;
        }
    }
    return usuarioExiste;
}

/**
 *
 * @author Marcos
 * @param DNI
 * @return
 */
struct Usuario recuperarUsuario(char *DNI){
    struct Usuario usuario;
    FILE* usuarioArch;
    bool usuarioExiste = false;
    if((usuarioArch = fopen("assets/Usuarios.dat", "rb")) != NULL) {
        while (!usuarioExiste && fread(&usuario, sizeof(struct Usuario), 1, usuarioArch) == 1){
            if(areStringsEqual(DNI, usuario.DNI)) usuarioExiste = true;
        }
        fclose(usuarioArch);
    }
    return usuario;
}

/**
 *
 * @author Marcos
 * @return
 */
int contarUsuariosConBeneficio(){
    struct Usuario usuario;
    FILE* usuarioArch;
    int cuentaUsuarios = 0;
    if((usuarioArch = fopen("assets/Usuarios.dat", "rb")) != NULL) {
        while (fread(&usuario, sizeof(struct Usuario), 1, usuarioArch) == 1){
            if(usuario.tipo != 1) cuentaUsuarios++;
        }
        fclose(usuarioArch);
    }

    return cuentaUsuarios;
}

/**
 * @author Matias
 * @param nombre
 * @param apellido
 * @param DNI
 * @return
 */
int buscarDNIporNombre(const char* nombre, const char* apellido, char* DNI){//
    struct Usuario usuario;
    FILE* usuarioArch;
    int contador=0;
    if((usuarioArch = fopen("assets/Usuarios.dat", "rb")) != NULL) {
        while (fread(&usuario, sizeof(struct Usuario), 1, usuarioArch) == 1) {
            if(strcmp(nombre,usuario.nombre)==0 && strcmp(apellido,usuario.apellido)==0){
                contador=contador+1;
                strcpy(DNI,usuario.DNI);
            }
        }
        fclose(usuarioArch);
    } else printf("\n Error de apertura del archivo 'lista de movimientos' ");

    return contador;
}

