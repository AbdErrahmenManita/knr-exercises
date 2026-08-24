#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void detab(int *, int, int, int);
int my_atoi(char *);
int main(int argc, char *argv[]) {

    // default variables
    int start_col = 0;
    int tab_width = 8;
    int nb_stops = 0;

    // stops index backet
    int stops[100];
    int previous_val = 0;

    // check variables for arguments
    char has_m = 0;
    char has_n = 0;
    char has_arg = 0;
    while (--argc > 0) {
        ++argv;
        switch ((*argv)[0]) {
        case '-':
            if (has_m || has_arg) {
                fprintf(stderr, "ERROR: Wrong command!!!\n");
                exit(1);
            }
            start_col = my_atoi(++(*argv));
            has_m = 1;
            break;
        case '+':
            if (has_n || has_arg) {
                fprintf(stderr, "ERROR: Wrong command\n");
                exit(1);
            }
            tab_width = my_atoi(++(*argv));
            if (tab_width == 0) {
                fprintf(stderr, "ERROR: Tab Width can't be <= 0\n");
                exit(1);
            }
            has_n = 1;
            break;
        default:
            if (nb_stops == 100) {
                fprintf(stderr, "Number of arguments allowed exceeded\n");
                exit(1);
            }
            if (has_m || has_n) {
                fprintf(stderr, "Wrong command !!!\n");
                exit(1);
            }
            stops[nb_stops] = my_atoi(*argv);
            if (previous_val >= stops[nb_stops]) {
                fprintf(stderr,
                        "ERROR: arguments should be in ascending order !!!\n");
                exit(1);
            }
            previous_val = stops[nb_stops++];
            has_arg = 1;
            break;
        }
    }
    detab(stops, nb_stops, start_col, tab_width);
    // printf("Detab done !!!\n");
    return 0;
}

int get_next_stop(int *tab, int maxsize, int curr, int start_col,
                  int tab_width) {
    for (int i = 0; i < maxsize; i++) {
        if (tab[i] > curr) {
            return tab[i];
        }
    }
    if (curr < start_col) {
        int next_default = (curr / 8 + 1) * 8;
        return (next_default >= start_col) ? start_col : next_default;
    }
    return start_col + ((curr - start_col) / tab_width + 1) * tab_width;
}

void detab(int *tab, int maxsize, int start_col, int tab_width) {
    int printed_char = 0;
    int c;
    while ((c = getchar()) != EOF) {
        if (c != '\t') { // print characters while they are not a tab
            putchar(c);
            printed_char++;
            if (c == '\n') { // reset the counter when we go to a new line
                printed_char = 0;
            }
            continue;
        }
        int next_stop =
            get_next_stop(tab, maxsize, printed_char, start_col, tab_width);
        while (printed_char < next_stop) {
            printf("[BLANK %d]", printed_char);
            printed_char++;
        }
    }
}

int my_atoi(char *s) {
    if (strlen(s) == 0) {
        fprintf(stderr, "Empty Flag\n");
        exit(1);
    }
    int n = 0;
    while (*s != '\0') {
        if (!isdigit(*s)) {
            fprintf(stderr, "ERROR: Invalid arguments!!!\n");
            exit(1);
        }
        n = n * 10 + (*s - '0');
        s++;
    }
    return n;
}
