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
  int number;
  Line *lines;
  size_t lines_count;
  ColorHex colors;
} Slide;

typedef struct {
  bool inside_options;
  bool inside_slide;
  Slide *slides;
  size_t slide_count;
  ColorHex colors;
} VisaParser;

void VisaParser_init(VisaParser *vp);

void parse(VisaParser *vp, FILE *file);
