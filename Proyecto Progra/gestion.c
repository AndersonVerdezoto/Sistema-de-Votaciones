#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "election.h"
#include "gestion.h"
#include "busqueda.h"
#include "ordenamiento.h"
#include "reportes.h"

// Variables globales
int eleccion_activa = 0;
int anio_eleccion = 2026;
char codigo_facultad[10] = "FIS"; 
int max_estudiantes = 20; 
int num_candidatos = 0;
Candidato lista_candidatos[MAX_CANDIDATOS];
char** registro_votos_global = NULL;
int total_votos_emitidos = 0;

// Funciones auxiliares
int esNumeroValido(const char* str) {
    while (*str) {
        if (!isdigit(*str)) return 0;
        str++;
    }
    return 1;
}

// Recursividad
int contarVotosRecursivo(Candidato* arr, int n) {
    if (n <= 0) return 0;
    if (arr[n - 1].activo == 0) return 0 + contarVotosRecursivo(arr, n - 1);
    return arr[n - 1].votos + contarVotosRecursivo(arr, n - 1);
}

// Imprimir matriz
void imprimirMatrizOpciones(Candidato* arr, int n, int mostrar_votos) {
    printf("+----+--------------------+------------------------------+------------------------------+\n");
    if (mostrar_votos) {
        printf("| ID | LISTA              | PRESIDENTE                   | VICEPRESIDENTE               | VOTOS |\n");
        printf("+----+--------------------+------------------------------+------------------------------+-------+\n");
    } else {
        printf("| ID | LISTA              | PRESIDENTE                   | VICEPRESIDENTE               |\n");
        printf("+----+--------------------+------------------------------+------------------------------+\n");
    }

    for (int i = 0; i < n; i++) {
        if (arr[i].activo == 0) continue; 
        if (mostrar_votos) {
            printf("| %-2d | %-18s | %-28s | %-28s | %-5d |\n", 
                   arr[i].id, arr[i].nombre_lista, arr[i].presidente, arr[i].vicepresidente, arr[i].votos);
        } else {
            printf("| %-2d | %-18s | %-28s | %-28s |\n", 
                   arr[i].id, arr[i].nombre_lista, arr[i].presidente, arr[i].vicepresidente);
        }
    }
    
    if (mostrar_votos) {
        printf("+----+--------------------+------------------------------+------------------------------+-------+\n");
    } else {
        printf("+----+--------------------+------------------------------+------------------------------+\n");
    }
}

// Guardar configuración
void guardarConfiguracionEleccion() {
    FILE* file = fopen("ElectionInfo.txt", "w");
    if (file == NULL) {
        printf("Error abriendo el archivo de configuracion.\n");
        return;
    }
    fprintf(file, "%d\n%s\n%d\n%d\n", anio_eleccion, codigo_facultad, max_estudiantes, num_candidatos);
    
    for(int i=0; i<num_candidatos; i++) {
        fprintf(file, "%s-%d\n", lista_candidatos[i].nombre_lista, lista_candidatos[i].activo);
    }
    fclose(file);

    for (int i = 0; i < num_candidatos; i++) {
        char filename[30];
        sprintf(filename, "candidate%d.txt", i + 1);
        FILE* f_cand = fopen(filename, "w");
        if (f_cand != NULL) {
            fprintf(f_cand, "%d\n%s\n%s\n%s\n%d\n", lista_candidatos[i].votos, lista_candidatos[i].nombre_lista, lista_candidatos[i].presidente, lista_candidatos[i].vicepresidente, lista_candidatos[i].activo);
            fclose(f_cand);
        }
    }
}

