#include <stdio.h>

void ui();
void initFiles();

struct User{
    char name[50];
    char lastName[50];
    char dni[20];
    char address[20];
    char birthDay[20];
    char cellphone[20];
    char type[20];
};

int main(int argc, char const *argv[]){
    FILE *myFile;

    initFiles();

    ui();
    return 0;
}

void ui(){
    printf("***************************************************************\n");
    printf("*                Sistema de transporte electronico            *\n");
    printf("*                                                             *\n");
    printf("*                        Iniciar                              *\n");
    printf("*                        Registrar                            *\n");
    printf("*                                                             *\n");
    printf("\n*************************************************************\n");
}

void uiLogin(){
    
}

void uiRegister(){
    struct User user = {"", "", "", "", "", "", ""};

    printf("Ingresa su nombre: ");
    scanf("%s", user.name);
    printf("\nIngresa su apellido: ");
    scanf("%s", user.lastName);
    printf("\nIngresa su Fecha de nacimiento: ");
    scanf("%s", user.birthDay);
    printf("\nIngresa su DNI: ");
    scanf("%s", user.dni);
    printf("\nIngresa su direccion: ");
    scanf("%s", user.address);
    printf("\nIngresa su telefono: ");
    scanf("%s", user.cellphone);
    printf("\nIngresa su direccion: ");
    scanf("%s", user.address);
 
}


void registerUser(struct User user){
    FILE *file;
    file = fopen("assets/Users.bat", "w+b");


    fclose(file);
}

void initFiles(){
    char* directory = "assets";
    FILE *file;
    _mkdir(directory);

    file = fopen("assets/Users.bat", "w");
    fclose(file);

    file= fopen("assets/Accounts.bat", "w");
    fclose(file);

    file = fopen("assets/Transactions.bat", "w");
    fclose(file);

    file = fopen("assets/Driver.bat", "w");
    fclose(file);

    file = fopen("assets/Units.bat", "w");
    fclose(file);

    file = fopen("assets/Docs.bat", "w");
    fclose(file);

}