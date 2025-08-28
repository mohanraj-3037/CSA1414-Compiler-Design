#include <stdio.h>
#include <string.h>

struct sym {
    char name[10];
    char type[10];
    char value[20];
    void *addr;
} table[20];

int n = 0;

void insert() {
    printf("Name Type Value: ");
    scanf("%s %s %s", table[n].name, table[n].type, table[n].value);
    table[n].addr = &table[n];   // store its address (symbol’s record)
    n++;
}

void display() {
    printf("\n%-10s %-10s %-10s %-15s\n", "Name", "Type", "Value", "Address");
    for (int i = 0; i < n; i++) {
        printf("%-10s %-10s %-10s %p\n",
               table[i].name,
               table[i].type,
               table[i].value,
               table[i].addr);
    }
}

int main() {
    int c;
    while (1) {
        printf("\n1.Insert 2.Display 3.Exit: ");
        scanf("%d", &c);
        if (c == 1) insert();
        else if (c == 2) display();
        else break;
    }
    return 0;
}

