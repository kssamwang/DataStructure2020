#include <bits/stdc++.h>
using namespace std;
const int maxn = 205;

struct Node
{
	string data;
	int nxt;
} s[maxn];

void print_st(int m)
{
	for (int i = 0; i < m; i++)
	{
		cout << i << " : " << (s[i].data.size() ? s[i].data : "N/A") << " : " << s[i].nxt;
		if ((i + 1) % 3 == 0)
		{
			cout << "\n";
		}
		else
		{
			cout << "        ";
		}
	}
	if (m % 3 != 0)
	{
		cout << "\n";
	}
}
 
int main()
{
	int m, n;
	cin >> m >> n;
	if (m == 1)
	{
		s[1].nxt = -1;
	}
	for (int i = 1; i < m - 1; i++)
	{
		s[i].nxt = i + 1;
	}
	s[0].nxt = s[m - 1].nxt = -1;
	string tmp;
	int l = 0;
	for (int i = 0; i < n; i++)
	{
		int u = s[1].nxt;
		if (u == -1)
		{
			cin >> tmp;//ignore the redundancy
			continue;
		}
		s[1].nxt = s[u].nxt;
		s[u].nxt = s[l].nxt;
		s[l].nxt = u;
		l = u;
		cin >> s[u].data;
	}
	print_st(m);
	int i;
	cin >> i >> tmp;
	if (s[1].nxt == -1)
	{
		cout << "FULL\n";
	}
	else if (i < 1)
	{
		cout << "-1\n";
	}
	else
	{
		int cur = 0;
		bool ok = true;
		while (--i)
		{
			cur = s[cur].nxt;
			if (cur == -1)
			{
				cout << "-1\n";
				ok = false;
				break;
			}
		}
		if (ok)
		{
			int u = s[1].nxt;
			if (u == -1)
			{
				cout << "FULL\n";
			}
			else
			{
				s[1].nxt = s[u].nxt;
				s[u].nxt = s[cur].nxt;
				s[u].data = tmp;
				s[cur].nxt = u;
				for (u = s[0].nxt; u != -1; u = s[u].nxt)
				{
					cout << s[u].data << (s[u].nxt == -1 ? "\n" : " ");
				}
			}
		}
	}
	cin >> i;
	if (i < 1)
	{
		cout << "-1\n";
	}
	else
	{
		int pre = 0, cur = s[0].nxt;
		if (cur == -1)
		{
			cout << "EMPTY\n";
		}
		else
		{
			bool ok = true;
			while (--i)
			{
				pre = s[pre].nxt;
				cur = s[cur].nxt;
				if (cur == -1)
				{
					cout << "-1\n";
					ok = false;
					break;
				}
			}
			if (ok)
			{
				cout << s[cur].data << "\n";
				s[cur].data.clear();
				s[pre].nxt = s[cur].nxt;
				s[cur].nxt = s[1].nxt;
				s[1].nxt = cur;
			}
		}
		/*
		for(cur=s[0].nxt; cur!=-1; cur=s[cur].nxt)
		{
			cout<<s[cur].data<<(s[cur].nxt==-1?"\n":" ");
		}*/
 
	}
	cin >> tmp;
	int pos = 0, cur = s[0].nxt;
	while (cur != -1)
	{
		pos++;
		if (s[cur].data == tmp)
		{
			cout << pos << "\n";
			break;
		}
		cur = s[cur].nxt;
	}
	if (cur == -1)
	{
		cout << "-1\n";
	}
	cin >> tmp;
	if (s[1].nxt == -1)
	{
		cout << "FULL\n";
	}
	else
	{
		for (cur = 0; s[cur].nxt != -1; cur = s[cur].nxt)
		{
			cout << s[s[cur].nxt].data << " ";
		}
		int v = s[1].nxt;
		s[cur].nxt = v;
		s[1].nxt = s[v].nxt;
		s[v].data = tmp;
		s[v].nxt = -1;
		cout << s[v].data << "\n";
	}
	print_st(m);
	return 0;
}