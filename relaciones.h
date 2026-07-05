#ifndef RELACIONES_H
#define RELACIONES_H

#include "ingredientes.h"
#include "platos.h"

#define MAX_RELACIONES 300

typedef struct {
    char codigo_plato[MAX_STR];
    char codigo_ing[MAX_STR];
    float cantidad_usada;
} PlatoIngrediente;

int cargar_relaciones_csv(const char *filename, PlatoIngrediente lista[]);
void guardar_relaciones_csv(const char *filename, PlatoIngrediente lista[], int total);
void asociar_ingrediente_a_plato(PlatoIngrediente lista_rel[], int *total_rel, Plato lista_platos[], int total_platos, Ingrediente lista_ing[], int total_ing);
void quitar_ingrediente_de_plato(PlatoIngrediente lista_rel[], int *total_rel);
void calcular_costos_menu(Plato lista_platos[], int total_platos, PlatoIngrediente lista_rel[], int total_rel, Ingrediente lista_ing[], int total_ing);
void mostrar_reporte_financiero(Plato lista_platos[], int total_platos);

#endif
