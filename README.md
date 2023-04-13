# str_header.h
## A header only C string library

```C
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
```


| Function                                                                  | Description                                                            |
| :------------                                                             |   :---:                                                                |
| ```Str str_new(char *string)```                                           | Returns a new string                                                   | 
| ```Str str_concat(Str str1, Str str2)```                                  | Concatenates 2 strings and returns a new string                        |
| ```Str str_upper(Str str)```                                              | Returns an uppercase version of the string                             |
| ```Str str_lower(Str str)```                                              | Returns an lowercase version of the string                             |
| ```Str str_capitalize(Str str)```                                         | Returns a string with the first letter capitalized                     |
| ```Str str_copy(Str str)```                                               | Returns a new copy of the string                                       |
| ```Str str_substr(Str str, uint32_t start, uint32_t end)```               | Returns a substring of the string                                      |
| ```Str str_new_from_string(char *allocated_string)```                     | Returns a new string from an already allocated char *                  |
| ```Str str_pad_right(Str str, char padding, uint32_t target_length)```    | Returns a new string padded to the right to the target length          |
| ```Str str_pad_left(Str str, char padding, uint32_t target_length)```     | Returns a new string padded to the left to the target length           |
| ```Str str_mult(Str str, uint32_t amount)```                              | Returns a new string with length multiplyed by the amount              |
| ```Str str_from_file(FILE *file)```                                       | Returns a new string with the contents of the file read                |
| ```Str str_push(Str str, char character)```                               | Pushes a character to the end of the string                            |
| ```bool str_equals(Str str1, Str str2)```                                 | Returns weather the 2 strings have equal value or not                  | 
| ```char str_char_at(Str str, int index)```                                | Returns the char at the given index, also allows negative indexing     |
| ```char str_pop(Str *str)```                                              | Pops the top character from the string                                 |
| ```char str_print(Str str)```                                             | Prints the string to stdout                                            |  
| ```char str_free(Str str)```                                              | Frees the string from memory                                           |  
