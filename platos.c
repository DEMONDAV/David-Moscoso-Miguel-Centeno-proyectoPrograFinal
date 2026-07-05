#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "platos.h"

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