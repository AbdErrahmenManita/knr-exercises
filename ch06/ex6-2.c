#include <ctype.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define MAXWORD 100
enum { IDENTIFIER, SKIPPEDLINE, OTHER };

size_t match_len;

char *keywords[] = {"_Alignas",      "_Alignof",  "_Atomic",
                    "_Bool",         "_Complex",  "_Generic",
                    "_Imaginary",    "_Noreturn", "_Static_assert",
                    "_Thread_local", "auto",      "break",
                    "case",          "char",      "const",
                    "continue",      "default",   "do",
                    "double",        "else",      "enum",
                    "extern",        "float",     "for",
                    "goto",          "if",        "inline",
                    "int",           "long",      "register",
                    "restrict",      "return",    "short",
                    "signed",        "sizeof",    "static",
                    "struct",        "switch",    "typedef",
                    "union",         "unsigned",  "void",
                    "volatile",      "while"};
int nkeys = sizeof(keywords) / sizeof(char *);

struct tnode {
    char *word;
    struct tnode *left;
    struct tnode *right;
};
struct tnode_root {
    struct tnode *root;
    int var_count;
    struct tnode_root *left;
    struct tnode_root *right;
};

size_t get_match_len(int, char **);
size_t str_to_size(char *);

int getvar(char *, int);
int getword(char *, int);
int is_keyword(char *);
int binsearch(char *);

void insert_group(struct tnode_root **, char *, size_t);
void insert_word(struct tnode **, char *, size_t, int *);

void write_groups(struct tnode_root *);
void write_words(struct tnode *);
void write_root(char *);

void free_groups(struct tnode_root *);
void free_nodes(struct tnode *);

void *xmalloc(size_t);

