#include <stdio.h>
#include <string.h>
#include "election.h"
#include "gestion.h"
#include "busqueda.h"
#include "ordenamiento.h"
#include "reportes.h"

#if defined(_WIN32) || defined(_WIN64)
    #include <conio.h> 
    char leerCaracterOculto() {
        return _getch();
    }
#else
    #include <termios.h>
    #include <unistd.h>
    char leerCaracterOculto() {
        struct termios viejo, nuevo;
        char ch;
        tcgetattr(STDIN_FILENO, &viejo);
        nuevo = viejo;
        nuevo.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &nuevo);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &viejo);
        return ch;
    }
#endif

void panelAdministrador() {
    char usuario[20];
    char contrasenia[20];
    char ch;
    int i = 0;

    printf("\n+-------------------------------------------------------+\n");
    printf("|       INGRESO AL PANEL DE ADMINISTRADOR               |\n");
    printf("+-------------------------------------------------------+\n\n");
    printf("Usuario: ");
    scanf("%s", usuario);
    
    while ((ch = getchar()) != '\n' && ch != EOF);
    printf("Contrasena: ");
    
    while (1) {
        ch = leerCaracterOculto();
        if (ch == 13 || ch == 10) break;
        else if (ch == 8 || ch == 127) {
            if (i > 0) {
                i--;
                printf("\b \b"); 
            }
        }
        else if (i < 19) {
            contrasenia[i++] = ch;
            printf("*"); 
        }
    }
    contrasenia[i] = '\0'; 
    printf("\n\n"); 

    if (strcmp(usuario, "POLIADMIN") == 0 && strcmp(contrasenia, "admin123") == 0) {
        printf("SESION INICIADA EXITOSAMENTE\n");
        int opcion_admin;
        
        do {
            printf("\n+-------------------------------------------------------+\n");
            printf("|              MENU ADMINISTRADOR - AEIS                |\n");
            printf("+-------------------------------------------------------+\n");
            printf("|  1. Nuevas Votaciones de AEIS                         |\n");
            printf("|  2. Continuar Votaciones Previas                      |\n");
            printf("|  3. Ver Resultados y Exportar Acta                    |\n");
            printf("|  4. Anadir Candidato/Lista                            |\n");
            printf("|  5. Quitar Candidato/Lista                            |\n");
            printf("|  6. Cerrar Sesion                                     |\n");
            printf("+-------------------------------------------------------+\n");
            printf("Opcion: ");
            scanf("%d", &opcion_admin);

            switch(opcion_admin) {
                case 1: nuevaEleccion(); break;
                case 2: continuarEleccion(); break;
                case 3: mostrarResultados(); break;
                case 4: agregarCandidatoDinamico(); break;
                case 5: quitarCandidatoDinamico(); break;
                case 6: printf("\nCerrando sesion...\n"); break;
                default: printf("\n ERROR: Opcion invalida. Intente de nuevo.\n");
            }
        } while(opcion_admin != 6);
        
    } else {
        printf("\n ERROR: Usuario o Contrasena Incorrectos\n");
    }
}

int main() {
    int opcion = 0;
    while(opcion != 3) {
        printf("\n+=======================================================+\n");
        printf("|                                                       |\n");
        printf("|      ESCUELA POLITECNICA NACIONAL - FACULTAD FIS      |\n");
        printf("|     SISTEMA DE ELECCIONES PARA PRESIDENCIA DE LA AEIS |\n");
        printf("|                                                       |\n");
        printf("+=======================================================+\n");
        printf("|  1. Panel de Estudiantes                              |\n");
        printf("|  2. Panel de Administrador                            |\n");
        printf("|  3. Salir                                             |\n");
        printf("+=======================================================+\n");
        printf("\nOpcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1: studentPanel(); break;
            case 2: panelAdministrador(); break;
            case 3: printf("\n+=======================================================+\n");
                    printf("|    Programa de Votaciones de la AEIS Finalizado        |\n");
                    printf("|     Gracias por su participacion en el proceso         |\n");
                    printf("+=======================================================+\n\n"); break;
            default: printf("\n ERROR: Opcion invalida. Intente de nuevo.\n");
        }
    }
    return 0;
}