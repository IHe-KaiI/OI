#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=200100;
int n,Q,cnt,last,now,maxlen[N],a[N][26],fa[N],vis[N],num[N];
char s[360010];
void extend(int c)
{
	int p=last,np;np=last=++cnt;
	maxlen[np]=maxlen[p]+1;
	while (!a[p][c]&&p) a[p][c]=np,p=fa[p];
	if (!p) fa[np]=1;
	else
	{
		int q=a[p][c];
		if (maxlen[q]==maxlen[p]+1) fa[np]=q;
		else
		{
			int nq=++cnt;
			maxlen[nq]=maxlen[p]+1;
			vis[nq]=vis[q];
			num[nq]=num[q];
			memcpy(a[nq],a[q],sizeof(a[q]));
			fa[nq]=fa[q];
			fa[q]=fa[np]=nq;
			while (a[p][c]==q) a[p][c]=nq,p=fa[p];
		}
	}
	while (np)
	{
		if (vis[np]!=now) vis[np]=now,num[np]++;
			else break;
		np=fa[np];
	}
}
int main()
{
	scanf("%d%d",&n,&Q);
	cnt=1;
	for (int i=1;i<=n;i++)
	{
		scanf("%s",s+1);
		int len=strlen(s+1);
		last=1;
		now=i;
		for (int j=1;j<=len;j++) extend(s[j]-'a');
	}
	while (Q--)
	{
		scanf("%s",s+1);
		int len=strlen(s+1),id=1;
		for (int i=1;i<=len;i++)
		{
			id=a[id][s[i]-'a'];
			if (!id) break;
		}
		printf("%d\n",num[id]);
	}
	return 0;
}
