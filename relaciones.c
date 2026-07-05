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