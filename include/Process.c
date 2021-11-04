#include "Process.h"

int Excute_Process(process* pro)
{
	if (pro == 0)
	{
		return -1;
	}
	pro->remain_time -= 1;
	return pro->pid;
}
void Init_Process(process* target, int arrive_time, int service_time, int pid)
{
	target->arrive_time = arrive_time;
	target->service_time = target->remain_time = service_time;
	target->pid = pid;
	target->priority = 0;
}

void Sort(process* process_arr, int n)
{
	for (int i = 0; i < n - 1; ++i)
	{
		process temp;
		int index = i;
		for (int j = i + 1; j < n; ++j)
		{
			if (process_arr[index].arrive_time > process_arr[j].arrive_time)
			{
				index = j;
			}
		}
		temp = process_arr[i];
		process_arr[i] = process_arr[index];
		process_arr[index] = temp;
	}
}