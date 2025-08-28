#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 50
#define SIZE 200

char prods[MAX][SIZE];
int n;

void strip_spaces(char *s) {
    char t[SIZE]; int k=0;
    for (int i=0; s[i]; i++) if (s[i] != ' ') t[k++] = s[i];
    t[k] = '\0'; strcpy(s, t);
}

void leftFactor(char *prod) {
    // prod form: A->rhs
    char LHS[10];
    LHS[0] = prod[0];
    LHS[1] = '\0';
    char *arrow = strstr(prod, "->");
    if (!arrow) return;
    char rhs[SIZE];
    strcpy(rhs, arrow + 2);

    // accept '/' as alternative separator as well as '|'
    for (int i=0; rhs[i]; i++) if (rhs[i] == '/') rhs[i] = '|';

    // split alternatives
    char *alts[50];
    int count = 0;
    char copy[SIZE];
    strcpy(copy, rhs);
    char *tok = strtok(copy, "|");
    while (tok && count < 50) {
        alts[count++] = strdup(tok);
        tok = strtok(NULL, "|");
    }
    if (count == 0) return;

    // find longest common prefix among alternatives
    int prefixLen = strlen(alts[0]);
    for (int i = 1; i < count; i++) {
        int j = 0;
        while (j < prefixLen && alts[0][j] == alts[i][j]) j++;
        prefixLen = j;
    }

    if (prefixLen == 0) {
        // no factoring possible, print original (use '|' to join)
        printf("%s->", LHS);
        for (int i=0;i<count;i++) {
            printf("%s", alts[i]);
            if (i != count-1) printf("|");
        }
        printf("\n");
    } else {
        // print factored production: A-> prefix A'
        // use A' as new nonterminal (LHS + ')
        printf("%s->", LHS);
        // print prefix
        for (int k = 0; k < prefixLen; k++) putchar(alts[0][k]);
        printf("%s'\n", LHS);

        // print A' -> remaining parts (if empty => e)
        printf("%s'->", LHS);
        for (int i = 0; i < count; i++) {
            if ((int)strlen(alts[i]) == prefixLen) {
                printf("e");
            } else {
                printf("%s", alts[i] + prefixLen);
            }
            if (i != count - 1) printf("|");
        }
        printf("\n");
    }

    // free duplicates
    for (int i=0;i<count;i++) free(alts[i]);
}

int main() {
    printf("Enter number of productions: ");
    if (scanf("%d", &n) != 1) return 0;
    getchar(); // consume newline

    for (int i = 0; i < n; i++) {
        fgets(prods[i], SIZE, stdin);
        prods[i][strcspn(prods[i], "\n")] = 0; // remove newline
        strip_spaces(prods[i]);
    }

    printf("\nAfter Left Factoring:\n");
    for (int i = 0; i < n; i++) leftFactor(prods[i]);

    return 0;
}

