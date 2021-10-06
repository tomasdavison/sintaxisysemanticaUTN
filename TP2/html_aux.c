#include "html_aux.h"

char* readDataFromTag(char* buffer, char* tag, int* seek){
    int i = 0, j = 0;
    char* init_tag = buildTag(OPEN, tag);
    char* end_tag =  buildTag(CLOSE, tag);

    char* content = strstr(buffer, init_tag);
    if(content == NULL) return NULL;

    while(content[i] != '>')   i++;
    i++;

    while(strncmp(&(content[i+j]),end_tag, 4 ) != 0) j++;
    
    if(seek != NULL){
        *seek += (i+j+strlen(end_tag)+1);
    }

    if(strncmp(&(content[i]),end_tag, 4 ) == 0) return "";

    char* returnValue = (char*)calloc(j, sizeof(char));
    strncpy(returnValue, &(content[i]),j);

    free(init_tag);
    free(end_tag);

    return returnValue;
}

char* buildTag(tag_position type, char* tagName){
    char* tag;
    
    if(type == OPEN){
        tag = (char*)calloc((strlen(tagName)+2), sizeof(char));
        strcat(tag, "<");
    } else {
        tag = (char*)calloc((strlen(tagName)+4), sizeof(char));
        strcat(tag, "</");
    }

    return strcat(tag, tagName);
}