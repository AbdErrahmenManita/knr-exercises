#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#define OUTSIZE 1000
#define MAXTOKEN 100
#define ERROR -2

enum { NAME, PARENS, BRACKETS };

void dcl(char[], char[]);
void dirdcl(char[], char[]);
int gettoken(void);
void err_msg(void);
void skip_line(void);
void getdatatype(char[]);
void getarg(char[]);
int isindict(void);
void safe_strcat(char *, const char *, size_t);
int error = 0;
int error_printed = 0;
int tokentype;
char token[MAXTOKEN];
char datatype[MAXTOKEN];
char name[MAXTOKEN];
char out[OUTSIZE];

int main(void) {
    while (gettoken() != EOF) {
        getdatatype(datatype);
        if (error) {
            skip_line();
            error = 0;
            error_printed = 0;
            continue;
        }
        out[0] = '\0';
        name[0] = '\0';
        dcl(name, out);
        if (error) {
            skip_line();
            if (!error_printed)
                err_msg();
            error = 0;
            error_printed = 0;
            continue;
        }
        if (strlen(name) == 0) {
            fprintf(stderr, "ERROR: missing name or (dcl)\n");
            skip_line();
            continue;
        }
        if (tokentype != '\n' && tokentype != ';' && tokentype != EOF) {
            fprintf(stderr, "syntax error\n");
            skip_line();
            continue;
        }

        printf("%s: %s%s\n", name, out, datatype);
    }
    return 0;
}

void dcl(char n_ame[], char output[]) {
    int ns = 0;
    while (tokentype == '*') {
        ns++;
        gettoken();
    }
    if (error) {
        return;
    }
    dirdcl(n_ame, output);
    if (error) {
        return;
    }
    while (ns-- > 0)
        safe_strcat(output, "pointer to ", OUTSIZE);
}

