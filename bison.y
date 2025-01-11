%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <math.h>

    extern int yylex(void);
    int yyerror(char* s);

    const int MAX = 100;
    const int MAX_FUN = 50;
    int varCount = 0;
    int funCount = 0;
    int conditionMatch = 0;
    int currentFun = 0;
    int currentParameter = 0;
    int functionRejected = 0;

    int maincase = 0,subcase = 0;
    double dmaincase = 0, dsubcase = 0;

    #define YYDEBUG 1
    #define UNIQUE 1
    #define DUPLICATE -1
    #define NUMBER  1
    #define FLOAT 2
    #define STRING 3

    typedef struct {
        char *name;
        int type;
        int length;
        int *ival;
        double *dval;
        char **sval;
        int is_array;
    } varStruct;
    varStruct *varptr;

    typedef struct {
        char *fname;
        varStruct *fptr;
        int var_cnt;
    } funStruct;
    funStruct *funcptr;

    void var_does_not_exist(char *name) {
        printf("variable \"%s\" doesn't exist.\n", name);
    }
    int check_unique(char *name) {
        for(int i = 0; i < varCount; ++i) {
            if(strcmp(varptr[i].name, name) == 0) {
                return DUPLICATE;
            }
        }
        return UNIQUE;
    } 

    
    int get_var_index(char *name) {
        for(int i = 0; i < varCount; ++i) {
            if(strcmp(varptr[i].name, name) == 0) {
                return i;
            }
        }
        return -1;
    }
    void store_value(char *n, int t, int l, int p, void *v, int is_Array) {
        varptr[p].name = n;
        varptr[p].type = t;
        varptr[p].length = l;
        varptr[p].is_array = is_Array;
        if(t == NUMBER) {
            int *value = (int *) v;
            varptr[p].ival = malloc(l * sizeof(int));
            for(int i = 0; i < l; ++i) {
                varptr[p].ival[i] = value[i];
            }
            printf("Variable name is: %s", varptr[p].name);
            printf(" and value is: %d\n", *varptr[p].ival);
        } else if(t == FLOAT) {
            double *value = (double *) v;
            varptr[p].dval = malloc(l * sizeof(double));
            for(int i = 0; i < l; ++i) {
                varptr[p].dval[i] = value[i];
            }
            printf("Variable name is: %s", varptr[p].name);
            printf(" and value is: %lf\n", *varptr[p].dval);
        } else if(t == STRING) {
            char **s = ((char**) v);
            varptr[p].sval = malloc(l * sizeof(char**));
            for(int i = 0; i < l; ++i) {
                varptr[p].sval[i] = s[i];
            }
            printf("Variable name is: %s", varptr[p].name);
            printf(" and value is: %s\n", *varptr[p].sval);
        }
    }
    void read_value(char *name) {
        int p = 0 ;
        printf("Scan Input for %s: ", name);
        int index = get_var_index(name);
        printf("index: %d\n", index);
        if (index == -1) {
            var_does_not_exist(name);
        } else {
            if(p >= varptr[index].length) {
                printf("Maximum Number of Variables Used.\n");
            } else {
                if (varptr[index].type == FLOAT) {
                    scanf("%lf", &varptr[index].dval[p]);
                } else if (varptr[index].type == NUMBER) {
                    scanf("%d", &varptr[index].ival[p]);
                    printf("%d\n", varptr[index].ival[p]);
                } else if(varptr[index].type == STRING) {
                    char str [1000];
                    scanf("%s", str);
                    varptr[index].sval[p] = str;
                }
            }
        }
    }
    void show_value(char *name) {
        int index = get_var_index(name);
        if(index == -1) {
            var_does_not_exist(name);
        } else {
            if(varptr[index].is_array) {
                //array print.
            } else {
                printf("Value of %s is: ", name);
                if(varptr[index].type == NUMBER) {
                    printf("%d\n", varptr[index].ival[0]);
                } else if(varptr[index].type == FLOAT) {
                    printf("%lf\n", varptr[index].dval[0]);
                } else if(varptr[index].type == STRING) {
                    printf("%s\n", varptr[index].sval[0]);
                }
            }
        }
    }

    void not_unique(char *name) {
        printf("variable \"%s\" already exists.\n", name);
    }

    
    
    int get_function_index(char *name){
        for(int i = 0; i < funCount; ++i) {
            if(strcmp(funcptr[i].fname, name) == 0) {
                return i;
            }
        }
        return -1;
    }
    unsigned long long factorial(int n) {
        if (n == 0 || n == 1) {
            return 1;
        } else {
            return n * factorial(n - 1);
        }
        return -1;
    }

    int prime(int n) {    
        if (n <= 1) {
            printf(" not Prime\n");
            return 0;
        } else {
            int is_prime = 1;  
            for (int i = 2; i <= n / 2; i++) {
                if (n % i == 0) {
                    is_prime = 0;
                    break;  
                }
            }
            if (is_prime) {
                printf(" prime\n");
                return 0;
            } else {
                printf(" not prime\n");
                return 1;
            }
        }
        
    }

