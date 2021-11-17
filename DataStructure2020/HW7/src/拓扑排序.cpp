#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
 
typedef long long ll;
 
const int maxn = 105;
 
int n,m;
 
struct Edge
{
	int to;
	int dist;
};
 
vector<Edge> G[maxn];
int in_degree[maxn];
 
int topo[maxn];//存储结果
 
//返回1表示存在拓扑序，0表示有环 
bool topo_sort()
{
	int cnt = 0;
	queue<int> q;
	for (int i = 1; i <= n; i++)
	{
		if (in_degree[i] == 0)
		{
			q.push(i);
		}
	}
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		topo[cnt++] = u;
		for (int i = 0; i < int(G[u].size()); i++)
		{
			int v = G[u][i].to;
			if (--in_degree[v] == 0)
			{
				q.push(v);
			}
		}
	}
	return cnt == n;
}
 
int main()
{
	cin >> n >> m;
	memset(in_degree, 0, sizeof(in_degree));
	for (int i = 0; i < m; i++)
	{
		int u;
		Edge e;
		cin >> u >> e.to >> e.dist;
		G[u].push_back(e);
		in_degree[e.to]++;
	}
	cout << topo_sort() ? "1" : "0";
	return 0;
}