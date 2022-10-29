/****************************************
 * File Name: pro_sch.h
 * Description:
 * headerfile of process schedule experiment
****************************************/

# define MAX_PRIOR 5

typedef enum p_status{
	W,	// waiting
	R,	// running
	F	// finish
}p_status;

typedef struct PCB{
	char name;			// process name
	p_status status;	// process status
	int prior;			// process priority
	int start_time; 	// start time of process
	int run_time;		// expected running time
	int use_time;		// already used time of cpu occupation
}PCB;

// process node
typedef struct P_Node{
	PCB p;
	struct P_Node* np;
}P_Node;


// process priority queue 
typedef struct P_Queue{
	int prior;
	P_Node* front;
	P_Node* rear;
}P_Queue;


P_Queue* create_p_queue(int prior);
void add_p_queue(P_Queue* q, PCB pcb);
int is_empty_q(P_Queue* q);
PCB de_p_queue(P_Queue* q);
void print_q(P_Queue* q);
void test_q(void);
P_Queue** create_process(void);
void run_schedule(P_Queue** p_queue);

