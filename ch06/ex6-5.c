#include <stdlib.h>
#include <string.h>
#define HASHSIZE 101
struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};
static struct nlist *hashtab[HASHSIZE];
int main(void) { return 0; }
unsigned hash(char *s) {
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
        hashval = (unsigned int)*s + 31 * hashval;
    return hashval % HASHSIZE;
}

struct nlist *lookup(char *s) {
    struct nlist *np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;
    return NULL;
}

struct nlist *lookup(char *);
char *strdup(char *);

struct nlist *install(char *name, char *defn) {
    struct nlist *np;
    unsigned hashval;
    if ((np = lookup(name)) == NULL) {
        np = (struct nlist *)malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else
        free(np->defn);
    if ((np->defn = strdup(defn)) == NULL)
        return NULL;
    return np;
}

void undef(char *name) {
    struct nlist *np;
    struct nlist dummy;
    unsigned int index = hash(name);
    np = hashtab[index];
    dummy.defn = NULL;
    dummy.name = NULL;
    dummy.next = np;
    struct nlist *prev = &dummy;
    while (np) {
        if (strcmp(np->name, name) == 0) {
            // struct nlist *temp=np;
            prev->next = np->next;
            np->next = NULL;
            free(np->name);
            free(np->defn);
            free(np);
            break;
        }
        prev = np;
        np = np->next;
    }
    hashtab[index] = dummy.next;
}
