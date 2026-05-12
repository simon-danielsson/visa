#include "../main.h"
#include "../utils.h"

#define BUF 512

/// content type of line
typedef enum {
    H1,
    H2,
    P,
    IMG,
} LineContentType;

/// colors
typedef struct {
    char *h1;
    char *h2;
    char *p;
    char *bg;
} ColorHex;

/// the contents of a line
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

static void Slide_init(Slide *s) {
    s->number = 0;
    s->lines = NULL;
    s->lines_count = 0;
}

static void Slide_push_line(Slide *s, Line *l) {
    Line *tmp = realloc(s->lines, (s->lines_count + 1) * sizeof(Line));

    if (!tmp) {
        ERROR("Allocation failure");
        return;
    }

    s->lines = tmp;
    s->lines[s->lines_count] = *l;
    s->lines_count++;
}

typedef struct {
    bool inside_options;
    bool inside_slide;
    Slide *slides;
    usize slide_count;
    ColorHex colors;
} VisaParser;

static void VisaParser_push_slide(VisaParser *vp, Slide *s) {
    Slide *tmp = realloc(vp->slides, (vp->slide_count + 1) * sizeof(Slide));

    if (!tmp) {
        ERROR("Allocation failure");
        return;
    }

    vp->slides = tmp;
    vp->slides[vp->slide_count] = *s;
    vp->slide_count++;
}

void VisaParser_init(VisaParser *vp) {
    vp->inside_options = false;
    vp->inside_slide = false;
    vp->slides = NULL;
    vp->slide_count = 0;
    vp->colors.h1 = "#000000";
    vp->colors.h2 = "#000000";
    vp->colors.p = "#000000";
    vp->colors.bg = "#ffffff";
}

static void VisaParser_print(VisaParser *vp) {
    printf("\n");
    for (usize i = 0; i < vp->slide_count; i++) {
        printf("SLIDE %d\n", vp->slides[i].number);
        for (usize j = 0; j < vp->slides[i].lines_count; j++) {
            printf("%s\n", vp->slides[i].lines[j].content);
        }
    }
}

void parse(VisaParser *vp, FILE *file) {
    char line[BUF];
    i32 i = 0;

    Slide tmp_s = {0};
    Slide_init(&tmp_s);

    while (fgets(line, sizeof(line), file)) {
        // increment line
        i++;

        // debug print each line
        // printf("%-3d│ %s", i, line);

        // slides --------------------------------------------------------------

        if (al_starts_with_no_w(line, "s {") && !vp->inside_options &&
                !vp->inside_slide) {
            // printf("found slide\n");
            vp->inside_slide = true;
            tmp_s.number = vp->slide_count;
            tmp_s.colors = vp->colors;
            continue;
        }

        if (vp->inside_slide) {
            if (al_starts_with_no_w(line, "h1(")) {
                Slide_push_line(&tmp_s,
                        &(Line){.line_type = H1,
                        .content = get_text_from_header_line(line)});

            } else if (al_starts_with_no_w(line, "h2(")) {
                Slide_push_line(&tmp_s,
                        &(Line){.line_type = H2,
                        .content = get_text_from_header_line(line)});

            } else if (al_starts_with_no_w(line, "img(")) {
                Slide_push_line(&tmp_s,
                        &(Line){.line_type = IMG,
                        .content = get_text_from_header_line(line)});

            } else if (al_starts_with_no_w(line, "}")) {
                vp->inside_slide = false;
                VisaParser_push_slide(vp, &tmp_s);
                Slide_init(&tmp_s);

            } else {
                Slide_push_line( // p
                        &tmp_s,
                        &(Line){.line_type = P, .content = al_strip_start_end(line)});
            }
        }

        // options -------------------------------------------------------------

        if (al_starts_with_no_w(line, "o {") && !vp->inside_options &&
                !vp->inside_slide) {
            // printf("found options\n");
            vp->inside_options = true;
            continue;
        }

        if (vp->inside_options) {
            if (al_starts_with_no_w(line, "h1")) {
                vp->colors.h1 = get_hex_from_line(line);
                continue;
            }
            if (al_starts_with_no_w(line, "h2")) {
                vp->colors.h2 = get_hex_from_line(line);
                continue;
            }
            if (al_starts_with_no_w(line, "p")) {
                vp->colors.p = get_hex_from_line(line);
                continue;
            }
            if (al_starts_with_no_w(line, "bg")) {
                vp->colors.bg = get_hex_from_line(line);
                continue;
            }
            if (al_starts_with_no_w(line, "}")) {
                vp->inside_options = false;
                continue;
            }
        }
    }
    // VisaParser_print(vp);
}
