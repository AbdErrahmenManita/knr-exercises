#include <stdio.h>

//page 89
void str_cat(char *s,char *t){
    while(*s++!='\0');
    s--;
    while((*s++=*t++)!='\0');
}


int main(){
    char s[20]="Hello, ";
    char t[20]="World!";
    str_cat(s,t);
    printf("%s\n",s);
    return 0;
}
