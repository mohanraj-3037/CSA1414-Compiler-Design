#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

char stack[MAX];
int top = -1;

void push(char c) {
    stack[++top] = c;
}

char pop() {
    if (top == -1) return '\0';
    return stack[top--];
}

void printStack() {
    for (int i = 0; i <= top; i++) printf("%c", stack[i]);
    printf("\t");
}

// Check for reducible pattern and reduce
int reduce() {
    // Try to reduce "id" -> E
    if (top >= 0 && stack[top] == 'i') {
        stack[top] = 'E';
        printf("REDUCE: id -> E\n");
        return 1;
    }
    // Try to reduce "E+E" -> E
    if (top >= 2 && stack[top-2] == 'E' && stack[top-1] == '+' && stack[top] == 'E') {
        top -= 2; // remove '+E'
        stack[top] = 'E';
        printf("REDUCE: E+E -> E\n");
        return 1;
    }
    // Try to reduce "E*E" -> E
    if (top >= 2 && stack[top-2] == 'E' && stack[top-1] == '*' && stack[top] == 'E') {
        top -= 2; // remove '*E'
        stack[top] = 'E';
        printf("REDUCE: E*E -> E\n");
        return 1;
    }
    return 0; // nothing to reduce
}

int main() {
    char input[100], symbol;
    printf("Enter input string (use 'i' for identifier): ");
    scanf("%s", input);

    printf("Stack\tInput\tAction\n");
    int i = 0;
    while (input[i] != '\0') {
        // SHIFT
        symbol = input[i++];
        push(symbol);
        printf("SHIFT\t");
        printStack();
        printf("%s\n", &input[i]);

        // Try REDUCE repeatedly
        while (reduce()) {
            printStack();
            printf("%s\n", &input[i]);
        }
    }

    // Final reductions
    while (reduce()) {
        printStack();
        printf("\n");
    }

    if (top == 0 && stack[top] == 'E')
        printf("\nInput Accepted!\n");
    else
        printf("\nInput Rejected!\n");

    return 0;
}

