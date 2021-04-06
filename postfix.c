/*
 * postfix.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10   /*최대 스택 사이즈 10*/
#define MAX_EXPRESSION_SIZE 20 /*최대 수식 사이즈 20*/

/* stack 내에서 우선순위, lparen = 0 가장 낮음 */
typedef enum{
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 7,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 5,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];   	/*중위표기식을 저장하는 배열*/
char postfixExp[MAX_EXPRESSION_SIZE];	/*후위표기식으로 변경된 문자열을 저장하는 배열*/
char postfixStack[MAX_STACK_SIZE];	/*후위표기식으로 변환을 위해 필요한 스택*/
int evalStack[MAX_STACK_SIZE];		/*계산을 위해 필요한 스택*/

int postfixStackTop = -1;  /* 후위표기식 스택 Top */
int evalStackTop = -1;	   /* 계산용 스택 Top */

int evalResult = 0;	   /* 계산 결과 저장 */

void postfixpush(char x); /*중위표기 스택에 push*/
char postfixPop(); /*중위표기 스택에 pop*/
void evalPush(int x); /*계산을 위한 스택에 push*/
int evalPop(); /*계산을 위한 스택에 pop*/
void getInfix(); /*중위 표기식 입력을 받음*/
precedence getToken(char symbol); /* symbol의 종류를 받음*/
precedence getPriority(char x); /*우선순위인 x의 값을 받음*/
void charCat(char* c); /*문자 하나를 받아 후위표기식으로 변경된 문자열을 저장하는 배열에 추가*/
void toPostfix(); /*중위표기식의 문자 하나씩 읽고 후위표기식으로 변경*/
void debug(); /*디버그*/
void reset(); /*선언된 배열을 초기화*/
void evaluation(); /*후위 표기식을 계산*/

int main()
{
	char command;
	printf("[----- [김현민]  [2018038088] -----]\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			getInfix();
			break;
		case 'p': case 'P':
			toPostfix();
			break;
		case 'e': case 'E':
			evaluation();
			break;
		case 'd': case 'D':
			debug();
			break;
		case 'r': case 'R':
			reset();
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

void postfixPush(char x)
{
    postfixStack[++postfixStackTop] = x; /*후위표기식으로 변환을 위해 필요한 스택에 x의 값을 추가 하면 후위표기식 스택 Top 위치 증가*/
}

char postfixPop()
{
    char x;
    if(postfixStackTop == -1)
        return '\0';
    else {
    	x = postfixStack[postfixStackTop--]; /*후위표기식으로 변환을 위해 필요한 스택에 x의 값을 빼면 후위표기식 스택 Top 위치 감소*/
    }
    return x;
}

void evalPush(int x)
{
    evalStack[++evalStackTop] = x; /*계산을 위한 스택에 x의 값을 추가 하면 계산을 위한 스택 Top 위치 증가*/
}

int evalPop()
{
    if(evalStackTop == -1)
        return -1;
    else
        return evalStack[evalStackTop--]; /*계산을 위한 스택에 문자를 pop하면 계산을 위한 스택 Top 위치 감소*/
}


void getInfix()
{
    printf("Type the expression >>> ");
    scanf("%s",infixExp); /*중위표기식을 받음*/
}

precedence getToken(char symbol)
{
	switch(symbol) { /*symbol을 입력받은후  symbol에 종류를 반환*/
	case '(' : return lparen;
	case ')' : return rparen;
	case '+' : return plus;
	case '-' : return minus;
	case '/' : return divide;
	case '*' : return times;
	default : return operand;
	}
}

precedence getPriority(char x)
{
	return getToken(x);
}

void charCat(char* c)
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);/*후위표기식으로 변경된 문자열 초기화*/
	else
		strncat(postfixExp, c, 1); /*후위표기식으로 변경된 문자열 붙이기*/
}

void toPostfix()
{
    char *exp = infixExp; /* 중위표기법의 문자를 하나씩 읽기 위한 포인터 */
	char x; /* 문자하나를 임시로 저장하기 위한 변수 */
	
    while (*exp != '\0') { /*중위표기법이 공백이 아닐때*/
		if (getPriority(*exp) == operand) { /*exp값이 피연산자 일때 출력*/
        	x = *exp; 
            charCat(&x); /*x의 값을 후위표기식으로 변경된 문자열에 붙이기*/
        }
		else if (getPriority(*exp) == lparen) {/*exp값이 왼쪽 괄호 일때*/
            postfixPush(*exp); /*후위표기식으로 변환을 위해 필요한 스택에 값을 push*/
        }
        else if (getPriority(*exp) == rparen) { /*exp값이 오른쪽 괄호 일때*/
            while ((x = postfixPop()) != '(') {/*'('이 아닐때까지 pop*/
                charCat(&x); /*x의 값을 후위표기식으로 변경된 문자열에 붙이기*/
            }
        }
        else {
			while (getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp)) { /*들어오는 쪽이 스택안의 것보다 우선순위가 높거나 같을때*/
                x = postfixPop(); /*후위표기식으로 변환을 위해 필요한 스택의 값을 pop*/
                charCat(&x); /*x의 값을 후위표기식으로 변경된 문자열에 붙이기*/
            }
            postfixPush(*exp); /*후위표기식으로 변환을 위해 필요한 스택에 값을 push*/
        }
        exp++; /*중위표기식을 저장하는 배열의 번호 증가*/
    }
    x = postfixPop(); /*후위표기식으로 변환을 위해 필요한 스택의 값을 pop*/
    charCat(&x); /*x의 값을 후위표기식으로 변경된 문자열에 붙이기*/
}


void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);

	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);

	printf("\n");

}

void reset()
{
	infixExp[0] = '\0'; /*중위표기식을 저장하는 배열 공백*/
	postfixExp[0] = '\0'; /*후위표기식으로 변경된 문자열을 저장하는 배열 공백*/

	for(int i = 0; i < MAX_STACK_SIZE; i++) 
		postfixStack[i] = '\0'; /*후위표기식으로 변환을 위해 필요한 스택 최대 사이즈까지 공백*/
         
	int postfixStackTop = -1;  /* 후위표기식 스택 Top */
	int evalStackTop = -1;	   /* 계산용 스택 Top */
	int evalResult = 0;	   /* 계산 결과를 저장 */
}

void evaluation()
{   
    int op1, op2; /*피연산자 값을 저장하기 위한 변수*/
	char symbol;
    int number = strlen(postfixExp); /*중위표기식을 저장하는 배열문자열의 문자 갯수*/
	
    for (int i = 0; i < number; i++) {
    	symbol = postfixExp[i];
        if (getToken(symbol) == operand) { /*symbol이 피연산자 일때*/
			evalPush(symbol - '0'); /*symbol로 받은값을 숫자로 변환('0' = 아스키 문자값 48을 의미)*/
		}
        else {
			op2 = evalPop(); /*두번째 피연산자*/
            op1 = evalPop(); /*첫번째 피연산자*/

            switch (getToken(symbol)) { /*symbol값을 받아옴*/
            case plus : evalPush(op1 + op2); break; /*더하기 한 값 push*/
            case minus : evalPush(op1 - op2); break; /*빼기 한 값 push*/
            case times : evalPush(op1 * op2); break; /*곱하기 한 값 push*/
            case divide : evalPush(op1 / op2); break; /*나누기 한 값 push*/
            default : break; /*기본 값*/
        	}
        }
    }
    evalResult = evalPop(); /*계산결과를 반환*/
}