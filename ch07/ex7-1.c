#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Please use symbolic link to make the program run with both ./upper ./lower
// For exemple compile with the name lower then use the command
//  ln -s lower upper to create a symbolic link
//  now you could either use ./upper or ./lower to execute the binary

int main(int argc, char *argv[]) {
    (void)argc;
    char *w = argv[1];
    char *command = &argv[0][2];
    if (strcmp(command, "lower") == 0) {
        for (; *w != '\0'; w++)
            *w = (char)tolower(*w);
    } else if (strcmp(command, "upper") == 0) {
        for (; *w != '\0'; w++)
            *w = (char)toupper(*w);
    } else {
        printf("Wrong Binary name \nPlease make sure to name the binary "
               "exactly upper or lower\n");
        exit(EXIT_FAILURE);
    }
    printf("%s\n", argv[1]);
    return 0;
}
