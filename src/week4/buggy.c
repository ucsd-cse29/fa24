#include <stdio.h>

// edits string, then returns how many changed
int X_to_Y(char str[]) {
    int num_xes = 0;
    for (int i=0; str[i] != '\0'; i++) {
        if (str[i] = 'X') {
            str[i] = 'Y';
            num_xes += 1;
        }
    }
}

int main(int argc, char *argv[]) {
    for (int i=1; i<=argc; i++) {
        int num_xes = X_to_Y(argv[i]);
        printf("\"%s\": %d 'X'es changed\n", argv[i], num_xes);
    }
}
