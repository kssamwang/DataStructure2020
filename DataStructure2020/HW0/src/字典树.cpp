#include <bits/stdc++.h>
using namespace std;
const int N = 200005; //���N����ĸ���ڵ�������ΪN
int son[N][26]; //��Ϊֻ����СдӢ����ĸ��ÿ���ڵ����������26����,ÿ���ڵ���ӽڵ�������Ϊ26
//son����洢ÿ��������ж���
int cnt[N]; //�Ե�ǰ������β�ĵ����ж��ٸ�
int idx; //ͬ�������idx,��ǰ�õ����ĸ��±�
//�±���0�ĵ���Ǹ��ڵ����ǿսڵ�
//���һ����û���ӽڵ㣬Ҳ����ָ��0
char str[N];
//�洢��Ҳ���ǲ��������ʵ�ֺ���
void insert(char str[]) {
	int p = 0; //�Ӹ��ڵ㿪ʼ
	int len = strlen(str);
	for (int i = 0; i < len; i++) { //����Ҫ�洢���ַ���
		int u = str[i] - 'a'; //�ѵ�ǰ�����ĸ��Ӧ���ӽڵ��ż������
		//Ҳ���ǰ�a ~ z��ӳ���0 ~ 25
		//�����ǰ������ϲ����������ĸ�Ļ� ��������������
		if (!son[p][u]) { //���p�ڵ㲻����u������ӵĻ�
			son[p][u] = ++idx; //��������
		}
		p = son[p][u]; //�ߵ���һ����
		//�������д������˼����˵��û������ڵ�Ļ����Ҵ���һ���ڵ㣬ҲҪ�ߵ�����ڵ���ȥ
		//������ڵ�Ļ����Ҿ��ߵ�����ڵ���ȥ
		//���p���ߵ����뵥�����һ����
		cnt[p]++; //��������β�ĵ���������һ
	}
	
}
//��ѯ�����������ַ������ֶ��ٴ�
int query(char str[]) {
	int p = 0;
	for (int i = 0; str[i]; i++) {
		int u = str[i] - 'a';
		if (!son[p][u]) {
			return 0;
		}
		p = son[p][u];
	}
	return cnt[p];
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n,m;
	cin >> n >> m;
	for(int i = 0;i < n;i++)
	{
		cin >> str;
		insert(str);
	}
	for(int i = 0;i < m;i++)
	{
		cin >> str;
		cout << query(str) << endl;
	}
	return 0;
}