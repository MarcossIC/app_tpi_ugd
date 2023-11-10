//
// Created by usuario on 28/10/2023.
//
#include "user.h"

/**
 * Arma el struct de Usuario con todos los datos
 *
 * @return Retorna el struct de account
 */
struct Usuario crearNuevoUsuarioValido(){
    struct Usuario account = {"", "", "", "", "", "", 0};
    fflush(stdin);
    escribirStringValido("nombre", account.nombre);
    escribirStringValido("apellido", account.apellido);
    escribirStringValido("DNI", account.DNI);
    escribirStringValido("telefono", account.telefono);
    escribirFechaValida("nacimiento", account.fechaNacimiento);
    escribirStringValido("direccion", account.direccion);
    bool esValidoElTipo = false;
    do {
        printf("Dime cual es su tipo de cuenta.\n");
        printf("1 - Normal(Sin beneficio.)\n");
        printf("2 - Boleto Estudiantil.\n");
        printf("3 - Beneficio Discapacidad.\n");
        printf("4 - Beneficio Anciano.\n");
        printf("5 - Beneficio por ex combatiente de malvinas.\n");

        account.tipo = escribirEnteroValido(":");
        esValidoElTipo = areIntegersEqual(account.tipo, 1) || areIntegersEqual(account.tipo, 2) || areIntegersEqual(account.tipo, 3) || areIntegersEqual(account.tipo, 4) || areIntegersEqual(account.tipo, 5);

        if(!esValidoElTipo) {
            setColorOutput(RED_COLOR);
            printf("El tipo que ingreso no es una opcion valida.\n");
            resetColor();
        }
    } while(!esValidoElTipo);

    return account;
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
 *
 * @author Marcos
 * @return El numero de cuentas que listo
 */
int listarTodosLosUsuariosRegistrados(){
    FILE* usuarioArch;
    struct Usuario usuario;
    int cuentaDeUsuariosRegistrados = 0;
    if((usuarioArch = fopen("assets/Usuarios.dat", "rb")) != NULL) {
        while (fread(&usuario, sizeof(struct Usuario), 1, usuarioArch) == 1){
            printf("*                                 Usuario                                    *\n");
            printf("%s %s, %s\n", usuario.nombre, usuario.apellido, usuario.DNI);
            printf("Nacio: %s\n",usuario.fechaNacimiento);
            printf("Direccion: %s\n", usuario.direccion);
            printf("Telefono: %s\n",usuario.telefono);
            printf("Tipo: %d\n",usuario.tipo);
            printf("*******************************************************************************\n");
            cuentaDeUsuariosRegistrados++;
        }
        fclose(usuarioArch);
    }
    return cuentaDeUsuariosRegistrados;
}
/**
 *
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