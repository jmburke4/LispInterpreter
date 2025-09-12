#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int lex(const char *str, const char **start, const char **end)
{
    const char *ws = " \t\r\n";
    const char *delim = "() \t\r\n";
    const char *prefix = "()'`";

    str += strspn(str, ws);

    if (str[0] == '\0') {
        *start = *end = NULL;
        return 1;
    }

    *start = str;

    if (strchr(prefix, str[0]) != NULL)
        *end = *start + 1;
    else
        *end = *start + strcspn(str, delim);

    return 0;
}

int main (){
    const char *input = "(foo bar 17 '(a b c) 2)";

    char *token;
    char *p = input;

    lex(p, &token, &p);

    while(token != NULL)
    {
        printf("%.*s\n", (int)(p - token), token);
        lex(p, &token, &p);
    }
}