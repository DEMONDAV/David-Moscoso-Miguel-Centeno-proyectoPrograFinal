#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "relaciones.h"

int cargar_relaciones_csv(const char *filename, PlatoIngrediente lista[]) {
    FILE *file = fopen(filename, "r");
    if (!file) return 0;
    char linea[256];
    int total = 0;
    if (fgets(linea, sizeof(linea), file)) {
        while (fgets(linea, sizeof(linea), file) && total < MAX_RELACIONES) {
            linea[strcspn(linea, "\n")] = 0;
            linea[strcspn(linea, "\r")] = 0;
            char *token_plato = strtok(linea, ",;");
            char *token_ing = strtok(NULL, ",;");
            char *token_cant = strtok(NULL, ",;");
            if (token_plato && token_ing && token_cant) {
                strcpy(lista[total].codigo_plato, token_plato);
                strcpy(lista[total].codigo_ing, token_ing);
                lista[total].cantidad_usada = atof(token_cant);
                total++;
            }
        }
    }
    fclose(file);
    return total;
}

void guardar_relaciones_csv(const char *filename, PlatoIngrediente lista[], int total) {
    FILE *file = fopen(filename, "w");
    if (!file) return;
    fprintf(file, "codigo_plato,codigo_ing,cantidad_usada\n");
    for (int i = 0; i < total; i++) {
        fprintf(file, "%s,%s,%.4f\n", lista[i].codigo_plato, lista[i].codigo_ing, lista[i].cantidad_usada);
    }
    fclose(file);
}

void asociar_ingrediente_a_plato(PlatoIngrediente lista_rel[], int *total_rel, Plato lista_platos[], int total_platos, Ingrediente lista_ing[], int total_ing) {
    if (*total_rel >= MAX_RELACIONES) return;
    char cod_p[MAX_STR], cod_i[MAX_STR];
    printf("Codigo del Plato: "); scanf("%s", cod_p);
    printf("Codigo del Ingrediente: "); scanf("%s", cod_i);
    
    if (buscar_plato_por_codigo(lista_platos, total_platos, cod_p) == -1 || buscar_ingrediente_por_codigo(lista_ing, total_ing, cod_i) == -1) {
        printf("Error: Verifique que ambos codigos existan.\n"); return;
    }
    
    strcpy(lista_rel[*total_rel].codigo_plato, cod_p);
    strcpy(lista_rel[*total_rel].codigo_ing, cod_i);
    printf("Cantidad a usar (en kg o unidad base): ");
    scanf("%f", &lista_rel[*total_rel].cantidad_usada);
    (*total_rel)++;
    printf("Relacion guardada de forma limpia.\n");
}

void quitar_ingrediente_de_plato(PlatoIngrediente lista_rel[], int *total_rel) {
    char cod_p[MAX_STR], cod_i[MAX_STR];
    printf("Codigo del Plato: "); scanf("%s", cod_p);
    printf("Codigo del Ingrediente a retirar: "); scanf("%s", cod_i);
    
    for(int i = 0; i < *total_rel; i++) {
        if(strcmp(lista_rel[i].codigo_plato, cod_p) == 0 && strcmp(lista_rel[i].codigo_ing, cod_i) == 0) {
            for(int j = i; j < (*total_rel) - 1; j++) {
                lista_rel[j] = lista_rel[j+1];
            }
            (*total_rel)--;
            printf("Relacion removida con exito.\n");
            return;
        }
    }
    printf("No se encontro relacion.\n");
}

void calcular_costos_menu(Plato lista_platos[], int total_platos, PlatoIngrediente lista_rel[], int total_rel, Ingrediente lista_ing[], int total_ing) {
    for (int i = 0; i < total_platos; i++) {
        lista_platos[i].costo_ingredientes = 0;
    }
    
    for (int i = 0; i < total_rel; i++) {
        int idx_p = buscar_plato_por_codigo(lista_platos, total_platos, lista_rel[i].codigo_plato);
        int idx_i = buscar_ingrediente_por_codigo(lista_ing, total_ing, lista_rel[i].codigo_ing);
        if (idx_p != -1 && idx_i != -1) {
            lista_platos[idx_p].costo_ingredientes += (lista_ing[idx_i].costo_unitario * lista_rel[i].cantidad_usada);
        }
    }
    
    for (int i = 0; i < total_platos; i++) {
        float cb = lista_platos[i].costo_ingredientes;
        float imp = cb * (lista_platos[i].impuesto_porcentaje / 100.0f);
        float ser = cb * (lista_platos[i].servicio_porcentaje / 100.0f);
        float gan = cb * (lista_platos[i].ganancia_porcentaje / 100.0f);
        lista_platos[i].costo_final = cb + imp + ser + gan;
    }
}

void mostrar_reporte_financiero(Plato lista_platos[], int total_platos) {
    printf("\n============== REPORTES Y MENU FINAL RESTAURANTE ==============\n");
    for(int i = 0; i < total_platos; i++) {
        printf("Plato: %-20s | Costo Base: $%6.2f | PRECIO VENTA: $%6.2f\n", 
               lista_platos[i].nombre_plato, lista_platos[i].costo_ingredientes, lista_platos[i].costo_final);
    }
}