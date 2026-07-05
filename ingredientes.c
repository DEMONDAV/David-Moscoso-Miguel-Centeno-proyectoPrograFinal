#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ingredientes.h"

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