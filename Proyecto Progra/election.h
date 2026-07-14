#ifndef ELECTION_H
#define ELECTION_H

#define MAX_CANDIDATOS 12 

typedef struct {
    int id;
    char nombre_lista[20];
    char presidente[30];
    char vicepresidente[30];
    int votos;
    int activo; 
} Candidato;

// Solo estructuras y constantes
// Las funciones van en sus respectivos .h

#endif