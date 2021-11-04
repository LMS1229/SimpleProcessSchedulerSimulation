#pragma once


typedef struct _vector
{
	int size, capacity;
	int* arr;
}vector;

void InitVector(vector* vec);
void PushInVector(vector* vec, int val);
int GetAtVector(vector* vec, int index);