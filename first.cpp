#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 20
#define SIZE 100

char prods[MAX][SIZE];
char nonTerminals[MAX][SIZE];
char firstSets[MAX][SIZE];
int n, ntCount = 0;

int isTerminal(char c) {
    return !(isupper(c));
}

int findIndex(char *nt) {
    for (int i = 0; i < ntCount; i++) {
        if (strcmp(nonTerminals[i], nt) == 0) return i;
    }
    return -1;
}

void addToFirst(int idx, char c) {
    int len = strlen(firstSets[idx]);
    for (int i = 0; i < len; i++) {
        if (firstSets[idx][i] == c) return;
    }
    firstSets[idx][len] = c;
    firstSets[idx][len+1] = '\0';
}

void computeFirst(char *nt);

void processRHS(int idx, char *rhs) {
    if (rhs[0] == '\0') return;

    // If terminal symbol
    if (isTerminal(rhs[0])) {
        addToFirst(idx, rhs[0]);
    } else {
        // extract nonterminal (can be A or A')
        char temp[SIZE] = "";
        int k = 0;
        temp[k++] = rhs[0];
        if (rhs[1] == '\'') temp[k++] = rhs[1];
        temp[k] = '\0';

        int pos = findIndex(temp);
        if (pos != -1) {
            computeFirst(temp);
            for (int i = 0; i < strlen(firstSets[pos]); i++) {
                if (firstSets[pos][i] != 'e')
                    addToFirst(idx, firstSets[pos][i]);
            }
        }
    }
}

void computeFirst(char *nt) {
    int idx = findIndex(nt);
    if (firstSets[idx][0] != '\0') return; // already computed

    for (int i = 0; i < n; i++) {
        // extract LHS
        char lhs[SIZE];
        int j = 0, k = 0;
        lhs[k++] = prods[i][j++];
        if (prods[i][j] == '\'') lhs[k++] = prods[i][j++];
        lhs[k] = '\0';

        if (strcmp(lhs, nt) == 0) {
            char *rhs = strchr(prods[i], '>') + 1;
            char copy[SIZE];
            strcpy(copy, rhs);

            char *tok = strtok(copy, "|");
            while (tok) {
                processRHS(idx, tok);
                tok = strtok(NULL, "|");
            }
        }
    }
}

int main() {
    printf("Enter number of productions: ");
    scanf("%d", &n);
    getchar();

    for (int i = 0; i < n; i++) {
        fgets(prods[i], SIZE, stdin);
        prods[i][strcspn(prods[i], "\n")] = 0;

        // extract LHS
        char lhs[SIZE];
        int j = 0, k = 0;
        lhs[k++] = prods[i][j++];
        if (prods[i][j] == '\'') lhs[k++] = prods[i][j++];
        lhs[k] = '\0';

        if (findIndex(lhs) == -1) {
            strcpy(nonTerminals[ntCount], lhs);
            firstSets[ntCount][0] = '\0';
            ntCount++;
        }
    }

    printf("\nFIRST sets:\n");
    for (int i = 0; i < ntCount; i++) {
        computeFirst(nonTerminals[i]);
        printf("FIRST(%s) = { ", nonTerminals[i]);
        for (int j = 0; j < strlen(firstSets[i]); j++) {
            printf("%c ", firstSets[i][j]);
        }
        printf("}\n");
    }

    return 0;
}

