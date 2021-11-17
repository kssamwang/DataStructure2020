#include <bits/stdc++.h>
using namespace std;
const int N = 200005; //最多N个字母，节点个数最多为N
int son[N][26]; //因为只包含小写英文字母，每个节点最多向下连26条边,每个节点的子节点个数最多为26
//son数组存储每个点的所有儿子
int cnt[N]; //以当前这个点结尾的单词有多少个
int idx; //同单链表的idx,当前用到了哪个下标
//下标是0的点既是根节点又是空节点
//如果一个点没有子节点，也把其指向0
char str[N];
//存储，也就是插入操作的实现函数
void insert(char str[]) {
	int p = 0; //从根节点开始
	int len = strlen(str);
	for (int i = 0; i < len; i++) { //遍历要存储的字符串
		int u = str[i] - 'a'; //把当前这个字母对应的子节点编号计算出来
		//也就是把a ~ z，映射成0 ~ 25
		//如果当前这个点上不存在这个字母的话 ，把它创建出来
		if (!son[p][u]) { //如果p节点不存在u这个儿子的话
			son[p][u] = ++idx; //创建出来
		}
		p = son[p][u]; //走到下一个点
		//上面三行代码的意思就是说，没有这个节点的话，我创造一个节点，也要走到这个节点上去
		//有这个节点的话，我就走到这个节点上去
		//最后p就走到插入单词最后一个点
		cnt[p]++; //以这个点结尾的单词数量加一
	}
	
}
//查询操作，返回字符串出现多少次
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