#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef STR_HEADER
#define STR_HEADER


#define STR_FUNCTION static inline
typedef struct {
    char *c_string;
    uint32_t length;
} Str;

STR_FUNCTION Str str_new(char *string);
STR_FUNCTION Str str_concat(Str str1, Str str2);
STR_FUNCTION Str str_upper(Str str);
STR_FUNCTION Str str_capitalize(Str str);
STR_FUNCTION Str str_lower(Str str);
STR_FUNCTION Str str_copy(Str str);
STR_FUNCTION Str str_substr(Str str, uint32_t start, uint32_t end);
STR_FUNCTION Str str_new_from_string(char *allocated_string);
STR_FUNCTION Str str_pad_right(Str str, char padding, uint32_t target_length);
STR_FUNCTION Str str_pad_left(Str str, char padding, uint32_t target_length);
STR_FUNCTION Str str_mult(Str str, uint32_t amount);
STR_FUNCTION Str str_from_file(FILE *file);
STR_FUNCTION Str str_push(Str str, char character);
STR_FUNCTION Str str_replace(Str str, char *dest, char *src);

STR_FUNCTION bool str_equals(Str str1, Str str2);
STR_FUNCTION char str_char_at(Str str1, int index);
STR_FUNCTION char str_pop(Str *str);
STR_FUNCTION void str_free(Str str);
STR_FUNCTION void str_print(Str str);

#define STR_ERROR(format, ...) do{printf("\033[31mStr error: \033[0m"); printf (format, ##__VA_ARGS__);exit(1);}while(0)
#define STR_C(str) str.c_string
#define STR_NEW(str) str_new(str)

#endif

#ifdef STR_HEADER_IMPLEMENTATION

STR_FUNCTION Str str_new(char *string) {
    Str str;
    char *c_string = malloc(sizeof(char) * strlen(string));
    for (int i = 0; i < strlen(string); i++) {
        c_string[i] = string[i];
    }
    str.c_string = c_string;
    str.length = strlen(string);
    return str;
}

STR_FUNCTION Str str_concat(Str str1, Str str2) {
    char *new_str = realloc(str1.c_string, sizeof(char) * (str1.length + str2.length));
    for (int s1 = 0; s1 < str1.length; s1++) {
        new_str[s1] = str1.c_string[s1];
    }    
    for (int s2 = str1.length; s2 < str1.length+str2.length; s2++) {
        new_str[s2] = str2.c_string[s2 - str1.length];
    }    
    str1.length = str1.length + str2.length;
    str1.c_string = new_str;
    return str1;
}

STR_FUNCTION Str str_copy(Str str) {
    return str_new(str.c_string);
}

STR_FUNCTION Str str_upper(Str str) {
    Str return_str;
    for (int i = 0; i < str.length; i++) {
        if (islower(str.c_string[i])) {
            str.c_string[i] -= 32;
        }
    }
    return_str = str_copy(str);
    str_free(str);
    return return_str;
}

STR_FUNCTION Str str_capitalize(Str str) {
    Str return_str;
    if (islower(str.c_string[0])) {
        str.c_string[0] -= 32;
    }
    return_str = str_copy(str);
    str_free(str);
    return return_str;
}

STR_FUNCTION Str str_lower(Str str) {
    Str return_str;
    for (int i = 0; i < str.length; i++) {
        if (isupper(str.c_string[i])) {
            str.c_string[i] += 32;
        }
    }
    return_str = str_copy(str);
    str_free(str);
    return return_str;
}

STR_FUNCTION char str_char_at(Str str, int index) {
    if (index < 0) {
        index += str.length;
    }
    if (index > str.length) {
        STR_ERROR("Index out of range\n");
    }
    return str.c_string[index];
}

STR_FUNCTION Str str_new_from_string(char *allocated_string) {
    Str str;
    str.c_string = allocated_string;
    str.length = strlen(allocated_string);
    return str;
}

STR_FUNCTION Str str_substr(Str str, uint32_t start, uint32_t end) {
    if (start > str.length || end > str.length) {
        STR_ERROR("Index out of range\n");
    }
    char *new_c_string = malloc(sizeof(char) * (end - start));
    for (int i = start; i < end; i++) {
        new_c_string[i] = str.c_string[i];
    }
    return str_new_from_string(new_c_string);
}

STR_FUNCTION Str str_pad_right(Str str, char padding, uint32_t target_length) {
    while (str.length <= target_length) {
        str.length++;
        str.c_string = realloc(str.c_string, str.length);
        str.c_string[str.length - 1] = padding;
    }
    str.c_string[str.length-1] = '\0';
    str.length = strlen(str.c_string);
    return str;
}

STR_FUNCTION Str str_pad_left(Str str, char padding, uint32_t target_length) {
    str.c_string = realloc(str.c_string, sizeof(char) * target_length);
    char *copy = malloc(sizeof(char) * str.length);
    strcpy(copy, str.c_string);
    for (int i = 0; i <= target_length; i++) {
        str.c_string[i] = ' ';
    }

    for (int z = 0; z <= target_length; z++) {
        str.c_string[z] = padding;
    }

    for (int i = 0; i <= str.length; i++) {
        str.c_string[target_length-i] = copy[str.length - i];
    }
    str.length = strlen(str.c_string);
    free(copy);
    return str;
}

STR_FUNCTION Str str_mult(Str str, uint32_t amount) {
    str.c_string = realloc(str.c_string, str.length * amount);
    char *copy = malloc(sizeof(char) * str.length);
    strcpy(copy, str.c_string);

    for (int i = str.length; i < str.length * amount; i++) {
        str.c_string[i] = copy[i % str.length];
    }

    str.length = strlen(str.c_string);
    free(copy);
    return str;
}

STR_FUNCTION Str str_from_file(FILE *file) {
    fseek(file, 0, SEEK_END);
    size_t length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *buffer = malloc(length);
    fread(buffer, 1, length, file);
    return str_new_from_string(buffer);
}

STR_FUNCTION Str str_push(Str str, char character) {
    str.c_string = realloc(str.c_string, sizeof(char) * (str.length + 1));
    str.length++;
    str.c_string[str.length-1] = character;
    return str;
}

STR_FUNCTION Str str_replace(Str str, char *dest, char *src) {
    return str;
}

STR_FUNCTION char str_pop(Str *str) {
    char character = str->c_string[str->length - 1];
    str->c_string = realloc(str->c_string, sizeof(char) * (str->length - 1));
    str->length--;
    str->c_string[str->length] = '\0';
    return character;
}

STR_FUNCTION bool str_equals(Str str1, Str str2) {
    return strcmp(str1.c_string, str2.c_string) == 0;
}

STR_FUNCTION void str_free(Str str) {
    free(str.c_string);
}

STR_FUNCTION void str_print(Str str) {
    printf("%s\n", str.c_string);
}

#endif