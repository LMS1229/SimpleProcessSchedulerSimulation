#include "FCFS.h"
#include <stdlib.h>

vector* FCFS(process* process_arr, int n)
{
	processqueue q;
	vector* processes_excute_flag=0;		//store excute state at each time for each process
	process* excute=0;
	int pid = -1;
	processes_excute_flag = (vector*)malloc(sizeof(vector) * n);
	InitProcessQueue(&q);
	for (int i = 0; i < n; ++i)
	{
		InitVector(processes_excute_flag + i);
	}
	int index = 0, time = 0;
	while (index<n||IsEmpty_Queue(&q)==0)
	{
		while (index < n && process_arr[index].arrive_time == time)
		{
			//if process arrive, push process in queue
			Push_Queue(&q, &process_arr[index]);
			++index;
		}
		while (IsEmpty_Queue(&q) == 0 &&excute==0 )
		{
			//if any process is terminated and any process in queue
			excute = Get_Queue(&q);
		}
		if (excute != 0)
		{
			//if exist excutable process
			//Get pid of excute process
			pid = Excute_Process(excute);
		}
		else
		{
			pid = -1;
		}
		for (int i = 0; i < n; ++i)
		{
			PushInVector(processes_excute_flag + i, pid == i);
		}
		if (excute != 0 && excute->remain_time == 0)
		{
			//if prevent process is terminated, Pop at queue
			Pop_Queue(&q);
			excute = 0;
		}
		time++;
	}
	return processes_excute_flag;
}