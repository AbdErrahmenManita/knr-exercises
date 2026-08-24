#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
void detab(int *, int);
int my_atoi(char *);
int main(int argc, char *argv[]) {
    int stops[100];
    int nb_stops = 0;
    int previous_val = 0;
    // printf("%s\n", *argv);
    while (--argc > 0) {
        // printf("%s\n", *argv);
        stops[nb_stops] = my_atoi(*++argv);
        if (stops[nb_stops] <= previous_val) {
            printf("arguments are not in ascending order !!!");
            exit(1);
        }
        previous_val = stops[nb_stops++];
    }

    detab(stops, nb_stops);
    // printf("Detab done !!!\n");
    return 0;
}

void detab(int *tab, int maxsize) {
    int printed_char = 0;
    int used_stop = 0;
    int c;
    while ((c = getchar()) != EOF) {
        if (c != '\t') { // print characters while they are not a tab
            putchar(c);
            printed_char++;
            if (c == '\n') { // reset the counter when we go to a new line
                printed_char = 0;
                used_stop = 0;
            }
            continue;
        }
        while (used_stop < maxsize && tab[used_stop] <= printed_char) {
            used_stop++;
        }
        int diff = (used_stop < maxsize)
                       ? tab[used_stop] - printed_char
                       : (printed_char / 8) * 8 + 8 - printed_char;
        // printf(" %d ", diff);
        do {
            // printf("[Blank %d]", printed_char);
            putchar(' ');
            printed_char++;
        } while (--diff > 0);
    }
}

int my_atoi(char *s) {
    int n = 0;
    while (*s != '\0') {
        if (!isdigit(*s)) {
            printf("ERROR: Invalid arguments!!!");
            exit(1);
        }
        n = n * 10 + (*s - '0');
        s++;
    }
    return n;
}
