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
    printf("\nError at position %d, char: %c\n", i, input[i]);
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
    // else e
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
    // else e
}

// F -> (E) | id | num
void F() {
    if (input[i] == '(') {
        match('(');
        E();
        match(')');
    } 
    else if (isalpha(input[i])) {  
        // Identifier: one or more letters/digits
        while (isalnum(input[i])) {
            i++;
        }
    } 
    else if (isdigit(input[i])) {
        // Number: one or more digits
        while (isdigit(input[i])) {
            i++;
        }
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
        printf("\nString ACCEPTED.\n");
    else
        printf("\nString REJECTED.\n");

    return 0;
}