// Nueva elección
void nuevaEleccion() {
    system("cls");
    int candidatos_reales;
    printf("\n+=======================================================+\n");
    printf("|        CONFIGURACION DE NUEVO PROCESO ELECTORAL       |\n");
    printf("|      Facultad de Ingenieria en Sistemas - EPN         |\n");
    printf("|   ELECCIONES PARA LA PRESIDENCIA DE LA AEIS 2026      |\n");
    printf("+=======================================================+\n\n");
    printf("Ingrese el Ano de las Votaciones: ");
    scanf("%d", &anio_eleccion);
    
    if (anio_eleccion > 2026) {
        printf("\n ERROR: No se puede configure un proceso posterior al ano actual.\n");
        eleccion_activa = 0;
        return;
    }

    strcpy(codigo_facultad, "FIS"); 
    max_estudiantes = 20; 
    
    printf("\nIngrese el Numero de listas iniciales: ");
    scanf("%d", &candidatos_reales);

    if (candidatos_reales > 10) candidatos_reales = 10;

    for (int i = 0; i < candidatos_reales; i++) {
        if (i == 0) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF); // limpiar buffer
        }
        lista_candidatos[i].id = i + 1;
        printf("\n+-------------------------------------------------+\n");
        printf("|       REGISTRO DE LISTA #%d                      |\n", i + 1);
        printf("+-------------------------------------------------+\n");
        printf("Nombre de la Lista: ");
        fgets(lista_candidatos[i].nombre_lista, sizeof(lista_candidatos[i].nombre_lista), stdin);
        lista_candidatos[i].nombre_lista[strcspn(lista_candidatos[i].nombre_lista, "\n")] = '\0';
        printf("Nombre del Presidente: ");
        fgets(lista_candidatos[i].presidente, sizeof(lista_candidatos[i].presidente), stdin);
        lista_candidatos[i].presidente[strcspn(lista_candidatos[i].presidente, "\n")] = '\0';
        printf("Nombre del Vicepresidente: ");
        fgets(lista_candidatos[i].vicepresidente, sizeof(lista_candidatos[i].vicepresidente), stdin);
        lista_candidatos[i].vicepresidente[strcspn(lista_candidatos[i].vicepresidente, "\n")] = '\0';
        lista_candidatos[i].votos = 0;
        lista_candidatos[i].activo = 1;
    }

    num_candidatos = candidatos_reales;
    
    // Voto Blanco
    lista_candidatos[num_candidatos].id = num_candidatos + 1;
    strcpy(lista_candidatos[num_candidatos].nombre_lista, "Voto Blanco");
    strcpy(lista_candidatos[num_candidatos].presidente, "N/A");
    strcpy(lista_candidatos[num_candidatos].vicepresidente, "N/A");
    lista_candidatos[num_candidatos].votos = 0;
    lista_candidatos[num_candidatos].activo = 1;
    num_candidatos++;

    // Voto Nulo
    lista_candidatos[num_candidatos].id = num_candidatos + 1;
    strcpy(lista_candidatos[num_candidatos].nombre_lista, "Voto Nulo");
    strcpy(lista_candidatos[num_candidatos].presidente, "N/A");
    strcpy(lista_candidatos[num_candidatos].vicepresidente, "N/A");
    lista_candidatos[num_candidatos].votos = 0;
    lista_candidatos[num_candidatos].activo = 1;
    num_candidatos++;

    FILE* f_padron = fopen("padron.txt", "w");
    if (f_padron != NULL) {
        // Se mantiene el orden numerico de menor a mayor para la busqueda binaria
        fprintf(f_padron, "202020672,JUAN PEREZ\n");
        fprintf(f_padron, "202311070,MARIA GOMEZ\n");
        fprintf(f_padron, "202311527,CARLOS LOPEZ\n");
        fprintf(f_padron, "202320638,ANA MARTINEZ\n");
        fprintf(f_padron, "202320751,ERICK CUJI\n");
        fprintf(f_padron, "202321756,LUIS RODRIGUEZ\n");
        fprintf(f_padron, "202410572,DIANA ALVAREZ\n");
        fprintf(f_padron, "202411468,PABLO CASTRO\n");
        fprintf(f_padron, "202420886,ELENA MEJIA\n");
        fprintf(f_padron, "202421275,JORGE ANDRADE\n");
        fprintf(f_padron, "202421654,CRISTINA DIAZ\n");
        fprintf(f_padron, "202510266,RICARDO SERRANO\n");
        fprintf(f_padron, "202510627,PATRICIA FUENTES\n");
        fprintf(f_padron, "202510751,SANTIAGO ORTIZ\n");
        fprintf(f_padron, "202510882,GABRIELA PINTO\n");
        fprintf(f_padron, "202511020,JAIRO ENRIQUEZ\n");
        fprintf(f_padron, "202511180,ANDERSON VERDEZOTO\n");
        fprintf(f_padron, "202511523,STEVEN TORRES\n");
        fprintf(f_padron, "202520625,VANESSA REYES\n");
        fprintf(f_padron, "202521207,JOSE VILLA\n");
        fclose(f_padron);
    }

    eleccion_activa = 1;
    total_votos_emitidos = 0; 
    guardarConfiguracionEleccion();
}

