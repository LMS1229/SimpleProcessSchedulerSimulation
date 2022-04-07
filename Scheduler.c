// Scheduler.cpp : 애플리케이션의 진입점을 정의합니다.
// 

#include "Scheduler.h"

int Get_MLFQ_timequntum(int base, int priority);
void PrintResult(vector* result, int n);

int main()
{
	process* arr = 0;
	vector* result;
	int n, timequantum, level;
	printf("Input Process count: ");
	scanf_s("%d", &n);
	arr = (process*)malloc(sizeof(process) * n);
	for (int i = 0; i < n; ++i)	{
		int arrive_time, service_time;
		printf("Input Process %d \'s arrive time and service time: ",i);
		scanf_s("%d %d", &arrive_time, &service_time);
		Init_Process(arr + i, arrive_time, service_time, i);
	}
	Sort(arr, n);
	printf("Input Timequantum of RoundRobin: ");
	scanf_s("%d", &timequantum);
	printf("Input level of MLFQ(first level is 1) : ");
	scanf_s("%d", &level);
	result = RR(arr, n, timequantum);
	printf("Round Robin(timequantum=%d)\n", timequantum);
	PrintResult(result,n);

	result = FCFS(arr, n);
	printf("FCFS\n");
	PrintResult(result, n);

	result = SJF(arr, n);
	printf("SJF\n");
	PrintResult(result, n);

	result = SRT(arr, n);
	printf("SRT\n");
	PrintResult(result, n);

	result = MLFQ(arr, n, level,0);
	printf("MLFQ(timquatum= %d\n",MLFQ_DEFAULT_TIMEQUNTUM);
	PrintResult(result, n);

	result = MLFQ(arr, n, level,Get_MLFQ_timequntum);
	printf("MLFQ(timquatum= 2^(level of queue-1)\n");
	PrintResult(result, n);
	return 0;
}

void PrintResult(vector* result, int n){
	for (int i = 0; i < n; i++)	{
		printf("process %d: ", i);
		for (int j = 0; j < result[i].size; ++j)		{
			printf("%s", GetAtVector(result + i, j) == 1 ? "■" : "□");
		}
		printf("\n");
		free((result + i)->arr);
	}
	free(result);
}

int Get_MLFQ_timequntum(int base, int priority){
	int result=1;
	while(priority){
		if(priority&1){
			result*=base;
		}
		base=base*base;
		priority=priority>>1;
	}
	return result;
}