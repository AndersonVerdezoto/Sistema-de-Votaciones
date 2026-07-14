#include "ordenamiento.h"

void ordenarCandidatosSeleccion(Candidato* arr, int n) {
    int i, j, max_idx;
    for (i = 0; i < n - 1; i++) {
        max_idx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j].votos > arr[max_idx].votos) {
                max_idx = j;
            }
        }
        Candidato temp = arr[max_idx];
        arr[max_idx] = arr[i];
        arr[i] = temp;
    }
}