// Agregar candidato
void agregarCandidatoDinamico() {
    system("cls");
    if (num_candidatos >= MAX_CANDIDATOS) {
        printf("\n ERROR: Limite maximo de listas alcanzado.\n");
        return;
    }
    lista_candidatos[num_candidatos] = lista_candidatos[num_candidatos - 1];
    lista_candidatos[num_candidatos - 1] = lista_candidatos[num_candidatos - 2];
    
    int idx = num_candidatos - 2;
    lista_candidatos[idx].id = idx + 1;
    printf("\n+-------------------------------------------------+\n");
    printf("|              AGREGAR NUEVA LISTA               |\n");
    printf("+-------------------------------------------------+\n");
    printf("Nombre de la Lista: ");
    
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    fgets(lista_candidatos[idx].nombre_lista, sizeof(lista_candidatos[idx].nombre_lista), stdin);
    lista_candidatos[idx].nombre_lista[strcspn(lista_candidatos[idx].nombre_lista, "\n")] = '\0';
    printf("Nombre del Presidente: ");
    fgets(lista_candidatos[idx].presidente, sizeof(lista_candidatos[idx].presidente), stdin);
    lista_candidatos[idx].presidente[strcspn(lista_candidatos[idx].presidente, "\n")] = '\0';
    printf("Nombre del Vicepresidente: ");
    fgets(lista_candidatos[idx].vicepresidente, sizeof(lista_candidatos[idx].vicepresidente), stdin);
    lista_candidatos[idx].vicepresidente[strcspn(lista_candidatos[idx].vicepresidente, "\n")] = '\0';
    lista_candidatos[idx].votos = 0;
    lista_candidatos[idx].activo = 1;

    lista_candidatos[num_candidatos - 1].id = num_candidatos;
    lista_candidatos[num_candidatos].id = num_candidatos + 1;
    
    num_candidatos++;
    guardarConfiguracionEleccion();
    printf("\n  Nueva lista integrada exitosamente al proceso.\n");
}

// Quitar candidato
void quitarCandidatoDinamico() {
    system("cls");
    int id_quitar;
    printf("\n+---------------------------------------------------+\n");
    printf("|      RETIRAR LISTA DEL PROCESO ELECTORAL      |\n");
    printf("+---------------------------------------------------+\n");
    printf("\nIngrese el ID de la lista que desea retirar: ");
    scanf("%d", &id_quitar);

    if (id_quitar >= 1 && id_quitar <= num_candidatos - 2) {
        lista_candidatos[id_quitar - 1].activo = 0; 
        guardarConfiguracionEleccion();
        printf("\n  La lista ID %d ha sido retirada exitosamente.\n", id_quitar);
    } else {
        printf("\n ERROR: ID invalido o no se puede remover las opciones obligatorias.\n");
    }
}

// Continuar elección
void continuarEleccion() {
    system("cls");
    FILE* file = fopen("ElectionInfo.txt", "r");
    if (file == NULL) {
        printf("\n ERROR: No existen votaciones previas registradas en disco.\n");
        return;
    }
    fscanf(file, "%d", &anio_eleccion);
    fscanf(file, "%s", codigo_facultad);
    fscanf(file, "%d", &max_estudiantes);
    fscanf(file, "%d", &num_candidatos);
    fclose(file);

    for (int i = 0; i < num_candidatos; i++) {
        char filename[30];
        sprintf(filename, "candidate%d.txt", i + 1);
        FILE* f_cand = fopen(filename, "r");
        if (f_cand != NULL) {
            lista_candidatos[i].id = i + 1;
            fscanf(f_cand, "%d", &lista_candidatos[i].votos);
            fscanf(f_cand, "%s", lista_candidatos[i].nombre_lista);
            fscanf(f_cand, "%s", lista_candidatos[i].presidente);
            fscanf(f_cand, "%s", lista_candidatos[i].vicepresidente);
            fscanf(f_cand, "%d", &lista_candidatos[i].activo);
            fclose(f_cand);
        }
    }
    eleccion_activa = 1;
    printf("\n  Proceso de votaciones restaurado exitosamente.\n");
}

