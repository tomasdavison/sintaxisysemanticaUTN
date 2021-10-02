#include "string_aux.h"

char *strsepm( char **stringp, const char *delim ) {
    char *begin, *end;
    begin = *stringp;
    
    if  ( begin == NULL ) return NULL;

    end = strstr( begin , delim );

    if ( end != NULL ) {
        *end = '\0';
        end  += strlen( delim );
        *stringp = end;
    } else {
        *stringp = NULL;  
    }

    return begin;
}