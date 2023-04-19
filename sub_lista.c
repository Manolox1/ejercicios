//Arreglo

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

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
        char valor[10];
        printf("Ingrese la clave del elemento[%d], dejando un espacio agregue el valor que va a contener: ", i);
        scanf("%d %s", &clave, &valor);

        // Crear un nuevo elemento con la clave ingresada y valor NULL
        TipoElemento elemento = te_crear_con_valor(clave, valor);

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

bool es_sublista(Lista lista1, Lista lista2) {
    int i, j;
    for (i = 0; i < lista2->cantidad; i++) {
        int encontrada = 0;
        for (j = 0; j < lista1->cantidad; j++) {
            if (lista2->elementos[i]->valor == lista1->elementos[j]->valor) {
                encontrada = 1;
                break;
            } else {
                return false;
            }
        }
        if (!encontrada) {
            return false;
        }
    }
    return true;
}

int main() {
    Lista lista = l_crear();
    Lista lista2 = l_crear();
    agregar_elementos_a_lista(lista);
    agregar_elementos_a_lista(lista2);
    l_mostrar(lista);
    l_mostrar(lista2);
    if (es_sublista(lista, lista2))
    {
        printf("\nEs sublista");
    }
    
    // liberar memoria de la lista y sus elementos
    // ...
    return 0;
}