%}

%error-verbose
%debug
%union {
	int integer;
	double real;
	char *string;
}

%token HEADER SCOM MCOM EOL VARIABLE ARROW INPUT PRINT INT_TYPE FLOAT_TYPE STRING_TYPE INT_VALUE FLOAT_VALUE STRING_VALUE 
%token ARR SWITCH CASE DEFAULT POW SIN COS TAN LOG10 LOG2 LN SQRT FACT PRIME ABS AND OR XOR NOT INC DEC LT GT EQ NE LE GE IF ELSIF ELSE FOR IN WHILE FUN CALL

%type <integer> INT_VALUE 
%type <real> FLOAT_VALUE statements assignment expr while_conditions 
%type <string> VARIABLE INT_TYPE FLOAT_TYPE STRING_TYPE STRING_VALUE

%nonassoc IFO
%nonassoc ELSIF 
%nonassoc ELSE

%left INC DEC
%left AND OR XOR NOT
%left LT GT EQ NE LE GE
%left '+' '-'
%left '*' '/' '%'

%%

program:
    HEADER statements {  printf("\n\nCOMPILATION SUCCESSFUL!\n"); }
    | statements {  printf("\n\nCOMPILATION SUCCESSFUL!\n"); }
;

statements: {}
    |statements statement
;

statement: 
    EOL
    |statement EOL statement
    |SCOM
    |MCOM
    |input EOL
    |print EOL
    |declarations EOL
    |assignments EOL
    |if_blocks { conditionMatch = 0; }
    |for_loop
    |while_loop
    |function_declare
    |function_call EOL
    |switch_statements {printf("*** switch block*****\n");}
    |array_int EOL
    |assign_array EOL
;

array_int : INT_TYPE ARR VARIABLE '[' INT_VALUE ']' {
  

    printf("array %s is declared of size %d\n",$3,$5);
}
;
assign_array: VARIABLE '[' INT_VALUE ']' '=' expr {
    printf("array %s [ %d ] assigned to %.2f",$1,$3,$6);
}
;

print:
    PRINT '(' output_var ')' { }
    |PRINT '(' STRING_VALUE ')' { printf("%s\n",$3);}
    
;
output_var:
    output_var ',' VARIABLE { show_value($3);}
    |VARIABLE { show_value($1); }
;

input:
    INPUT '(' in_vars ')' { printf("Enter input from console\n"); }
;

in_vars:
    in_vars ',' VARIABLE { read_value($3);}
    |VARIABLE { read_value($1); }

function_declare:
    FUN function_name '(' fun_var ')' ARROW return_types '{' statements '}' {}
;
return_types:
    INT_TYPE
    |FLOAT_TYPE
    |STRING_TYPE
;

function_name:
    VARIABLE {
        int index = get_function_index($1);
        if(index != -1) {
            printf("Function Already Declared.\n");
        } else {
            printf("Declaring Function\n");
            funcptr[funCount].fname = malloc((strlen($1) + 10) * sizeof(char));
            strcpy(funcptr[funCount].fname, $1);
            funcptr[funCount].var_cnt = 0;
            funcptr[funCount].fptr = malloc(4 * sizeof(funStruct));
        }
    }
fun_var:
    |fun_var ',' parameter_var
    | parameter_var
;

parameter_var:
    INT_TYPE VARIABLE {
        int index = funcptr[funCount].var_cnt;
        int value = 0;
        store_value($2, NUMBER, 1, varCount, &value, 0);
        funcptr[funCount].fptr[index] = varptr[varCount];
        varCount++;
        funcptr[funCount].var_cnt++;
        funCount++;
    }
    |FLOAT_TYPE VARIABLE {
        int index = funcptr[funCount].var_cnt;
        double value = 0;
        store_value($2, FLOAT, 1, varCount, &value, 0);
        funcptr[funCount].fptr[index] = varptr[varCount];
        varCount++;
        funcptr[funCount].var_cnt++;
        funCount++;
    }