// Mostrar resultados
void mostrarResultados() {
    system("cls");
    FILE* f_verificar = fopen("ElectionInfo.txt", "r");
    if (f_verificar != NULL) {
        int dump_int; char dump_str[20];
        fscanf(f_verificar, "%d\n%s\n%d\n%d\n", &dump_int, dump_str, &dump_int, &dump_int);
        
        for(int i = 0; i < num_candidatos; i++) {
            char nombre_esperado[20]; int activo_esperado;
            if(fscanf(f_verificar, "%[^-]-%d\n", nombre_esperado, &activo_esperado) != EOF) {
                if(strcmp(nombre_esperado, lista_candidatos[i].nombre_lista) != 0) {
                    printf("\n+=======================================================+\n");
                    printf("|  ALERTA DE SEGURIDAD - FRAUDE DETECTADO            |\n");
                    printf("+=======================================================+\n");
                    printf("|  Los resultados NO SON VALIDOS                        |\n");
                    printf("|  Se detecto una modificacion fisica externa en los    |\n");
                    printf("|  archivos del sistema electoral.                      |\n");
                    printf("+=======================================================+\n");
                    fclose(f_verificar);
                    return;
                }
            }
        }
        fclose(f_verificar);
    }

    int total_votos = contarVotosRecursivo(lista_candidatos, num_candidatos);
    Candidato copia_ordenada[MAX_CANDIDATOS];
    memcpy(copia_ordenada, lista_candidatos, sizeof(lista_candidatos));
    ordenarCandidatosSeleccion(copia_ordenada, num_candidatos);

    printf("\n+=======================================================+\n");
    printf("|      CUADRO DE RESULTADOS FINALES DE VOTACION         |\n");
    printf("|           PRESIDENCIA DE LA AEIS - 2026               |\n");
    printf("+=======================================================+\n\n");
    
    imprimirMatrizOpciones(copia_ordenada, num_candidatos, 1);
    
    if (num_candidatos > 0) {
        for(int i = 0; i < num_candidatos; i++) {
            if(copia_ordenada[i].activo == 0) continue;
            if(strcmp(copia_ordenada[i].nombre_lista, "Voto Blanco") != 0 && strcmp(copia_ordenada[i].nombre_lista, "Voto Nulo") != 0) {
                printf("\n+=======================================================+\n");
                printf("|                  DIGNIDADES ELECTAS                   |\n");
                printf("+=======================================================+\n");
                printf("|  LISTA GANADORA:      %-31s |\n", copia_ordenada[i].nombre_lista);
                printf("|  PRESIDENTE ELECTO:   %-31s |\n", copia_ordenada[i].presidente);
                printf("|  VICEPRESIDENTE ELEC: %-31s |\n", copia_ordenada[i].vicepresidente);
                printf("+=======================================================+\n");
                break;
            }
        }
    }

    float porcentaje_votaron = ((float)total_votos / max_estudiantes) * 100;
    float porcentaje_no_votaron = 100.0 - porcentaje_votaron;

    printf("\n+=======================================================+\n");
    printf("|         ESTADISTICAS GENERALES DEL PROCESO            |\n");
    printf("+=======================================================+\n");
    printf("|  Total estudiantes del padron FIS:      %-13d |\n", max_estudiantes);
    printf("|  Votos emitidos totales:                %-13d |\n", total_votos);
    printf("|  Porcentaje de Participacion:           %-11.1f%%  |\n", porcentaje_votaron);
    printf("|  Porcentaje de Ausentismo:              %-11.1f%%  |\n", porcentaje_no_votaron);
    printf("+=======================================================+\n");

    generarReporteActa(total_votos, porcentaje_votaron, porcentaje_no_votaron, copia_ordenada);
}

