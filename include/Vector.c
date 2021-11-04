#include "Vector.h"
#include <stdio.h>
#include <stdlib.h>

void InitVector(vector* vec)
{
	vec->size = 0;
	vec->capacity = 4;
	vec->arr = (int*)malloc(sizeof(int)*vec->capacity);
}
void Push_Vector(vector* vec, int val)
{
	//if vector is full, resize prevent size * 2
	if (vec->size == vec->capacity)
	{
		int tempSize=vec->capacity<<1;
		int* temp = (int*)malloc(sizeof(int) * tempSize);
		for (int i = 0; i < vec->size; ++i)
		{
			temp[i] = vec->arr[i];
		}
		free(vec->arr);
		vec->arr = temp;
		vec->capacity=tempSize;
	}
	vec->arr[vec->size] = val;
	vec->size++;
}
int Get_Vector(vector* vec, int index)
{
	if(vec->size<=index)
	{
		perror("OutOfBound!\n");
		exit(1);
	}
	int val = vec->arr[index];
	return val;
}