;

function_call:
    CALL fun_call_name '(' parameters ')' {
        if(functionRejected) {
            printf("Function Not Declared.\n");
        } else {
            printf("Function Successfully Called.\n");
        }
    }
;

fun_call_name:
    VARIABLE {
        int index = get_function_index($1);
        if(index == -1) {
            printf("Function Doesn't Exist.\n");
        } else {
            currentFun = index;
            currentParameter = 0;
            functionRejected = 0;
        }
    }
;

parameters:
    parameters ',' single_parameter
    |single_parameter
;

single_parameter: 
    VARIABLE {
        int index = get_var_index($1);
        if(currentParameter >= funcptr[currentFun].var_cnt) {
            printf("Way too many arguments.\n");
            functionRejected = 1;
        } else if(funcptr[currentFun].fptr[currentParameter].type != varptr[index].type) {
            printf("Data Types Don't Match.\n");
            functionRejected = 1;
        } else {
            currentParameter++;
        }
    }
;
// switch case rules.......
switch_statements:
    SWITCH '(' INT_VALUE ')' '{' case_stmts '}' {
        maincase =(int)$3;
        printf("Inside switch statement int value %d\n",$3);
    }
    |SWITCH '(' FLOAT_VALUE ')' '{' case_stmts '}' {
            dmaincase =(double)$3;
        printf ("Inside switch statement double %f\n",$3);
    }
    |SWITCH '(' VARIABLE ')' '{' case_stmts '}' {
        int i = get_var_index($3);
        if(i == -1) {
            var_does_not_exist($3);
            
        } else if(varptr[i].type == NUMBER) {
            maincase = varptr[i].ival[0];
        } else if(varptr[i].type == FLOAT) {
            dmaincase = varptr[i].dval[0];
        }
        printf ("Inside switch statement with variable name %s and value \n",$3);
    }

;
    
case_stmts: case_stmt
| case_stmt def_stmt
| case_stmt case_stmts

;

case_stmt: CASE INT_VALUE ':' statements  {
    subcase = (int)$2;
    printf("inside int case %d : \n",$2);
    
    if(maincase == subcase) {
        printf("%d matched\n",subcase);
    }else{
        printf("%d doen't match\n",subcase);
    }
    subcase = 0;
    
    }
    |CASE FLOAT_VALUE ':' statements  {
    dsubcase = (double) $2;
    if(dmaincase == dsubcase){
        printf("%.2lf matched\n",dsubcase);
     }else{
        printf("%.2lf not matched\n",dsubcase);
     }
    dsubcase = 0;
    }
;

def_stmt: DEFAULT ':' statements {
  printf("default case from switch case\n");
}
;

for_loop:
    FOR VARIABLE IN '[' expr ',' expr ',' expr ']' '{' statements '}' {
        printf("**** For Loop Block ****\n");
        int from = $5;
        int to = $7;
        int inc = $9;
        int sub = to - from;
        if(sub * inc < 0) {
            printf("Infinite FOR Loop\n");
        } else {
            int c = 1;
            for(int i = from; i <= to; i += inc) {
                printf("For Loop Iteration: %d\n", c);
                c++;
            }
        }
    }
while_loop:
    WHILE '(' while_conditions ')' '{' statements '}' {
        printf("*** WHILE BLOCK ***\n");
        for(int i = 0; i < $3; ++i) {
            printf("Repeat Loop Iteration: %d\n", i + 1);
        }
    }
