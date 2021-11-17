#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
 
#ifdef _MSC_VER
#pragma warning(disable:6031)
#endif
 
int N, P, M, K;
int HashTable[10008];
char s[10005];
 
bool isprime(int n)
{
	for (int i = 2; i * i <= n; i++)
		if (n % i == 0)
			return false;
	return true;
}
 
int myhash(const char s[10005])
{
	int h = 0;
	int i = 0;
	while (s[i])
	{
		h = h * 37 + int(s[i++]);
		h %= M;
	}
	if (!HashTable[h])
	{
		HashTable[h] = 1;
		return h;
	}
	else
	{
		int newh;
		for (int i = 1; i <= K; i++)
		{
			newh = (h + i * i) % M;
			if (!HashTable[newh])
			{
				HashTable[newh] = 1;
				return newh;
			}
			newh = (h - i * i + M * i) % M;
			if (!HashTable[newh])
			{
				HashTable[newh] = 1;
				return newh;
			}
		}
		return -1;
	}
	
}
 
int main()
{
	ios::sync_with_stdio(false);
	cin >> N >> P;
	M = P;
	while (!isprime(M))M++;
	K = M / 2;
	memset(HashTable, 0, sizeof(HashTable));
	for (int i = 0; i < N; i++)
	{
		cin >> s;
		int ans = myhash(s);
		if (ans == -1)
			cout << "-";
		else
			cout << ans;
		cout << " ";
	}
	return 0;
}