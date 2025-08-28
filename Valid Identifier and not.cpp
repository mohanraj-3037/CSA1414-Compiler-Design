#include <stdio.h>
#include <string.h>
#include <ctype.h>

char input[100];
int pos = 0;

void E(); void Edash(); void T(); void Tdash(); void F();

void match(char expected) {
    if (input[pos] == expected) pos++;
    else {
        printf("Error: expected '%c' at pos %d\n", expected, pos);
        exit(1);
    }
}

void E() {
    T();
    Edash();
}

void Edash() {
    if (input[pos] == '+') {
        match('+');
        T();
        Edash();
    }
    // else epsilon
}

void T() {
    F();
    Tdash();
}

void Tdash() {
    if (input[pos] == '*') {
        match('*');
        F();
        Tdash();
    }
    // else epsilon
}

void F() {
    if (input[pos] == '(') {
        match('(');
        E();
        match(')');
    } else if (isalnum(input[pos])) {
        pos++; // identifier/number
    } else {
        printf("Error: invalid symbol '%c' at pos %d\n", input[pos], pos);
        exit(1);
    }
}

int main() {
    printf("Enter expression: ");
    scanf("%s", input);

    E();

    if (input[pos] == '\0')
        printf("Parsing Successful!\n");
    else
        printf("Error: extra input at pos %d\n", pos);
}

