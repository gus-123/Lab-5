/*
 * circularQ.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;
typedef struct {
	element queue[MAX_QUEUE_SIZE]; /* ť�� ���Ҹ� �����ϴ� �迭 */
	int front, rear; /*front ����ť�� ����, rear ����ť�� ��*/
}QueueType;


QueueType *createQueue();
int freeQueue(QueueType *cQ);
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element* item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);
element getElement();

int main(void)
{
	QueueType *cQ = createQueue();
	element data;
	char command;
	printf("[----- [������]  [2018038088] -----]\n");

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ, &data);
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);
			break;
		case 'q': case 'Q':
   	        freeQueue(cQ);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');


	return 1;
}

QueueType *createQueue()
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType)); /*cQ�� QueueTypeũ�� ��ŭ ���� �޸� �Ҵ�*/
	cQ->front = 0; /*����ť�� ����*/
	cQ->rear = 0; /*����ť�� ��*/
	return cQ;
}

int freeQueue(QueueType *cQ)
{
    if(cQ == NULL) return 1; /*�޸� �Ҵ��� �����Ǿ� �ִ� ��� ����*/
    free(cQ); /*cQ�� �޸� �Ҵ� ����*/
    return 1;
}

element getElement()
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item); /*�Է� ���� ����*/
	return item;
}


/* complete the function */
int isEmpty(QueueType *cQ)
{
	return (cQ->front == cQ->rear);
}

/* complete the function */
int isFull(QueueType *cQ)
{
   return (((cQ->rear + 1) % MAX_QUEUE_SIZE) == cQ->front);
}


/* complete the function */
void enQueue(QueueType *cQ, element item)
{
	if (isFull(cQ)){ /*cQ�� MAX_QUEUE_SIZE�� ��á����*/
		printf("\nQueue is Full\n");
		return;
	}
	else{
	cQ->rear = ((cQ->rear + 1) % MAX_QUEUE_SIZE); /*rear��ġ�� �ϳ� ����*/
	cQ->queue[cQ->rear] = item; /*cQ�� ������ rear��ġ�� ���� ����*/
	}
}

/* complete the function */
void deQueue(QueueType *cQ, element *item)
{
	if (isEmpty(cQ)){ /*cQ�� MAX_QUEUE_SIZE�� �������*/
		printf("\nQueue is Empty\n");
		return;
	}
	else{ 
	cQ->front = (cQ->front + 1) % (MAX_QUEUE_SIZE); /*front��ġ�� �ϳ� ����*/
    cQ->queue[cQ -> front]; /*cQ�� ���� ������ front��ġ�� ����Ŵ*/
	}
}


void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE; /*ť���� ù ������ ��ġ*/
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE; /*ť���� ������ ������ ��ġ*/

	printf("Circular Queue : [");

	i = first;
	while(i != last){
		printf("%3c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE; /*first -> last�� MAX_QUEUE_SIZE��ŭ ���*/

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++) /*0���� MAX_QUEUE_SIZEũ�⸸ŭ �ݺ�*/
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i); /*front�� ����Ű�� �迭�� ���*/
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]); /*�迭�� �ִ� ���Ҹ� ��� ���*/

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);  /*front�� rear��ġ���*/
}