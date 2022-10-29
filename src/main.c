#include <stdio.h>
#include "pro_sch.h"

int main(){
	P_Queue** p_queue;
	p_queue = create_process();
//	for (int i = 0; i < MAX_PRIOR; i++)
//		print_q(p_queue[i]);
	run_schedule(p_queue);
	return 0;
}
