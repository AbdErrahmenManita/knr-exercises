#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HASHSIZE 101
#define MAXWORD 100

struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};

void read_file(void);
int getword(char *, int);
void *xmalloc(size_t);
int handle_name(char *);
int handle_defn(char *);
struct nlist *install(char *, char *);
unsigned hash(char *);
struct nlist *lookup(char *);
char *strdup(char *);
void check_word(char *);
void free_hashtable(void);

enum {
    ONECHAR,
    SKIPPEDDEFINE,
    SKIPPEDCOMMENT,
    CHECKWORD,
    ADDEDDEFINITION,
    SKIPPEDQUOTES
};

int main(void) {
    read_file();
    free_hashtable();
    return 0;
}

void read_file(void) {
    char word[MAXWORD];
    int message;
    while ((message = getword(word, MAXWORD)) != EOF) {
        if (message == CHECKWORD) {
            check_word(word);
        }
    }
}
int getword(char *word, int lim) {
    int c;
    int prev = '\0';
    int target_quotes = '\0';
    char *w = word;
    while (isspace(c = getchar()))
        putchar(c);
    if (c == EOF)
        return EOF;

    if (c == '#') {
        putchar(c);
        while ((c = getchar()) != EOF && isalpha(c)) {
            *w++ = (char)c;
        }
        *w = '\0';
        if (c != EOF)
            ungetc(c, stdin);
        printf("%s", word);
        if (strcmp("define", word) == 0) {
            char *name = (char *)xmalloc(MAXWORD * sizeof(char));
            char *defn = (char *)xmalloc(MAXWORD * sizeof(char));
            if (handle_name(name) == 0) {
                free(name);
                free(defn);
                return SKIPPEDDEFINE;
            }
            handle_defn(defn);
            struct nlist *def = install(name, defn);
            if (def == NULL) {
                fprintf(stderr,
                        "\nerror while adding a definition to the hashtable\n");
            }
            free(name);
            free(defn);
        } else {
            while ((c = getchar()) != EOF && c != '\n') {
                putchar(c);
            }
            if (c != EOF)
                putchar(c);
        }

    } else if (c == '/') {
        putchar(c);
        c = getchar();
        putchar(c);
        switch (c) {
        case '/':
            while ((c = getchar()) != EOF && c != '\n')
                putchar(c);
            if (c != EOF) {
                putchar(c);
            }
            return SKIPPEDCOMMENT;
        case '*':
            while ((c = getchar()) != EOF && !(prev == '*' && c == '/')) {
                putchar(c);
                prev = c;
            }
            if (c != EOF) {
                putchar(c);
            }
            return SKIPPEDCOMMENT;
        default:
            break;
        }
    } else if (c == '"' || c == '\'') {
        putchar(c);
        target_quotes = c;
        while ((c = getchar()) != EOF && c != target_quotes) {
            putchar(c);
            if (c == '\\' && (c = getchar()) != EOF)
                putchar(c);
        }
        if (c != EOF)
            putchar(c);
        return SKIPPEDQUOTES;
    } else if (isalpha(c) || c == '_') {
        *w++ = (char)c;
        while (--lim > 0 && (c = getchar()) != EOF && c != '\n' &&
               (isalnum(c) || c == '_')) {
            *w++ = (char)c;
        }
        *w = '\0';
        if (c != EOF && lim != 0)
            ungetc(c, stdin);
        return CHECKWORD;
    } else if (c == '\\') {
        putchar(c);
        if (c != EOF)
            putchar(getchar());
    } else {
        putchar(c);
    }
    return ONECHAR;
}

int handle_name(char *name) {
    int c;
    char *w = name;
    int i = 0;
    *w = '\0';

    while ((c = getchar()) == ' ' || c == '\t')
        putchar(c);
    if (isalpha(c) || c == '_') {
        *w++ = (char)c;
        putchar(c);
        while ((c = getchar()) != EOF && c != '\n' &&
               (isalnum(c) || c == '_')) {
            putchar(c);
            if (i++ < MAXWORD - 1)
                *w++ = (char)c;
        }
        *w = '\0';

        if (c == ' ' || c == '\t') {
            putchar(c);
            return 1;
        }
    }
    while (c != EOF && c != '\n') {
        putchar(c);
        c = getchar();
    }
    if (c == '\n')
        putchar(c);
    return 0;
}
int handle_defn(char *defn) {
    int c;
    char *w = defn;
    int i = 0;
    *w = '\0';
    while ((c = getchar()) == ' ' || c == '\t')
        putchar(c);
    if (c != EOF && c != '\n') {
        *w++ = (char)c;
        putchar(c);
        while ((c = getchar()) != EOF && c != '\n') {
            putchar(c);
            if (i++ < MAXWORD - 1)
                *w++ = (char)c;
        }
        while (*(w - 1) == ' ' || *(w - 1) == '\t')
            w--;
        *w = '\0';
    }
    if (c != EOF)
        putchar(c);
    return 1;
}

static struct nlist *hashtab[HASHSIZE] = {0};
unsigned hash(char *s) {
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
        hashval = ((unsigned int)*s) + 31 * hashval;
    return hashval % HASHSIZE;
}

struct nlist *lookup(char *s) {
    struct nlist *np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;
    return NULL;
}

struct nlist *install(char *name, char *defn) {
    struct nlist *np;
    unsigned hashval;
    if ((np = lookup(name)) == NULL) {
        np = (struct nlist *)xmalloc(sizeof(*np));
        np->name = strdup(name);
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else {
        free(np->defn);
    }
    np->defn = strdup(defn);
    return np;
}

void check_word(char *name) {
    int c;
    struct nlist *np = lookup(name);
    if (np == NULL) {
        printf("%s", name);
        while ((c = getchar()) != EOF && c != '\n' &&
               (isalnum(c) || c == '_')) {
            putchar(c);
        }
    } else {
        printf("%s", np->defn);
        while ((c = getchar()) != EOF && c != '\n' &&
               (isalnum(c) || c == '_')) {
        }
    }
    if (c != EOF)
        ungetc(c, stdin);
}

char *strdup(char *string) {
    size_t len = strlen(string) + 1;
    char *res = xmalloc(len * sizeof(char));
    char *end = res;
    while ((*end++ = *string++) != '\0')
        ;
    return res;
}
void *xmalloc(size_t len) {
    void *temp = malloc(len);
    if (temp == NULL) {
        fprintf(stderr, "Allocation Error !\n");
        exit(EXIT_FAILURE);
    }
    return temp;
}
void free_liste(struct nlist *np) {
    if (np == NULL)
        return;
    free_liste(np->next);
    free(np->name);
    free(np->defn);
    free(np);
}
void free_hashtable(void) {
    for (int i = 0; i < 100; i++) {
        free_liste(hashtab[i]);
        hashtab[i] = NULL;
    }
}
