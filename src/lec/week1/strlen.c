#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char hello[] = "Hello class!";
  char apple[] = "apple";
  char hello_0[] = "Hello\0class!";

  printf("%ld\n", strlen(hello));
  printf("%ld\n", strlen(apple));

  printf("%s, length: %ld\n", hello_0, strlen(hello_0));

  hello[7] = 0;

  printf("%s, length: %ld\n", hello, strlen(hello));

  return 0;
}
