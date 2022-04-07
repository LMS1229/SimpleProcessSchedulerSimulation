#include "MLFQ.h"
#include <stdio.h>

vector* MLFQ(process* process_arr, int n, int max_level, int(*timequntum)(int, int)){
	int time = 0, index = 0, excute_time = 0, pid = -1;
	int all_q_empty = 1;
	processqueue* lq;		//MLQ
	vector* processes_excute_flag = 0;
	process* excute = 0;	//prevent excute process 
	processes_excute_flag = (vector*)malloc(sizeof(vector) * n);
	lq = (processqueue*)malloc(sizeof(processqueue) * max_level);
	for (int i = 0; i < n; ++i){
		InitVector(processes_excute_flag + i);
	}
	for (int i = 0; i < max_level; ++i){
		InitProcessQueue(&lq[i]);
	}
	while (index < n || all_q_empty == 0){
		while (index < n && process_arr[index].arrive_time == time){
			Push_Queue(&lq[0], &process_arr[index]);
			++index;
		}
		//gGt next excute process 
		excute = Schedueling(lq, excute, &excute_time, max_level, timequntum);
		if (excute != 0){
			pid = Excute_Process(excute);
			excute_time++;
		}
		else{
			pid = -1;
		}
		for (int i = 0; i < n; ++i){
			PushInVector(processes_excute_flag + i, pid == i);
		}
		if (excute->remain_time == 0){
			excute_time = 0;
			Pop_Queue(&lq[excute->priority]);
			excute = 0;
		}
		all_q_empty = 1;
		for (int i = 0; i < max_level; ++i){
			if (IsEmpty_Queue(&lq[i]) == 0)
			{
				all_q_empty = 0;
			}
		}
		++time;
	}
	return processes_excute_flag;
}

process* Schedueling(processqueue* lq, process* previous_process, int* excute_time, int max_level,int(*timequntum)(int, int)){
	process* next_process = 0;
	if (previous_process == 0){
		//if process terminated;
		next_process = Get_HighestPriorityProcess(lq, max_level); 
		*excute_time = 0;
		return next_process;
	}
	else{
		if ( *excute_time==(timequntum==0?MLFQ_DEFAULT_TIMEQUNTUM:timequntum(2, previous_process->priority))){
			//if all use timequantum
			//check all queue is empty
			int flag = 0;
			process temp = *previous_process;		//store previous process state
			Pop_Queue(&lq[previous_process->priority]);
			for (int i = 0; i < max_level; ++i){
				if (IsEmpty_Queue(&lq[i]) == 0){
					flag = 1;
					break;
				}
			}
			//if any queue is not empty
			//decrease process priority
			if (flag){
				++temp.priority;
				if (temp.priority == max_level){
					temp.priority = max_level - 1;
				}
			}
			Push_Queue(&lq[temp.priority], &temp);
			next_process = Get_HighestPriorityProcess(lq, max_level);
			*excute_time = 0;
			return next_process;
		}
		else{
			return previous_process;
		}
	}
}

process* Get_HighestPriorityProcess(processqueue* lq, int max_level){
	process* ret = 0;
	for (int i = 0; i < max_level; ++i){
		if (IsEmpty_Queue(&lq[i]) == 0){
			//Get highest priority process
			ret= Get_Queue(&lq[i]);
			break;
		}
	}
	return ret;
}
