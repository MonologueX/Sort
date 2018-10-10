#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include<stdio.h>
#include<assert.h>
#include <windows.h>

#define TEST_HEADER printf("\n============%s============\n",__FUNCTION__)

void PrintSort(int array[], int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		printf("%d ", array[i]);
	}
	printf("\n");
}
//////////////////////////////////////////////
//插入 基本 内部
void InsertSort(int array[], int size)
{
	int i, j;
	int key;
	for (i = 1; i < size; i++)
	{
		key = array[i];
		for (j = i - 1; j >= 0; j--)
		{
			if (array[j] <= key)
			{
				break;
			}
			else
			{
				array[j + 1] = array[j];
			}		
		}
		array[j + 1] = key;
	}
}

//////////////////////////////////////////
//大概率乱序  --- 二分法
void InerstSortBS(int array[], int size)
{
	int i;
	int left, right, mid;

	for (i = 0; i < size; i++)
	{
		int key = array[i];
		int j;
		left = 0;
		right = i - 1;
		while (left <= right)
		{
			mid = left + ((right - left) >> 1);
			if (array[mid] <= key)
			{
				left = mid + 1;
			}
			else
			{
				right = mid - 1;
			}
		}
		for (j = i; j > left; j--)
		{
			array[j] = array[j - 1];
		}
		array[j] = key;
	}
}

//////////////////////////////////////////////
//希尔排序
void ShellSort1(int array[], int size)
{
	int i, j, g;
	int key;
	int gap = size;
	while (gap > 1)
	{
		gap = gap / 3 + 1;
		for (g = 0; g < gap; g++)
		{
			for (i = g + gap; i < size; i += gap)
			{
				key = array[i];
				for (j = i - gap; j >= 0; j -= gap)
				{
					if (array[j] <= key)
					{
						break;
					}
					else
					{
						array[j + gap] = array[j];
					}
				}
				array[j + gap] = key;
			}
		}
	}
	
	InsertSort(array, size);
}

void ShellSort2(int array[], int size)
{
	int i, j;
	int key;
	int gap = size;
	while (gap > 1)
	{
		gap = gap / 3 + 1;
		for (i = gap; i < size; i++)
		{
			key = array[i];
			for (j = i - gap; j >= 0; j -= gap)
			{
				if (array[j] <= key)
				{
					break;
				}
				else
				{
					array[j + gap] = array[j];
				}
			}
			array[j + gap] = key;
		}
	}
	InsertSort(array, size);
}
////////////////////////////////////////////////
//堆排序
void Swap(int* x, int* y)
{
	int t = *x;
	*x = *y;
	*y = t;
}

void AdjustDownRecursion(int array[], int size, int parent)
{
	//结束条件
	int left = parent * 2 + 1;
	int right = parent * 2 + 2;
	int MaxChild;
	if (left >= size)
	{
		return;
	}

	if (right < size)
	{
		if (array[left] < array[right])
		{
			MaxChild = right;
		}
		else
		{
			MaxChild = left;
		}
	}
	else
	{
		MaxChild = left;
	}
	if (array[parent] >= array[MaxChild])
	{
		return;
	}
	Swap(array + parent, array + MaxChild);
	AdjustDownRecursion(array, size, parent);
}

void HeapSort(int array[], int size)
{
	int i;
	for (i = (size - 2) / 2; i >= 0; i--)
	{
		AdjustDownRecursion(array, size, i);
	}
	for (i = 1; i < size; i++)
	{
		Swap(array, array + size - i);
		AdjustDownRecursion(array, size - i, 0);
	}
	/*for (i = 0; i < size; i++)
	{
		Swap(array, array + size - 1 - i);
		AdjustDownRecursion(array, size - i - 1, 0);
	}*/
}

void AdjustDownLoop(int array[], int size, int parent)
{
	//结束条件
	int left = parent * 2 + 1;
	int right = parent * 2 + 2;
	int MaxChild;
	while (1)
	{
		if (left >= size)
		{
			break;
		}

		if (right < size)
		{
			if (array[left] < array[right])
			{
				MaxChild = right;
			}
			else
			{
				MaxChild = left;
			}
		}
		else
		{
			MaxChild = left;
		}
		if (array[parent] >= array[MaxChild])
		{
			break;
		}
		Swap(array + parent, array + MaxChild);
		parent = MaxChild;
		left = parent * 2 + 1;
		right = parent * 2 + 2;
	}
}
void HeapSortLoop(int array[], int size)
{
	int i;
	for (i = (size - 2) / 2; i >= 0; i--)
	{
		AdjustDownLoop(array, size, i);
	}
	for (i = 1; i < size; i++)
	{
		Swap(array, array + size - i);
		AdjustDownLoop(array, size - i, 0);
	}
	/*for (i = 0; i < size; i++)
	{
	Swap(array, array + size - 1 - i);
	AdjustDownRecursion(array, size - i - 1, 0);
	}*/
}

