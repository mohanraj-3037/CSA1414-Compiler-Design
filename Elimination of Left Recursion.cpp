#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 20
#define SIZE 100

char prods[MAX][SIZE];
int n;

void eliminateLeftRec(char nt, char *rules) {
    char alpha[MAX][SIZE], beta[MAX][SIZE];
    int ac = 0, bc = 0;
    char *tok = strtok(rules, "|");

    while (tok) {
        if (tok[0] == nt) {
            strcpy(alpha[ac++], tok + 1); // remove leading nt
        } else {
            strcpy(beta[bc++], tok);
        }
        tok = strtok(NULL, "|");
    }

    if (ac == 0) {
        printf("%c->%s\n", nt, rules);
        return;
    }

    // print A -> betaA'
    printf("%c->", nt);
    for (int i = 0; i < bc; i++) {
        printf("%s%c'", beta[i], nt);
        if (i != bc - 1) printf("|");
    }
    printf("\n");

    // print A' -> alphaA'|e
    printf("%c'->", nt);
    for (int i = 0; i < ac; i++) {
        printf("%s%c'|", alpha[i], nt);
    }
    printf("e\n");
}

int main() {
    printf("Enter number of productions: ");
    scanf("%d", &n);
    getchar();

    for (int i = 0; i < n; i++) {
        printf("Enter production %d: ", i+1);
        fgets(prods[i], SIZE, stdin);
        prods[i][strcspn(prods[i], "\n")] = 0; // remove newline
    }

    printf("\nAfter eliminating left recursion:\n");
    for (int i = 0; i < n; i++) {
        char nt = prods[i][0];
        char *rhs = strchr(prods[i], '>') + 1;
        eliminateLeftRec(nt, rhs);
    }

    return 0;
}

