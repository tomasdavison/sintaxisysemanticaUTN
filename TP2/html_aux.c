#include "html_aux.h"

char* obtenerDataDentroDeTag(char* buffer, char* tag){
    char init_tag[4] = "<";
    char end_tag[6] = "</";
    strcat(init_tag, tag);
    strcat(end_tag, tag);
    strcat(end_tag, ">");
    char* fila = strstr(buffer, init_tag);
    if(fila == NULL){
        return NULL;
    }
    int i = 0;
    int j = 0;

    while(fila[i] != '>')   i++;
    i++;
    while(strncmp(&(fila[i+1+j]),end_tag, 5 ) != 0) j++;
    j++;
    
    char* dest = (char*)calloc(j, sizeof(char));
    strncpy(dest,&(fila[i]),j);

    return dest;
}