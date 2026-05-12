#define ANALIB_IMPLEMENTATION
#include "main.h"
#include "gen/gen.h"
#include "utils.h"

#define BUF 512

void launch(char *src_file, char *dest_dir, bool doc_open) {
    FILE *file = fopen(src_file, "r");
    if (file == NULL) {
        ERROR("unable to open file");
    }

    VisaParser vp = {0};
    VisaParser_init(&vp);

    parse(&vp, file);

    fclose(file);

    // create gen folder
    char mkdir_cmd[BUF];
    snprintf(mkdir_cmd, sizeof(mkdir_cmd), "mkdir -p %s", dest_dir);
    system(mkdir_cmd);

    // generate
    gen(&vp, dest_dir);

    // open in browser if doc_open flag
    if (doc_open) {
        char cmd[BUF * 4];
        cmd[0] = '\0';
#ifdef __APPLE__
        strncat(cmd, "open ", BUF);

#elif defined(__linux__)
        strncat(cmd, "xdg-open ", size);

#else
        ERROR("Unknown or non-unix platform detected\n");
#endif
        char path[BUF * 2];
        snprintf(path, sizeof(path), "%s/0.html", dest_dir);
        strncat(cmd, path, BUF);
        system(cmd);
    }
}

i32 main(i32 argc, char *argv[]) {
    char *src_file = NULL;
    char *dest_dir = NULL;
    i32 open = 0;

    char *err_msg = "visa -s <src_file> -d <dest_dir> [-o: open in browser]\n";

    i32 opt;

    while ((opt = getopt(argc, argv, "s:d:o")) != -1) {
        switch (opt) {
            case 's':
                src_file = optarg;
                break;
            case 'd':
                dest_dir = optarg;
                break;
            case 'o':
                open = 1;
                break;
            default:
                fprintf(stderr, "%s", err_msg);
                return 1;
        }
    }

    if (src_file == NULL || dest_dir == NULL) {
        fprintf(stderr, "%s", err_msg);
        return 1;
    }

    launch(src_file, dest_dir, open);

    return 0;
}
