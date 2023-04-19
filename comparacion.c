#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct TipoElementoRep {
    int clave;
    void* valor;
} TipoElementoRep;

typedef TipoElementoRep* TipoElemento;

typedef struct ListaRep {
    TipoElemento* elementos;
    int cantidad;
} ListaRep;

typedef ListaRep* Lista;


int comparar_listas(Lista l1, Lista l2) {
    int cantidad_mayores_l1 = 0;
    int cantidad_mayores_l2 = 0;
    int i;
    
    // Comparar los elementos de ambas listas posición por posición
    for (i = 0; i < l1->cantidad && i < l2->cantidad; i++) {
        if (l1->elementos[i]->clave > l2->elementos[i]->clave) {
            cantidad_mayores_l1++;
        } else if (l1->elementos[i]->clave < l2->elementos[i]->clave) {
            cantidad_mayores_l2++;
        }
    }
    
    // Si ambas listas tienen la misma cantidad de elementos, entonces la que tenga
    // más claves mayores será la mayor
    if (l1->cantidad == l2->cantidad) {
        if (cantidad_mayores_l1 > cantidad_mayores_l2) {
            printf("L1 es  mayor");
            return 1; // L1 > L2
        } else if (cantidad_mayores_l1 < cantidad_mayores_l2) {
            printf("L1 es  menor");
            return -1; // L1 < L2
        } else {
            printf("L1 y L2 son iguales");
            return 0; // L1 = L2
        }
    }
    
    // Si no tienen la misma cantidad de elementos, entonces la lista más larga será la mayor
    if (l1->cantidad > l2->cantidad) {
        printf("L1 es  mayor");
        return 1; // L1 > L2
    } else {
        printf("L1 es  menor");
        return -1; // L1 < L2
    }
}

TipoElemento te_crear(int clave) {
    TipoElemento elemento = (TipoElemento) malloc(sizeof(TipoElementoRep));
    elemento->clave = clave;
    elemento->valor = NULL;
    return elemento;
}

TipoElemento te_crear_con_valor(int clave, void* valor) {
    TipoElemento elemento = (TipoElemento) malloc(sizeof(TipoElementoRep));
    elemento->clave = clave;
    elemento->valor = valor;
    return elemento;
}



Lista l_crear() {
    Lista lista = (Lista) malloc(sizeof(ListaRep));
    if (lista != NULL) {
        lista->elementos = NULL;
        lista->cantidad = 0;
    }
    return lista;
}

int l_agregar(Lista lista, TipoElemento elemento) {
    if (lista == NULL || elemento == NULL) {
        return 0;
    }

    TipoElemento* elementos_nuevos = (TipoElemento*) realloc(lista->elementos, (lista->cantidad + 1) * sizeof(TipoElemento));
    if (elementos_nuevos == NULL) {
        return 0;
    }

    lista->elementos = elementos_nuevos;
    lista->elementos[lista->cantidad] = elemento;
    lista->cantidad++;
    return 1;
}

void l_mostrar(Lista lista) {
    if (lista == NULL) {
        return;
    }
    printf("Cantidad de elementos en la lista: %d\n", lista->cantidad);
    printf("lista= [");
    for (int i = 0; i < lista->cantidad; i++) {
        printf("%d:%p ", lista->elementos[i]->clave, lista->elementos[i]->valor);
    }
    printf("]");
}

void agregar_elementos_a_lista(Lista lista) {
    int cantidad_elementos;
    printf("Cuantos elementos desea agregar a la lista? ");
    scanf("%d", &cantidad_elementos);

    for (int i = 0; i < cantidad_elementos; i++) {
        int clave;
        printf("Ingrese la clave del elemento[%d]: ", i);
        scanf("%d", &clave);

        // Crear un nuevo elemento con la clave ingresada y valor NULL
        TipoElemento elemento = te_crear(clave);

        if (elemento != NULL) {
            // Agregar el elemento a la lista
            if (l_agregar(lista, elemento) == 0) {
                printf("Error al agregar el elemento %d a la lista.\n", i);
            }
        } else {
            printf("Error al crear el elemento %d.\n", i);
        }
    }
}


int main() {
    Lista lista = l_crear();
    Lista lista2 = l_crear();
    agregar_elementos_a_lista(lista);
    agregar_elementos_a_lista(lista2);
    l_mostrar(lista);
    l_mostrar(lista2);
    printf("\n");
    comparar_listas(lista, lista2);
    
    // liberar memoria de la lista y sus elementos
    // ...
    return 0;
}