#include <string.h>
#include <stdlib.h>

typedef enum {
    OPEN,
    CLOSE
} tag_position;

char* readDataFromTag(char* buffer, char* tag, int* seek);
char* buildTag(tag_position type, char* tagName);