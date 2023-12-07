#include <stdio.h>
#define Swap(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

typedef struct {
	int array[20];
	int front, rear;
}QueueType;

void init_queue(QueueType* q)
{
	q->rear = q->front = 0;
}

int is_empty(QueueType* q)
{
	return (q->rear == q->front);
}

void enqueue(QueueType* q, int data)
{
	q->array[++(q->rear)] = data;
}

int dequeue(QueueType* q)
{
	int data = q->array[++(q->front)];
	return data;
}

void selection_sort(int list[], int n)
{
	int t = 0, k, i;
	for (int i = 0; i < n - 1; i++)
	{
		int min = i;
		for (k = i + 1; k < n; k++)
		{
			if (list[min] > list[k])
				min = k;
		}
		Swap(list[i], list[min], t);
	}
}

void insertion_sort(int list[], int n)
{
	int k = 0, i, key;
	for (i = 1; i < n; i++)
	{
		key = list[i];
		for (k = i - 1; k >= 0 && list[k] > key; k--)
		{
			list[k + 1] = list[k];
		}	
		list[k + 1] = key;
	}
}

void bubble_sort(int list[], int n)
{
	int i, j, t = 0;
	for (i = n - 1; i > 0; i--)
	{
		for (j = 0; j < i; j++)
		{
			if (list[j + 1] < list[j]) Swap(list[j], list[j + 1], t);
		}
	}
}

void merge(int list[], int left, int mid, int right)
{
	int l, r, m, i = left;
	int sorted[10];
	l = left; r = right; m = mid + 1;

	while (l <= mid && m <= r)
	{
		if (list[l] > list[m])
		{
			sorted[i] = list[m];
			i++; m++;
		}
		else if (list[l] < list[m])
		{
			sorted[i] = list[l];
			i++; l++;
		}
	}
	while (l <= mid)
	{
		sorted[i] = list[l];
		i++; l++;
	}
	while (m <= r)
	{
		sorted[i] = list[m];
		i++; m++;
	}

	for (l = left; l <= right; l++)
	{
		list[l] = sorted[l];
	}
}

void merge_sort(int list[], int left, int right)
{
	if (left < right)
	{
		int middle = (left + right) / 2;
		merge_sort(list, left, middle);
		merge_sort(list, middle + 1, right);
		merge(list, left, middle, right);
	}
}

int partition(int list[], int left, int right)
{
	int low, high, pivot, t;
	pivot = left;
	low = left; high = right + 1;

	do
	{
		do
			low++;
		while (list[low] < list[pivot]);

		do
				high--;
		while (list[high] > list[pivot]);

		if(low < high) Swap(list[low], list[high], t);
	} while (low < high);

	Swap(list[pivot], list[high], t);
	return high;
}

void quick_sort(int list[], int left, int right)
{
	int p;
	if (left < right)
	{
		p = partition(list, left, right);
		quick_sort(list, left, p-1);
		quick_sort(list, p + 1, right);
	}
}

void radix_sort(int list[], int n)
{
	QueueType queue[10];
	int t = 1, d = 2, b;

	for (int i = 0; i < 10; i++)
	{
		init_queue(&queue[i]);
	}
	
	for (int k = 0; k < d; k++)
	{
		for (int i = 0; i < n; i++)
		{
			enqueue(&queue[(list[i] / t) % 10], list[i]);
		}
		for (int i = b = 0; i < n; i++)
		{
			while (!is_empty(&queue[i]))
			{
				list[b] = dequeue(&queue[i]);
				b++;
			}
		}
		t = t * 10;
	}
}

int main()
{
	int list[10];
	for (int i = 0; i < 10; i++)
	{
		list[i] = rand() % 100;
	}
	radix_sort(list, 10);

	for (int i = 0; i < 10; i++)
	{
		printf("%d ", list[i]);
	}
}