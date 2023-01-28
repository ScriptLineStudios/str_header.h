# str_header.h
A header only C string library

| Function                                  | Description                                                            |
| :------------                             |   :---:                                                                |
| ```Str str_new(char *string)```           | Returns a new string                                                   | 
| ```Str str_concat(Str str1, Str str2)```  | Concatenates 2 strings and returns a new string                        |
| ```Str str_upper(Str str)```              | Returns an uppercase version of the string                             |
| ```Str str_lower(Str str)```              | Returns an lowercase version of the string                             |
| ```Str str_capitalize(Str str)```         | Returns a string with the first letter capitalized                     |
