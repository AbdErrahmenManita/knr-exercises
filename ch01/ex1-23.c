#include <stdio.h>
#define IN 1
#define OUT 0
void remove_comments() {
  int c, state = OUT;
  int prev = ' ';
  int i=0;
  int quotes=-1;
  while ((c = getchar()) != EOF) {
      if(quotes==-1){ // This check if we are inside does quote "" if we are not it's -1
          if(state==OUT && prev=='/' && c=='*' ){ // If we are inside quotes we should print everything no matter what
              state=IN;
              //prev=' ';
              c=' ';    // This allow us to only use prev=c; once at the end of the while loop
              // It prevent the /*/ bug which if we don't do this would be counted as a finished comment
          }   // 1st loop : prev=='/' c=='*' : we are inside a comment then state =IN and prev advance to '*'
              //2nd loop : prev=='*' c=='/' : we are outside of the comment state =OUT (which is wrong)
          else{
              if (state==OUT){
                  if(c=='"'&& prev!='\\'){ // (1)* : this condition ensure we escape the problem of the \"
                      quotes=quotes*(-1);  //so when we have it we don't multiply quotes by -1
                  }                        // and lose count of real double quotes
                  if(c!='/' && c!='*'){
                      putchar(c);
                  }
                  else if(c!='*' && prev=='/'){
                      putchar(prev);
                      putchar(c);
                  }
              }
              else{
                  if(c=='/' && prev=='*' ){
                      state=OUT;
                  }
              }
              //prev=c;
          }
      }
      else{
          putchar(c);
          if(c=='"' && prev!='\\' ){ //(1)*
              quotes=quotes*(-1);
          }
          //prev=c;
      }
      prev=c;
  }
}
int main() {
    remove_comments();
    return 0;
}
