#include <stdio.h>

int main() {
    char hello[] = { 72, 101, 108, 111, 111, 33, 33, 33 };
    char hellohello[] = { 'H', 'e', 'l', 'l', 'o', ',', ' ', 'e', 'v', 'e', 'r', 'y', 'o', 'n', 'e', '!' };
    puts(hello);
    puts(hellohello);
    printf("%x %x\n", &hello, &hellohello);
}