while_conditions:
    VARIABLE INC LT expr {
        int index = get_var_index($1);
        if(index == -1) {
            var_does_not_exist($1);
        } else if(varptr[index].type != NUMBER) {
            printf("Variable should be NUMBER Type.\n");
        } else {
            int value = varptr[index].ival[0];
            if(value > $4) {
                $$ = -1;
            } else {
                $$ = (int) $4 - value;
            }
        }
    }
    |VARIABLE INC LE expr {
        int index = get_var_index($1);
        if(index == -1) {
            var_does_not_exist($1);
        } else if(varptr[index].type != NUMBER) {
            printf("Variable should be NUMBER Type.\n");
        } else {
            int value = varptr[index].ival[0];
            if(value > $4) {
                $$ = -1;
            } else {
                $$ = (int) $4 - value + 1;
            }
        }
    }
    |VARIABLE INC NE expr {
        int index = get_var_index($1);
        if(index == -1) {
            var_does_not_exist($1);
        } else if(varptr[index].type != NUMBER) {
            printf("Variable should be NUMBER Type.\n");
        } else {
            int value = varptr[index].ival[0];
            if(value > $4) {
                $$ = -1;
            } else {
                $$ = (int) $4 - value;
            }
        }
    }
    |VARIABLE DEC GT expr {
        int index = get_var_index($1);
        if(index == -1) {
            var_does_not_exist($1);
        } else if(varptr[index].type != NUMBER) {
            printf("Variable should be NUMBER Type.\n");
        } else {
            int value = varptr[index].ival[0];
            if(value < $4) {
                $$ = -1;
            } else {
                $$ = value - (int) $4;
            }
        }
    }
    |VARIABLE DEC GE expr {
        int index = get_var_index($1);
        if(index == -1) {
            var_does_not_exist($1);
        } else if(varptr[index].type != NUMBER) {
            printf("Variable should be NUMBER Type.\n");
        } else {
            int value = varptr[index].ival[0];
            if(value < $4) {
                $$ = -1;
            } else {
                $$ = value - (int) $4 + 1;
            }
        }
    }
    |VARIABLE DEC NE expr {
        int index = get_var_index($1);
        if(index == -1) {
            var_does_not_exist($1);
        } else if(varptr[index].type != NUMBER) {
            printf("Variable should be NUMBER Type.\n");
        } else {
            int value = varptr[index].ival[0];
            if(value < $4) {
                $$ = -1;
            } else {
                $$ = value - (int) $4;
            }
        }
    }
;

if_blocks:
    IF if_block else_part { printf("******if else block finished*******\n\n"); }
    | IF if_block %prec IFO { printf("***only if block finished*****\n\n");}
    

if_block:
    '(' expr ')' '{' statement '}' {
        printf("<<< IF BLOCK >>>\n");
        int condition = (fabs($2) > 1e-9);
        if(condition) {
            conditionMatch = 1;
            printf("Condition Matched in if Block.\n");
        } else {
            printf("Condition Didn't match in if Block.\n");
        }
    }
    | '(' expr ')' '{' if_blocks '}' { printf("*****Nested if else found********\n\n"); }
else_part:
    |elif_part
    |elif_part single_else_part
    |single_else_part
;

elif_part:
    elif_part single_elif_part
    | single_elif_part
;
single_elif_part:
    ELSIF '(' expr ')' '{' statement '}' {
        if(conditionMatch == 1) {
            printf("Condition Already Matched in IF Block.\n");
        } else {
            int condition = (fabs($3) > 1e-9);
            if(condition) {
                printf("Condition Matched in else if Block.\n");
                conditionMatch = 1;
            } else {
                printf("Condition Didn't Match in else if Block.\n");
            }
        }
    }
    ;

single_else_part:
    ELSE '{' statement '}' {
        if(conditionMatch == 1) {
            printf("Condition Already Matched.\n");
        } else {
            printf("Condition Matched in ELSE Block.\n");
        }
    }
    ;


declarations:
    INT_TYPE int_vars
    |FLOAT_TYPE float_vars
    |STRING_TYPE str_vars
;

str_vars:
    str_vars ',' str_var
    |str_var
;
str_var:
    VARIABLE '=' STRING_VALUE {
        int exists = check_unique($1);
        if(exists == DUPLICATE) {
            not_unique($1);
        } else {
            char *value = $3;
            store_value($1, STRING, 1, varCount, &value, 0);
            varCount++;
        }
    }
    |VARIABLE {
        char *value = "";
        store_value($1, STRING, 1, varCount, &value, 0);
        varCount++;
    }
    ;
float_vars:
    float_vars ',' float_var
    |float_var
;
float_var:
    VARIABLE '=' expr {
        if(check_unique($1) == DUPLICATE) {
            not_unique($1);
        } else {
            double value = $3;
            store_value($1, FLOAT, 1, varCount, &value, 0);
            varCount++;
        }
    }
    |VARIABLE {
        double value = 0.0;
        store_value($1, FLOAT, 1, varCount, &value, 0);
        varCount++;
    }

int_vars: 
    int_vars ',' int_var
    |int_var
