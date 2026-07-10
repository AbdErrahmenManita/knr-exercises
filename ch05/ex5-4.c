#include <stdio.h>
int strend(char *s, char *t){
    char *start_t=t;        //saves the address of the first char of t
    char *start_s=s;
    while (*s!='\0') s++;   //move until the end of s
    while(*t!='\0') t++;    //move until the end of t
    while(*s==*t){
        if(t==start_t){     //
            return 1;
        }
        if (s == start_s) {
            return 0;
        }
        t--;
        s--;
    }
    return 0;
}
int main(){
    char s[]="";
    char t[]="";
    printf("%d\n",strend(s,t));
}
