#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "html_aux.h"

#define MAIN_MENU       0
#define FIRST_OPTION    1
#define SECOND_OPTION   2
#define THIRD_OPTION    3
#define ERROR_OPTION    9
#define MAX_COLUMN 17

FILE *source;
char *buffer;
row_t table[65];

typedef char* row_t[16];

typedef enum{
    ESPECIE,
    VTO,
    CANT_NOMINAL_1,
    COMPRA,
    VENTA,
    CANT_NOMINAL_2,
    ULTIMO,
    VARIACION,
    APERTURA,
    MAX,MIN,
    CIERRE_ANTERIOR,
    VOLUMEN,
    MONTO,
    OPERACION,
    HORA
} column_t;

void extractData() {
    int seek_fila = 0;
    int seek_column = 0;
    int column = 0;
    int rowAmount = 0;
    
    char* htmlRow = readDataFromTag(buffer,"tr",&seek_fila);
    char* delta;
    bool emptyRow = true;

    while(htmlRow != NULL){
        seek_column = 0;
        column = 0;
        char* data = readDataFromTag(htmlRow, "td", &seek_column);
        while(data!= NULL){
            emptyRow = false;
            if(strstr(data, "span") != NULL){
                delta = readDataFromTag(data, "span", NULL);
                data = (char*) realloc(data, strlen(delta));
                strcpy(data,delta);
            }

            table[rowAmount][column] = (char*) calloc(strlen(data) +1 , sizeof(char));
            memcpy(table[rowAmount][column], data, strlen(data));

            data = readDataFromTag(&(htmlRow[seek_column]), "td", &seek_column);
            column++;   
        }

        htmlRow = readDataFromTag(&(buffer[seek_fila]), "tr",&seek_fila);
        if(!emptyRow)
            rowAmount++;
    }
}

void printMainMenu() {
    puts("Elija que reporte desea obtener:");
    puts("1- Listar las especies cuyo porcentaje de variacion es negativo.");
    puts("2- Obtener las cotizaciones de compra y venta en un archivo .CSV");
    puts("3- Listar las especies cuyo porcentaje de variacion es negativo en una tabla HTML\n");
}

void getSpeciesWithNegativePercentage(bool shouldPrintAsHTML) {
    if(shouldPrintAsHTML) {
        //TODO
    } else {
        puts("Especies con variacion negativa:\n");
        for(int i=0; i<65; i++){
            if(table[i][VARIACION][0] == '-'){
                printf("\t\t\t");
                puts(table[i][ESPECIE]);
            }
        }
        puts("");
    }
}

void getBuyAndSellQuotesAndPrintAsCSV() {
}

char* openFileAndLoadBuffer(char* filename) {
    FILE* file = fopen(filename,"r");
    if(file == NULL){
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long int size = ftell(file);
    rewind(file);

    char* content = calloc(size + 1, 1);

    fread(content,1,size,file);
    fclose(file);

    return content;
}

void initialize() {
    buffer = openFileAndLoadBuffer("SSL-TP2.html");
    extractData();
}

int main(void) {
    int option;
    int state = MAIN_MENU;
    
    puts("---          Bienvenido          ---");
    initialize();
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
