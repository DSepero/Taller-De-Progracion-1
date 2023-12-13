#include <stdio.h>
#include <stdlib.h>
#include "KruskalFinal.h"



int main() {

    //Cartel de bienvenida
    printf("Bienvenido al programa del Algoritmo de Kruskal. \n");
    printf("El programa te pide ingresar ambas aristas y su peso correspondiente.\n");
    printf("Una vez que quiera que el algoritmo analize el grafo aprete N cuando se le indique.\n");

    rama* aristas = NULL;  // Lista enlazada de aristas
    
    ingresarAristas(&aristas);

    printf("Grafo original:\n");
    lista(aristas);

    ordenar_aristas(&aristas);
    kruskal(aristas);
    
    // Liberar memoria de las aristas originales
    rama* temp = aristas;
    while (temp != NULL) {
        rama* siguiente = temp->sig;
        free(temp);
        temp = siguiente;
    }

    system("Pause");
    return 0;
}


// Funcion que inicializa la estructura para luego llenarla con los datos de las aristas y sus pesos //
void inicial(tipo_nombre A, tipo_elemento x, conjunto_CE* C) { 
    //Le asignamos nombre 'A' y una "referencia" a 0 para luego hacer el recorrido en la estructura
    C->nombres[x].nombre_conjunto = A;
    C->nombres[x].siguiente_elemento = 0;
    //aplicamos un contador que empieza en 1 y volvemos a llamar A como X para mantener enlace al primer elemento
    C->encabezamientos_conjunto[A].cuenta = 1;
    C->encabezamientos_conjunto[A].primer_elemento = x;
}

//Funcion Combina, une ambas listas (A y B) en una sola, dependiendo del tamaño de ambas, con el fin de analizar que no se generen ciclos//
void combina(tipo_nombre A, tipo_nombre B, conjunto_CE* C) {
    // Verifica la cuenta de elementos en cada conjunto para decidir cuál es el conjunto principal
    if (C->encabezamientos_conjunto[A].cuenta > C->encabezamientos_conjunto[B].cuenta) {
        // Recorre todos los elementos del conjunto B y los asigna al conjunto A
        int i = C->encabezamientos_conjunto[B].primer_elemento;
        while (C->nombres[i].siguiente_elemento != 0) {
            C->nombres[i].nombre_conjunto = A;
            i = C->nombres[i].siguiente_elemento;
        }
        C->nombres[i].nombre_conjunto = A;
        C->nombres[i].siguiente_elemento = C->encabezamientos_conjunto[A].primer_elemento;
        C->encabezamientos_conjunto[A].primer_elemento = C->encabezamientos_conjunto[B].primer_elemento;
        C->encabezamientos_conjunto[A].cuenta += C->encabezamientos_conjunto[B].cuenta;
    }
    // Recorre todos los elementos del conjunto A y los asigna al conjunto B
    else {
        int i = C->encabezamientos_conjunto[A].primer_elemento;
        while (C->nombres[i].siguiente_elemento != 0) {
            C->nombres[i].nombre_conjunto = B;
            i = C->nombres[i].siguiente_elemento;
        }
        C->nombres[i].nombre_conjunto = B;
        C->nombres[i].siguiente_elemento = C->encabezamientos_conjunto[B].primer_elemento;
        C->encabezamientos_conjunto[B].primer_elemento = C->encabezamientos_conjunto[A].primer_elemento;
        C->encabezamientos_conjunto[B].cuenta += C->encabezamientos_conjunto[A].cuenta;
    }
}

// Encuentra el conjunto al que pertenece un elemento en el algoritmo de Kruskal
tipo_nombre encuentra(int x, conjunto_CE* C) {
    return C->nombres[x].nombre_conjunto;
}

//La función formaCiclo utiliza la función "encuentra" para obtener los nombres de los conjuntos a los que pertenecen dos elementos (u y v).
//Luego, compara los nombres de los conjuntos para determinar si u y v están en el mismo conjunto o no
int formaCiclo(int u, int v, conjunto_CE* C) {
    tipo_nombre comp_u = encuentra(u, C);
    tipo_nombre comp_v = encuentra(v, C);
    return (comp_u == comp_v);
}