// Panel de estudiantes
void studentPanel() {
    system("cls");
    
    if (!eleccion_activa || total_votos_emitidos >= max_estudiantes) {
        printf("\n+===================================================+\n");
        printf("|  ERROR: PROCESO CERRADO                          |\n");
        printf("|  Se ha alcanzado el cupo maximo de votantes.      |\n");
        printf("+===================================================+\n");
        printf("\nPresione Enter para continuar...");
        getchar();
        getchar();
        eleccion_activa = 0;
        return;
    }

    char id_usuario[15];
    printf("\n+=======================================================+\n");
    printf("|         PANEL DE VOTACION - PRESIDENCIA AEIS          |\n");
    printf("+=======================================================+\n\n");
    printf("Ingrese su CODIGO UNICO de estudiante: ");
    scanf("%s", id_usuario);

    if (!esNumeroValido(id_usuario)) {
        printf("\n+=======================================================+\n");
        printf("|  ERROR: ID Invalido. Solo numeros permitidos.         |\n");
        printf("+=======================================================+\n");
        printf("\nPresione Enter para continuar...");
        getchar();
        getchar();
        return;
    }

    if (strlen(id_usuario) < 8 || strlen(id_usuario) > 10) {
        printf("\n+=======================================================+\n");
        printf("|  ERROR: ID Invalido. Longitud incorrecta (8-10 digitos).|\n");
        printf("+=======================================================+\n");
        printf("\nPresione Enter para continuar...");
        getchar();
        getchar();
        return;
    }

    char anio_str[5];
    strncpy(anio_str, id_usuario, 4);
    anio_str[4] = '\0';
    int anio_ingreso = atoi(anio_str);

    if (anio_ingreso > 2026) {
        printf("\n+=======================================================+\n");
        printf("|  ERROR: ID Invalido. Anio de ingreso incorrecto.        |\n");
        printf("+=======================================================+\n");
        printf("\nPresione Enter para continuar...");
        getchar();
        getchar();
        return;
    }

    FILE* file_padron = fopen("padron.txt", "r");
    if (file_padron == NULL) {
        printf("\n ERROR: Padron electoral no encontrado.\n");
        return;
    }

    char padron_codigos[20][15];
    char padron_nombres[20][40];
    int total_padron = 0;
    char linea[100];

    // Procesamos linea por linea separando el codigo del nombre usando la coma ','
    while (total_padron < 20 && fgets(linea, sizeof(linea), file_padron) != NULL) {
        linea[strcspn(linea, "\r\n")] = '\0';
        char* token_codigo = strtok(linea, ",");
        char* token_nombre = strtok(NULL, ",");
        
        if (token_codigo != NULL && token_nombre != NULL) {
            strcpy(padron_codigos[total_padron], token_codigo);
            strcpy(padron_nombres[total_padron], token_nombre);
            total_padron++;
        }
    }
    fclose(file_padron);

    // Buscamos solo el codigo numerico en el arreglo de codigos
    int indice_encontrado = busquedaBinariaVotante(padron_codigos, total_padron, id_usuario);
    if (indice_encontrado == -1) {
        printf("\n+=======================================================+\n");
        printf("|  ERROR: ACCESO DENEGADO                                 |\n");
        printf("|  No consta en el padron electoral.                      |\n");
        printf("+=======================================================+\n");
        printf("\nPresione Enter para continuar...");
        getchar();
        getchar();
        return;
    }

    for (int i = 0; i < total_votos_emitidos; i++) {
        if (strcmp(registro_votos_global[i], id_usuario) == 0) {
            printf("\n+=======================================================+\n");
            printf("|  ERROR: El codigo ingresado YA REGISTRA UN VOTO.      |\n");
            printf("|  No se permite el doble voto.                         |\n");
            printf("+=======================================================+\n");
            printf("\nPresione Enter para continuar...");
            getchar();
            getchar();
            return;
        }
    }

    // Si todo esta correcto, damos una bienvenida personalizada
    printf("\n  Identificacion validada correctamente.\n");
    printf("  Bienvenido/a: %s\n", padron_nombres[indice_encontrado]);
    
    printf("\n+-----------------------------------------------------+\n");
    printf("|      OPCIONES DE VOTO DISPONIBLES (FIS)             |\n");
    printf("+-----------------------------------------------------+\n\n");
    imprimirMatrizOpciones(lista_candidatos, num_candidatos, 0);

    int seleccion;
    printf("\nSeleccione su opcion (ID) para votar: ");
    scanf("%d", &seleccion);

    if (seleccion >= 1 && seleccion <= num_candidatos && lista_candidatos[seleccion - 1].activo == 1) {
        char** temporal = realloc(registro_votos_global, (total_votos_emitidos + 1) * sizeof(char*));
        if (temporal == NULL) {
            printf("\n ERROR: Falla en la asignacion de memoria.\n");
            return;
        }
        registro_votos_global = temporal;
        registro_votos_global[total_votos_emitidos] = malloc(15 * sizeof(char));
        strcpy(registro_votos_global[total_votos_emitidos], id_usuario);
        total_votos_emitidos++;

        lista_candidatos[seleccion - 1].votos++;
        guardarConfiguracionEleccion();
        printf("\n+=======================================================+\n");
        printf("|           VOTO PROCESADO EXITOSAMENTE                 |\n");
        printf("|    Gracias por su participacion en el proceso         |\n");
        printf("+=======================================================+\n\n");

        if (total_votos_emitidos >= max_estudiantes) {
            printf("\n+=======================================================+\n");
            printf("|   PROCESO DE VOTACION COMPLETADO                    |\n");
            printf("|    Se ha alcanzado el cupo maximo de votantes.        |\n");
            printf("|    Procediendo a mostrar resultados...                |\n");
            printf("+=======================================================+\n\n");
            eleccion_activa = 0; 
            mostrarResultados(); 
        }
    } else {
        printf("\n ERROR: Opcion invalida o candidato no disponible.\n");
    }
}