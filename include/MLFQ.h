#pragma once
#include "ProcessQueue.h"
#include "Vector.h"
#DEFAULT_TIMEQUNTUM 2

vector* MLFQ(process* process_arr, int n, int max_level, int(*timequntum)(int, int));

process* Schedueling(processqueue* lq, process* previous_process, int* excute_time, int max_level,int(*timequntum)(int, int));		//Get next excute process
process* Get_HighestPriorityProcess(processqueue* lq, int max_level);
