#include <stdio.h>
#include <string.h>
char *ip; 
int E(),T();
int E(){ if(T()){ if(*ip=='+'){ ip++; return E(); } return 1;} return 0; }
int T(){ if(!strncmp(ip,"id",2)){ ip+=2; return 1;} return 0; }
int main(){
    char s[20]; printf("Enter string: "); scanf("%s",s); ip=s;
    if(E() && *ip=='\0') printf("Valid\n"); else printf("Invalid\n");
}

