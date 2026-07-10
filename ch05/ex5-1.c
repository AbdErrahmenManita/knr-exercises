#include <stdio.h>
#include <ctype.h>
int getch(void);
void ungetch(int);
int getint(int *);

int main(){
    printf("Hello World\n");
    return 0;
}
// getint: get next integer from input into *pn
int getint(int *pn){
    int c,sign,sign_char;
    while(isspace(c=getch()));
    if(!isdigit(c) && c!=EOF && c!='+' && c!='-'){
        ungetch(c);
        return 0;
    }
    sign =(c=='-')? -1:1;
    sign_char=c;
    if(c=='-' || c=='+'){
        c=getch();
        if(!isdigit(c)){
            if(c!=EOF){
                ungetch(c);
            }
            ungetch(sign_char);
            return 0;
        }
    }
    for(*pn=0;isdigit(c);c=getch()){ //there is a typo here in the book
        *pn= 10 * *pn + (c-'0');     //it was ',' instead of ';'
    }                                //which wrong in syntax and logic
    *pn *=sign;
    if(c!=EOF){
        ungetch(c);
    }
    return c;
}
//
//
//
//
#define BUFSIZE 100
int buf[BUFSIZE];
char bufp = 0;
//
//
//
//
int getch() { return (bufp > 0) ? buf[--bufp] : getchar(); }
//
//
//
//
//
void ungetch(int c) {
  if (bufp >= BUFSIZE) {
    printf("Ungetch : Too many arguments\n");
  } else {
    buf[bufp++] = c;
  }
}
