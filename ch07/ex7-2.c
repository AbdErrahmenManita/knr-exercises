#include <ctype.h>
#include <stdio.h>
#define MAXLINE 80
void read_input(void);
int main(void) {
    read_input();
    return 0;
}
void read_input(void) {
    int c;
    int cursor = 0;
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            putchar(c);
            cursor = 0;
            continue;
        } else if (isprint(c)) {
            if (cursor == MAXLINE) {
                putchar('\n');
                cursor = 0;
            }
            putchar(c);
            cursor++;
        } else {
            if (cursor + 4 > MAXLINE) {
                putchar('\n');
                cursor = 0;
            }
            printf("\\%03o", c);
            cursor += 4;
        }
    }
}
