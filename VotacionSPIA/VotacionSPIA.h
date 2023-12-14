#ifndef VotacionSPIA_H
#define VotacionSPIA_H

#define Nombre_MAX 20

struct nodo                     //Estructura principal
{
    char nombre[Nombre_MAX];
    struct nodo *sig;
};

//FUNCIONES para manejo de datos

void insertar_Legislador(char voto, char *legislador);
void extraer();
void imprimir_Listas(char elegir);
int miembro(char *nombre, struct nodo *listas);
void guardar_datos();
void mostrar_listas();

#endif