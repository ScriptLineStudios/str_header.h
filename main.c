#include <stdio.h>
#define STR_HEADER_IMPLEMENTATION
#include "str_header.h"

int main(void) {
    Str str = str_new("Hello World this is a test!");

    for (int i = 0; i < 6; i++) {
        Str tok = str_token(&str, ' ');
        printf("%s\n", tok.string);
        str_free(tok);
    }

    str_free(str);
    return 0;
}