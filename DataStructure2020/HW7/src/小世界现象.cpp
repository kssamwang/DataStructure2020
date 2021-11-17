#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
 
#ifdef _MSC_VER
#pragma warning(disable:6031)
#endif
 
const int MAXN = 2005;
const int MAXM = MAXN * 33;
 
vector<int> net[MAXN];
int vis[MAXN];
int dist[MAXN];
int n, m;
 
double bfs(const int k)
{
	queue<int>q;
	q.push(k);
	int count = 0;
	memset(vis, 0, sizeof(int) * MAXN);
	vis[k] = 1;
	for (int i = 1; i <= n; i++)
		dist[i] = MAXN;
	dist[k] = 0;
	while (!q.empty())
	{
		int cur = q.front();
		q.pop();
		for (size_t i = 0; i < net[cur].size(); i++)
		{
			int next = net[cur][i];
			if (!vis[next])
			{
				q.push(next);
				vis[next] = 1;
				dist[next] = dist[cur] + 1;
			}
		}
	}
	for (int i = 1; i <= n; i++)
		if (vis[i] && dist[i] <= 6)
			count++;
	return count * 100.00000000 / n;
}
 
int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		net[u].push_back(v);
		net[v].push_back(u);
	}
	for (int i = 1; i <= n; i++)
		printf("%d: %.2f%%\n", i, bfs(i) + 0.0001f);
	return 0;
}