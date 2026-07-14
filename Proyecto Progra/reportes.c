#include "reportes.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "gestion.h"

void generarReporteActa(int total_votos, float porc_part, float porc_aus, Candidato* copia_ordenada) {
    FILE* f_acta = fopen("Acta_Electoral_AEIS.txt", "w");
    if (f_acta == NULL) {
        printf("[Error] No se pudo generar el acta de votacion en texto plano.\n");
        return;
    }

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    fprintf(f_acta, "=================================================================================\n");
    fprintf(f_acta, "                ESCUELA POLITECNICA NACIONAL - FACULTAD DE FIS                   \n");
    fprintf(f_acta, "             ACTA FORMAL DE ESCRUTINIO: PRESIDENCIA DE LA AEIS                   \n");
    fprintf(f_acta, "=================================================================================\n\n");
    fprintf(f_acta, "Fecha y Hora de Cierre: %02d-%02d-%d %02d:%02d:%02d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
    fprintf(f_acta, "Ano del Proceso Electoral: %d\n", anio_eleccion);
    fprintf(f_acta, "Padron de Estudiantes FIS Habilitados: %d\n", max_estudiantes);
    fprintf(f_acta, "Total de Votos Emitidos: %d\n", total_votos);
    fprintf(f_acta, "Porcentaje de Participacion Efectiva: %.1f%%\n", porc_part);
    fprintf(f_acta, "Porcentaje de Ausentismo: %.1f%%\n\n", porc_aus);

    fprintf(f_acta, "\n----------------------------- RANKING ELECTORAL FINAL -----------------------------\n");
    fprintf(f_acta, "+----+--------------------+------------------------------+--------------------+-------+\n");
    fprintf(f_acta, "| Pos| Lista              | Presidente                   | Vicepresidente     | Votos |\n");
    fprintf(f_acta, "+----+--------------------+------------------------------+--------------------+-------+\n");

    int pos = 1;
    for (int i = 0; i < num_candidatos; i++) {
        if (copia_ordenada[i].activo == 0) continue;
        fprintf(f_acta, "| %-2d | %-18s | %-28s | %-18s | %-5d |\n", 
                pos++, copia_ordenada[i].nombre_lista, copia_ordenada[i].presidente, copia_ordenada[i].vicepresidente, copia_ordenada[i].votos);
    }
    fprintf(f_acta, "+----+--------------------+------------------------------+--------------------+-------+\n\n");

    for(int i = 0; i < num_candidatos; i++) {
        if(strcmp(copia_ordenada[i].nombre_lista, "Voto Blanco") != 0 && strcmp(copia_ordenada[i].nombre_lista, "Voto Nulo") != 0) {
            fprintf(f_acta, "--------------------------------- DIGNIDADES ELECTAS ---------------------------\n");
            fprintf(f_acta, "LISTA GANADORA ELECTA DE LA AEIS: %s\n", copia_ordenada[i].nombre_lista);
            fprintf(f_acta, "PRESIDENTE: %s\n", copia_ordenada[i].presidente);
            fprintf(f_acta, "VICEPRESIDENTE: %s\n", copia_ordenada[i].vicepresidente);
            fprintf(f_acta, "--------------------------------------------------------------------------------\n\n");
            break;
        }
    }

    fprintf(f_acta, "Firmas de Validacion del Tribunal FIS:\n\n\n");
    fprintf(f_acta, "      __________________________              __________________________\n");
    fprintf(f_acta, "         Presidente del Tribunal                  Secretario de Actas\n");
    fclose(f_acta);

    printf("[Reportes] El acta electoral oficial ha sido exportada.\n");
}