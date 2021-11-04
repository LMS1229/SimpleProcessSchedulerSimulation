#include "ProcessQueue.h"
#include <stdlib.h>
#include <stdio.h>

node* CreatNode(process* p)
{
	node* ret = (node*)malloc(sizeof(node));
	ret->process_ele = *p;	//copy process
	ret->next = 0;
	return ret;
}

void FreeNode(node* target)
{
	free(target);
}

void InitProcessQueue(processqueue* q)
{
	q->front = q->raer = 0;
}

void Push_Queue(processqueue* q, process* p)
{
	if (q->front == 0)
	{
		q->front = q->raer = CreatNode(p);
	}
	else
	{
		q->raer->next = CreatNode(p);
		q->raer = q->raer->next;
	}
}
void Pop_Queue(processqueue* q)
{
	if (IsEmpty_Queue(&q) == 0)
	{
		node* temp = q->front;
		q->front = q->front->next;
		FreeNode(temp);
	}
}
process* Get_Queue(processqueue* q)
{
	return &(q->front->process_ele);
}

int IsEmpty_Queue(processqueue* q)
{
	return q->front == NULL;
}

void InitPriorityQueue(priorityqueue* pq, int (*compare)(process*, process*))
{
	pq->capacity = 4;
	pq->size = 0;
	pq->tree = (process*)malloc(sizeof(process) * (pq->capacity + 1));
	pq->compare = compare;
}

void Push_PriorityQueue(priorityqueue* q, process* p)
{
	int i;
	q->size += 1;
	if (q->capacity < q->size)
	{
		q->capacity *= 2;
		process* temp = (process*)malloc(sizeof(process) * q->capacity + 1);
		for (int i = 1; i < q->size; ++i)
		{
			temp[i] = q->tree[i];
		}
		free(q->tree);
		q->tree = temp;
	}
	for (i = q->size; i != 1; i = i / 2)
	{
		if (q->compare(&(q->tree[i/2]), p) == 1)
		{
			//if tree[i/2] is p's child
			q->tree[i] = q->tree[i / 2];
		}
		else
		{
			break;
		}
	}
	q->tree[i] = *p;
}

void Pop__PriorityQueue(priorityqueue* q)
{
	int n = q->size;
	int parent;
	q->size--;
	process temp = q->tree[n];
	for (parent = 1; parent * 2 <= q->size;)
	{
		int child = parent * 2;
		if (child + 1 < q->size)
		{
			if (q->compare(&(q->tree[child]), &(q->tree[child + 1]))==1)
			{
				child++;
			}
		}
		if (q->compare(&(q->tree[child]),&temp) == 1)
		{
			break;
		}
		q->tree[parent] = q->tree[child];
		parent = child;
	}
	q->tree[parent] = temp;
}

process Get_PriorityQueue(priorityqueue* q)
{
	//return copy
	process temp;
	temp = q->tree[1];
	return temp;
}
process* Get_SJ(processqueue* q)
{
	//Get Shortest service time in 
	process* temp = &(q->front->process_ele);
	for (node* p = q->front; p != 0; p = p->next)
	{
		if (p->process_ele.service_time < temp->service_time)
		{
			temp = &(p->process_ele);
		}
	}
	return temp;
}


void Delete_Ele_Queue(processqueue* q, int pid)
{
	node* head=0, *tail;
	for (tail = q->front; tail != 0; tail = tail->next)
	{
		if (pid == tail->process_ele.pid)
		{
			break;
		}
		head = tail;
	}
	if (head == 0)
	{
		//if delete q front
		node* del = q->front;
		q->front = q->front->next;
		FreeNode(del);
	}
	else
	{
		head->next = tail->next;
		FreeNode(tail);
	}
}
int IsEmpty_PriorityQueue(priorityqueue* q)
{
	return q->size == 0;
}