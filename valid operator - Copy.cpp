#include <stdio.h>
#include <string.h>

int isOperator(char c) {
    // Single-character operators
    char ops[] = "+-*/%=&|<>!^";
    for (int i = 0; ops[i] != '\0'; i++) {
        if (c == ops[i])
            return 1;
    }
    return 0;
}

int main() {
    char op[3]; // to handle 1 or 2 character operators
    printf("Enter operator: ");
    scanf("%s", op);

    if (strlen(op) == 1) {
        if (isOperator(op[0]))
            printf("Valid operator.\n");
        else
            printf("Invalid operator.\n");
    }
    else if (strlen(op) == 2) {
        // Check common 2-character operators
        if (strcmp(op, "==") == 0 || strcmp(op, "!=") == 0 ||
            strcmp(op, "<=") == 0 || strcmp(op, ">=") == 0 ||
            strcmp(op, "&&") == 0 || strcmp(op, "||") == 0 ||
            strcmp(op, "++") == 0 || strcmp(op, "--") == 0 ||
            strcmp(op, "+=") == 0 || strcmp(op, "-=") == 0 ||
            strcmp(op, "*=") == 0 || strcmp(op, "/=") == 0 ||
            strcmp(op, "%=") == 0 )
            printf("Valid operator.\n");
        else
            printf("Invalid operator.\n");
    }
    else {
        printf("Invalid operator.\n");
    }

    return 0;
}

