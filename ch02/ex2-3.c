#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int htoi(char string[] );
int main (){
    char s[100];
    scanf("%s",s);
    int n=htoi(s);
    printf("%d\n",n);
    return 0;
}
int htoi(char s[] ){
    int result =0;
    int i=strlen(s)-1;
    printf("%d\n",i);
    int multiplier=1;
    int lim =-1; // this ensures that we reach the index 0
    if(i>0 && s[0]=='0' && (s[1]=='x' || s[1]=='X')) // this check if there is a 0x or 0X prefix if so we need to ignore it
        lim=1;
    while(i>lim){
        printf ("result = %d\nmultiplier = %d\ns[i] = %c\n",result,multiplier,s[i]);
        if(isdigit(s[i])){
            result=result + multiplier*(s[i]-'0');
        }
        else if(tolower(s[i])>='a' && tolower(s[i])<='f'){
            result=result + multiplier*(10+tolower(s[i])-'a');
        }
        else{ //this is activated when the character s[i] is not in the base 16
            printf("This is not a valid Hex format \nPlease Verify !\n");
            exit(1);
        }
        multiplier=multiplier*16;
        --i;
    }
    // another way i found

    /*
    int result =0;
    int i=0;
    if(strlen(s) > 1 && s[0]=='0' && (s[1]=='x' || s[1]=='X'))
     i=2;
    while (s[i]!='\0'){
        int add;
        if(isdigit(s[i])){
            add=s[i]-'0';

        }
        else if(tolower(s[i])>='a' && tolower(s[i])<='f'){
            add=10+tolower(s[i])-'a';
        }
        else{ //this is activated when the character s[i] is not in the base 16
            printf("This is not a valid Hex format \nPlease Verify !\n");
            exit(1);
        }
        result=result*16 + add;
        i++;
    } */
    // How this work is actually a little confusing but when you move from left to right it's like we are building a Polynomial
    // X(X(aX+b)+c)+d which becomes aX³+bX²+cX+d so here in base 16 we hace X=16
    return result;
}
