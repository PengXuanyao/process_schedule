#include <stdio.h>
#include <stdlib.h>
#include "pro_sch.h"

P_Queue* create_p_queue(int prior){
	P_Queue* q = (P_Queue*)malloc(sizeof(P_Queue));
	if(!q){
		printf("create queue malloc failed\n");
		return NULL;
	}
	q->prior = prior;
	q->front = NULL;
	q->rear = NULL;
	return q;
}

void add_p_queue(P_Queue* q, PCB pcb){
	P_Node* n = (P_Node*) malloc (sizeof(P_Node));
	if(!n){
		printf("add queue malloc failed\n");
	}
	n->p = pcb;
	n->np = NULL;
	if(q->front == NULL){
		q->front = n;
	}
	if(q->rear == NULL){
		q->rear = n;
	}
	else{
		q->rear->np = n;
		q->rear = n;
	}
}

int is_empty_q(P_Queue* q){
	return (q->front == NULL);
}

PCB de_p_queue(P_Queue* q){
	if(is_empty_q(q)){
		printf("dequeue failed, null queue");
	}
	P_Node* temp = q->front;
	PCB item;
	if (q->front == q->rear){
		q->front = NULL;
		q->rear = NULL;
	}
	else{
		q->front = q->front->np;
	}	
	item = temp->p;
	free(temp);
	return item;
}

void print_q(P_Queue* q){
	if (is_empty_q(q)){
		printf("print failed, null queue");
	}
	printf("print queue:\n");
	P_Node* node= q->front;
	while (node != NULL){
		printf("%c ", node->p.name);
		node = node->np;
	}
	printf("\n");
}	

void test_q(void){
	P_Queue* q = create_p_queue(0);
	PCB temp;
	temp.name = 'A';
	add_p_queue(q, temp);
	temp.name = 'B';
	add_p_queue(q, temp);
	temp.name = 'C';
	add_p_queue(q, temp);
	
	print_q(q);
	
	de_p_queue(q);
	temp.name = 'D';
	add_p_queue(q, temp);
	
	print_q(q);
}


