#pragma once

typedef struct _process{
	int arrive_time;	//created time of process
	int service_time;	//excute time of process
	int remain_time;	//remain time to terminated
	int priority;		//priority of process
	int pid;			
}process;

int Excute_Process(process* pro);				//return excute process's pid, (if pro is null, return -1)
void Init_Process(process* target,int arrive_time, int service_time, int pid);
void Sort(process* process_arr, int n);			//sort by arrive time