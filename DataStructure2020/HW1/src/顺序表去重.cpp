#include <iostream>
#include <cstdio>
using namespace std;
 
int a[1000005];
 
int find(const int n, const int e)//��[0-n-1]�±������Ԫ��e
{
	if (!n)
		return 1;
	int i = 0;
	while (i < n && a[i] != e)
		i++;
	return (i == n);//û�ҵ��ظ���
}
 
int main()
{
	int n;
	scanf("%d",&n);
	for(int i = 0;i < n;i++)
	{
		scanf("%d", &a[i]);
		if (find(i, a[i]))
		{
			if(i)
				printf(" ");
			printf("%d", a[i]);
		}
	}
	return 0;
}