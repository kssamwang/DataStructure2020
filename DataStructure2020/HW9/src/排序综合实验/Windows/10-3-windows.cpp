#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <time.h>
#include <windows.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <iomanip>
#include <string>
using namespace std;

/* 宏定义是否重建输入文件 */
#define NEED_TO_RECREATE 0

#define MAX_SIZE 1024*1024

#define TEST_METHOD_NUM 7
/* 随机数据三种模式 */
enum class INPUT_MODE {
	RAND,ORDERING,REVERSE
};

/* 排序方法 */
enum class SORT_METHOD {
	Insertion,Selection,Bubble,Shell,Heap,Quick,Merge
};

const string SORT_METHOD_NAME[TEST_METHOD_NUM] = {
	"插入排序","选择排序","冒泡排序","希尔排序",
	" 堆排序","快速排序","归并排序"
};

void Create_Input_File(const char* filename,const int size,const INPUT_MODE im)
{
	if (size < 0)
		return;

	ofstream fout;
	fout.open(filename, ios::out | ios::binary);
	if (!fout.is_open())
		cerr << "open " << filename << "error!" << endl;

	int* p = new(nothrow) int[size];
	if (!p)
	{
		fout.close();
		exit(-1);
	}

	for (int i = 0; i < size; i++)
		p[i] = rand();

	if (im == INPUT_MODE::RAND)
	{
		for (int j = 0; j < size; j++)
			fout << p[j] << " ";
	}
	else if (im == INPUT_MODE::ORDERING)
	{
		sort(p, p + size);
		for (int j = 0; j < size; j++)
			fout << p[j] << " ";
	}
	else if (im == INPUT_MODE::REVERSE)
	{
		sort(p, p + size);
		for (int j = size - 1; j >= 0; j--)
			fout << p[j] << " ";
	}

	fout.close();

	return;
}

void Create_My_Test_Files()
{
	const int size[] = { 10,100,1024,10 * 1024,100 * 1024,1024 * 1024,10 * 1024,10 * 1024 ,0 };
	const INPUT_MODE im[] = { INPUT_MODE::RAND,INPUT_MODE::RAND, INPUT_MODE::RAND, INPUT_MODE::RAND,
							INPUT_MODE::RAND, INPUT_MODE::RAND, INPUT_MODE::ORDERING, INPUT_MODE::REVERSE };
	const string filename[] = {
		"input1.txt","input2.txt","input3.txt","input4.txt","input5.txt","input6.txt","input7.txt","input8.txt",
	};

	for (int i = 0; size[i]; i++)
	{
		Create_Input_File(filename[i].c_str(), size[i], im[i]);

		cout << "已成功建立测试输入文件" << filename[i] << ",大小" << size[i] << ",模式为";
		switch (im[i])
		{
			case INPUT_MODE::RAND:
				cout << "随机";
				break;
			case INPUT_MODE::ORDERING:
				cout << "顺序";
				break;
			case INPUT_MODE::REVERSE:
				cout << "逆序";
				break;
		}
		cout << endl;
	}

	return;
}

/* 插入排序 */
void InsertionSort(int array[], const int size)
{
	for (int i = 1; i < size; i++)// size - 1 趟插入
	{
		/* 寻找元素 array[i] 合适的插入位置 */
		if (array[i] < array[i - 1])//否则不用往前插
		{
			int t = array[i];
			array[i] = array[i - 1];
			int j = i - 2;
			for (j = i - 2; j >= 0 && array[j] > t; j--)//后移一位
				array[j + 1] = array[j];
			array[j + 1] = t;//在次插入
		}
	}
}

/* 选择排序 */
void SelectionSort(int array[], const int size)
{
	for (int i = 0; i < size; i++)// size - 1 趟选择
	{
		int k = i;
		for (int j = i; j < size; j++)//从[i,size)选出最小者,其下标为k
		{
			if (array[j] < array[k])
				k = j;
		}
		/* 最小者array[k]换到位置i */
		int t = array[i];
		array[i] = array[k];
		array[k] = t;
	}
}

/* 冒泡排序 */
void BubbleSort(int array[], const int size)
{
	for (int i = 0; i < size - 1; i++)// size - 2 趟冒泡
	{
		for (int j = 0; j < size - i - 1; j++)
		{
			if (array[j] > array[j + 1])
			{
				int t = array[j];
				array[j] = array[j + 1];
				array[j + 1] = t;
			}
		}
	}
}

