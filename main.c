#include <stdio.h>
#include <stdlib.h>
#include "ingredientes.h"
#include "platos.h"
#include "relaciones.h"

int main() {
    Ingrediente ingredientes[MAX_ING];
    Plato platos[MAX_PLATOS];
    PlatoIngrediente relaciones[MAX_RELACIONES];

    int t_ing = cargar_ingredientes_csv("ingredientes.csv", ingredientes);
    int t_pla = cargar_platos_csv("platos.csv", platos);
    int t_rel = cargar_relaciones_csv("plato_ingredientes.csv", relaciones);

    int op = 0, sub_op = 0;
    do {
        printf("\n=== RESTAURANTE SGCA - MENU PRINCIPAL ===\n");
        printf("1. Gestion de Ingredientes\n2. Gestion de Platos\n3. Gestion de Recetas (Ingredientes por Plato)\n4. Calculo de costos y Reportes\n5. Guardar Cambios (.csv)\n6. Salir\nSeleccione: ");
        scanf("%d", &op);

        if (op == 1) {
            printf("\n1. Registrar\n2. Listar\n3. Actualizar\n4. Eliminar\nSeleccione: ");
            scanf("%d", &sub_op);
        } else if (op == 2) {
            printf("\n1. Registrar\n2. Listar\n3. Actualizar\n4. Eliminar\nSeleccione: ");
            scanf("%d", &sub_op);
        } else if (op == 3) {
            printf("\n1. Asociar ingrediente a plato\n2. Quitar relacion\nSeleccione: ");
            scanf("%d", &sub_op);
        } else if (op == 4) {
            printf("Proximamente: Calculos y Reportes.\n");
        } else if (op == 5) {
            guardar_ingredientes_csv("ingredientes.csv", ingredientes, t_ing);
            guardar_platos_csv("platos.csv", platos, t_pla);
            guardar_relaciones_csv("plato_ingredientes.csv", relaciones, t_rel);
            printf("Archivos .csv sincronizados de forma correcta.\n");
        }
    } while (op != 6);

    return 0;
}