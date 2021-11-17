#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
using namespace std;
 
#ifdef _MSC_VER
#pragma warning(disable:6031)
#endif
 
#define MAXN 20005
vector<int>a;
 
int ans;
 
void merge_sort(vector<int>& vec)
{
	int size = vec.size();
	if (size < 2)
		return;
	int mid = size / 2;
	vector<int> l;
	vector<int> r;
	for (int i = 0; i < mid; i++)
		l.push_back(vec[i]);
	for (int i = mid; i < size; i++)
		r.push_back(vec[i]);
	vec.clear();
	merge_sort(l);
	merge_sort(r);
	int i = 0;
	int j = 0;
	while (i < l.size() && j < r.size())
	{
		if (l[i] <= r[j])
		{
			ans += j;
			vec.push_back(l[i++]);
		}
		else
		{
			vec.push_back(r[j++]);
		}
	}
	while (i < l.size())
	{
		ans += j;
		vec.push_back(l[i++]);
	}
	while (j < r.size())
	{
		vec.push_back(r[j++]);
	}
}
 
int main()
{
	while (true)
	{
		int n;
		scanf("%d", &n);
		if (!n)break;
		a.clear();
		for (int i = 0; i < n; i++)
		{
			int x;
			scanf("%d", &x);
			a.push_back(x);
		}
		ans = 0;
		merge_sort(a);
		printf("%d\n", ans);
	}
	return 0;
}