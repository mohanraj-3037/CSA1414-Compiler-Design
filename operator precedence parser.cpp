#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAX 100

// Stack for operators
char opStack[MAX];
int opTop = -1;

// Stack for operands
double valStack[MAX];
int valTop = -1;

// Push and pop functions for operator stack
void pushOp(char c) {
    opStack[++opTop] = c;
}
char popOp() {
    return opStack[opTop--];
}
char peekOp() {
    return (opTop == -1) ? '\0' : opStack[opTop];
}

// Push and pop for value stack
void pushVal(double v) {
    valStack[++valTop] = v;
}
double popVal() {
    return valStack[valTop--];
}

// Precedence function (PEMDAS)
int precedence(char op) {
    switch(op) {
        case '^': return 3; // Exponent highest
        case '*':
        case '/': return 2; // Multiplication & Division
        case '+':
        case '-': return 1; // Addition & Subtraction
        default: return 0;
    }
}

// Apply operator to operands
double applyOp(char op, double a, double b) {
    switch(op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return pow(a, b);
        default: return 0;
    }
}

// Convert infix to postfix (Shunting Yard Algorithm)
void infixToPostfix(char *infix, char *postfix) {
    int i, k = 0;
    for (i = 0; infix[i]; i++) {
        char c = infix[i];

        if (isdigit(c)) { // If number
            postfix[k++] = c;
        }
        else if (c == '(') {
            pushOp(c);
        }
        else if (c == ')') {
            while (peekOp() != '(')
                postfix[k++] = popOp();
            popOp(); // remove '('
        }
        else { // operator
            while (precedence(peekOp()) >= precedence(c))
                postfix[k++] = popOp();
            pushOp(c);
        }
    }
    while (opTop != -1)
        postfix[k++] = popOp();

    postfix[k] = '\0';
}

// Evaluate postfix expression
double evalPostfix(char *postfix) {
    int i;
    for (i = 0; postfix[i]; i++) {
        char c = postfix[i];

        if (isdigit(c)) {
            pushVal(c - '0'); // convert char to number
        }
        else { // operator
            double b = popVal();
            double a = popVal();
            double res = applyOp(c, a, b);
            pushVal(res);
        }
    }
    return popVal();
}

int main() {
    char infix[MAX], postfix[MAX];

    printf("Enter expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);

    printf("\nInfix:   %s", infix);
    printf("\nPostfix: %s", postfix);

    double result = evalPostfix(postfix);
    printf("\nResult:  %.2f\n", result);

    printf("\nPEMDAS Rule Applied: Parentheses > Exponent > Multiplication/Division > Addition/Subtraction\n");

    return 0;
}

