#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
void entab(int *, int);
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
            fprintf(stderr, "arguments are not in ascending order !!!");
            exit(1);
        }
        previous_val = stops[nb_stops++];
    }
    entab(stops, nb_stops);
    // printf("Detab done !!!\n");
    return 0;
}

int get_next_stop(int *tab, int maxsize, int curr) {
    for (int i = 0; i < maxsize; i++) {
        if (tab[i] > curr) {
            return tab[i];
        }
    }
    return (curr / 8 + 1) * 8;
}

void entab(int *tab, int maxsize) {
    int printed_char = 0;
    int blanks_count = 0;
    int next_stop = 0;
    int c;
    while ((c = getchar()) != EOF) {
        next_stop = get_next_stop(tab, maxsize, printed_char);
        switch (c) {
        case ' ':
            if (printed_char + 1 == next_stop) {
                printf("[TAB %d]", printed_char);
                blanks_count = 0;
            } else {
                blanks_count++;
            }
            printed_char++;
            break;

        case '\t':
            printf("[TAB]");
            printed_char = next_stop;
            blanks_count = 0;
            break;

        default:
            while (blanks_count != 0) {
                printf("[BLANK]");
                blanks_count--;
            }
            putchar(c);
            printed_char++;
            if (c == '\n') {
                printed_char = 0;
            }
            break;
        }
    }
}
int my_atoi(char *s) {
    int n = 0;
    while (*s != '\0') {
        if (!isdigit(*s)) {
            fprintf(stderr, "ERROR: Invalid arguments!!!");
            exit(1);
        }
        n = n * 10 + (*s - '0');
        s++;
    }
    return n;
}
