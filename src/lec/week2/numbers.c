#include <stdint.h>
#include <stdio.h>

int8_t is_ascii(char c) {
    return c <= 128;
}

void test_is_ascii(char c) {
    printf("is_ascii(%c %d) = %s\n", c, c, is_ascii(c) ? "true" : "false");
}
void tests_is_ascii() {
    test_is_ascii('a');
    test_is_ascii(0b10000000);
    test_is_ascii(0b01111111);
    for(int i = 0b00000000; i <= 0b11111111; i += 1) {
        test_is_ascii(i);
    }
}

int main() {
    tests_is_ascii();
}
