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

/* �궨���Ƿ��ؽ������ļ� */
#define NEED_TO_RECREATE 0

#define MAX_SIZE 1024*1024

#define TEST_METHOD_NUM 7
/* �����������ģʽ */
enum class INPUT_MODE {
	RAND,ORDERING,REVERSE
};

/* ���򷽷� */
enum class SORT_METHOD {
	Insertion,Selection,Bubble,Shell,Heap,Quick,Merge
};

const string SORT_METHOD_NAME[TEST_METHOD_NUM] = {
	"��������","ѡ������","ð������","ϣ������",
	" ������","��������","�鲢����"
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

		cout << "�ѳɹ��������������ļ�" << filename[i] << ",��С" << size[i] << ",ģʽΪ";
		switch (im[i])
		{
			case INPUT_MODE::RAND:
				cout << "���";
				break;
			case INPUT_MODE::ORDERING:
				cout << "˳��";
				break;
			case INPUT_MODE::REVERSE:
				cout << "����";
				break;
		}
		cout << endl;
	}

	return;
}

/* �������� */
void InsertionSort(int array[], const int size)
{
	for (int i = 1; i < size; i++)// size - 1 �˲���
	{
		/* Ѱ��Ԫ�� array[i] ���ʵĲ���λ�� */
		if (array[i] < array[i - 1])//��������ǰ��
		{
			int t = array[i];
			array[i] = array[i - 1];
			int j = i - 2;
			for (j = i - 2; j >= 0 && array[j] > t; j--)//����һλ
				array[j + 1] = array[j];
			array[j + 1] = t;//�ڴβ���
		}
	}
}

/* ѡ������ */
void SelectionSort(int array[], const int size)
{
	for (int i = 0; i < size; i++)// size - 1 ��ѡ��
	{
		int k = i;
		for (int j = i; j < size; j++)//��[i,size)ѡ����С��,���±�Ϊk
		{
			if (array[j] < array[k])
				k = j;
		}
		/* ��С��array[k]����λ��i */
		int t = array[i];
		array[i] = array[k];
		array[k] = t;
	}
}

/* ð������ */
void BubbleSort(int array[], const int size)
{
	for (int i = 0; i < size - 1; i++)// size - 2 ��ð��
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

/* ϣ������ */
void ShellSort(int array[],const int size) 
{
	//����gap��������С����
	for (int gap = size / 2; gap > 0; gap /= 2)
	{
		//�ӵ�gap��Ԫ�أ�����������������ֱ�Ӳ����������
		for (int i = gap; i < size; i++)
		{
			int j = i;
			int temp = array[j];
			if (array[j] < array[j - gap])
			{
				while (j - gap >= 0 && temp < array[j - gap])
				{
					//�ƶ���
					array[j] = array[j - gap];
					j -= gap;
				}
				array[j] = temp;
			}
		}
	}
}

/* ����������Ѷ� */
void HeapAdjust(int array[], int i, int length)
{
	int temp = array[i];//��ȡ����ǰԪ��i
	for (int k = i * 2 + 1; k < length; k = k * 2 + 1)
	{	
		//��i�������ӽ�㿪ʼ��Ҳ����2i+1����ʼ
		if (k + 1 < length && array[k] < array[k + 1])//������ӽ��С�����ӽ�㣬kָ�����ӽ��
			k++;

		if (array[k] > temp)
		{	//����ӽڵ���ڸ��ڵ㣬���ӽڵ�ֵ�������ڵ㣨���ý��н�����
			array[i] = array[k];
			i = k;
		}
		else
			break;
	}
	array[i] = temp;//��tempֵ�ŵ����յ�λ��
}

/* ������ */
void HeapSort(int array[],const int size)
{
	//1.�����󶥶�
	for (int i = size / 2 - 1; i >= 0; i--)
	{
		//�ӵ�һ����Ҷ�ӽ��������ϣ�������������ṹ
		HeapAdjust(array, i, size);
	}
	//2.�����ѽṹ+�����Ѷ�Ԫ����ĩβԪ��
	for (int j = size - 1; j > 0; j--)
	{
		//���Ѷ�Ԫ����ĩβԪ�ؽ��н���
		int t = array[0];
		array[0] = array[j];
		array[j] = t;
		HeapAdjust(array, 0, j);//���¶Զѽ��е���
	}

}

/* �������� */
void QuickSort(int a[], int l, int r)
{
	int mid = a[(l + r) / 2];
	int i = l;
	int j = r;
	do
	{
		while (a[i] < mid)//�ҵ�mid����mid�����
			i++;
		while (a[j] > mid)//�ҵ�mid�Ҳ��midС����
			j--;

		if (i <= j)//Ҫ�����
		{
			int t = a[i];
			a[i] = a[j];
			a[j] = t;
			i++;
			j--;
		}
	} while (i <= j);

	if (i < r)
		QuickSort(a, i, r);//[i,r]�����ڲ���֤���򣬽���ȷ�����Ƕ�����mid���ݹ�����

	if (j > l)
		QuickSort(a, l, j);//[l,j]�����ڲ���֤���򣬽���ȷ�����Ƕ�С��mid���ݹ�����
}

/* �鲢���� */
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

	QueryPerformanceFrequency(&tick);	//��ü�����Ƶ��
	QueryPerformanceCounter(&begin);	//��ó�ʼӲ������������

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

	QueryPerformanceCounter(&end);		//�����ֹӲ������������

	fout << "������" << testfilename << "��Ϊ����,�����СΪ" << size << ",ʹ��";
	switch (sm)
	{
		case SORT_METHOD::Insertion:
		{
			fout << "����";
			break;
		}
		case SORT_METHOD::Selection:
		{
			fout << "ѡ��";
			break;
		}
		case SORT_METHOD::Bubble:
		{
			fout << "ð��";
			break;
		}
		case SORT_METHOD::Shell:
		{
			fout << "ϣ��";
			break;
		}
		case SORT_METHOD::Heap:
		{
			fout << "��";
			break;
		}
		case SORT_METHOD::Quick:
		{
			fout << "����";
			break;
		}
		case SORT_METHOD::Merge:
		{
			fout << "�鲢";
			break;
		}
	}

	fout << "����Ĳ���,������ʱ����:" << endl;
	fout << "������Ƶ�� : " << tick.QuadPart << "Hz" << endl;
	fout << "���������� : " << end.QuadPart - begin.QuadPart << endl;
	fout << setiosflags(ios::fixed) << setprecision(6) << double(end.QuadPart - begin.QuadPart) / tick.QuadPart << "��" << endl;

	delete[]array;
}

int main()
{
	srand(unsigned int(time(NULL)));

	/* �Ƿ��ؽ������ļ� */
	if (NEED_TO_RECREATE)
	{
		Create_My_Test_Files();
		cout << "���������ļ��������" << endl;
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
	
	outres << "======================������ʽ��ʼ======================" << endl;

	for (int i = 0; size[i]; i++)
	{
		for (int j = 0;j < TEST_METHOD_NUM;j++)
		{
			cout << "��ǰ���ڲ���,���� : " << filename[i] << "  ��С : " << setw(6) << size[i] << " ���򷽷� : " << setw(6) << SORT_METHOD_NAME[j] << endl;
			test(filename[i].c_str(), size[i], sm[j], outres);
		}
	}

	outres << "========================���Խ���========================" << endl;
	outres.close();

	return 0;
}