////////////////////////////////////////////////
//选择排序
void SelectSort(int array[], int size)
{
	int MaxSpace = size - 1;
	int i;
	int MaxPos;
	for (; MaxSpace > 0; MaxSpace--)
	{
		MaxPos = 0;
		for (i = 0; i <= MaxSpace; i++)
		{
			if (array[i] > array[MaxPos])
			{
				MaxPos = i;
			}
		}
		int t = array[MaxSpace];
		array[MaxSpace] = array[MaxPos];
		array[MaxPos] = t;
	}
}

void SelectSortAd(int array[], int size)
{
	int MaxSpace;		//最小数下标；左边界；闭区间
	int MinSpace;		//最大数下标；边右界；闭区间
	int MinPos;			//找到的最小数下标
	int MaxPos;			//找到的最小数下标
	int i;	
	MinSpace = 0;
	MaxSpace = size - 1;
	while(MinSpace < MaxSpace)
	{
		MinPos = MinSpace;
		MaxPos = MaxSpace;
		for (i = MinSpace; i <= MaxSpace; i++)
		{
			if (array[i] > array[MaxPos])
			{
				MaxPos = i;
			}
			if (array[i] < array[MinPos])
			{
				MinPos = i;
			}
		}
		Swap(array + MinSpace, array + MinPos);
		if (MinSpace == MaxPos)
			MaxPos = MinPos;
		Swap(array + MaxSpace, array + MaxPos);

		MinSpace++;
		MaxSpace--;
	}
}

////////////////////////////////////////////////
//
void BubbleSort(int array[], int size)
{
	int MaxSpace = size - 1; 
	int i;
	int exchange;
	for (; MaxSpace >= 1; MaxSpace--)
	{
		exchange = 0;
		for (i = 0; i < MaxSpace; i++)
		{
			if (array[i] > array[i + 1])
			{
				Swap(array + i, array + i + 1);
				exchange = 1;
			}
		}
		if (0 == exchange)
		{
			break;
		}
	}

}

////////////////////////////////////////////////
//快速排序
int GetMiddle(int array[], int left, int right)
{
	int mid = left + (right - left) / 2;
	if (array[left] < array[mid])
	{
		if (array[mid] < array[right])
			return mid;
		else if (array[left] > array[right])
			return left;
		else
			return right;
	}
	else
	{
		if (array[mid] < array[right])
			return right;
		else if (array[left] < array[right])
			return left;
		else
			return mid;
	}
}
int PartSort4(int array[], int left, int right)
{
	int key = array[right];
	int begin = left;
	int end = right;	//1 2 3 4 5(right-1)的反例

	while (begin < end)
	{
		while (begin < end && array[begin] <= key)
		{
			//小于的反例 5 5 5 5 5
			begin++;
		}
		while (begin < end && array[end] >= key)
		{
			end--;
		}
		if (begin < end)
		{
			Swap(array + begin, array + end);
		}
	}
	// begin 只会有两个位置
	// 可能1 array[begin] > key
	// 可能2 array[begin] 就是 key 的位置
	// 坑点
	// 错误1 Swap(array + begin, key);
	// 错误2 Swap(array + begin, array + end);

	Swap(array + begin, array + right);
	return begin;	//哨兵数所在的下标
}
void QuickSortRecursion4(int array[], int left, int right)
{
	if (left >= right)
	{
		return;
	}
	// 结束条件是：
	// [left, right] 数量只剩 0 个或 1 个
	int pivot = GetMiddle(array, left, right);
	Swap(array + pivot, array + right);
	// [left, div)	这里的数都比 array[div] 小
	// (div, right]	这里的数都比 array[div] 大
	int div = PartSort4(array, left, right);
	QuickSortRecursion4(array, left, div - 1);
	QuickSortRecursion4(array, div + 1, right);
}
void QuickSort4(int array[], int size)
{
	QuickSortRecursion4(array, 0, size - 1);
}

