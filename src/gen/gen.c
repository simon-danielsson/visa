#include "../main.h"
#include "../parser/parse.h"
#include "../utils.h"
#include "static.h"

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

            fprintf(fp, "p {color: %s}\n", vp->slides[i].colors.p);
            fprintf(fp, "</style>");
        }
        { // content
            fprintf(fp, "<div class=\"screen\">");

            for (usize j = 0; j < vp->slides[i].lines_count; j++) {
                switch (vp->slides[i].lines[j].line_type) {
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
