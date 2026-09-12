#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#define MAXWORD 100
int line_num = 1;
struct tnode {
    int val;
    struct tnode *left;
    struct tnode *right;
};
struct tnode_root {
    struct tnode *root;
    char *word;
    struct tnode_root *left;
    struct tnode_root *right;
};
char *keywords[] = {
    "a",       "about",  "above",      "after",     "again",     "against",
    "all",     "am",     "an",         "and",       "any",       "are",
    "as",      "at",     "be",         "because",   "been",      "before",
    "being",   "below",  "between",    "both",      "but",       "by",
    "can",     "could",  "did",        "do",        "does",      "doing",
    "down",    "during", "each",       "few",       "for",       "from",
    "further", "had",    "has",        "have",      "having",    "he",
    "her",     "here",   "hers",       "herself",   "him",       "himself",
    "his",     "how",    "i",          "if",        "in",        "into",
    "is",      "it",     "its",        "itself",    "just",      "me",
    "more",    "most",   "my",         "myself",    "no",        "nor",
    "not",     "of",     "off",        "on",        "once",      "only",
    "or",      "other",  "our",        "ours",      "ourselves", "out",
    "over",    "own",    "same",       "she",       "should",    "so",
    "some",    "such",   "than",       "that",      "the",       "their",
    "theirs",  "them",   "themselves", "then",      "there",     "these",
    "they",    "this",   "those",      "through",   "to",        "too",
    "under",   "until",  "up",         "very",      "was",       "we",
    "were",    "what",   "when",       "where",     "which",     "while",
    "who",     "whom",   "why",        "will",      "with",      "you",
    "your",    "yours",  "yourself",   "yourselves"};
int nkeys = sizeof(keywords) / sizeof(char *);
int getword(char *, int);
void *my_malloc(size_t);
void *my_realloc(void *, size_t);
int is_not_keyword(char *);
int binsearch(char *);
void fill_tree(struct tnode_root **, char *);
void my_strcpy(char **, char *);
void add_line(struct tnode **);
void write_words(struct tnode_root *);
void write_lines(struct tnode *);
int main(void) {
    char word[MAXWORD];
    struct tnode_root *Tree = NULL;
    while (getword(word, MAXWORD) != EOF) {
        if (is_not_keyword(word)) {
            fill_tree(&Tree, word);
        }
    }
    write_words(Tree);
    return 0;
}

void *my_malloc(size_t size) {
    void *p = malloc(size);
    if (p == NULL) {
        fprintf(stderr, "Allocation error !\n");
        exit(EXIT_FAILURE);
    }
    return p;
}
void *my_realloc(void *buff, size_t size) {
    void *ptr = realloc(buff, size);
    if (!ptr) {
        fprintf(stderr, "my_shell: Allocation ERROR\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}
int getword(char *string, int lim) {
    int c;
    char *end = string;
    while ((c = getchar()) != EOF && !isalpha(c)) {
        if (c == '\n')
            line_num++;
    }
    if (c == EOF)
        return EOF;
    *end++ = (char)c;
    lim--;
    for (; --lim > 0 && isalpha(c = getchar()); end++) {
        *end = (char)c;
    }
    if (c == '\n')
        ungetc(c, stdin);
    *end = '\0';
    return 0;
}
int is_not_keyword(char *w) {
    if (binsearch(w))
        return 0;
    return 1;
}
int binsearch(char *string) {
    int start = 0, end = nkeys - 1;
    int mid;
    while (start <= end) {
        mid = (start + end) / 2;
        int cmp = strcasecmp(keywords[mid], string);
        if (cmp == 0)
            return 1;
        else if (cmp < 0)
            start = mid + 1;
        else
            end = mid - 1;
    }
    return 0;
}
void fill_tree(struct tnode_root **T, char *w) {
    if (*T == NULL) {
        struct tnode_root *temptree = my_malloc(sizeof(struct tnode_root));
        struct tnode *tempnode = my_malloc(sizeof(struct tnode));
        tempnode->val = line_num;
        tempnode->left = NULL;
        tempnode->right = NULL;
        temptree->root = tempnode;
        my_strcpy(&temptree->word, w);
        temptree->left = NULL;
        temptree->right = NULL;
        *T = temptree;
        return;
    }
    int cmp = strcasecmp((*T)->word, w);
    if (cmp == 0) {
        add_line(&(*T)->root);
    } else if (cmp > 0) {
        fill_tree(&(*T)->left, w);
    } else {
        fill_tree(&(*T)->right, w);
    }
    return;
}
void my_strcpy(char **dest, char *src) {
    size_t len = strlen(src) + 1;
    *dest = my_malloc(len * sizeof(char));
    for (size_t i = 0; i < len; i++) {
        (*dest)[i] = src[i];
    }
}
void add_line(struct tnode **root) {
    if (*root == NULL) {
        struct tnode *tempnode = my_malloc(sizeof(struct tnode));
        tempnode->val = line_num;
        tempnode->left = NULL;
        tempnode->right = NULL;
        *root = tempnode;
        return;
    }
    if ((*root)->val == line_num)
        return;
    else if ((*root)->val > line_num)
        add_line(&(*root)->left);
    else
        add_line(&(*root)->right);
    return;
}
void write_words(struct tnode_root *T) {
    if (T == NULL)
        return;
    write_words(T->left);
    printf("=================================\n");
    printf("Word: %s\n", T->word);
    printf("=================================\n");
    free(T->word);
    write_lines(T->root);
    putchar('\n');
    write_words(T->right);
    free(T);
}
void write_lines(struct tnode *root) {
    if (root == NULL)
        return;
    write_lines(root->left);
    printf("- %d\n", root->val);
    write_lines(root->right);
    free(root);
    return;
}
