#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ingredientes.h"
#include "relaciones.h"

int cargar_ingredientes_csv(const char *filename, Ingrediente lista[]) {
    FILE *file = fopen(filename, "r");
    if (!file) return 0;
    char linea[256];
    int total = 0;
    if (fgets(linea, sizeof(linea), file)) {
        while (fgets(linea, sizeof(linea), file) && total < MAX_ING) {
            linea[strcspn(linea, "\n")] = 0;
            linea[strcspn(linea, "\r")] = 0;
            char *token_cod = strtok(linea, ",;");
            char *token_nom = strtok(NULL, ",;");
            char *token_costo = strtok(NULL, ",;");
            char *token_uni = strtok(NULL, ",;");
            if (token_cod && token_nom && token_costo && token_uni) {
                strcpy(lista[total].codigo_ing, token_cod);
                strcpy(lista[total].nombre_ing, token_nom);
                lista[total].costo_unitario = atof(token_costo);
                strcpy(lista[total].unidad_medida, token_uni);
                total++;
            }
        }
    }
    fclose(file);
    return total;
}

void guardar_ingredientes_csv(const char *filename, Ingrediente lista[], int total) {
    FILE *file = fopen(filename, "w");
    if (!file) return;
    fprintf(file, "codigo_ing,nombre_ing,costo_unitario,unidad_medida\n");
    for (int i = 0; i < total; i++) {
        fprintf(file, "%s,%s,%.2f,%s\n", lista[i].codigo_ing, lista[i].nombre_ing, lista[i].costo_unitario, lista[i].unidad_medida);
    }
    fclose(file);
}

void registrar_ingrediente(Ingrediente lista[], int *total) {
    if (*total >= MAX_ING) { printf("Capacidad maxima alcanzada.\n"); return; }
    char cod[MAX_STR];
    printf("Ingrese codigo unico del ingrediente (ej: ING001): ");
    scanf("%s", cod);
    if (buscar_ingrediente_por_codigo(lista, *total, cod) != -1) {
        printf("Error: El codigo ya existe.\n"); return;
    }
    strcpy(lista[*total].codigo_ing, cod);
    printf("Nombre: ");
    scanf(" %[^\n]", lista[*total].nombre_ing);
    do {
        printf("Costo Unitario (>0): ");
        scanf("%f", &lista[*total].costo_unitario);
    } while (lista[*total].costo_unitario <= 0);
    printf("Unidad de medida (ej: kg): ");
    scanf("%s", lista[*total].unidad_medida);
    (*total)++;
    printf("Ingrediente registrado con exito.\n");
}

void listar_ingredientes(Ingrediente lista[], int total) {
    printf("\n--- CATALOGO DE INGREDIENTES ---\n");
    for (int i = 0; i < total; i++) {
        printf("[%s] %s - Costo/U: $%.2f (%s)\n", lista[i].codigo_ing, lista[i].nombre_ing, lista[i].costo_unitario, lista[i].unidad_medida);
    }
}

int buscar_ingrediente_por_codigo(Ingrediente lista[], int total, const char *codigo) {
    for (int i = 0; i < total; i++) {
        if (strcmp(lista[i].codigo_ing, codigo) == 0) return i;
    }
    return -1;
}

void actualizar_ingrediente(Ingrediente lista[], int total) {
    char cod[MAX_STR];
    printf("Ingrese el codigo del ingrediente a modificar: ");
    scanf("%s", cod);
    int idx = buscar_ingrediente_por_codigo(lista, total, cod);
    if (idx == -1) { printf("No encontrado.\n"); return; }
    printf("Nuevo Nombre: ");
    scanf(" %[^\n]", lista[idx].nombre_ing);
    printf("Nuevo Costo: ");
    scanf("%f", &lista[idx].costo_unitario);
    printf("Nueva Unidad: ");
    scanf("%s", lista[idx].unidad_medida);
    printf("Modificado correctamente.\n");
}

void eliminar_ingrediente(Ingrediente lista[], int *total, void *lista_rel, int total_rel) {
    char cod[MAX_STR];
    printf("Ingrese el codigo del ingrediente a eliminar: ");
    scanf("%s", cod);
    
    PlatoIngrediente *relaciones = (PlatoIngrediente *)lista_rel;
    for (int i = 0; i < total_rel; i++) {
        if (strcmp(relaciones[i].codigo_ing, cod) == 0) {
            printf("Error Obligatorio: No se puede eliminar porque esta asociado a un plato.\n");
            return;
        }
    }
    
    int idx = buscar_ingrediente_por_codigo(lista, *total, cod);
    if (idx == -1) { printf("No encontrado.\n"); return; }
    
    for (int i = idx; i < (*total) - 1; i++) {
        lista[i] = lista[i + 1];
    }
    (*total)--;
    printf("Ingrediente eliminado exitosamente.\n");
}