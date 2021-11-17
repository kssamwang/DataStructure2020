#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <queue>
#include <vector>
using namespace std;
 
const int MAXN = 25;
 
vector<int> dis[MAXN];
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
	if (dis[s].empty())return;
	for (int i = int(dis[s].size()) - 1; i >= 0; i--)
		if (!vis[dis[s][i]])
			dfs(dis[s][i]);
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
		if (dis[k].empty())continue;
		for (int i = int(dis[k].size()) - 1; i >= 0; i--)
		{
			if (!vis[dis[k][i]])
			{
				q.push(dis[k][i]);
				vis[dis[k][i]] = 1;
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
		dis[u].push_back(v);
		dis[v].push_back(u);
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