#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
 
const int maxn = 105;
 
struct Edge
{
	int to, dist;
	bool is_key;
};
 
vector<Edge> G[maxn];
 
int indgr[maxn];
int cnt[maxn];
int topo_sort[maxn];
int dp[maxn];
bool vis[maxn];
 
int main()
{
	int n, m;
	cin >> n >> m;
 
	for (int i = 0, u, v, w; i < m; i++)
	{
		cin >> u >> v >> w;
		G[u].push_back(Edge{ v,w,0 });
		indgr[v]++;
	}
	queue<int> q;
	int cur = 0;
	memset(cnt, -1, sizeof(cnt));
	for (int i = 1; i <= n; i++)
	{
		if (!indgr[i])
		{
			q.push(i);
			topo_sort[cur] = i;
			cnt[i] = cur++;
		}
	}
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		for (Edge& e : G[u])
		{
			int v = e.to;
			if (--indgr[v] == 0)
			{
				if (cnt[v] == -1)
				{
					topo_sort[cur] = v;
					cnt[v] = cur++;
					q.push(v);
				}
				else
				{
					cout << 0 << endl;
					return 0;
				}
			}
		}
	}
	for (int i = 1; i <= n; i++)
	{
		if (cnt[i] == -1)
		{
			cout << 0 << endl;
			return 0;
		}
	}
	int res = -1;
	for (int i = 0; i < n; i++)
	{
		int u = topo_sort[i];
		for (Edge& e : G[u])
		{
			int v = e.to, w = e.dist;
			dp[v] = max(dp[v], dp[u] + w);
			res = max(res, dp[v]);
		}
	}
	cout << res << "\n";
	for (int i = n - 1; i >= 0; i--)
	{
		int u = topo_sort[i];
		if (dp[u] == res)
		{
			vis[u] = true;
		}
		for (Edge& e : G[u])
		{
			int v = e.to, w = e.dist;
			if (vis[v] && dp[v] == dp[u] + w)
			{
				vis[u] = true;
				e.is_key = true;
			}
		}
	}
	for (int i = 1; i <= n; i++)
	{
		for (auto it = G[i].rbegin(); it != G[i].rend(); ++it)
		{
			if (it->is_key)
			{
				cout << i << "->" << (it->to) << "\n";
			}
		}
	}
	return 0;
}