#ifndef PARSE_H
#define PARSE_H
#include "../main.h"
#include <stdio.h>

#define BUF 512

typedef enum {
    H1,
    H2,
    P,
    IMG,
} LineContentType;

typedef struct {
    char *h1;
    char *h2;
    char *p;
    char *bg;
} ColorHex;

typedef struct {
    LineContentType line_type;
    char *content;
} Line;

typedef struct {
    i32 number;
    Line *lines;
    usize lines_count;
    ColorHex colors;
} Slide;

typedef struct {
    bool inside_options;
    bool inside_slide;
    Slide *slides;
    usize slide_count;
    ColorHex colors;
} VisaParser;

void VisaParser_init(VisaParser *vp);

void parse(VisaParser *vp, FILE *file);

#endif