/* 希尔排序 */
void ShellSort(int array[],const int size) 
{
	//增量gap，并逐步缩小增量
	for (int gap = size / 2; gap > 0; gap /= 2)
	{
		//从第gap个元素，逐个对其所在组进行直接插入排序操作
		for (int i = gap; i < size; i++)
		{
			int j = i;
			int temp = array[j];
			if (array[j] < array[j - gap])
			{
				while (j - gap >= 0 && temp < array[j - gap])
				{
					//移动法
					array[j] = array[j - gap];
					j -= gap;
				}
				array[j] = temp;
			}
		}
	}
}

/* 堆排序调整堆顶 */
void HeapAdjust(int array[], int i, int length)
{
	int temp = array[i];//先取出当前元素i
	for (int k = i * 2 + 1; k < length; k = k * 2 + 1)
	{	
		//从i结点的左子结点开始，也就是2i+1处开始
		if (k + 1 < length && array[k] < array[k + 1])//如果左子结点小于右子结点，k指向右子结点
			k++;

		if (array[k] > temp)
		{	//如果子节点大于父节点，将子节点值赋给父节点（不用进行交换）
			array[i] = array[k];
			i = k;
		}
		else
			break;
	}
	array[i] = temp;//将temp值放到最终的位置
}

/* 堆排序 */
void HeapSort(int array[],const int size)
{
	//1.构建大顶堆
	for (int i = size / 2 - 1; i >= 0; i--)
	{
		//从第一个非叶子结点从下至上，从右至左调整结构
		HeapAdjust(array, i, size);
	}
	//2.调整堆结构+交换堆顶元素与末尾元素
	for (int j = size - 1; j > 0; j--)
	{
		//将堆顶元素与末尾元素进行交换
		int t = array[0];
		array[0] = array[j];
		array[j] = t;
		HeapAdjust(array, 0, j);//重新对堆进行调整
	}

}

/* 快速排序 */
void QuickSort(int a[], int l, int r)
{
	int mid = a[(l + r) / 2];
	int i = l;
	int j = r;
	do
	{
		while (a[i] < mid)//找到mid左侧比mid大的数
			i++;
		while (a[j] > mid)//找到mid右侧比mid小的数
			j--;

		if (i <= j)//要加这句
		{
			int t = a[i];
			a[i] = a[j];
			a[j] = t;
			i++;
			j--;
		}
	} while (i <= j);

	if (i < r)
		QuickSort(a, i, r);//[i,r]区间内不保证按序，仅能确定他们都大于mid，递归排序

	if (j > l)
		QuickSort(a, l, j);//[l,j]区间内不保证按序，仅能确定他们都小于mid，递归排序
}

/* 归并排序 */
void MergeSort(int array[], const int size)
{
	if (size < 2)
		return;

	int mid = size / 2;

	int* l = new(nothrow) int[mid + 1];
	if (!l)
		exit(-1);

	int* r = new(nothrow) int[mid + 1];
	if (!r)
	{
		delete[] l;
		exit(-1);
	}

	int li = 0;
	int ri = 0;

	for (int i = 0; i < mid; i++)
		l[li++] = array[i];
	for (int i = mid; i < size; i++)
		r[ri++] = array[i];

	int l_size = mid;
	int r_size = size - mid;

	MergeSort(l,l_size);
	MergeSort(r,r_size);

	int i, j, k;
	i = j = k = 0;

	while (i < l_size && j < r_size)
		if (l[i] <= r[j])
			array[k++] = l[i++];
		else
			array[k++] = r[j++];

	while (i < l_size)
		array[k++] = l[i++];
	while (j < r_size)
		array[k++] = r[j++];

	delete[] l;
	delete[] r;
}

