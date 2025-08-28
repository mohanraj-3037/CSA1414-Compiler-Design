#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// Stack for operators
char stack[MAX];
int top = -1;

void push(char c) {
    stack[++top] = c;
}
char pop() {
    return stack[top--];
}
char peek() {
    return (top == -1) ? '\0' : stack[top];
}

// Precedence function
int precedence(char op) {
    switch(op) {
        case '^': return 3;
        case '*':
        case '/': return 2;
        case '+':
        case '-': return 1;
        default: return 0;
    }
}

// Convert infix to postfix
void infixToPostfix(char *infix, char *postfix) {
    int i, k = 0;
    for (i = 0; infix[i]; i++) {
        char c = infix[i];
        if (isalnum(c)) {
            postfix[k++] = c;
        }
        else if (c == '(') {
            push(c);
        }
        else if (c == ')') {
            while (peek() != '(')
                postfix[k++] = pop();
            pop(); // remove '('
        }
        else { // operator
            while (precedence(peek()) >= precedence(c))
                postfix[k++] = pop();
            push(c);
        }
    }
    while (top != -1)
        postfix[k++] = pop();

    postfix[k] = '\0';
}

// Generate three address code from postfix
void generateTAC(char *postfix) {
    char tempVar[10][10]; // store names of temporaries
    int tCount = 1;       // temp counter
    int sp = -1;          // operand stack pointer

    printf("\n--- Three Address Code ---\n");

    for (int i = 0; postfix[i]; i++) {
        char c = postfix[i];
        if (isalnum(c)) {
            char str[2] = {c, '\0'};
            strcpy(tempVar[++sp], str);
        }
        else {
            char op2[10], op1[10], res[10];
            strcpy(op2, tempVar[sp--]);
            strcpy(op1, tempVar[sp--]);

            sprintf(res, "t%d", tCount++);
            printf("%s = %s %c %s\n", res, op1, c, op2);

            strcpy(tempVar[++sp], res);
        }
    }
    printf("Result stored in: %s\n", tempVar[sp]);
}

int main() {
    char infix[MAX], postfix[MAX];

    printf("Enter infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);

    printf("\nInfix:   %s", infix);
    printf("\nPostfix: %s\n", postfix);

    generateTAC(postfix);

    return 0;
}

