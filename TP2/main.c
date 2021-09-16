#include <stdio.h>
#include <stdbool.h>

#define MAIN_MENU       0
#define FIRST_OPTION    1
#define SECOND_OPTION   2
#define THIRD_OPTION    3
#define ERROR_OPTION    9

void printMainMenu() {
    puts("Elija que reporte desea obtener:");
    puts("1- Listar las especies cuyo porcentaje de variacion es negativo.");
    puts("2- Obtener las cotizaciones de compra y venta en un archivo .CSV");
    puts("3- Listar las especies cuyo porcentaje de variacion es negativo en una tabla HTML\n");
}

void getSpeciesWithNegativePercentage(bool shouldPrintAsHTML) {
}

void getBuyAndSellQuotesAndPrintAsCSV() {
}

int main(void) {
    int option;
    int state = MAIN_MENU;

    puts("---          Bienvenido          ---");
    
    /* Máquina de estados */
    while(1) {
        switch(state) {
            case MAIN_MENU:
                printMainMenu();

                scanf("%d", &option);
                fflush(stdin);

                if (
                    option != FIRST_OPTION && 
                    option != SECOND_OPTION && 
                    option != THIRD_OPTION
                ) {
                    state = ERROR_OPTION;
                } else {
                    state = option;
                }
                break;

            case FIRST_OPTION:
                getSpeciesWithNegativePercentage(false);
                state = MAIN_MENU;
                break;

            case SECOND_OPTION:
                getBuyAndSellQuotesAndPrintAsCSV();
                state = MAIN_MENU;
                break;

            case THIRD_OPTION:
                getSpeciesWithNegativePercentage(true);
                state = MAIN_MENU;
                break;

            default:
                puts("Opcion incorrecta.\n");
                state = MAIN_MENU;
        }
    }

    return 0;
}