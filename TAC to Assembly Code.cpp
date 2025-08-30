#include <stdio.h>

int main() {
    int n,i; char code[20][20],lhs[10],a,b,op,c;
    printf("Enter number of 3AC statements: "); scanf("%d",&n);
    printf("Enter statements:\n");
    for(i=0;i<n;i++) scanf("%s",code[i]);

    printf("\nAssembly Code:\n");
    for(i=0;i<n;i++){
        sscanf(code[i],"%[^=]=%c%c%c",lhs,&a,&op,&c);
        printf("MOV R%d,%c\n",i+1,a);
        if(op=='+') printf("ADD R%d,%c\n",i+1,c);
        else if(op=='-') printf("SUB R%d,%c\n",i+1,c);
        else if(op=='*') printf("MUL R%d,%c\n",i+1,c);
        else if(op=='/') printf("DIV R%d,%c\n",i+1,c);
        printf("MOV %s,R%d\n",lhs,i+1);
    }
    return 0;
}