//Utiliza el metodo burbuja para ir ordenando las aristas de menor a mayor costo
void ordenar_aristas(rama** aristas) {
    rama* actual = *aristas;
    rama* siguiente = NULL;
    rama* temp = NULL;
    int intercambio = 0;

    do {
        intercambio = 0;
        actual = *aristas;

        while (actual->sig != siguiente) {
            if (actual->a.costo > actual->sig->a.costo) {
                // Realiza el intercambio de aristas
                temp = actual->sig;
                actual->sig = actual->sig->sig;
                temp->sig = actual;

                if (actual == *aristas)
                    *aristas = temp;
                else {
                    rama* anterior = *aristas;
                    while (anterior->sig != actual)
                        anterior = anterior->sig;
                    anterior->sig = temp;
                }

                actual = temp;
                intercambio = 1;
            }

            actual = actual->sig;
        }

        siguiente = actual;
    } while (intercambio);
}

//Funcion PRINCIPAL para ver el arbol de expancion minima
void kruskal(rama* aristas) {
    conjunto_CE conjuntos;
    int comp_n = 0;
    rama* r = aristas;
    
    // Inicializa los conjuntos para cada vértice del grafo
    for (int i = 0; i < VERTICES; i++) {
        inicial(i, i, &conjuntos);
        comp_n++;
    }
    
    rama* arbol_exp_min = NULL;
    
    // Aplica el algoritmo de Kruskal para construir el árbol de expansión mínima
    while (comp_n > 1 && r != NULL) {
        arista a = r->a;
        tipo_nombre comp_u = encuentra(a.u, &conjuntos);
        tipo_nombre comp_v = encuentra(a.v, &conjuntos);
        
        if (comp_u != comp_v) {
            if (!formaCiclo(a.u, a.v, &conjuntos)) {
                // Combina los conjuntos y agrega la arista al árbol de expansión mínima
                combina(comp_u, comp_v, &conjuntos);
                comp_n--;
                
                rama* nueva_rama = (rama*)malloc(sizeof(rama));
                nueva_rama->a = a;
                nueva_rama->sig = arbol_exp_min;
                arbol_exp_min = nueva_rama;
            }
            else {
                printf("Se forma un ciclo con la arista (%d, %d)\n", a.u, a.v);
            }
        }
        
        r = r->sig;
    }
    // Imprime el grafo original con los pesos ordenados
    printf("Grafo original con Pesos Ordenados:\n");
    lista(aristas);
    
    // Imprime el árbol de expansión mínima resultante
    printf("\nGrafo con Kruskal aplicado:\n");
    lista(arbol_exp_min);
    
    // Liberar memoria del árbol de expansión mínimo resultante
    rama* temp = arbol_exp_min;
    while (temp != NULL) {
        rama* siguiente = temp->sig;
        free(temp);
        temp = siguiente;
    }
}

// Inserta una nueva arista en la lista de aristas del grafo
void inserta(int u, int v, int costo, rama** aristas) {
    rama* nueva_rama = (rama*)malloc(sizeof(rama));
    nueva_rama->a.u = u;
    nueva_rama->a.v = v;
    nueva_rama->a.costo = costo;
    nueva_rama->sig = *aristas;
    *aristas = nueva_rama;
}

// Imprime la lista de aristas
void lista(rama* aristas) {
    rama* actual = aristas;
    
    while (actual != NULL) {
        printf("(%d, %d, %d)\n", actual->a.u, actual->a.v, actual->a.costo);
        actual = actual->sig;
    }
}

// Permite al usuario ingresar las aristas del grafo
void ingresarAristas(rama** aristas) {
    int u, v, costo;
    char continuar;
    
    do {
        printf("Ingrese el nodo U: ");
        scanf("%d", &u);
        
        printf("Ingrese el nodo V: ");
        scanf("%d", &v);
        
        printf("Ingrese el costo: ");
        scanf("%d", &costo);
        
        inserta(u, v, costo, aristas);
        
        printf("Desea ingresar otra arista? 'S'\n");
        printf("Para analizar el grafo insertado precione 'N'\n");
        scanf(" %c", &continuar);
    } while (continuar == 's' || continuar == 'S');
}

