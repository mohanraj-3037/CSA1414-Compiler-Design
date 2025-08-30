#include <stdio.h>
#include <ctype.h>

int main() {
    char ch;
    int chars=0, words=0, lines=0, inWord=0;

    printf("Enter text:\n");

    while((ch=getchar())!=EOF) {
        chars++;

        if(ch=='\n') lines++;

        if(isspace(ch)) inWord=0;
        else if(!inWord) {
            inWord=1;
            words++;
        }
    }

    printf("\nTotal Characters: %d\n", chars);
    printf("Total Words     : %d\n", words);
    printf("Total Lines     : %d\n", lines);

    return 0;
}