////////////////////////////////////////////////
//1
int PartSort1(int array[], int left, int right)
{
	int key = array[right];
	int begin = left;
	int end = right;	//1 2 3 4 5(right-1)的反例

	while (begin < end)
	{
		while (begin < end && array[begin] <= key)
		{
			//小于的反例 5 5 5 5 5
			begin++;
		}
		while (begin < end && array[end] >= key)
		{
			end--;
		}
		if (begin < end)
		{
			Swap(array + begin, array + end);
		}
	}
	// begin 只会有两个位置
	// 可能1 array[begin] > key
	// 可能2 array[begin] 就是 key 的位置
	// 坑点
	// 错误1 Swap(array + begin, key);
	// 错误2 Swap(array + begin, array + end);

	Swap(array + begin, array + right);
	return begin;	//哨兵数所在的下标
}
void QuickSortRecursion(int array[], int left, int right)
{
	if (left >= right)
	{
		return;
	}
	// 结束条件是：
	// [left, right] 数量只剩 0 个或 1 个
	//
	// [left, div)	这里的数都比 array[div] 小
	// (div, right]	这里的数都比 array[div] 大
	int div = PartSort1(array, left, right);
	QuickSortRecursion(array, left, div - 1);
	QuickSortRecursion(array, div + 1, right);
}
void QuickSort(int array[], int size)
{
	QuickSortRecursion(array, 0, size - 1);
}

///////////////////////////////////////////////////
//2
int PartSort2(int array[], int left, int right)
{
	int key = array[right];
	int begin = left;
	int end = right;

	while (begin < end)
	{
		while (begin < end && array[begin] <= key)
		{
			begin++;
		}

		array[end] = array[begin];

		while (begin < end && array[end] >= key)
		{
			end--;
		}

		array[begin] = array[end];
	}

	array[begin] = key;
	return begin;
}
void QuickSortRecursion2(int array[], int left, int right)
{
	if (left >= right)
	{
		return;
	}
	// 结束条件是：
	// [left, right] 数量只剩 0 个或 1 个
	//
	// [left, div)	这里的数都比 array[div] 小
	// (div, right]	这里的数都比 array[div] 大
	int div = PartSort2(array, left, right);
	QuickSortRecursion2(array, left, div - 1);
	QuickSortRecursion2(array, div + 1, right);
}
void QuickSort2(int array[], int size)
{
	QuickSortRecursion2(array, 0, size - 1);
}

//////////////////////////////////////////////////
//3
int PartSort3(int array[], int left, int right)
{
	int cur;
	int fb;
	int key = array[right];

	for (cur = left, fb = left; cur < right; cur++)
	{
		if (array[cur] < key)
		{
			Swap(array + cur, array + fb);
			fb++;
		}
	}
	Swap(array + fb, array + right);
	return fb;
}
void QuickSortRecursion3(int array[], int left, int right)
{
	if (left >= right)
	{
		return;
	}
	int div = PartSort3(array, left, right);
	QuickSortRecursion3(array, left, div - 1);
	QuickSortRecursion3(array, div + 1, right);
}
void QuickSort3(int array[], int size)
{
	QuickSortRecursion3(array, 0, size - 1);
}

////////////////////////////////////////////////
//非递归
void QuickSortNor(int array[], int size)
{
	int stack[100];
	int top = 0;
	int left, right;

	//先从左边界，再从右边界
	stack[top++] = 0;
	stack[top++] = size - 1;

	while (top > 0)
	{
		right = stack[--top];
		left = stack[--top];
		if (left >= right)
		{
			continue;
		}
		int div = PartSort4(array, left, right);
		//先入左边区间
		stack[top++] = left;
		stack[top++] = div - 1;
		//再入右边区间
		stack[top++] = div + 1;
		stack[top++] = right;
	}
}

////////////////////////////////////////////////
//归并
void Merge(int array[], int left, int mid, int right, int extra[])
{
	int ileft = left, iright = mid;
	int iextra = left;

	for (; ileft < mid && iright <= right; iextra++)
	{
		if (array[ileft] <= array[iright])
		{
			extra[iextra] = array[ileft++];
		}
		else
		{
			extra[iextra] = array[iright++];
		}
	}
	while (ileft < mid)
	{
		extra[iextra++] = array[ileft++];
	}
	while (iright <= right)
	{
		extra[iextra++] = array[iright++];
	}

	int i;
	for (i = 0; i <= right; i++)
	{
		array[i] = extra[i];
	}
}

void MergeSortRecursion(int array[], int left, int right, int extra[])
{
	if (left >= right)
	{
		return;
	}
	int mid = left + (right - left) / 2;
	MergeSortRecursion(array, left, mid, extra);
	MergeSortRecursion(array, mid + 1, right, extra);
	Merge(array, left, mid + 1, right, extra);
}

