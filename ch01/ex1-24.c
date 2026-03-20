#include <stdio.h>
#define MAXSTRING 1000
#define IN 1
#define OUT 0
void check_syntax(void);
int main() {
  check_syntax();
  return 0;
}
void check_syntax(void) {
  int c;
  char s[MAXSTRING];
  s[0]='\0';
  int i = 0;
  int prev = ' ';
  int quoted=-1;
  int comment=OUT;
  while ((c = getchar()) != EOF) {
      putchar (c);
      if ((c == '"' || c=='\'' ) && prev != '\\') {             // This part tell us if we are inside quotes or not
        quoted = quoted * (-1);
        if(s[0]!='\0' && s[i-1]==c){
            --i;
            s[i]='\0';
        }
        else{
            s[i]=c;
            ++i;
        }
      }
      if(quoted==-1){                                  /*this part check only if we are inside a comment */
          if(comment == OUT && prev=='/' && c=='*'){   /*but only after being sure we are not inside aquoted string */
              comment=IN;
              c=' ';
          }
          else if (comment == IN && prev=='*' && c=='/'){
              comment=OUT;
              c=' ';
          }
      }
      if(quoted==-1 && comment==OUT){
          if((c=='{' || c=='(' || c=='[') && prev!='\\'){
              s[i]=c;
              ++i;
          }
          else if((c=='}' || c==']' || c==')') && prev!='\\'){
              if(s[0]=='\0'){
                  printf(" [NO Opened Brakects or Brace or parenthese to close here] ");
              }
              else if((s[i-1]=='(' && c!=')')||
                  (s[i-1]=='[' && c!=']')||
                  (s[i-1]=='{' && c!='}')||
                  (s[i-1]=='"' && c!='"')||
                  (s[i-1]=='\'' && c!='\'')){
                  printf(" [Unmatched closing] ");

              }
              else{
                  --i;
                  s[i]='\0';
              }
          }
      }
      prev=c;
  }
  if(i!=0){
      printf(" [Syntax Error : Unclosed brakets or parentheses or braces]\n");
  }
}
