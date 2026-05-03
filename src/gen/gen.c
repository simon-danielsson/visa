#include "../env.h"
#include "../parser/parse.h"
#include "../utils.h"
#include "static.h"

char *append_to_path(char *path, int to_append) {
    char to_append_as_str[64];
    snprintf(to_append_as_str, sizeof(to_append_as_str), "%d", to_append);

    size_t ext = strlen(".html");
    size_t output_size = strlen(path) + strlen(to_append_as_str) + 1 + 2 + ext;
    char *output = (char *)malloc(sizeof(char) * output_size);

    strcpy(output, path);
    strcat(output, "/");
    strcat(output, to_append_as_str);
    strcat(output, ".html");

    return output;
}

void gen(VisaParser *vp, char *dest_dir) {

    for (size_t i = 0; i < vp->slide_count; i++) {
        char *file_path = append_to_path(dest_dir, vp->slides[i].number);
        FILE *fp = fopen(file_path, "w");

        fprintf(fp, "%s\n", header_part1);
        // style
        fprintf(fp, ":root {\n");
        fprintf(fp, "--c_h1: %s;\n", vp->slides[i].colors.h1);
        fprintf(fp, "--c_h2: %s;\n", vp->slides[i].colors.h2);
        fprintf(fp, "--c_p: %s;\n", vp->slides[i].colors.p);
        fprintf(fp, "--c_bg: %s;\n", vp->slides[i].colors.bg);
        fprintf(fp, "}\n");
        fprintf(fp, "%s\n", header_part2);
        fprintf(fp, "<body>\n");
        // content
        fprintf(fp, "<main class=\"screen\">\n");
        for (size_t j = 0; j < vp->slides[i].lines_count; j++) {
            switch (vp->slides[i].lines[j].line_type) {
                case H1:
                    fprintf(fp, "<h1>%s</h1>\n", vp->slides[i].lines[j].content);
                    continue;
                case H2:
                    fprintf(fp, "<h2>%s</h2>\n", vp->slides[i].lines[j].content);
                    continue;
                case IMG: {
                              char relative_path_to_img[BUF];
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

        fprintf(fp, "</main>\n");
        // footer and script
        fprintf(fp, "%s\n", footer_part1);
        fprintf(fp, "const MAX_PAGE = %d\n", (int)vp->slide_count - 1);
        fprintf(fp, "%s\n", footer_part2);

        fprintf(fp, "</body>\n");

        fclose(fp);
    }
}

static void VisaParser_print(VisaParser *vp) {
    printf("\n");
    for (size_t i = 0; i < vp->slide_count; i++) {
        printf("SLIDE %d\n", vp->slides[i].number);
        for (size_t j = 0; j < vp->slides[i].lines_count; j++) {
            printf("%s\n", vp->slides[i].lines[j].content);
        }
    }
}