void test(const char* testfilename, const int size, const SORT_METHOD sm,ofstream& fout)
{
	ifstream fin;
	fin.open(testfilename, ios::in | ios::binary);
	if (!fin.is_open())
		cerr << "open " << testfilename << "error!" << endl;

	int* array = new(nothrow) int[MAX_SIZE];
	if (!array)
		exit(-1);

	for (int i = 0; i < size; i++)
		fin >> array[i];

	fin.close();

	LARGE_INTEGER tick, begin, end;

	QueryPerformanceFrequency(&tick);	//获得计数器频率
	QueryPerformanceCounter(&begin);	//获得初始硬件计数器计数

	switch (sm)
	{
		case SORT_METHOD::Insertion:
		{
			InsertionSort(array, size);
			break;
		}
		case SORT_METHOD::Selection:
		{
			SelectionSort(array, size);
			break;
		}
		case SORT_METHOD::Bubble:
		{
			BubbleSort(array, size);
			break;
		}
		case SORT_METHOD::Shell:
		{
			ShellSort(array, size);
			break;
		}
		case SORT_METHOD::Heap:
		{
			HeapSort(array, size);
			break;
		}
		case SORT_METHOD::Quick:
		{
			QuickSort(array, 0, size - 1);
			break;
		}
		case SORT_METHOD::Merge:
		{
			MergeSort(array, size);
			break;
		}
	}

	QueryPerformanceCounter(&end);		//获得终止硬件计数器计数

	fout << "以下是" << testfilename << "作为输入,数组大小为" << size << ",使用";
	switch (sm)
	{
		case SORT_METHOD::Insertion:
		{
			fout << "插入";
			break;
		}
		case SORT_METHOD::Selection:
		{
			fout << "选择";
			break;
		}
		case SORT_METHOD::Bubble:
		{
			fout << "冒泡";
			break;
		}
		case SORT_METHOD::Shell:
		{
			fout << "希尔";
			break;
		}
		case SORT_METHOD::Heap:
		{
			fout << "堆";
			break;
		}
		case SORT_METHOD::Quick:
		{
			fout << "快速";
			break;
		}
		case SORT_METHOD::Merge:
		{
			fout << "归并";
			break;
		}
	}

	fout << "排序的测试,测试用时如下:" << endl;
	fout << "计数器频率 : " << tick.QuadPart << "Hz" << endl;
	fout << "计数器计数 : " << end.QuadPart - begin.QuadPart << endl;
	fout << setiosflags(ios::fixed) << setprecision(6) << double(end.QuadPart - begin.QuadPart) / tick.QuadPart << "秒" << endl;

	delete[]array;
}

int main()
{
	srand(unsigned int(time(NULL)));

	/* 是否重建输入文件 */
	if (NEED_TO_RECREATE)
	{
		Create_My_Test_Files();
		cout << "测试输入文件创建完成" << endl;
	}

	const int size[] = { 10,100,1024,10 * 1024,100 * 1024,1024 * 1024,10 * 1024,10 * 1024 ,0 };
	const INPUT_MODE im[] = { INPUT_MODE::RAND,INPUT_MODE::RAND, INPUT_MODE::RAND, INPUT_MODE::RAND,
							INPUT_MODE::RAND, INPUT_MODE::RAND, INPUT_MODE::ORDERING, INPUT_MODE::REVERSE };
	const string filename[] = {
		"input1.txt","input2.txt","input3.txt","input4.txt","input5.txt","input6.txt","input7.txt","input8.txt",
	};
	const SORT_METHOD sm[TEST_METHOD_NUM] = {
		SORT_METHOD::Insertion,SORT_METHOD::Selection,SORT_METHOD::Bubble,
		SORT_METHOD::Shell,SORT_METHOD::Heap,SORT_METHOD::Quick,SORT_METHOD::Merge
	};

	ofstream outres;
	outres.open("test_results.txt", ios::out | ios::binary);
	if (!outres.is_open())
	{
		cerr << "open test_results.txt error!" << endl;
		exit(-1);
	}
	
	outres << "======================测试正式开始======================" << endl;

	for (int i = 0; size[i]; i++)
	{
		for (int j = 0;j < TEST_METHOD_NUM;j++)
		{
			cout << "当前正在测试,输入 : " << filename[i] << "  大小 : " << setw(6) << size[i] << " 排序方法 : " << setw(6) << SORT_METHOD_NAME[j] << endl;
			test(filename[i].c_str(), size[i], sm[j], outres);
		}
	}

	outres << "========================测试结束========================" << endl;
	outres.close();

	return 0;
}