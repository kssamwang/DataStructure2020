#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <queue>
using namespace std;
 
const int MAXN = 1000;
 
int dis[MAXN][MAXN];
int vis[MAXN];
 
int n;
int m;
bool first = false;
 
void dfs(int s)
{
	if (first)cout << " "; 
	cout << s;
	vis[s] = 1;
	first = true;
	for (int i = 0; i < n; i++)
		if (!vis[i] && dis[s][i])
			dfs(i);
}
 
void bfs(int s)
{
	first = false;
	queue<int>q;
	q.push(s);
	while (!q.empty())
	{
		int k = q.front();
		q.pop();
		if (first) cout << " ";
		else first = true;
		cout << k;
		for (int i = 0; i < n; i++)
		{
			if (!vis[i] && dis[k][i] > 0)
			{
				q.push(i);
				vis[i] = 1;
			}
		}
	}
}
 
int main()
{
	ios::sync_with_stdio(false);
	memset(dis, 0, sizeof(dis));
	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		int u, v;
		cin >> u >> v;
		dis[u][v] = dis[v][u] = 1;
	}
	memset(vis, 0, sizeof(vis));
	for (int i = 0; i < n; i++)
	{
		if (!vis[i])
		{
			first = false;
			cout << "{";
			dfs(i);
			cout << "}";
		}
	}
	cout << endl;
	memset(vis, 0, sizeof(vis));
	for (int i = 0; i < n; i++)
	{
		if (!vis[i])
		{
			first = false;
			vis[i] = 1;
			cout << "{";
			bfs(i);
			cout << "}";
		}
	}
	return 0;
}