#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

char input[100];
int i = 0;

// Function prototypes
void E();
void Eprime();
void T();
void Tprime();
void F();

void error() {
    printf("\nError: invalid string at position %d (char '%c')\n", i, input[i]);
    exit(1);
}

void match(char c) {
    if (input[i] == c) {
        i++;
    } else {
        error();
    }
}

// E -> T E'
void E() {
    T();
    Eprime();
}

// E' -> + T E' | e
void Eprime() {
    if (input[i] == '+') {
        match('+');
        T();
        Eprime();
    }
}

// T -> F T'
void T() {
    F();
    Tprime();
}

// T' -> * F T' | e
void Tprime() {
    if (input[i] == '*') {
        match('*');
        F();
        Tprime();
    }
}

// F -> (E) | id | num
void F() {
    if (input[i] == '(') {
        match('(');
        E();
        match(')');
    } 
    else if (isalpha(input[i])) {  
        // Identifier (multi-letter allowed)
        while (isalnum(input[i])) i++;
    } 
    else if (isdigit(input[i])) {
        // Number (multi-digit allowed)
        while (isdigit(input[i])) i++;
    } 
    else {
        error();
    }
}

int main() {
    printf("Enter expression: ");
    scanf("%s", input);

    E();

    if (input[i] == '\0')
        printf("\n? String ACCEPTED (belongs to grammar)\n");
    else
        printf("\n? String REJECTED (extra characters)\n");

    return 0;
}

