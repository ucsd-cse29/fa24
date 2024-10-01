#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void inspect(char s[]) {
  int index = 0;
  while(s[index] != 0) {
    printf("%c (%hhu) ", s[index], s[index]);
    index += 1;
  }
  printf("\n");
}

char lower(char c) {



  
}

void lowercase(char s[]) {
  int index = 0;

  while(                      ) {

    s[index] = lower(s[index]);
    index += 1;
  }
}

int main() {
  char abc[] = "ABC";
  lowercase(abc);
  inspect(abc);

  char mixed[] = "Hello Aaron!";
  lowercase(mixed);
  inspect(mixed);






}
