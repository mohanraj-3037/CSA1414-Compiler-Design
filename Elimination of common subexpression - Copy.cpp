#include <stdio.h>
#include <string.h>

struct TAC {
    char res[10], arg1[10], op[5], arg2[10];
    int alive; // mark if instruction is needed
} code[50];

int n;

// Check if two TAC instructions compute the same expression
int sameExpr(struct TAC a, struct TAC b) {
    return (strcmp(a.op, b.op) == 0 &&
            strcmp(a.arg1, b.arg1) == 0 &&
            strcmp(a.arg2, b.arg2) == 0 &&
            strlen(a.op) > 0); // must be an operation
}

// Replace all uses of oldVar with newVar
void substitute(char oldVar[], char newVar[], int start) {
    for (int i = start; i < n; i++) {
        if (strcmp(code[i].arg1, oldVar) == 0)
            strcpy(code[i].arg1, newVar);
        if (strcmp(code[i].arg2, oldVar) == 0)
            strcpy(code[i].arg2, newVar);
    }
}

int main() {
    printf("Enter number of TAC instructions: ");
    scanf("%d", &n);
    getchar();

    for (int i = 0; i < n; i++) {
        char line[50];
        fgets(line, sizeof(line), stdin);
        line[strcspn(line, "\n")] = '\0';

        char res[10], arg1[10], op[5], arg2[10];
        int filled = sscanf(line, "%s = %s %s %s", res, arg1, op, arg2);

        strcpy(code[i].res, res);
        code[i].alive = 1;

        if (filled == 4) { // x = y op z
            strcpy(code[i].arg1, arg1);
            strcpy(code[i].op, op);
            strcpy(code[i].arg2, arg2);
        } else if (filled == 2) { // x = y
            strcpy(code[i].arg1, arg1);
            strcpy(code[i].op, "");
            strcpy(code[i].arg2, "");
        }
    }

    // Step 1: Common subexpression elimination
    for (int i = 0; i < n; i++) {
        if (strlen(code[i].op) == 0) continue; // skip assignments
        for (int j = 0; j < i; j++) {
            if (sameExpr(code[i], code[j])) {
                substitute(code[i].res, code[j].res, i+1);
                code[i].alive = 0; // eliminate duplicate
                break;
            }
        }
    }

    // Step 2: Dead code elimination (remove unused temporaries)
    for (int i = 0; i < n; i++) {
        if (!code[i].alive) continue;
        if (code[i].res[0] == 't') { // temp variable
            int used = 0;
            for (int j = i+1; j < n; j++) {
                if (strcmp(code[j].arg1, code[i].res) == 0 ||
                    strcmp(code[j].arg2, code[i].res) == 0) {
                    used = 1;
                    break;
                }
            }
            if (!used) code[i].alive = 0;
        }
    }

    // Final optimized TAC
    printf("\n--- Optimized TAC ---\n");
    for (int i = 0; i < n; i++) {
        if (!code[i].alive) continue;
        if (strlen(code[i].op) == 0)
            printf("%s = %s\n", code[i].res, code[i].arg1);
        else
            printf("%s = %s %s %s\n", code[i].res, code[i].arg1, code[i].op, code[i].arg2);
    }
    return 0;
}

