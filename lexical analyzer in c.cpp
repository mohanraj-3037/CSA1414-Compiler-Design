#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main() {
    FILE *f=fopen("input.c","r"); char c,s[30]; int i;
    while((c=fgetc(f))!=EOF){
        if(isspace(c)) continue;
        if(c=='/'){ char n=fgetc(f);
            if(n=='/') while((c=fgetc(f))!='\n'&&c!=EOF);
            else if(n=='*') while((c=fgetc(f))!=EOF) if(c=='*'&&(c=fgetc(f))=='/') break;
            else {ungetc(n,f); printf("Op: /\n");}
            continue;
        }
        if(isalnum(c)||c=='_'){
            i=0; s[i++]=c;
            while((c=fgetc(f))!=EOF&&(isalnum(c)||c=='_')) s[i++]=c;
            s[i]=0; ungetc(c,f);
            printf("%s: %s\n", isdigit(s[0])?"Const":"Id", s);
        }
        else if(strchr("+-*=%<>&|!^",c)) printf("Op: %c\n",c);
    }
}

