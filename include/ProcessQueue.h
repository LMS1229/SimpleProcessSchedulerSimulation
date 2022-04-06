#pragma once
#include "Process.h"

typedef struct _node
{
	process process_ele;
	struct _node* next;
}node;

typedef struct _processQueue
{
	node* front, *raer;
}processqueue;

typedef struct _priorityqueue
{
	process* tree;
	int capacity;		//capacity of priority queue
	int size;			//element of priority queue
	int (*compare)(process*, process*);		//priority_queue compare
	//if compare function return 0, first parameter is child, else return 1, first parameter is parent
}priorityqueue;


node* CreatNode(process* p);		//creat queue node
void FreeNode(node* target);		//delete queue node

void InitProcessQueue(processqueue* q);
void Push_Queue(processqueue* q, process* p);
void Pop_Queue(processqueue* q);
process* Get_SJ(processqueue* q);					//Get Shortest service time process in queue
void Delete_Ele_Queue(processqueue* q, int pid);	//Delete process(process's pid is pid) in queue
int IsEmpty_Queue(processqueue* q);
process* Get_Queue(processqueue* q);

void InitPriorityQueue(priorityqueue* q, int (*compare)(process*, process*));
void Push_PriorityQueue(priorityqueue* q, process* p);
void Pop__PriorityQueue(priorityqueue* q);
process Get_PriorityQueue(priorityqueue* q);
int IsEmpty_PriorityQueue(priorityqueue* q);
