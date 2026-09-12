#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000

void filecmp(FILE *, FILE *);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Compare: Was waiting for 2 arguments but got %d\n",
                argc - 1);
        exit(EXIT_FAILURE);
    }
    FILE *file1, *file2;
    if ((file1 = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "Compare: Error while opening %s \n", argv[1]);
        exit(EXIT_FAILURE);
    }
    if ((file2 = fopen(argv[2], "r")) == NULL) {
        fprintf(stderr, "Compare: Error while opening %s \n", argv[2]);
        exit(EXIT_FAILURE);
    }
    filecmp(file1, file2);
    fclose(file1);
    fclose(file2);
}

void filecmp(FILE *file1, FILE *file2) {
    long long line_num = 1;
    char line_file1[MAXLINE], line_file2[MAXLINE];
    char *p1, *p2;

    while (1) {
        p1 = fgets(line_file1, MAXLINE, file1);
        p2 = fgets(line_file2, MAXLINE, file2);
        if (p1 == NULL && p2 == NULL) {
            printf("All lines are matching between the two files \n");
            return;
        }
        if (p1 == NULL || p2 == NULL || strcmp(line_file1, line_file2) != 0) {
            break;
        }
        if (line_file1[strlen(line_file1) - 1] == '\n')
            line_num++;
    }

    printf("The first line to differ between the two files is line N° %lld:\n",
           line_num);

    printf("- File 1: ");
    if (p1 == NULL) {
        printf("<EOF>\n");
    } else {
        do {
            printf("%s", line_file1);
        } while (line_file1[strlen(line_file1) - 1] != '\n' &&
                 fgets(line_file1, MAXLINE, file1) != NULL);
        if (line_file1[strlen(line_file1) - 1] != '\n')
            putchar('\n');
    }

    printf("- File 2: ");
    if (p2 == NULL) {
        printf("<EOF>\n");
    } else {
        do {
            printf("%s", line_file2);
        } while (line_file2[strlen(line_file2) - 1] != '\n' &&
                 fgets(line_file2, MAXLINE, file2) != NULL);
        if (line_file2[strlen(line_file2) - 1] != '\n')
            putchar('\n');
    }
}
