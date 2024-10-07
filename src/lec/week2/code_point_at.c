#include <stdio.h>
#include <stdint.h>

int32_t code_point2(char c1, char c2) {
    return (c1 & 0b00011111) * 64 + (c2 & 0b00111111);
}

int32_t code_point3(char c1, char c2, char c3) {
    return (c1 & 0b00001111) * 4096 + (c2 & 0b00111111) * 64 + (c3 & 0b00111111);
}

int main() {
    char joseph[] = "Joséph";
    printf("Code point: %d\n", code_point2(joseph[3], joseph[4]));




}
