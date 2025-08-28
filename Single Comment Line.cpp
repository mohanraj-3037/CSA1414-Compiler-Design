#include <stdio.h>
int main(){
    FILE *f=fopen("input.c","r"); char c; int sp=0,nl=0;
    while((c=fgetc(f))!=EOF){ if(c==' '||c=='\t') sp++; else if(c=='\n') nl++; }
    printf("Whitespaces: %d\nNewlines: %d\n",sp,nl);
}

