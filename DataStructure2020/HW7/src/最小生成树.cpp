#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
 
#ifdef _MSC_VER
#pragma warning(disable:6031)
#endif
 
const int N = 505;
int n;
int ans;
 
struct Edge {
	int from;
	int to;
	int dist;
 
	bool operator<(const Edge& e)const
	{
		return dist > e.dist;
	}
};
 
 
priority_queue<Edge> pq;
 
struct UnionSet
{
	int Father[N];
 
	void init()
	{
		for (int i = 1; i <= n; i++)
			Father[i] = i;
	}
 
	int find(int x)
	{
		if (Father[x] == x)
			return x;
		else
			return Father[x] = find(Father[x]);//查找时继续更新
	}
 
	bool merge(int x, int y)//合并
	{
		int fx = find(x);
		int fy = find(y);
		if (fx != fy)
		{
			Father[fy] = fx;
			return true;
		}
		else
			return false;
	}
};
 
struct UnionSet us;
 
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1;j <= n;j++)
		{
			int v;
			scanf("%d", &v);
			Edge e;
			e.from = i;
			e.to = j;
			e.dist = v;
			if (i < j)
			{
				pq.push(e);
			}
		}
	}
	int count = 0;
	us.init();
	while (!pq.empty())
	{
		Edge e = pq.top();
		pq.pop();
		if (us.merge(e.to, e.from))
		{
			count++;
			ans += e.dist;
		}
		if (count == n - 1)break;
	}
	printf("%d", ans);
	return 0;
}