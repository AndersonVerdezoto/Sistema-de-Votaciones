#include "busqueda.h"
#include <string.h>

int busquedaBinariaVotante(char lista_votos[][15], int total_votos, char* id_objetivo) {
    int izquierda = 0, derecha = total_votos - 1;
    while (izquierda <= derecha) {
        int medio = izquierda + (derecha - izquierda) / 2;
        int cmp = strcmp(lista_votos[medio], id_objetivo);
        if (cmp == 0) return medio; 
        if (cmp < 0) izquierda = medio + 1;
        else derecha = medio - 1;
    }
    return -1; 
}