#include "RR.h"
#include <stdio.h>

vector* RR(process* process_arr, int n, int timequantum){
	processqueue q;
	vector* processes_excute_flag = 0;
	process* excute=0;	//prevent excute process 
	processes_excute_flag = (vector*)malloc(sizeof(vector) * n);
	InitProcessQueue(&q);
	for (int i = 0; i < n; ++i)	{
		InitVector(processes_excute_flag + i);
	}
	int index = 0, time = 0, excute_time=0,pid=-1;
	while (index < n || IsEmpty_Queue(&q) == 0)	{
		while (index < n && process_arr[index].arrive_time == time){
			Push_Queue(&q, &process_arr[index]);
			++index;
		}
		if (excute!=0&&excute_time == timequantum){
			//if all use timequatum, push queue
			Push_Queue(&q, excute);
			Pop_Queue(&q);
			excute = 0;
			excute_time = 0;
		}
		if (excute == 0){
			excute = Get_Queue(&q);
		}
		if (excute != 0){
			pid=Excute_Process(excute);
			excute_time++;
		}
		else{
			pid = -1;
		}
		for (int i = 0; i < n; ++i){
			PushInVector(processes_excute_flag + i, pid == i);
		}
		if (excute!=0&&excute->remain_time == 0){
			//process terminate
			excute_time = 0;
			Pop_Queue(&q);
			excute = 0;
		}
		time++;
	}
	return processes_excute_flag;
}