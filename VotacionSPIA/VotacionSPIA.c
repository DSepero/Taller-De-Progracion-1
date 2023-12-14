#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "VotacionSPIA.h"

struct nodo *inicio_Chicos_Buenos = NULL;   //puntero al primer elemento del nodo de los chicos BUENOS
struct nodo *inicio_Chicos_Malos = NULL;    //puntero al primer elemento del nodo de los chicos MALOS

    FILE *archivo1;
    FILE *archivo2;

// FUNCION MAIN !!!!! //
int main(){

    

    char nombre_legislador[Nombre_MAX];
    int cantidad_votaciones = 0;
    char voto = ' ';
    char listas_ver= ' ';
    

    printf("Bienvenidos al programa de votacion de la SPIA.\n");
    printf("Donde veremos quien es de la casta y quien no...\n\n");
    printf("Por favor respete las mayusculas para efectuar los votos y para elegir las opcines correspondientes\n");
    

    archivo1= fopen("Chicos_Buenos.txt","w");                       //Apertura de los archivos en modo "append"
    archivo2= fopen("Chicos_Malos.txt","w");

    if (archivo1 == NULL && archivo2 == NULL)                       //Comprobacion de apertura de archivos
    {
        printf("Error, ambos archivos no se pudieron abrir.\n");
        return 1;
    }

    
        

    while (voto != 'E'){
        cantidad_votaciones++;

        printf("Votacion numero %d \n", cantidad_votaciones);
        printf("Ingrese 'F' para voto Favorable seguido del nombre del diputado votante: \n");
        printf("Ingrese 'D' para voto Desfavorable seguido del nombre del diputado votante: \n");
        printf("Ingrese 'E' para finalizar el proceso de votacion.\n");
        scanf(" %c", &voto);
        
        if (voto == 'F' || voto == 'D'){
            printf("Ingrese el nombre del Legislador: \n");
            scanf("%s", nombre_legislador);
            insertar_Legislador(voto, nombre_legislador);
            printf("\n");
        }
        
    }
    system("cls"); //borra pantalla para mejor legibilidad 
    printf("La votacion ha finalizado \n");
    guardar_datos(inicio_Chicos_Buenos, inicio_Chicos_Malos, archivo1, archivo2);   //llamada a la funcion que guarda los datos de los nodos

    fclose(archivo1);                                                               //cerramos ambos archivos para evitar problemas y "rendimiento del programa"
    fclose(archivo2);

    printf("\n");
    
    printf("Desea ver ambas listas de los legisladores votantes? 'S'i  - 'N'o (Salir Del Programa) \n");   //BLOQUE A CAMBIAR PARA QUE LEA LISTAS DE .TXT
    scanf(" %c",&listas_ver);

    if (listas_ver == 'S')
    {
        mostrar_listas();
    }
    else
    {
      return EXIT_SUCCESS;   
    } 
     
    system("pause");
    return EXIT_SUCCESS;

}


void insertar_Legislador(char voto, char *legislador) {

    //INSERTAR NUEVO LEGISLADOR
    struct nodo *nuevo;

    nuevo = malloc(sizeof(struct nodo));
    strcpy(nuevo->nombre, legislador);
    nuevo->sig = NULL;

  if (voto == 'F') {  // Voto favorable (Chicos Buenos)
        if (miembro(legislador, inicio_Chicos_Malos)) {
            extraer(legislador, &inicio_Chicos_Malos);
        }
        
        if (miembro(legislador, inicio_Chicos_Buenos)) {
            printf("El legislador ya se encuentra en la lista de Chicos Buenos.\n");
            free(nuevo);
            return;
        }
        
        if (inicio_Chicos_Buenos == NULL) {
            inicio_Chicos_Buenos = nuevo;
        } else {
            nuevo->sig = inicio_Chicos_Buenos;
            inicio_Chicos_Buenos = nuevo;
        }
    } else if (voto == 'D') {  // Voto desfavorable (Chicos Malos)
        if (miembro(legislador, inicio_Chicos_Buenos)) {
            extraer(legislador, &inicio_Chicos_Buenos);
        }
        
        if (miembro(legislador, inicio_Chicos_Malos)) {
            printf("El legislador ya se encuentra en la lista de Chicos Malos.\n");
            free(nuevo);
            return;
        }
        
        if (inicio_Chicos_Malos == NULL) {
            inicio_Chicos_Malos = nuevo;
        } else {
            nuevo->sig = inicio_Chicos_Malos;
            inicio_Chicos_Malos = nuevo;
        }
    }
}

void extraer(char *nombre, struct nodo **lista) {
    struct nodo *actual = *lista;
    struct nodo *anterior = NULL;

    while (actual != NULL) {
        if (strcmp(actual->nombre, nombre) == 0) {
            if (anterior != NULL) {
                anterior->sig = actual->sig;
            } else {
                *lista = actual->sig;
            }
            free(actual);
            printf("El legislador '%s' ha sido eliminado de la lista de los Chicos Buenos.\n", nombre);
            return;
        }
        anterior = actual;
        actual = actual->sig;
    }

    printf("El legislador '%s' no se encontraba en la lista de los Chicos Malos.\n", nombre);
}

void mostrar_listas() {

    archivo1 = fopen("Chicos_Buenos.txt", "r");
    archivo2 = fopen("Chicos_Malos.txt", "r");

    if (archivo1 == NULL || archivo2 == NULL) {
        printf("Error al abrir los archivos.\n");
        return;
    }

    printf("Contenido de Chicos_Buenos.txt:\n");
    char linea[Nombre_MAX];
    while (fgets(linea, sizeof(linea), archivo1) != NULL) {
        printf("%s", linea);
    }

    printf("\nContenido de Chicos_Malos.txt:\n");
    while (fgets(linea, sizeof(linea), archivo2) != NULL) {
        printf("%s", linea);
    }

    fclose(archivo1);
    fclose(archivo2);
}

int miembro(char *nombre, struct nodo *listas){
     
        struct nodo *legislador = listas;

        while (legislador != NULL) {
        if (strcmp(legislador->nombre, nombre) == 0) {
            return 1; // El nombre se encontró en la lista
        }
        
        legislador = legislador->sig;
    }
    
    return 0; // El nombre no se encuentra en la lista
}

void guardar_datos(struct nodo *inicio_Buenos, struct nodo *inicio_Malos){  //Funcion que GUARDA los datos de los nodos en los archivos

    struct nodo *buenos = inicio_Buenos;
    struct nodo *malos = inicio_Malos;

    while (buenos != NULL)
    {
        fprintf(archivo1, "%s\n", buenos->nombre);
        buenos=buenos->sig;
    }
    while (malos != NULL)
    {
        fprintf(archivo2, "%s\n", malos->nombre);
        malos=malos->sig;
    }
    
}