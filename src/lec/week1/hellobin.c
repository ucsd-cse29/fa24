#include <stdio.h>

int main() {
  char hello[] = "Hello!";
  char hello2[] = { 72, 101, 108, 108, 111, 33, 0 };
  char hello3[] = { 0b1001000, 0b1100101, 0b1101100, 0b1101100, 0b1101111, 0b100001, 0b0 };

  puts(hello);
  puts(hello2);
  puts(hello3);

  printf("%d %d %d\n", hello[0], hello2[0], hello3[0]);
  printf("%b %b %b\n", hello[0], hello2[0], hello3[0]);
}
