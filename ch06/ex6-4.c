#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXWORD 100

struct tnode {
    char *word;
    int occurrence;
    struct tnode *left;
    struct tnode *right;
};
void *xmalloc(size_t);
int getword(char *, int);
void fill_tree(struct tnode **, char *, size_t);
void sort_tree_dec(struct tnode **, struct tnode *);
void free_tree(struct tnode *);
void write_tree(struct tnode *);
int main(void) {
    char word[MAXWORD];
    struct tnode *tree = NULL;
    while (getword(word, MAXWORD) != EOF) {
        size_t len = strlen(word);
        fill_tree(&tree, word, len + 1);
    }
    struct tnode *final_tree = NULL;
    sort_tree_dec(&final_tree, tree);
    free_tree(tree);
    write_tree(final_tree);
    free_tree(final_tree);
    return 0;
}
void *xmalloc(size_t size) {
    void *p = malloc(size);
    if (p == NULL) {
        fprintf(stderr, "Allocation error !\n");
        exit(EXIT_FAILURE);
    }
    return p;
}
void fill_tree(struct tnode **node, char *word, size_t len) {
    struct tnode **curr = node;
    while (*curr) {
        int cmp = strcmp((*curr)->word, word);
        if (cmp == 0) {
            (*curr)->occurrence++;
            return;
        } else if (cmp > 0) {
            curr = &(*curr)->left;
        } else {
            curr = &(*curr)->right;
        }
    }
    *curr = xmalloc(sizeof(struct tnode));
    (*curr)->word = xmalloc(len * sizeof(char));
    strcpy((*curr)->word, word);
    (*curr)->occurrence = 1;
    (*curr)->left = NULL;
    (*curr)->right = NULL;
    return;
}
void put_in_place(struct tnode **dest, struct tnode *src) {
    struct tnode **curr = dest;
    while (*curr) {
        int cmp = (*curr)->occurrence - src->occurrence;
        if (cmp < 0) {
            curr = &(*curr)->left;
        } else {
            curr = &(*curr)->right;
        }
    }
    *curr = xmalloc(sizeof(struct tnode));
    size_t len = strlen(src->word) + 1;
    (*curr)->word = xmalloc(len * sizeof(char));
    strcpy((*curr)->word, src->word);
    (*curr)->occurrence = src->occurrence;
    (*curr)->left = NULL;
    (*curr)->right = NULL;
    return;
}
void sort_tree_dec(struct tnode **dest, struct tnode *src) {
    if (src == NULL)
        return;
    put_in_place(dest, src);
    sort_tree_dec(dest, src->left);
    sort_tree_dec(dest, src->right);
    return;
}
void free_tree(struct tnode *tree) {
    if (tree == NULL)
        return;
    free_tree(tree->left);
    free_tree(tree->right);
    free(tree->word);
    free(tree);
    return;
}
void write_tree(struct tnode *tree) {
    if (tree == NULL)
        return;
    write_tree(tree->left);
    printf("[%03d] - %s\n", tree->occurrence, tree->word);
    write_tree(tree->right);
    return;
}
int getword(char *word, int lim) {
    int c;
    char *end = word;
    while ((c = getchar()) != EOF && !isalpha(c))
        ;
    if (c == EOF)
        return EOF;
    while (--lim > 0 && isalpha(c)) {
        *end++ = (char)c;
        c = getchar();
    }
    *end = '\0';
    return 0;
}
