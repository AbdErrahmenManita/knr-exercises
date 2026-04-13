#include <stdio.h>
int main() {
    /*

      for(i=0; i<lim-1; ++i){
          if((c=getchar()) != '\n'){
              if(c!= EOF){
                  s[i]=c;
              }
              else{
                  break;
              }
          }
          else{
              break;
          }
      }*/
    /*
        for(i=0; i<lim-1; ++i){
            if((c=getchar()) == '\n'){
                break;
            }
    if(c== EOF){
          break;
        }
        s[i]=c;
       }*/


    // if we don't want to use break
    /*
     int ok=1;
     for(i=0; ok; ++i){
     ok=(i < lim)*((c=getchar())!='\n')*(c!= EOF);   Here we use lim instead of lim-1 because i already moved by 1
     if(ok){
      s[i-1]=c;       same goes here we use i-1 instead of i
     }
    }*/
    // OR
    /*
     int ok=1;
     int i=0;
     while(ok){
      if((c=getchar()) != '\n'){
        if(c!= EOF){
          s[i]=c;
          ++i;
        }
        else{
          ok=0;
        }
      }
      else{
      ok=0;
      }
     }*/
}
