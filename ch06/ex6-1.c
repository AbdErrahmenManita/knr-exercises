#include <ctype.h>
#include <stdio.h>
#include <string.h>
#define MAXWORD 100
struct key {
    char *word;
    int count;
} keytab[] = {{"auto", 0},
              {"break", 0},
              {"case", 0},
              {"char", 0},
              {"const", 0},
              {"continue", 0},
              {"default", 0},
              /* ... */
              {"unsigned", 0},
              {"void", 0},
              {"volatile", 0},
              {"while", 0}};
#define NKEYS (int)(sizeof(keytab) / sizeof(struct key))
int getword(char *, int);
int binsearch(char *, struct key *, int);
/* count C keywords */
int main(void) {
    int n;
    char word[MAXWORD];
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]) || word[0] == '_')
            if ((n = binsearch(word, keytab, NKEYS)) >= 0)
                keytab[n].count++;
    for (n = 0; n < NKEYS; n++)
        if (keytab[n].count > 0)
            printf("%4d %s\n", keytab[n].count, keytab[n].word);
    return 0;
}
/* binsearch: find word in tab[0]...tab[n-1] */
int binsearch(char *word, struct key tab[], int n) {
    int cond;
    int low, high, mid;
    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if ((cond = strcmp(word, tab[mid].word)) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

int getword(char *word, int lim) {
    int c, opened_quotes;
    char *end = word;
    while (isspace(c = getchar()))
        ;
    switch (c) {
    case EOF:
        return c;
    case '/':
        c = getchar();
        if (c == '/') {
            while ((c = getchar()) != EOF && c != '\n')
                ;
        } else if (c == '*') {
            int prev = 0;
            while ((c = getchar()) != EOF) {
                if (c == '/' && prev == '*')
                    break;
                prev = c;
            }
        } else {
            *end++ = '/';
            *end = '\0';
            ungetc(c, stdin);
            return '/';
        }
        return getword(word, lim);
    case '"':
    case '\'':
        opened_quotes = c;
        while ((c = getchar()) != EOF && c != opened_quotes) {
            if (c == '\\')
                getchar();
        }
        return getword(word, lim);
    case '#':
        while ((c = getchar()) != EOF && c != '\n')
            ;
        return getword(word, lim);
    default:
        *end++ = (char)c;
        if (!isalpha(c) && c != '_') {
            *end = '\0';
            return c;
        }
        for (; --lim > 0 && (c = getchar()) != EOF; end++) {
            if (!isalnum(c) && c != '_') {
                ungetc(c, stdin);
                break;
            }
            *end = (char)c;
        }
        *end = '\0';
    }
    return word[0];
}
