#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

char expr[100];
int pos = 0;

// Function prototypes
int expression();
int term();
int factor();

// Skip whitespace
void skipSpaces() {
    while (expr[pos] == ' ' || expr[pos] == '\t') pos++;
}

// Parse numbers and parentheses
int factor() {
    skipSpaces();
    int result = 0;
    if (expr[pos] == '(') {
        pos++; // skip '('
        result = expression();
        if (expr[pos] == ')') pos++;
        else {
            printf("Error: missing closing parenthesis\n");
            exit(1);
        }
    } else if (isdigit(expr[pos])) {
        while (isdigit(expr[pos])) {
            result = result * 10 + (expr[pos] - '0');
            pos++;
        }
    } else {
        printf("Error: invalid character '%c'\n", expr[pos]);
        exit(1);
    }
    return result;
}

// Parse multiplication and division
int term() {
    int result = factor();
    skipSpaces();
    while (expr[pos] == '*' || expr[pos] == '/') {
        char op = expr[pos++];
        int right = factor();
        if (op == '*') result *= right;
        else result /= right;
    }
    return result;
}

// Parse addition and subtraction
int expression() {
    int result = term();
    skipSpaces();
    while (expr[pos] == '+' || expr[pos] == '-') {
        char op = expr[pos++];
        int right = term();
        if (op == '+') result += right;
        else result -= right;
    }
    return result;
}

int main() {
    printf("Enter arithmetic expression: ");
    fgets(expr, sizeof(expr), stdin);

    int result = expression();

    printf("Result = %d\n", result);
    return 0;
}

