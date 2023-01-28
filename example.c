#define STR_HEADER_IMPLEMENTATION
#include "str_header.h"

#include <stdio.h>

int main(void) {
    Str str = str_new("Hello");
    printf("%s\n", STR_C(str));

    str = str_concat(str, str_new(" World!"));
    printf("%s\n", STR_C(str));

    str_free(str);
    return 0;
}