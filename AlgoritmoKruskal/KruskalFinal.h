#ifndef KRUSKALFINAL_H
#define KRUSKALFINAL_H

#define VERTICES 5

typedef int tipo_nombre;
typedef int tipo_elemento;
typedef int vertice;

// Estructura para representar una arista del grafo
typedef struct _ARISTA {
    vertice u;
    vertice v;
    int costo;
} arista;

// Estructura para representar una rama en la lista de aristas
typedef struct _RAMA {
    arista a;
    struct _RAMA* sig;
} rama;

// Estructura para almacenar la información del encabezado de un conjunto
typedef struct _ENCABEZADO {
    int cuenta;             // Cantidad de elementos en el conjunto
    int primer_elemento;    // Primer elemento del conjunto
} encabezado;

// Estructura para almacenar el nombre y el siguiente elemento de un elemento del conjunto
typedef struct _NOMBRE {
    tipo_nombre nombre_conjunto;    // Nombre del conjunto al que pertenece
    int siguiente_elemento;         // Siguiente elemento en el conjunto
} nombre;

// Estructura para almacenar conjuntos de elementos y sus encabezamientos
typedef struct _CONJUNTO_CE {
    nombre nombres[VERTICES];               // Elementos del conjunto
    encabezado encabezamientos_conjunto[VERTICES];    // Encabezamientos de los conjuntos
} conjunto_CE;

// Inicializa un conjunto en el algoritmo de Kruskal
void inicial(tipo_nombre A, tipo_elemento x, conjunto_CE* C);

// Combina dos conjuntos en el algoritmo de Kruskal
void combina(tipo_nombre A, tipo_nombre B, conjunto_CE* C);

// Encuentra el conjunto al que pertenece un elemento en el algoritmo de Kruskal
tipo_nombre encuentra(int x, conjunto_CE* C);

// Implementa el algoritmo de Kruskal para encontrar el árbol de expansión mínima
void kruskal(rama* aristas);

// Inserta una nueva arista en la lista de aristas del grafo
void inserta(int u, int v, int costo, rama** aristas);

// Saca y devuelve la arista de costo mínimo de la lista de aristas
arista* sacar_min(rama** aristas);

// Imprime la lista de aristas
void lista(rama* aristas);

// Muestra el grafo original con las aristas y sus costos
void mostrarGrafo(rama* aristas);

// Comprueba si la inclusión de una arista forma un ciclo en el algoritmo de Kruskal
int formaCiclo(int u, int v, conjunto_CE* C);

// Ordena las aristas en orden ascendente según sus costos
void ordenar_aristas(rama** aristas);

// Permite al usuario ingresar las aristas del grafo
void ingresarAristas(rama** aristas);

#endif
