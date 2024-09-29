#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char hello[] = "Hello class!";
  char apple[] = "apple";

  printf("%ld\n", mystrlen(hello));
  printf("%ld\n", mystrlen(apple));

  hello[6] = 0;

  printf("%ld\n", mystrlen(hello));
  printf("%s\n", hello);

  return 0;
}
