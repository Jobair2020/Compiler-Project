%{
    #include <stdio.h>
    #include <string.h>
    #include "bison.tab.h"
    int yylineno = 1;
%}

ID                [a-zA-Z][_a-zA-Z0-9]*


%%
"import"[ ]+[<]{ID}[.][h][ ]*[>] {
    printf("Header file included\n");
    return HEADER;
}

";" {
    return EOL;
}

"#"[ ]* {
    char comment[1000];
    int i = 0;
    while(1) {
        char c = input();
        if(c == '\n' || c == EOF) {
            comment[i] = '\0';
            break;
        }
        comment[i++] = c;
    }
    printf("Single line comment deteted. The Comment is: \n");
    printf("%s\n", comment);
    return SCOM;
}

"/*"[ ]* {
    char comment[1000];
    int i = 0;
    while(1) {
        char c = input();
        if(c == '*') {
            char d = input();
            if(d == '/') {
                comment[i++] = '\0';
                break;
            }
            comment[i++] = (c == '\n') ? ' ' : c;
            comment[i++] = (d == '\n') ? ' ' : c;
        } else {
            if(comment[i - 1] == '*' && c == '/') {
                comment[i - 1] = '\0';
                break;
            }
            comment[i++] = (c == '\n') ? ' ' : c;
        }
    }
    printf("Multiline commment detected! The Comment is: \n");
    printf("%s\n", comment);
    return MCOM;
}


"for" {
    return FOR;
}
"in" {
    return IN;
}
"repeat" {
    return WHILE;
}
"fun" {
    return FUN;
}
"switch" {
    return SWITCH;
}
"int"[ ]+ {
    return INT_TYPE;
}

"float"[ ]+ {
    return FLOAT_TYPE;
}
"string"[ ]+ {
    return STRING_TYPE;
}

"scan" {
    return INPUT;
}
"print" {
    return PRINT;
}
"if" {
    return IF;
}
"else if" {
    return ELSIF;
}
"else" {
    return ELSE;
}

"case" {
    return CASE;
}
"default" {
    return DEFAULT;
}

">>" {
    return ARROW;
}
"call" {
    return CALL;
}
"++" {
    return INC;
}

"--" {
    return DEC;
}
"==" {
    return EQ;
}										
"!=" {
    return NE;
}
"<" {
    return LT;
}
">" {
    return GT;
}
"<=" {
    return LE;
}
">=" {
    return GE;
}
"&&" {
    return AND;
}
"||" {
    return OR;
}
"^^" {
    return XOR;
}
"~" {
    return NOT;
}
"^" {
    return POW;
}
"sin" {
    return SIN;
}
"cos" {
    return COS;
}
"tan" {
    return TAN;
}
"log10" {
    return LOG10;
}
"log2" {
    return LOG2;
}
"ln" {
    return LN;
}
"sqrt" {
    return SQRT;
}
"fact" {
    return FACT;
}
"prime" {
    return PRIME;
}
"abs" {
    return ABS;
}
"arr" {
    return ARR;
}

{ID} {
    yylval.string = strdup(yytext);
    return VARIABLE;
 }

[0-9]+ {
    yylval.integer = atoi(yytext);
    return INT_VALUE;
}

[0-9]+[.][0-9]+ {
    yylval.real = atof(yytext);
    return FLOAT_VALUE;
}

\"(\\.|[^"\\])*\" {
    char* tmp = strdup(yytext);
    int n = strlen(tmp);
    yylval.string = malloc(n * sizeof(char));
    //starts after quatasion and ends before quatasion.
    memcpy(yylval.string, &tmp[1], n  - 2);
    yylval.string[n - 2]= '\0';
    return STRING_VALUE;
}


[ \t] { }
[\n] { yylineno++; }

[-+/*<>=,();:%^{}\[\]] {
    return yytext[0];
}
. {
    printf("Unknown Character. %s\n", yytext);
}


%%
int yywrap() {
    return 1;
}

int yyerror(char *s){
	fprintf(stderr,"error: %s in line %d\n", s,yylineno);
    return 1;
}