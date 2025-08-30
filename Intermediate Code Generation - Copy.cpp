#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char expr[100];
int pos = 0;
int tempCount = 1;

// Function prototypes
char* E();
char* T();
char* F();

void skipSpaces() {
    while (expr[pos] == ' ' || expr[pos] == '\t') pos++;
}

// Generate a new temporary variable
char* newTemp() {
    static char temp[10];
    sprintf(temp, "t%d", tempCount++);
    return strdup(temp);
}

// E -> T { + T }
char* E() {
    char* t1 = T();
    skipSpaces();
    while (expr[pos] == '+') {
        pos++;
        char* t2 = T();
        char* temp = newTemp();
        printf("%s = %s + %s\n", temp, t1, t2);
        free(t1);
        free(t2);
        t1 = strdup(temp);
    }
    return t1;
}

// T -> F { * F }
char* T() {
    char* f1 = F();
    skipSpaces();
    while (expr[pos] == '*') {
        pos++;
        char* f2 = F();
        char* temp = newTemp();
        printf("%s = %s * %s\n", temp, f1, f2);
        free(f1);
        free(f2);
        f1 = strdup(temp);
    }
    return f1;
}

// F -> (E) | id | number
char* F() {
    skipSpaces();
    char buffer[20];
    if (expr[pos] == '(') {
        pos++;
        char* t = E();
        if (expr[pos] == ')') pos++;
        return t;
    } else if (isalpha(expr[pos]) || isdigit(expr[pos])) {
        int k = 0;
        while (isalnum(expr[pos])) {
            buffer[k++] = expr[pos++];
        }
        buffer[k] = '\0';
        return strdup(buffer);
    } else {
        printf("Error: invalid symbol '%c' at pos %d\n", expr[pos], pos);
        exit(1);
    }
}

int main() {
    printf("Enter expression: ");
    fgets(expr, sizeof(expr), stdin);
    expr[strcspn(expr, "\n")] = '\0'; // remove newline

    char* result = E();
    printf("Result stored in: %s\n", result);

    free(result);
    return 0;
}

