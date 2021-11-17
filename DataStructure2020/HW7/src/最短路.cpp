#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <cstring>
#include <queue>
using namespace std;
 
#ifdef _MSC_VER
#pragma warning(disable:6031)
#endif
 
 
const int maxn = 100000 + 5;
 
struct Edge
{
	int to;
	int dist;
};
 
vector<Edge> G[maxn];
 
struct Node
{
	int num;
	int dis;
	bool operator < (const Node& rhs) const
	{
		return dis > rhs.dis;
	}
};
 
int n, m, s;
 
int d[maxn];
bool done[maxn];
 
void dij(int s)
{
	memset(d, 0x3f, sizeof(d));
	d[s] = 0;
	priority_queue<Node> pq;
	pq.push(Node{ s,0 });
	while (!pq.empty())
	{
		int u = pq.top().num;
		pq.pop();
 
		if (done[u])
			continue;
		done[u] = true;
 
		for (int i = 0; i < G[u].size(); i++)
		{
			Edge e = G[u][i];
			if (d[u] + e.dist < d[e.to])
			{
				d[e.to] = d[u] + e.dist;
				pq.push(Node{ e.to,d[e.to] });
			}
		}
	}
}
 
 
int main()
{
	scanf("%d %d %d", &n, &m, &s);
	for (int i = 0; i < m; i++)
	{
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		G[u].push_back(Edge{ v,w });
		G[v].push_back(Edge{ u,w });
	}
	dij(s);
	for(int i = 1;i <= n;i++)
		printf("%d ",done[i] ? d[i] : 2147483647);
	return 0;
}