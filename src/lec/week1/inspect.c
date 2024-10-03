#include <stdio.h>
#include <string.h>

void inspect(char s[]) {
    int index = 0;
    printf("%s, length %ld: ", s, strlen(s));
    while(s[index] != 0) {
        char current = s[index];
        printf("%c (%hhu 0b", current, current);
        for(int place = 128; place > 0; place /= 2) {
            if((current & place) == 0) printf("0");
            else printf("1");
        }
        printf(") ");
        index += 1;
    }
    printf("\n");
}

int main() {
    char input[100];
    fgets(input, 100, stdin);
    printf("\n");
    inspect(input);
}
