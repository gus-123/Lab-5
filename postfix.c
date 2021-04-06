/*
 * postfix.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10   /*�ִ� ���� ������ 10*/
#define MAX_EXPRESSION_SIZE 20 /*�ִ� ���� ������ 20*/

/* stack ������ �켱����, lparen = 0 ���� ���� */
typedef enum{
	lparen = 0,  /* ( ���� ��ȣ */
	rparen = 9,  /* ) ������ ��ȣ*/
	times = 7,   /* * ���� */
	divide = 6,  /* / ������ */
	plus = 5,    /* + ���� */
	minus = 4,   /* - ���� */
	operand = 1 /* �ǿ����� */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];   	/*����ǥ����� �����ϴ� �迭*/
char postfixExp[MAX_EXPRESSION_SIZE];	/*����ǥ������� ����� ���ڿ��� �����ϴ� �迭*/
char postfixStack[MAX_STACK_SIZE];	/*����ǥ������� ��ȯ�� ���� �ʿ��� ����*/
int evalStack[MAX_STACK_SIZE];		/*����� ���� �ʿ��� ����*/

int postfixStackTop = -1;  /* ����ǥ��� ���� Top */
int evalStackTop = -1;	   /* ���� ���� Top */

int evalResult = 0;	   /* ��� ��� ���� */

void postfixpush(char x); /*����ǥ�� ���ÿ� push*/
char postfixPop(); /*����ǥ�� ���ÿ� pop*/
void evalPush(int x); /*����� ���� ���ÿ� push*/
int evalPop(); /*����� ���� ���ÿ� pop*/
void getInfix(); /*���� ǥ��� �Է��� ����*/
precedence getToken(char symbol); /* symbol�� ������ ����*/
precedence getPriority(char x); /*�켱������ x�� ���� ����*/
void charCat(char* c); /*���� �ϳ��� �޾� ����ǥ������� ����� ���ڿ��� �����ϴ� �迭�� �߰�*/
void toPostfix(); /*����ǥ����� ���� �ϳ��� �а� ����ǥ������� ����*/
void debug(); /*�����*/
void reset(); /*����� �迭�� �ʱ�ȭ*/
void evaluation(); /*���� ǥ����� ���*/

int main()
{
	char command;
	printf("[----- [������]  [2018038088] -----]\n");

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
    postfixStack[++postfixStackTop] = x; /*����ǥ������� ��ȯ�� ���� �ʿ��� ���ÿ� x�� ���� �߰� �ϸ� ����ǥ��� ���� Top ��ġ ����*/
}

char postfixPop()
{
    char x;
    if(postfixStackTop == -1)
        return '\0';
    else {
    	x = postfixStack[postfixStackTop--]; /*����ǥ������� ��ȯ�� ���� �ʿ��� ���ÿ� x�� ���� ���� ����ǥ��� ���� Top ��ġ ����*/
    }
    return x;
}

void evalPush(int x)
{
    evalStack[++evalStackTop] = x; /*����� ���� ���ÿ� x�� ���� �߰� �ϸ� ����� ���� ���� Top ��ġ ����*/
}

int evalPop()
{
    if(evalStackTop == -1)
        return -1;
    else
        return evalStack[evalStackTop--]; /*����� ���� ���ÿ� ���ڸ� pop�ϸ� ����� ���� ���� Top ��ġ ����*/
}


void getInfix()
{
    printf("Type the expression >>> ");
    scanf("%s",infixExp); /*����ǥ����� ����*/
}

