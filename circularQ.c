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
	element queue[MAX_QUEUE_SIZE]; /* 큐의 원소를 저장하는 배열 */
	int front, rear; /*front 원형큐용 시작, rear 원형큐용 끝*/
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
	printf("[----- [김현민]  [2018038088] -----]\n");

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
	cQ = (QueueType *)malloc(sizeof(QueueType)); /*cQ에 QueueType크기 만큼 동적 메모리 할당*/
	cQ->front = 0; /*원형큐용 시작*/
	cQ->rear = 0; /*원형큐용 끝*/
	return cQ;
}

int freeQueue(QueueType *cQ)
{
    if(cQ == NULL) return 1; /*메모리 할당이 해제되어 있는 경우 종료*/
    free(cQ); /*cQ의 메모리 할당 해제*/
    return 1;
}

element getElement()
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item); /*입력 원소 받음*/
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
	if (isFull(cQ)){ /*cQ의 MAX_QUEUE_SIZE가 꽉찼을시*/
		printf("\nQueue is Full\n");
		return;
	}
	else{
	cQ->rear = ((cQ->rear + 1) % MAX_QUEUE_SIZE); /*rear위치를 하나 증가*/
	cQ->queue[cQ->rear] = item; /*cQ의 증가한 rear위치에 원소 넣음*/
	}
}

/* complete the function */
void deQueue(QueueType *cQ, element *item)
{
	if (isEmpty(cQ)){ /*cQ의 MAX_QUEUE_SIZE가 비었을시*/
		printf("\nQueue is Empty\n");
		return;
	}
	else{ 
	cQ->front = (cQ->front + 1) % (MAX_QUEUE_SIZE); /*front위치를 하나 증가*/
    cQ->queue[cQ -> front]; /*cQ의 원소 삭제후 front위치를 가리킴*/
	}
}


void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE; /*큐에서 첫 원소의 위치*/
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE; /*큐에서 마지막 원소의 위치*/

	printf("Circular Queue : [");

	i = first;
	while(i != last){
		printf("%3c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE; /*first -> last를 MAX_QUEUE_SIZE만큼 출력*/

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++) /*0부터 MAX_QUEUE_SIZE크기만큼 반복*/
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i); /*front가 가르키는 배열에 출력*/
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]); /*배열에 있는 원소를 모두 출력*/

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);  /*front와 rear위치출력*/
}