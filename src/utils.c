

#include "env.h"
#include <stdio.h>
char *get_hex_from_line(char *line) {
    char buf[512];
    buf[0] = '\0';
    char *p;
    p = line;
    bool hex_found = false;
    int hex_counter = 0;
    while (*p != '\0') {
        if (*p == '#' || hex_found) {
            hex_found = true;
            strncat(buf, p, 1);
            hex_counter++;
        }
        if (hex_counter > 6) {
            break;
        }
        p++;
    }
    if (!hex_found) {
        ERROR("No hex was found at line: ");
    }
    return al_strdup(buf);
}

char *get_text_from_header_line(char *line) {
    char buf[512];
    buf[0] = '\0';
    char *p;
    p = line;
    bool header = false;
    while (*p != '\0') {
        if (!header) {
            if (*p == '(') {
                header = true;
                p++;
                continue;
            }
        }
        if (header) {
            if (*p == ')') {
                return al_strdup(buf);
            }
            strncat(buf, p, 1);
        }
        p++;
    }
    if (!header) {
        ERROR("No hex was found at line: ");
    }
    return NULL;
}
