#include <stdio.h>
#define TABSTOP 8
void entab(void);
int main() {
  entab();
  return 0;
}
void entab(void) {
  int c;
  int cursor = 0;
  int start, end;
  start = end = 0;
  while ((c = getchar()) != EOF) {
    if (c == ' ') {
        ++end;
    } else {
        if(end!=start){
            int nb=end-start;
            if(nb==1){
                putchar(' ');
            }
            else{
                int tab=(cursor/8)-(start/8);
                int blanks=nb;       /*here the i used the "int blanks=cursor%8;" instead so i got the problem where */
                if(tab!=0)          /* when the tab==0 it gave me a wrong number once i noticed that i introduced the if condition */
                    blanks=cursor%8;
                for(int i=0;i<tab;i++){
                    printf(" [tab] ");
                }
                for(int i=0;i<blanks;i++){
                    printf(" [blanks] ");
                }
            }
        }
        putchar(c);
        if(c=='\n')
            cursor =-1;    /*here i noticed that when i add a newline the cursor then when  */
        start=end=cursor+1; /*incremented at the end pf the while loop it starts from index 1 instead of 0 */
                            /*that's why i tweaked it a little bit to ensure the cursor starts from 0 after a newline */
    }
    ++cursor;
}
  if(end!=start){
      int nb=end-start;
      if(nb==1){
          putchar(' ');
      }
      else{
          int tab=(cursor/8)-(start/8);
          int blanks=nb;
          if(tab!=0)
              blanks=cursor%8;
          for(int i=0;i<tab;i++){
              printf(" [tab] ");
          }
          for(int i=0;i<blanks;i++){
              printf(" [blank] ");
          }
      }
  }
}
