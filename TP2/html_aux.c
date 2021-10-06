#include "html_aux.h"

char* readDataFromTag(char* buffer, char* tag, int* seek){
    char init_tag[4] = "<";
    char end_tag[6] = "</";
    strcat(init_tag, tag);
    strcat(end_tag, tag);
    strcat(end_tag, ">");
    char* contenido = strstr(buffer, init_tag);
    if(contenido == NULL){
        return NULL;
    }
    int i = 0;
    int j = 0;

    while(contenido[i] != '>')   i++;
    i++;
    while(strncmp(&(contenido[i+1+j]),end_tag, 5 ) != 0) j++;
    j++;
    
    char* dest = (char*)calloc(j, sizeof(char));
    strncpy(dest,&(contenido[i]),j);
    if(seek != NULL){
        *seek += i+j;
    }

    return dest;
}