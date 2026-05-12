#include "../main.h"
#include "../parser/parse.h"
#include "../utils.h"
#include "static.h"

typedef struct {
    char *name;
    char *link;
} Link;

Link derive_namelink_from_a(const char *line);
char **get_list_items(char *a_str);

void gen(VisaParser *vp, char *dest_dir) {

    char file_path[BUF];
    snprintf(file_path, sizeof(file_path), "%s/presentation.html", dest_dir);
    FILE *fp = fopen(file_path, "w");

    fprintf(fp, "%s\n", header);
    fprintf(fp, "<body>\n");

    for (usize i = 0; i < vp->slide_count; i++) {
        fprintf(fp, "<div class=\"slide\">\n");
        { // style
            fprintf(fp, "<style type=\"text/plain\">\n");
            fprintf(fp, "html, body {background-color: %s !important}\n",
                    vp->slides[i].colors.bg);
            fprintf(fp, "h1 {color: %s; font-size: clamp(3rem, 10vw, 10rem) }\n",
                    vp->slides[i].colors.h1);
            fprintf(fp, "h2 {color: %s}\n", vp->slides[i].colors.h2);

            fprintf(fp, "p, ul, li {color: %s}\n", vp->slides[i].colors.p);
            fprintf(fp, "</style>");
        }
        { // content
            fprintf(fp, "<div class=\"screen\">");

            for (usize j = 0; j < vp->slides[i].lines_count; j++) {
                switch (vp->slides[i].lines[j].line_type) {
                    case LIST: {
                                   char **l = get_list_items(vp->slides[i].lines[j].content);
                                   fprintf(fp, "<ul>");
                                   if (l) {
                                       int i;
                                       for (i = 0; *(l + i); i++) {
                                           fprintf(fp, "<li>%s</li>", *(l + i));
                                           free(*(l + i));
                                       }
                                       printf("\n");
                                       free(l);
                                   }
                                   fprintf(fp, "</ul>");
                               }
                    case A: {
                                Link l = derive_namelink_from_a(vp->slides[i].lines[j].content);
                                if (l.name && l.link) {
                                    fprintf(fp, "<a href=\"%s\" target=\"_blank\">%s</a>", l.link,
                                            l.name);
                                    free(l.name);
                                    free(l.link);
                                }
                            }
                            continue;
                    case H1:
                            fprintf(fp, "<h1>%s</h1>\n", vp->slides[i].lines[j].content);
                            continue;
                    case H2:
                            fprintf(fp, "<h2>%s</h2>\n", vp->slides[i].lines[j].content);
                            continue;
                    case IMG: {
                                  char cmd[BUF];
                                  snprintf(cmd, sizeof(cmd), "mkdir -p %s/static", dest_dir);
                                  system(cmd);
                                  cmd[0] = '\0';
                                  snprintf(cmd, sizeof(cmd), "cp %s %s/static",
                                          vp->slides[i].lines[j].content, dest_dir);
                                  system(cmd);
                              }
                              fprintf(fp, "<img src=\"static/%s\" alt=\"%s\">\n",
                                      al_strip_path(vp->slides[i].lines[j].content),
                                      al_strip_path(vp->slides[i].lines[j].content));
                              continue;

                    default:
                    case P:
                              fprintf(fp, "<p>%s</p>\n", vp->slides[i].lines[j].content);
                              continue;
                }
            }
            fprintf(fp, "</div>");
        }
        fprintf(fp, "</div>");
    }

    // footer and script
    fprintf(fp, "%s\n", footer);
    fprintf(fp, "</body>\n");
    fclose(fp);
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

Link derive_namelink_from_a(const char *line) {
    Link l = {0};

    char *copy = malloc(strlen(line) + 1);
    if (copy == NULL) {
        ERROR("malloc failed");
    }
    strcpy(copy, line);

    char *name = strtok(copy, ",");
    char *link = strtok(NULL, "");

    if (name == NULL || link == NULL) {
        free(copy);
        return l;
    }

    while (*link == ' ') {
        link++;
    }

    l.name = malloc(strlen(name) + 1);
    l.link = malloc(strlen(link) + 1);

    if (l.name == NULL || l.link == NULL) {
        free(l.name);
        free(l.link);
        free(copy);
        ERROR("Parsing error while deriving name and link from link() statement");
    }

    strcpy(l.name, name);
    strcpy(l.link, link);

    free(copy);
    return l;
}

char **get_list_items(char *a_str) {
    const char a_delim = ',';
    char **result = 0;
    size_t count = 0;
    char *tmp = a_str;
    char *last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;
    while (*tmp) {
        if (a_delim == *tmp) {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }
    count += last_comma < (a_str + strlen(a_str) - 1);
    count++;
    result = malloc(sizeof(char *) * count);
    if (result) {
        size_t idx = 0;
        char *token = strtok(a_str, delim);
        while (token) {
            while (*token == ' ') {
                token++;
            }
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        *(result + idx) = 0;
    }
    return result;
}
