#include "SRT.h"

vector* SRT(process* process_arr, int n){
	priorityqueue pq;
	vector* processes_excute_flag = 0;
	process excute;
	processes_excute_flag = (vector*)malloc(sizeof(vector) * n);
	InitPriorityQueue(&pq,compare);
	int pid = -1;
	for (int i = 0; i < n; ++i){
		InitVector(processes_excute_flag + i);
	}
	int index = 0, time = 0;
	while (index < n || IsEmpty_PriorityQueue(&pq) == 0){
		while (index < n && process_arr[index].arrive_time == time){
			Push_PriorityQueue(&pq, &process_arr[index]);
			++index;
		}
		if (IsEmpty_PriorityQueue(&pq) == 0){
			//if Get shorteset remine time process
			excute = Get_PriorityQueue(&pq);
			Pop__PriorityQueue(&pq);
			pid = Excute_Process(&excute);	//excute
			if (excute.remain_time != 0){
				//not terminate
				Push_PriorityQueue(&pq, &excute);
			}
		}
		else{
			pid = -1;
		}
		for (int i = 0; i < n; ++i){
			PushInVector(processes_excute_flag + i, pid == i);
		}
		time++;
	}
	free(pq.tree);
	return processes_excute_flag;
}
int compare(process* p1, process* p2){
	//Min heap (by remain time)
	if (p1->remain_time >= p2->remain_time){
		return 1;
	}
	else{
		return 0;
	}
}