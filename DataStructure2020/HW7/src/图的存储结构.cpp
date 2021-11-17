#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <map>
#include <cstring>
#include <iomanip>
using namespace std;
 
#ifdef _MSC_VER
#pragma warning(disable:6031)
#endif
 
const int wdg = 1;//����ͼ
const int wdn = 2;//������
const int ndg = 3;//����ͼ
const int ndn = 4;//������
 
const int MAXN = 100;
 
int dis[MAXN][MAXN];
char sign[MAXN];
 
int mode;
int n;
int m;
 
map<char, int> sign_to_index;//�Ӷ����ַ�ӳ�䵽�����±�
 
int main()
{
	ios::sync_with_stdio(false);
	memset(dis, 0, sizeof(dis));
	//scanf("%d", &mode);
	//scanf("%d%d", &n, &m);
	cin >> mode;
	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		char ch;
		cin >> ch;
		sign[i] = ch;
		sign_to_index.insert({ch,i});
	}
	//getchar();
	for (int i = 0; i < m; i++)
	{
		char uc, vc;
		int l = 0;
		cin >> uc >> vc;
		int u = sign_to_index[uc];
		int v = sign_to_index[vc];
		if (!(mode % 2))
			cin >> l;// scanf("%d", &l);
		if (mode == ndg)//����ͼ
			dis[u][v] = dis[v][u] = 1;
		else if (mode == ndn)//������
			dis[u][v] = dis[v][u] = l;
		else if (mode == wdg)//����ͼ
			dis[u][v] = 1;
		else if (mode == wdn)//������
			dis[u][v] = l;
	}
	for (int i = 0; i < n; i++)
		printf("%c ", sign[i]);
	printf("\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			printf("%4d", dis[i][j]);
		printf("\n");
	}
	for (int i = 0; i < n; i++)
	{
		printf("%c-->", sign[i]);
		for (int j = n - 1; j >= 0; j--)
			if (dis[i][j] > 0)
			{
				printf("%d", j);
				if(!(mode%2))
					printf(",%d",dis[i][j]);
				printf(" ");
			}
		printf("\n");
	}
	return 0;
}