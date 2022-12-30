
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#define MAX_COL_DEF  85
#define WORD_BUFSIZE 255

void die(const char* fmt, ...) {
    va_list va;
    va_start(va, fmt);

    vfprintf(stderr, fmt, va);

    va_end(va);
    exit(1);
}

int main(int argc, char** argv) {
    int error      = 0;
    int in_place   = 0;
    int max_col    = MAX_COL_DEF;
    char* filename = NULL;

    /* Read arguments */
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] != '-')
            continue;

        switch (argv[i][1]) {
            case 'c':
                if (i + 1 >= argc) {
                    fprintf(stderr, "Error. Not enough arguments for \"-c\".\n");
                    error = 1;
                    break;
                }

                max_col = atoi(argv[++i]);

                /* We tried to use -c but max_col is 0. Invalid number. */
                if (max_col == 0) {
                    fprintf(stderr, "Error. Invalid column number for \"-c\".\n");
                    error = 1;
                    break;
                }

                break;
            case 'f':
                if (i + 1 >= argc) {
                    fprintf(stderr, "Error. Not enough arguments for \"-f\".\n");
                    error = 1;
                    break;
                }

                filename = argv[++i];
                break;
            case 'i':
                /* TODO */
                die("The \"-i\" option is not implemented. Feel free to make a PR "
                    "at:\n"
                    "https://github.com/r4v10l1/text-formatter\n");

                in_place = 1;
                break;
            case 'h':
                error = 1; /* "-h" */
                break;
            case '\0': /* "-", no other char */
                fprintf(stderr, "Unknown option: \'-\'.\n");
                error = 1;
                break;
            default:
                fprintf(stderr, "Unknown option: \'%c\'.\n", argv[i][1]);
                error = 1;
                break;
        }
    }

    if (in_place && !filename) {
        fprintf(stderr, "Error. Can't use \"-i\" without \"-f\".\n");
        error = 1;
    }

    if (error)
        die("Usage:\n"
            "    %s               - Format stdin to stdout\n"
            "    %s -c <cols>     - Specify the max column number\n"
            "    %s -f <file>     - Read from file and write to stdout\n"
            "    %s -f <file> -i  - Read from file and write in-place (to that same "
            "file)\n",
            argv[0], argv[0], argv[0], argv[0]);

    FILE* fd = stdin;
    if (filename) {
        fd = fopen(filename, (in_place) ? "rw" : "r");

        if (!fd)
            die("Error. Can't find file: %s\n", filename);
    }

    /* Actual formatting */
    char last_word[WORD_BUFSIZE] = { 0 };
    int c = 0, last_c = 0, word_p = 0, line_p = 0, last_space = 0;
    while ((c = getc(fd)) != EOF) {
        if (c == ' ') {
            /* Once reach a space, put the previous one or a newline if we have
             * space. Then put the word. < because we don't count the space after
             * the word as the word length */
            if (line_p <= max_col) {
                if (last_space != 0)
                    putc(last_space, stdout);

                /* Reset pos in the line */
                if (last_space == '\n')
                    line_p = word_p;
            } else {
                if (last_space != 0)
                    putc('\n', stdout);

                /* Reset pos in the line */
                line_p = word_p;
            }

            /* TODO: "-i", change stdout from putc's */
            /* From 0 to the last char we wrote to last_word[] */
            for (int i = 0; i < word_p; i++)
                putc(last_word[i], stdout);

            /* Reset word pos for next word */
            word_p = 0;

            /* Save ' ' or '\n' as the last space */
            last_space = c;
        } else if (c == '\n') {
            putc(last_space, stdout);

            /* Reset pos in the line */
            line_p = 0;

            for (int i = 0; i < word_p; i++)
                putc(last_word[i], stdout);

            /* Reset word pos for next word */
            word_p = 0;

            /* Save ' ' or '\n' as the last space */
            last_space = c;
        } else {
            if (word_p >= WORD_BUFSIZE)
                die("Error. Tried to overflow the last_word buffer. Try increasing "
                    "WORD_BUFSIZE\n");

            /* If we are not reading a space, save the chars */
            last_word[word_p++] = c;
        }

        /* Only used to check if the last char before EOF was \n or ' ' */
        last_c = c;

        /* Current pos in the current line */
        line_p++;
    }

    if (word_p > 0)
        for (int i = 0; i < word_p; i++)
            putc(last_word[i], stdout);

    if (last_c == '\n' || last_c == ' ')
        putc(last_c, stdout);

    if (filename)
        fclose(fd);

    return 0;
}