;

int_var: 
    VARIABLE '=' expr {
        if(check_unique($1) == UNIQUE) {
            int value = $3;
            store_value($1, NUMBER, 1, varCount, &value, 0);
            varCount++;
        } else {
            not_unique($1);
        }
    }
    |VARIABLE {
        int value = 0;
        store_value($1, NUMBER, 1, varCount, &value, 0);
        varCount++;
    }
;

assignments:
    assignments ',' assignment
    |assignment
;

assignment:
    VARIABLE '=' expr {
        int i = get_var_index($1);
        if(i == -1) {
            var_does_not_exist($1);
            $$ = 0;
        } else if(varptr[i].type == NUMBER) {
            $$ = varptr[i].ival[0];
        } else if(varptr[i].type == FLOAT) {
            $$ = varptr[i].dval[0];
        }
    }
;
expr:
    INT_VALUE {
        $$ = $1;
    }
    |FLOAT_VALUE {
        $$ = $1;
    }
    |VARIABLE {
        int i = get_var_index($1);
        if(i == -1) {
            var_does_not_exist($1);
            $$ = 0;
        } else if(varptr[i].type == NUMBER) {
            $$ = varptr[i].ival[0];
        } else if(varptr[i].type == FLOAT) {
            $$ = varptr[i].dval[0];
        }
    }
    |'+' expr  { $$ = $2;}
    |'-' expr  { $$ = -$2;}
    |INC expr  { $$ = $2;}
    |DEC expr  { $$ = $2;}
    |expr '+' expr  { $$ = $1 + $3;}
    |expr '-' expr  { $$ = $1 - $3;}
    |expr '*' expr  { $$ = $1 * $3;} 
    |expr '/' expr  { $$ = $1 / $3;}
    |expr '%' expr  {  $$ = (int)$1 % (int)$3;}
    |expr POW expr  {  $$ = pow($1, $3);}
    |expr EQ expr   { $$ = ($1 == $3);}
    |expr NE expr   { $$ = ($1 != $3);}
    |expr LT expr  { $$ = ($1 < $3);}
    |expr GT expr  { $$ = ($1 > $3);}
    |expr LE expr  { $$ = ($1 <= $3);}
    |expr GE expr  { $$ = ($1 >= $3);}
    |expr AND expr { $$ = ( $1 && $3);}
    |expr OR expr   { $$ = ($1 || $3);}
    |expr XOR expr   { $$ = ((int)$1 ^ (int)$3);}
    |NOT expr   { $$ = !$2;}
    |VARIABLE INC
    {
        int index = get_var_index($1);
        if(index == -1) {
            var_does_not_exist($1);
        } else if(varptr[index].type != NUMBER) {
            printf("Can't Increment Incompatible Types.\n");
        } else {
            varptr[index].ival[0]++;
            $$ = varptr[index].ival[0];

        }
    }
    |VARIABLE DEC       
    {
        int index = get_var_index($1);
        if(index == -1) {
            var_does_not_exist($1);
        } else if(varptr[index].type != NUMBER) {
            printf("Can't Increment Incompatible Types.\n");
        } else {
            varptr[index].ival[0]--;
            $$ = varptr[index].ival[0];

        }
    }
    |'(' expr ')' {  $$ = $2;}
    |SIN '(' expr ')' {  $$ = sin($3);  }
    |COS '(' expr ')' {  $$ = cos($3);  }
    |TAN '(' expr ')' {  $$ = tan($3);  }
    |LOG10 '(' expr ')' {  $$ = log10($3);  }
    |LOG2 '(' expr ')' {  $$ = log2($3);  }
    |LN '(' expr ')' {  $$ = log($3);  }
    |SQRT '(' expr ')' {  $$ = sqrt($3);  }
    |FACT '(' expr ')' {  $$ = factorial($3);  }
    |PRIME '(' expr ')' {  $$ = prime($3);  }
    |ABS '(' expr ')' {  $$ = abs($3);  }
; 
    

%%
int main() {
    varptr = malloc(MAX * sizeof(varStruct));
    funcptr = malloc(MAX_FUN * sizeof(funStruct));

    FILE *yyin = freopen("input.txt", "r", stdin);
    FILE *yyout = freopen("output.txt", "w", stdout);

    yyparse();

fclose(yyin);
fclose(yyout);

    free(varptr);
    free(funcptr);

    return 0;
}