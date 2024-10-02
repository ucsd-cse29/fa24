#include <stdio.h>


int strlenn(char str[]) {
    int length = 0;
    for (int i = 0; str[i] != '\0' && str[i] != '\n'; i++){
        length++;
    }
    return length;
}

void first_substring(char str[]){
    int stringlength = strlenn(str);
    char substring[stringlength+1];
    for (int i=0; str[i] != 0 && str[i] != '\n'; i++){
        if (str[i] == ' '){
            puts(substring);
            return;
        }
        substring[i] = str[i];
    }
    puts(substring);
    return;

}

int main(){
    char string[] = "Hello World!";
    printf("%s\n", "Input a string:");
    char buffer[50];
    fgets(buffer,50, stdin);
    printf("%d\n", strlenn(string));
    printf("%d\n", strlenn(buffer));
    first_substring(buffer);
    return 0;
}