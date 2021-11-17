#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
 
#ifdef _MSC_VER
#pragma warning(disable:6031)
#endif
 
 
#define K 1024
int map[K][K];
int m, n;
 
struct UnionSet
{
	int Father[K][K];
 
	void init()
	{
		for (int i = 1; i <= m; i++)
			for (int j = 1; j <= n; j++)
				Father[i][j] = (i - 1) * n + j - 1;
	}
 
	int find(int i,int j)
	{
		if (Father[i][j] == (i - 1) * n + j - 1)
			return (i - 1) * n + j - 1;
		else
		{
			int ii = Father[i][j] / n + 1;
			int jj = Father[i][j] % n + 1;
			return Father[i][j] = find(ii,jj);//查找时继续更新
		}
	}
 
	bool merge(int i1, int j1, int i2, int j2)//合并
	{
		int f1 = find(i1, j1);
		int f2 = find(i2, j2);
		int f1i = f1 / n + 1;
		int f2i = f2 / n + 1;
		int f1j = f1 % n + 1;
		int f2j = f2 % n + 1;
		if ((f1i == 1 || f1i == m || f1j == 1 || f1j == n) && !(f2i == 1 || f2i == m || f2j == 1 || f2j == n))
		{
			Father[f1i][f1j] = Father[f2i][f2j];
			return true;
		}
		else if (!(f1i == 1 || f1i == m || f1j == 1 || f1j == n) && (f2i == 1 || f2i == m || f2j == 1 || f2j == n))
		{
			Father[f2i][f2j] = Father[f1i][f1j];
			return true;
		}
		if (f1 < f2)
		{
			Father[f2i][f2j] = Father[f1i][f1j];
			return true;
		}
		else if (f1 > f2)
		{
			Father[f1i][f1j] = Father[f2i][f2j];
			return true;
		}
		else
			return false;
	}
};
 
struct UnionSet us;
 
int getanswer()
{
	us.init();
	int ans = 0;
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if(i >= 2 && map[i][j] && map[i - 1][j])
				us.merge(i, j, i - 1, j);
			if (i <= m - 1 && map[i][j] && map[i + 1][j])
				us.merge(i, j, i + 1, j);
			if (j >= 2 && map[i][j] && map[i][j - 1])
				us.merge(i, j, i, j - 1);
			if (j <= n - 1 && map[i][j] && map[i][j + 1])
				us.merge(i, j, i, j + 1);
		}
	}
	for (int i = 2; i < m; i++)
	{
		for (int j = 2; j < n; j++)
		{
			if (map[i][j] && us.Father[i][j] == (i - 1) * n + j - 1)
			{
				//cout << i << " " << j << endl;
				ans++;
			}
		}
	}
#if 0
	for (int i = 1; i <= m; i++)
	{
		if (map[i][1] && us.Father[i][1] == (i - 1) * n + 1 - 1)
		{
			int t = (i - 1) * n + 1 - 1;
			bool sign = false;
			for (int j = 1; j <= m; j++)
				if (map[j][2] == t)sign = true;
			if (!sign)
				ans--;
		}
	}
	if (n >= 2)
	{
		for (int i = 1; i <= m; i++)
		{
			if (map[i][n] && us.Father[i][n] == (i - 1) * n + n - 1)
			{
				int t = (i - 1) * n + n - 1;
				bool sign = false;
				for (int j = 1; j <= m; j++)
					if (map[j][n - 1] == t)sign = true;
				if (!sign)
					ans--;
			}
		}
	}
	for (int j = 1; j <= n; j++)
	{
		if (map[1][j] && us.Father[1][j] == (1 - 1) * n + j - 1)
		{
			int t = (1 - 1) * n + j - 1;
			bool sign = false;
			for (int i = 1; i <= n; i++)
				if (map[2][i] == t)sign = true;
			if (!sign)
				ans--;
		}
	}
	if (m >= 2)
	{
		for (int j = 1; j <= n; j++)
		{
			if (map[m][j] && us.Father[m][j] == (m - 1) * n + j - 1)
			{
				int t = (m - 1) * n + j - 1;
				bool sign = false;
				for (int i = 1; i <= n; i++)
					if (map[m - 1][i] == t)sign = true;
				if (!sign)
					ans--;
			}
		}
	}
#endif
 
	return ans;
}
 
int main()
{
	cin >> m >> n;
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++)
			cin >> map[i][j];
	if (m == 1 || n == 1)
		cout << 0;
	else
		cout << getanswer();
	return 0;
}