void dirdcl(char n_ame[], char output[]) {
    int type;
    if (tokentype == '(') {
        gettoken();
        if (tokentype != NAME ||
            (tokentype == NAME && !error && (isindict()) == -1)) {
            dcl(n_ame, output);
            if (tokentype != ')') {
                fprintf(stderr, "error: missing )\n");
                error = 1;
                error_printed = 1;
                return;
            }
        } else {
            safe_strcat(output, "function taking as arguments [[ ", OUTSIZE);
            getarg(output);
            safe_strcat(output, " returning ", OUTSIZE);
        }
    } else if (tokentype == NAME) {
        strcpy(n_ame, token);
    } else {
        return;
    }
    while ((type = gettoken()) == PARENS || type == BRACKETS || type == '(') {
        if (type == PARENS)
            safe_strcat(output, "function returning ", OUTSIZE);
        else if (type == '(') {
            safe_strcat(output, "function taking as arguments [[ ", OUTSIZE);
            gettoken();
            getarg(output);
            safe_strcat(output, " returning ", OUTSIZE);
        } else {
            safe_strcat(output, "array", OUTSIZE);
            safe_strcat(output, token, OUTSIZE);
            safe_strcat(output, " of ", OUTSIZE);
        }
    }
}
int gettoken(void) {
    int c, getch(void);
    void ungetch(int);
    token[0] = '\0';
    char *p = token;
    while ((c = getch()) == ' ' || c == '\t')
        ;
    if (c == '(') {
        if ((c = getch()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetch(c);
            return tokentype = '(';
        }
    } else if (c == '[') {
        for (*p++ = (char)c; isdigit(c = getch()) || c == ' ' || c == '\t';) {
            if (!isspace(c)) {
                *p = (char)c;
                p++;
            }
        }
        if (c != ']') {
            fprintf(stderr, "ERROR: missing ]\n");
            error = 1;
            error_printed = 1;
            return tokentype = ERROR;
        }
        *p = (char)c;
        p++;
        *p = '\0';
        return tokentype = BRACKETS;
    } else if (isalpha(c) || c == '_') {
        for (*p++ = (char)c; isalnum(c = getch()) || c == '_';) {
            *p++ = (char)c;
        }
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    } else {
        return tokentype = c;
    }
}
#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;
int getch(void) { return (bufp > 0) ? buf[--bufp] : getchar(); }
void ungetch(int c) {
    if (bufp >= BUFSIZE) {
        printf("Ungetch : Too many arguments\n");
    } else {
        buf[bufp++] = (char)c;
    }
}

void err_msg(void) { fprintf(stderr, "ERROR: Misplaced %c <<<", tokentype); }

void skip_line(void) {
    tokentype = 0;
    token[0] = '\0';
    datatype[0] = '\0';
    name[0] = '\0';
    out[0] = '\0';
    int c;
    while ((c = getch()) != '\n' && c != EOF && c != ';')
        ;
    if (c == EOF) {
        ungetch(c);
    }
}
static const char *dictionary[] = {"const",  "volatile", "signed", "unsigned",
                                   "long",   "short",    "void",   "float",
                                   "double", "char",     "int"};

enum {
    IDX_CONST,
    IDX_VOLATILE,
    IDX_SIGNED,
    IDX_UNSIGNED,
    IDX_LONG,
    IDX_SHORT,
    IDX_VOID,
    IDX_FLOAT,
    IDX_DOUBLE,
    IDX_CHAR,
    IDX_INT
};
int check_flag(int[]);
void getdatatype(char data_type[]) {
    data_type[0] = '\0';
    int flag[11] = {0};
    int c;
    while (tokentype == NAME && !error && (c = isindict()) != -1) {

        flag[c]++;
        token[0] = '\0';
        gettoken();
    }

    if (check_flag(flag)) {
        error = 1;
        return;
    }
    char count = 0;
    for (int i = 0; i < 11; i++) {
        while (flag[i] > 0) {
            if (count != 0) {
                safe_strcat(data_type, " ", MAXTOKEN);
            }
            safe_strcat(data_type, dictionary[i], MAXTOKEN);
            count++;
            flag[i]--;
        }
    }
}

int isindict(void) {
    int i = 0;
    while (i <= 10) {
        if (strcmp(dictionary[i], token) == 0) {
            return i;
        }
        i++;
    }
    return -1;
}

int check_flag(int flag[]) {

    if (flag[IDX_SHORT] > 1) {
        fprintf(stderr, "ERROR: Duplicate short\n");
        error_printed = 1;
        return -1;
    }
    if (flag[IDX_UNSIGNED] > 1) {
        fprintf(stderr, "ERROR: Duplicate unsigned\n");
        error_printed = 1;
        return -1;
    }
    if (flag[IDX_SIGNED] > 1) {
        fprintf(stderr, "ERROR: Duplicate signed\n");
        error_printed = 1;
        return -1;
    }
    if (flag[IDX_LONG] > 2) {
        fprintf(stderr, "ERROR: Triple long\n");
        error_printed = 1;
        return -1;
    }
    if (flag[IDX_LONG] == 2 && flag[IDX_DOUBLE]) {
        fprintf(stderr, "ERROR: Double can't have double long\n");
        error_printed = 1;
        return -1;
    }

    if (flag[IDX_SIGNED] && flag[IDX_UNSIGNED]) {
        fprintf(stderr, "ERROR: Can't be signed and unsigned\n");
        error_printed = 1;
        return -1;
    }
    if (flag[IDX_LONG] && flag[IDX_SHORT]) {
        fprintf(stderr, "ERROR: Can't be short and long\n");
        error_printed = 1;
        return -1;
    }
    int base_cnt = flag[IDX_INT] + flag[IDX_CHAR] + flag[IDX_FLOAT] +
                   flag[IDX_DOUBLE] + flag[IDX_VOID];
    if (base_cnt > 1) {
        fprintf(stderr, "ERROR: multiple base types\n");
        error_printed = 1;
        return -1;
    }
    if ((flag[IDX_DOUBLE] || flag[IDX_FLOAT] || flag[IDX_VOID]) &&
        (flag[IDX_SIGNED] || flag[IDX_UNSIGNED])) {
        fprintf(stderr, "ERROR: base type can't be signed or unsigned\n");
        error_printed = 1;
        return -1;
    }
    if ((flag[IDX_CHAR] || flag[IDX_DOUBLE] || flag[IDX_FLOAT] ||
         flag[IDX_VOID]) &&
        flag[IDX_SHORT]) {
        fprintf(stderr, "ERROR: base type can't be short\n");
        error_printed = 1;
        return -1;
    }
    if ((flag[IDX_CHAR] || flag[IDX_FLOAT] || flag[IDX_VOID]) &&
        flag[IDX_LONG]) {
        fprintf(stderr, "ERROR: base type can't be long\n");
        error_printed = 1;
        return -1;
    }
    return 0;
}
void getarg(char output[]) {
    int prev = '(';
    char tmp[MAXTOKEN];
    char name1[MAXTOKEN];
    char out1[OUTSIZE];
    out1[0] = '\0';
    tmp[0] = '\0';
    name1[0] = '\0';
    while (tokentype != ')' && tokentype != EOF) {
        getdatatype(tmp);
        if (error)
            return;
        dcl(name1, out1);
        if (error)
            return;
        if (tokentype != ',' && tokentype != ')') {
            fprintf(stderr, "syntax error2\n");
            error = 1;
            error_printed = 1;
            return;
        }
        if (strlen(name1)) {
            safe_strcat(output, name1, OUTSIZE);
            safe_strcat(output, " : ", OUTSIZE);
        }
        safe_strcat(output, out1, OUTSIZE);
        safe_strcat(output, tmp, OUTSIZE);
        if (tokentype != ')')
            safe_strcat(output, ", ", OUTSIZE);
        if (error)
            return;
        name1[0] = '\0';
        tmp[0] = '\0';
        out1[0] = '\0';
        prev = tokentype;
        if (tokentype == ',')
            gettoken();
    }
    if (prev == ',' && tokentype == ')') {
        fprintf(stderr, "syntax error2\n");
        error = 1;
        error_printed = 1;
        return;
    }
    if (tokentype == EOF) {
        fprintf(stderr, "ERROR: missing ) for function closing\n");
        error = 1;
        error_printed = 1;
    }
    safe_strcat(output, " ]]", OUTSIZE);
}
void safe_strcat(char *dest, const char *src, size_t maxsize) {
    if (error) {
        return;
    }
    size_t dest_len = strlen(dest);
    size_t src_len = strlen(src);
    if (dest_len + src_len > maxsize - 1) {
        fprintf(stderr, "ERROR: Allowed output size exceeded\n");
        error = 1;
        error_printed = 1;
        return;
    }
    strcat(dest, src);
}