int main(int argc, char *argv[]) {
    match_len = get_match_len(--argc, ++argv);
    struct tnode_root *tree = NULL;
    char word[MAXWORD];
    while (getvar(word, MAXWORD) != EOF) {
        size_t len = strlen(word);
        insert_group(&tree, word, len + 1);
    }
    write_groups(tree);
    free_groups(tree);
    return 0;
}
size_t get_match_len(int argcount, char *args[]) {
    if (argcount == 0 || args[0][0] == '\0')
        return 6;
    else if (argcount == 1) {
        return str_to_size(args[0]);
    }
    fprintf(stderr, "ERROR: too many Arguments !\n");
    exit(EXIT_FAILURE);
}
size_t str_to_size(char *string) {
    size_t res = 0;
    unsigned int digit;
    while (*string != '\0') {
        if (!isdigit((unsigned char)*string)) {
            fprintf(stderr, "ERROR: the given argument isn't a number !\n");
            exit(EXIT_FAILURE);
        }
        digit = (unsigned char)*string - '0';
        if (res > (SIZE_MAX - digit) / 10) {
            fprintf(stderr, "ERROR: Number exceeded Max Size Limit ! Try a "
                            "smaller number\n");
            exit(EXIT_FAILURE);
        }
        res = res * 10 + digit;
        string++;
    }
    return res;
}
int getvar(char *w, int lim) {
    int res;
    while ((res = getword(w, lim)) != EOF) {
        switch (res) {
        case SKIPPEDLINE:
        case OTHER:
            continue;
        case IDENTIFIER:
            return IDENTIFIER;
        }
    }
    return EOF;
}
int getword(char *word, int lim) {
    int c, opened_quotes;
    char *end = word;
    while (isspace(c = getchar()) || c == '*')
        ;
    switch (c) {
    case EOF:
        return EOF;
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
            return OTHER;
        }
        return SKIPPEDLINE;
    case '"':
    case '\'':
        opened_quotes = c;
        while ((c = getchar()) != EOF && c != opened_quotes) {
            if (c == '\\')
                getchar();
        }
        return SKIPPEDLINE;
    case '#':
        while ((c = getchar()) != EOF && c != '\n')
            ;
        return SKIPPEDLINE;
    default:
        *end++ = (char)c;
        lim--;
        if (!isalpha((unsigned char)c) && c != '_') {
            *end = '\0';
            return OTHER;
        }
        while ((c = getchar()) != EOF && (isalnum(c) || c == '_')) {
            if (--lim > 0) // Discard character of the same word if the limit
                           // reached to avoid creating two word from the same
                           // one
                *end++ = (char)c;
        }
        if (c != EOF)
            ungetc(c, stdin);
        *end = '\0';
    }
    return IDENTIFIER;
}
int is_keyword(char *w) {
    if (binsearch(w))
        return 1;
    return 0;
}
int binsearch(char *string) {
    int start = 0, end = nkeys - 1;
    int mid;
    while (start <= end) {
        mid = (start + end) / 2;
        int cmp = strcmp(keywords[mid], string);
        if (cmp == 0)
            return 1;
        else if (cmp < 0)
            start = mid + 1;
        else
            end = mid - 1;
    }
    return 0;
}
void insert_group(struct tnode_root **tree, char *word, size_t len) {
    struct tnode_root **curr = tree;
    while (*curr) {
        int cmp = strncmp((*curr)->root->word, word, match_len);
        if (cmp == 0) {
            insert_word(&(*curr)->root, word, len, &(*curr)->var_count);
            return;
        } else if (cmp > 0)
            curr = &(*curr)->left;
        else
            curr = &(*curr)->right;
    }
    *curr = xmalloc(sizeof(struct tnode_root));
    (*curr)->root = xmalloc(sizeof(struct tnode));

    (*curr)->left = NULL;
    (*curr)->right = NULL;
    (*curr)->root->word = xmalloc(len * sizeof(char));
    strcpy((*curr)->root->word, word);
    (*curr)->var_count = 1;
    (*curr)->root->left = NULL;
    (*curr)->root->right = NULL;
    return;
}
void insert_word(struct tnode **root, char *w, size_t len, int *count) {
    struct tnode **curr = root;
    while (*curr) {
        int cmp = strcmp((*curr)->word, w);
        if (cmp == 0) {
            return;
        } else if (cmp > 0) {
            curr = &(*curr)->left;
        } else {
            curr = &(*curr)->right;
        }
    }
    *curr = xmalloc(sizeof(struct tnode));
    (*curr)->word = xmalloc(len * sizeof(char));
    strcpy((*curr)->word, w);
    (*count)++;
    (*curr)->left = NULL;
    (*curr)->right = NULL;
    return;
}

void write_groups(struct tnode_root *tree) {
    if (!tree)
        return;
    write_groups(tree->left);
    if (tree->var_count > 1) {
        printf("=================================\n");
        write_root(tree->root->word);
        printf("=================================\n");
        write_words(tree->root);
        putchar('\n');
    }
    write_groups(tree->right);
    return;
}
void write_words(struct tnode *root) {
    if (!root)
        return;
    write_words(root->left);
    printf("- %s\n", root->word);
    write_words(root->right);
    return;
}
void write_root(char *string) {
    size_t len = strlen(string);
    size_t size = (len > match_len) ? match_len : len;
    printf("Groupe : ");
    for (size_t i = 0; i < size; i++) {
        putchar(string[i]);
    }
    putchar('\n');
}
void *xmalloc(size_t size) {
    void *p = malloc(size);
    if (p == NULL) {
        fprintf(stderr, "Allocation error !\n");
        exit(EXIT_FAILURE);
    }
    return p;
}
void free_groups(struct tnode_root *tree) {
    if (tree == NULL)
        return;
    free_groups(tree->left);
    free_groups(tree->right);
    free_nodes(tree->root);
    free(tree);
    return;
}
void free_nodes(struct tnode *root) {
    if (root == NULL)
        return;
    free_nodes(root->left);
    free_nodes(root->right);
    free(root->word);
    free(root);
    return;
}
