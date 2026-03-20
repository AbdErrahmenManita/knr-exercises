#include <stdio.h>
#define MAXLINE 1000
#define TABSTOP 8
void fold(int n);
int get_line(char s[], int lim);
void copy(char to[], char from[]);
int main() {
  /*int n;
  printf("donner n : ");
  scanf("%d", &n);*/
  fold(15 + 2);
}
void fold(int n) {
  int c;
  int cursor = 0;
  int len = 0;
  char s[n];
  char buffer[n];
  s[0] = '\0';
  while ((len = get_line(s, n)) > 0) {
      //printf("\n first : %s\n",s);
    if (len < n) {
      printf("*%s\n", s);
      s[0]='\0';
    } else {
        /*printf("*2*%s\n", s);*/
      int i = len;
      if (s[i] == '\n') {
        s[i] = '\0';
        printf("**%s\n", s);
      }
      else{
          /*printf("*2*%s\n", s);*/
          while (s[i] != ' ') {
            --i;
          }
          /*printf("*%d\n",i);*/
          while (s[i] == ' ') {
            --i;
          }
          /*printf("**%d\n",i);*/
          int k = 0;
          for (int j = i + 1; s[j] != '\0'; j++) {
            if (s[j] != ' ') {
              buffer[k] = s[j];
              ++k;
            }
          }
          s[i + 1] = '\0';
          buffer[k] = '\0';
          printf("***%s\n", s);
          copy(s, buffer);
      }
    }
  }
}
int get_line(char s[], int n) {
  int c;
  int prev = ' ';
  int i=0;
  while (s[i] != '\0') {
    ++i;
  }
  int k=i;
  for (i = i; i < n - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
    if (c == '\t') {
      int tab = TABSTOP - (i % TABSTOP);
      for (int j = 0; j < tab && i < n - 1; j++) {
        s[i] = ' ';
        ++i;
      }
      --i;
      c = ' ';
    } else {
      s[i] = c;
    }
    prev = c;
  }
  /*if (k==i){          ///here when i tested my terminal got flooded with the last part of the input that's when i noticed that
      return 0;        ///this function will always return 1
  }*/
  if (c == '\n') {
    s[i] = '\n';
    ++i;
  }
  s[i] = '\0';
  //++i;
  return i;
}
void copy(char to[], char from[]) {
  int i = 0;
  while ((to[i] = from[i]) != '\0') {
    ++i;
  }
}

/*







if(c=='\n'){
    if(len>0 && s[len-1]!=' ' && s[len-1]!='\t'){
        s[len]='\0';
        printf("%s",s);
    }
    putchar('\n');
    nb_blanks=len=cursor=0;
}
else if(cursor<n){
    if(c==' ' || c=='\t'){
        if(len >0 && s[len-1]!=' ' && s[len-1]!='\t'){
            s[len]='\0';
            printf("%s",s);
        }
        len=0;
        s[len]=c;
        ++nb_blanks;
    }
    else{
        s[len]=c;
        ++len;
    }
    ++cursor;
}
else{
    if(nb_blank==0){
        printf("%s-\n",s);
    }
    else{
        if(len>0 && s[len-1]!=' ' && s[len-1]!='\t'){
            printf("%s",s);
        }
        putchar("\n");
        nb_blanks=len=cursor=0;
    }
}*/
