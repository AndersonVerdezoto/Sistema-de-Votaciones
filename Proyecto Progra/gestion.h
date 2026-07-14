// ============================================
// GESTION.H / Declaraciones (extern) para otros archivos
// ============================================

#ifndef GESTION_H
#define GESTION_H

#include "election.h"

// DECLARACIONES con extern (no crean variables, solo las "mencionan")
extern int eleccion_activa;
extern int anio_eleccion;
extern char codigo_facultad[10];
extern int max_estudiantes;
extern int num_candidatos;
extern Candidato lista_candidatos[MAX_CANDIDATOS];
extern char** registro_votos_global;
extern int total_votos_emitidos;

// Prototipos de funciones de gestion.c
void guardarConfiguracionEleccion(void);
void nuevaEleccion(void);
void continuarEleccion(void);
void agregarCandidatoDinamico(void);
void quitarCandidatoDinamico(void);
void mostrarResultados(void);
void studentPanel(void);

// Funciones auxiliares
int esNumeroValido(const char* str);
void imprimirMatrizOpciones(Candidato* arr, int n, int mostrar_votos);

#endif