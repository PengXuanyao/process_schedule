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
		printf("print failed, null queue\n");
		return ;
	}
	printf("print queue:\n");
	P_Node* node= q->front;
	while (node != NULL){
		printf("name: %c\n", node->p.name);
		printf("priority: %d\n", node->p.prior);
		printf("start time: %d\n ", node->p.start_time);
		printf("run time: %d\n ", node->p.run_time);
		printf("use time: %d\n ", node->p.use_time);
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

P_Queue** create_process(void){
	int num = 0;
	static P_Queue* p_queue[MAX_PRIOR];
	for ( int i = 0; i < MAX_PRIOR; i++){
		p_queue[i] = create_p_queue(i);
	} 
	printf("how many process do you want to create: ");
	scanf("%d", &num);
	if (num == 0){
		printf("no prcess is created, bye!\n");
	}
	while(num--){ // attention bug. while or do while
		static int i = 0;
		PCB tmp;
		printf("please input process, last %d\n", num);
		tmp.name = 'A' + i;
		tmp.status = W;
		printf("priority (make sure less than %d):", MAX_PRIOR);
		scanf("%d", &tmp.prior);
		printf("start time: ");
		scanf("%d", &tmp.start_time);
		printf("run time: ");
		scanf("%d", &tmp.run_time);
		tmp.use_time=0;
		add_p_queue(p_queue[tmp.prior], tmp);
		i++;
	}
	return p_queue;
}

int is_waiting_queue_not_null(P_Queue** p_queue){
	int flag = 0;
   	for (int i = 0; i < MAX_PRIOR; i++){
		if (!is_empty_q(p_queue[i]))
				flag = 1;
	}
	return flag;
}

void run_schedule(P_Queue** p_queue){
	while(is_waiting_queue_not_null(p_queue)){
		// print queue
		for (int i = 0; i < MAX_PRIOR; i++)
			print_q(p_queue[i]);
		// choose process
		int ch_pr = 0;
		for (int i = 0; i < MAX_PRIOR; i++){
			if(!is_empty_q(p_queue[i])){
				ch_pr = i;
			}
		}
		// run process
		// dequeue process
		PCB tmp = de_p_queue(p_queue[ch_pr]);
		// change status
		tmp.use_time++;
		if (tmp.use_time == tmp.run_time)
			tmp.status = F;
		else {
			tmp.status = R;
			if (tmp.prior < 4){
				tmp.prior++;
			}
			// enqueue
			add_p_queue(p_queue[tmp.prior], tmp);
		}
	}		
}