void MergeSort(int array[], int size)
{
	int* extra = (int*)malloc(sizeof(int)* size);
	assert(extra);
	MergeSortRecursion(array, 0, size - 1, extra);
	free(extra);
}
////////////////////////////////////////////////
//
void MergeSortNor(int array[], int size, int extra[])
{
	int gap, i;
	for (gap = 1; gap < size; gap *= 2)
	{
		for (i = 0; i < size; i += 2 * gap)
		{
			int left = i;
			int mid = i + gap;
			int right = mid + gap - 1;
			if (mid >= size)
				break;
			if (right >= size)
				right = size - 1;
			Merge(array, left, mid, right, extra);
		}
	}
}
void MergeSortLoop(int array[], int size)
{
	int* extra = (int*)malloc(sizeof(int)* size);
	assert(extra);
	MergeSortNor(array, size, extra);
	free(extra);
}
////////////////////////////////////////////////
//测试
void TestInerstSortBS()
{
	TEST_HEADER;
	srand(20180827);
	int array[10];
	for (int i = 0; i < 10; i++)
	{
		array[i] = rand() % 40;
	}
	PrintSort(array, 10);
	InerstSortBS(array, 10);
	PrintSort(array, 10);
}

void TestInsertSort()
{
	TEST_HEADER;
	srand(20180827);
	int array[50];
	for (int i = 0; i < 50; i++)
	{
		array[i] = rand() % 40;
	}
	PrintSort(array, 50);
	InsertSort(array, 50);
	PrintSort(array, 50);
}

void TestShellSort1()
{
	TEST_HEADER;
	srand(20180827);
	int array[10];
	for (int i = 0; i < 10; i++)
	{
		array[i] = rand() % 40;
	}
	PrintSort(array, 10);
	ShellSort1(array, 10);
	PrintSort(array, 10);
}

void TestShellSort2()
{
	TEST_HEADER;
	srand(20180827);
	int array[10];
	for (int i = 0; i < 10; i++)
	{
		array[i] = rand() % 40;
	}
	PrintSort(array, 10);
	ShellSort2(array, 10);
	PrintSort(array, 10);
}

void TestHeapSort()
{
	TEST_HEADER;
	srand(20180827);
	int array[10];
	for (int i = 0; i < 10; i++)
	{
		array[i] = rand() % 40;
	}
	PrintSort(array, 10);
	HeapSort(array, 10);
	PrintSort(array, 10);
}

void TestHeapSortLoop()
{
	TEST_HEADER;
	srand(20180827);
	int array[10];
	for (int i = 0; i < 10; i++)
	{
		array[i] = rand() % 40;
	}
	PrintSort(array, 10);
	HeapSortLoop(array, 10);
	PrintSort(array, 10);
}

void TestSelectSort()
{
	TEST_HEADER;
	srand(20180827);
	int array[10];
	for (int i = 0; i < 10; i++)
	{
		array[i] = rand() % 40;
	}
	PrintSort(array, 10);
	SelectSort(array, 10);
	PrintSort(array, 10);
}

void TestSelectSortAd()
{
	TEST_HEADER;
	srand(20180827);
	int array[10];
	for (int i = 0; i < 10; i++)
	{
		array[i] = rand() % 40;
	}
	PrintSort(array, 10);
	SelectSortAd(array, 10);
	PrintSort(array, 10);
}

void TestBubbleSort()
{
	TEST_HEADER;
	srand(20180827);
	int array[10];
	for (int i = 0; i < 10; i++)
	{
		array[i] = rand() % 40;
	}
	PrintSort(array, 10);
	BubbleSort(array, 10);
	PrintSort(array, 10);
}

void TestQuickSort()
{
	TEST_HEADER;
	srand(20180827);
	int array[10];
	for (int i = 0; i < 10; i++)
	{
		array[i] = rand() % 40;
	}
	PrintSort(array, 10);
	QuickSort(array, 10);
	PrintSort(array, 10);
}

void TestQuickSort2()
{
	TEST_HEADER;
	srand(20180827);
	int array[10];
	for (int i = 0; i < 10; i++)
	{
		array[i] = rand() % 40;
	}
	PrintSort(array, 10);
	QuickSort2(array, 10);
	PrintSort(array, 10);
}

void TestQuickSort3()
{
	TEST_HEADER;
	srand(20180827);
	int array[10];
	for (int i = 0; i < 10; i++)
	{
		array[i] = rand() % 40;
	}
	PrintSort(array, 10);
	QuickSort3(array, 10);
	PrintSort(array, 10);
}

void TestMergeSort()
{
	TEST_HEADER;
	srand(20180827);
	int array[10];
	for (int i = 0; i < 10; i++)
	{
		array[i] = rand() % 40;
	}
	PrintSort(array, 10);
	MergeSort(array, 10);
	PrintSort(array, 10);
}

void TestMergeSortLoop()
{
	TEST_HEADER;
	srand(20180827);
	int array[10];
	for (int i = 0; i < 10; i++)
	{
		array[i] = rand() % 40;
	}
	PrintSort(array, 10);
	MergeSortLoop(array, 10);
	PrintSort(array, 10);
}