#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "string_aux.h"

#define MAIN_MENU       0
#define FIRST_OPTION    1
#define SECOND_OPTION   2
#define THIRD_OPTION    3
#define ERROR_OPTION    9

FILE *source;
char buffer[1048576];

typedef struct {
    char name[5];
    char expiration[4];
    int nominal;
    float buyValue;
    float sellValue;
    int nominalAmount;
    float lastPrice;
    float variation;
    float openingValue;
    float minValue;
    float maxValue;
    float lastClosingValue;
    float volume;
    float amount;
    int operation;
    char hour[8];
} specie_t;
specie_t* species;

void extractData() {
    char* token;
    char* row;
    int amountOfSpecies = 1;
    const char ROW_TOKEN[] = "<tr id";
    const char NAME_TOKEN[] = "link('";
    const char TD_TOKEN[] = "/td><td";

    species = (specie_t *) malloc(sizeof(specie_t));
    while (fgets(buffer, sizeof(buffer), source) != NULL) {
        row = strstr(buffer, ROW_TOKEN);
        if(row != NULL) {
            while ( ( token = strsepm( &row , NAME_TOKEN ) ) != NULL ) {
                strncpy(species[amountOfSpecies - 1].name, token, 4);
                species[amountOfSpecies - 1].name[4] = '\n';
                printf("SPECIE NAME = %s\n", species[amountOfSpecies - 1].name);
            }

            /** Agrando el array de Species **/
            amountOfSpecies++;
            species = (specie_t*) realloc(species, sizeof(specie_t) * amountOfSpecies);
        }
    }
}

void printMainMenu() {
    puts("Elija que reporte desea obtener:");
    puts("1- Listar las especies cuyo porcentaje de variacion es negativo.");
    puts("2- Obtener las cotizaciones de compra y venta en un archivo .CSV");
    puts("3- Listar las especies cuyo porcentaje de variacion es negativo en una tabla HTML\n");
}

void getSpeciesWithNegativePercentage(bool shouldPrintAsHTML) {
    extractData();
}

void getBuyAndSellQuotesAndPrintAsCSV() {
}


int main(void) {
    int option;
    int state = MAIN_MENU;
    
    puts("---          Bienvenido          ---");
    
    source = fopen("SSL-TP2.html", "r");
    if(source == NULL) {
        printf("Error al intentar abrir el archivo.");
        return -1;
    } else {
        printf("El archivo se pudo abrir correctamente!\n\n");
    }
    
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

    free(species);
    return 0;
}