precedence getToken(char symbol)
{
	switch(symbol) { /*symbol�� �Է¹�����  symbol�� ������ ��ȯ*/
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
		strncpy(postfixExp, c, 1);/*����ǥ������� ����� ���ڿ� �ʱ�ȭ*/
	else
		strncat(postfixExp, c, 1); /*����ǥ������� ����� ���ڿ� ���̱�*/
}

void toPostfix()
{
    char *exp = infixExp; /* ����ǥ����� ���ڸ� �ϳ��� �б� ���� ������ */
	char x; /* �����ϳ��� �ӽ÷� �����ϱ� ���� ���� */
	
    while (*exp != '\0') { /*����ǥ����� ������ �ƴҶ�*/
		if (getPriority(*exp) == operand) { /*exp���� �ǿ����� �϶� ���*/
        	x = *exp; 
            charCat(&x); /*x�� ���� ����ǥ������� ����� ���ڿ��� ���̱�*/
        }
		else if (getPriority(*exp) == lparen) {/*exp���� ���� ��ȣ �϶�*/
            postfixPush(*exp); /*����ǥ������� ��ȯ�� ���� �ʿ��� ���ÿ� ���� push*/
        }
        else if (getPriority(*exp) == rparen) { /*exp���� ������ ��ȣ �϶�*/
            while ((x = postfixPop()) != '(') {/*'('�� �ƴҶ����� pop*/
                charCat(&x); /*x�� ���� ����ǥ������� ����� ���ڿ��� ���̱�*/
            }
        }
        else {
			while (getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp)) { /*������ ���� ���þ��� �ͺ��� �켱������ ���ų� ������*/
                x = postfixPop(); /*����ǥ������� ��ȯ�� ���� �ʿ��� ������ ���� pop*/
                charCat(&x); /*x�� ���� ����ǥ������� ����� ���ڿ��� ���̱�*/
            }
            postfixPush(*exp); /*����ǥ������� ��ȯ�� ���� �ʿ��� ���ÿ� ���� push*/
        }
        exp++; /*����ǥ����� �����ϴ� �迭�� ��ȣ ����*/
    }
    x = postfixPop(); /*����ǥ������� ��ȯ�� ���� �ʿ��� ������ ���� pop*/
    charCat(&x); /*x�� ���� ����ǥ������� ����� ���ڿ��� ���̱�*/
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
	infixExp[0] = '\0'; /*����ǥ����� �����ϴ� �迭 ����*/
	postfixExp[0] = '\0'; /*����ǥ������� ����� ���ڿ��� �����ϴ� �迭 ����*/

	for(int i = 0; i < MAX_STACK_SIZE; i++) 
		postfixStack[i] = '\0'; /*����ǥ������� ��ȯ�� ���� �ʿ��� ���� �ִ� ��������� ����*/
         
	int postfixStackTop = -1;  /* ����ǥ��� ���� Top */
	int evalStackTop = -1;	   /* ���� ���� Top */
	int evalResult = 0;	   /* ��� ����� ���� */
}

void evaluation()
{   
    int op1, op2; /*�ǿ����� ���� �����ϱ� ���� ����*/
	char symbol;
    int number = strlen(postfixExp); /*����ǥ����� �����ϴ� �迭���ڿ��� ���� ����*/
	
    for (int i = 0; i < number; i++) {
    	symbol = postfixExp[i];
        if (getToken(symbol) == operand) { /*symbol�� �ǿ����� �϶�*/
			evalPush(symbol - '0'); /*symbol�� �������� ���ڷ� ��ȯ('0' = �ƽ�Ű ���ڰ� 48�� �ǹ�)*/
		}
        else {
			op2 = evalPop(); /*�ι�° �ǿ�����*/
            op1 = evalPop(); /*ù��° �ǿ�����*/

            switch (getToken(symbol)) { /*symbol���� �޾ƿ�*/
            case plus : evalPush(op1 + op2); break; /*���ϱ� �� �� push*/
            case minus : evalPush(op1 - op2); break; /*���� �� �� push*/
            case times : evalPush(op1 * op2); break; /*���ϱ� �� �� push*/
            case divide : evalPush(op1 / op2); break; /*������ �� �� push*/
            default : break; /*�⺻ ��*/
        	}
        }
    }
    evalResult = evalPop(); /*������� ��ȯ*/
}