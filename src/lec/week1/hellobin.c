#include <stdio.h>

int main() {
  char hello[] = "Hello!";
  char hellonum[] = { 72,        101,       108,       108,       111,       33,       0 };
  char hellobin[] = { 0b1001000, 0b1100101, 0b1101100, 0b1101100, 0b1101111, 0b100001, 0b0 };

  puts(hello);
  puts(hellonum);
  puts(hellobin);

  printf("%c %c %c\n", hello[0], hello[1], hello[2]);

  printf("%d %d %d\n", hello[0], hellonum[0], hellobin[0]);
  printf("%c %c %c\n", hello[0], hellonum[0], hellobin[0]);
}
