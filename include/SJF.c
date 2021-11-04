#include "SJF.h"

vector* SJF(process* process_arr, int n)
{
	processqueue q;
	vector* processes_excute_flag = 0;
	process* excute=0;
	processes_excute_flag = (vector*)malloc(sizeof(vector) * n);
	InitProcessQueue(&q);
	int pid = -1;
	for (int i = 0; i < n; ++i)
	{
		InitVector(processes_excute_flag + i);
	}
	int index = 0, time = 0;
	while (index < n || IsEmpty_Queue(&q) == 0)
	{
		while (index < n && process_arr[index].arrive_time == time)
		{
			//if process arrive, push process in queue
			Push_Queue(&q, &process_arr[index]);
			++index;
		}
		if (excute == 0)
		{
			//if previous process was terminated, Get Shorterst service process in queue
			if (IsEmpty_Queue(&q) == 0)
			{
				excute = Get_SJ(&q);
			}
		}
		if (excute != 0)
		{
			//if exist excutable process
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
		if(excute!=0&&excute->remain_time == 0)
		{
			//process terminated
			Delete_Ele_Queue(&q, pid);
			excute = 0;
		}
		time++;
	}
	return processes_excute_flag;
}
