#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 20
#define SIZE 100

char prods[MAX][SIZE];
char nonTerminals[MAX][SIZE];
char firstSets[MAX][SIZE];
char followSets[MAX][SIZE];
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

void addUnique(char *set, char c) {
    if (strchr(set, c) == NULL) {
        int l = strlen(set);
        set[l] = c;
        set[l+1] = '\0';
    }
}

void addSet(char *dest, char *src) {
    for (int i = 0; i < strlen(src); i++) {
        if (src[i] != 'e') addUnique(dest, src[i]);
    }
}

// ---------------- FIRST ----------------
void computeFirst(char *nt);

void processRHS_First(int idx, char *rhs) {
    if (rhs[0] == '\0') return;

    if (isTerminal(rhs[0])) {
        addUnique(firstSets[idx], rhs[0]);
    } else {
        char temp[SIZE] = "";
        int k = 0;
        temp[k++] = rhs[0];
        if (rhs[1] == '\'') temp[k++] = rhs[1];
        temp[k] = '\0';

        int pos = findIndex(temp);
        if (pos != -1) {
            computeFirst(temp);
            addSet(firstSets[idx], firstSets[pos]);
        }
    }
}

void computeFirst(char *nt) {
    int idx = findIndex(nt);
    if (firstSets[idx][0] != '\0') return;

    for (int i = 0; i < n; i++) {
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
                processRHS_First(idx, tok);
                tok = strtok(NULL, "|");
            }
        }
    }
}

// ---------------- FOLLOW ----------------
void computeFollow() {
    // Rule 1: add $ to start symbol
    addUnique(followSets[0], '$');

    int changed = 1;
    while (changed) {
        changed = 0;

        for (int i = 0; i < n; i++) {
            // extract LHS
            char lhs[SIZE];
            int j = 0, k = 0;
            lhs[k++] = prods[i][j++];
            if (prods[i][j] == '\'') lhs[k++] = prods[i][j++];
            lhs[k] = '\0';
            int lhsIndex = findIndex(lhs);

            char *rhs = strchr(prods[i], '>') + 1;
            char symbols[SIZE];
            strcpy(symbols, rhs);

            int len = strlen(symbols);
            for (int s = 0; s < len; s++) {
                if (isupper(symbols[s])) {
                    char cur[SIZE] = "";
                    int t = 0;
                    cur[t++] = symbols[s];
                    if (symbols[s+1] == '\'') cur[t++] = symbols[++s];
                    cur[t] = '\0';

                    int curIndex = findIndex(cur);

                    // check what follows this non-terminal
                    if (s+1 < len) {
                        // next symbol exists
                        if (isTerminal(symbols[s+1])) {
                            if (!strchr(followSets[curIndex], symbols[s+1])) {
                                addUnique(followSets[curIndex], symbols[s+1]);
                                changed = 1;
                            }
                        } else {
                            // next is a non-terminal
                            char nxt[SIZE] = "";
                            int u = 0;
                            nxt[u++] = symbols[s+1];
                            if (symbols[s+2] == '\'') nxt[u++] = symbols[s+2];
                            nxt[u] = '\0';

                            int nxtIndex = findIndex(nxt);
                            addSet(followSets[curIndex], firstSets[nxtIndex]);

                            if (strchr(firstSets[nxtIndex], 'e')) {
                                addSet(followSets[curIndex], followSets[lhsIndex]);
                            }
                        }
                    } else {
                        // if at end, FOLLOW(lhs) ? FOLLOW(cur)
                        addSet(followSets[curIndex], followSets[lhsIndex]);
                    }
                }
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

        char lhs[SIZE];
        int j = 0, k = 0;
        lhs[k++] = prods[i][j++];
        if (prods[i][j] == '\'') lhs[k++] = prods[i][j++];
        lhs[k] = '\0';

        if (findIndex(lhs) == -1) {
            strcpy(nonTerminals[ntCount], lhs);
            firstSets[ntCount][0] = '\0';
            followSets[ntCount][0] = '\0';
            ntCount++;
        }
    }

    // compute FIRST for all
    for (int i = 0; i < ntCount; i++) {
        computeFirst(nonTerminals[i]);
    }

    // compute FOLLOW
    computeFollow();

    printf("\nFOLLOW sets:\n");
    for (int i = 0; i < ntCount; i++) {
        printf("FOLLOW(%s) = { ", nonTerminals[i]);
        for (int j = 0; j < strlen(followSets[i]); j++) {
            printf("%c ", followSets[i][j]);
        }
        printf("}\n");
    }

    return 0;
}

