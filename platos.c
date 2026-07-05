#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "platos.h"
#include "relaciones.h"

int cargar_platos_csv(const char *filename, Plato lista[]) {
    FILE *file = fopen(filename, "r");
    if (!file) return 0;
    char linea[256];
    int total = 0;
    if (fgets(linea, sizeof(linea), file)) {
        while (fgets(linea, sizeof(linea), file) && total < MAX_PLATOS) {
            linea[strcspn(linea, "\n")] = 0;
            linea[strcspn(linea, "\r")] = 0;
            char *token_cod = strtok(linea, ",;");
            char *token_nom = strtok(NULL, ",;");
            char *token_cat = strtok(NULL, ",;");
            char *token_imp = strtok(NULL, ",;");
            char *token_ser = strtok(NULL, ",;");
            char *token_gan = strtok(NULL, ",;");
            if (token_cod && token_nom && token_cat) {
                strcpy(lista[total].codigo_plato, token_cod);
                strcpy(lista[total].nombre_plato, token_nom);
                strcpy(lista[total].categoria, token_cat);
                lista[total].impuesto_porcentaje = token_imp ? atof(token_imp) : 15.0f;
                lista[total].servicio_porcentaje = token_ser ? atof(token_ser) : 10.0f;
                lista[total].ganancia_porcentaje = token_gan ? atof(token_gan) : 40.0f;
                lista[total].costo_ingredientes = 0;
                lista[total].costo_final = 0;
                total++;
            }
        }
    }
    fclose(file);
    return total;
}

void guardar_platos_csv(const char *filename, Plato lista[], int total) {
    FILE *file = fopen(filename, "w");
    if (!file) return;
    fprintf(file, "codigo_plato,nombre_plato,categoria,impuesto_porcentaje,servicio_porcentaje,ganancia_porcentaje\n");
    for (int i = 0; i < total; i++) {
        fprintf(file, "%s,%s,%s,%.1f,%.1f,%.1f\n", lista[i].codigo_plato, lista[i].nombre_plato, lista[i].categoria, lista[i].impuesto_porcentaje, lista[i].servicio_porcentaje, lista[i].ganancia_porcentaje);
    }
    fclose(file);
}

void registrar_plato(Plato lista[], int *total) {
    if (*total >= MAX_PLATOS) return;
    printf("Codigo unico del plato (ej: PLA001): ");
    scanf("%s", lista[*total].codigo_plato);
    if (buscar_plato_por_codigo(lista, *total, lista[*total].codigo_plato) != -1) {
        printf("Error: El codigo ya existe.\n"); return;
    }
    printf("Nombre del plato: ");
    scanf(" %[^\n]", lista[*total].nombre_plato);
    printf("Categoria: ");
    scanf("%s", lista[*total].categoria);
    printf("Porcentaje Impuesto: ");
    scanf("%f", &lista[*total].impuesto_porcentaje);
    printf("Porcentaje Servicio: ");
    scanf("%f", &lista[*total].servicio_porcentaje);
    printf("Porcentaje Ganancia: ");
    scanf("%f", &lista[*total].ganancia_porcentaje);
    lista[*total].costo_ingredientes = 0;
    lista[*total].costo_final = 0;
    (*total)++;
    printf("Plato creado.\n");
}

void listar_platos(Plato lista[], int total) {
    printf("\n--- MENU DE PLATOS ---\n");
    for (int i = 0; i < total; i++) {
        printf("[%s] %s (%s) -> Costo Base: $%.2f | Venta: $%.2f\n", lista[i].codigo_plato, lista[i].nombre_plato, lista[i].categoria, lista[i].costo_ingredientes, lista[i].costo_final);
    }
}

int buscar_plato_por_codigo(Plato lista[], int total, const char *codigo) {
    for (int i = 0; i < total; i++) {
        if (strcmp(lista[i].codigo_plato, codigo) == 0) return i;
    }
    return -1;
}

void actualizar_plato(Plato lista[], int total) {
    char cod[MAX_STR];
    printf("Codigo del plato a modificar: ");
    scanf("%s", cod);
    int idx = buscar_plato_por_codigo(lista, total, cod);
    if (idx == -1) return;
    printf("Nuevo Nombre: ");
    scanf(" %[^\n]", lista[idx].nombre_plato);
    printf("Nueva Categoria: ");
    scanf("%s", lista[idx].categoria);
    printf("Nueva Ganancia (%%): ");
    scanf("%f", &lista[idx].ganancia_porcentaje);
}

void eliminar_plato(Plato lista[], int *total, void *lista_rel, int *total_rel) {
    char cod[MAX_STR];
    printf("Codigo del plato a eliminar: ");
    scanf("%s", cod);
    int idx = buscar_plato_por_codigo(lista, *total, cod);
    if (idx == -1) return;

    PlatoIngrediente *relaciones = (PlatoIngrediente *)lista_rel;
    for (int i = 0; i < *total_rel; i++) {
        if (strcmp(relaciones[i].codigo_plato, cod) == 0) {
            for (int j = i; j < (*total_rel) - 1; j++) {
                relaciones[j] = relaciones[j + 1];
            }
            (*total_rel)--;
            i--;
        }
    }

    for (int i = idx; i < (*total) - 1; i++) {
        lista[i] = lista[i + 1];
    }
    (*total)--;
    printf("Plato eliminado.\n");
}