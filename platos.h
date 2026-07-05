#ifndef PLATOS_H
#define PLATOS_H

#define MAX_PLATOS 50
#define MAX_STR 100

typedef struct {
    char codigo_plato[MAX_STR];
    char nombre_plato[MAX_STR];
    char categoria[MAX_STR];
    float costo_ingredientes; 
    float impuesto_porcentaje;
    float servicio_porcentaje;
    float ganancia_porcentaje;
    float costo_final; 
} Plato;

int cargar_platos_csv(const char *filename, Plato lista[]);
void guardar_platos_csv(const char *filename, Plato lista[], int total);
void registrar_plato(Plato lista[], int *total);
void listar_platos(Plato lista[], int total);
int buscar_plato_por_codigo(Plato lista[], int total, const char *codigo);
void actualizar_plato(Plato lista[], int total);
void eliminar_plato(Plato lista[], int *total, void *lista_rel, int *total_rel);

#endif