#pragma once
#include "ProcessQueue.h"
#include "Vector.h"

vector* MLFQ(process* process_arr, int n, int max_level);

process* Schedueling(processqueue* lq, process* previous_process, int* excute_time, int max_level);		//Get next excute process
process* Get_HighestPriorityProcess(processqueue* lq, int max_level);