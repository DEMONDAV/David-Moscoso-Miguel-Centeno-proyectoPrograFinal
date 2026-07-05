#ifndef INGREDIENTES_H
#define INGREDIENTES_H

#define MAX_ING 100
#define MAX_STR 100

typedef struct {
    char codigo_ing[MAX_STR];
    char nombre_ing[MAX_STR];
    float costo_unitario;
    char unidad_medida[MAX_STR];
} Ingrediente;

int cargar_ingredientes_csv(const char *filename, Ingrediente lista[]);
void guardar_ingredientes_csv(const char *filename, Ingrediente lista[], int total);
void registrar_ingrediente(Ingrediente lista[], int *total);
void listar_ingredientes(Ingrediente lista[], int total);
int buscar_ingrediente_por_codigo(Ingrediente lista[], int total, const char *codigo);
void actualizar_ingrediente(Ingrediente lista[], int total);
void eliminar_ingrediente(Ingrediente lista[], int *total, void *lista_rel, int total_rel);

#endif