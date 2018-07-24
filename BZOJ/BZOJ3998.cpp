#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
char s[500010];
int n,T,K;
struct SAM
{
	int last,cnt,a[1000010][26],fa[1000010],maxlen[1000010],val[1000010],sum[1000010],v[500010],Q[1000010];
	SAM() { last=++cnt;}
	void extend(int c)
	{
		int p=last,np=last=++cnt;
		maxlen[np]=maxlen[p]+1;
		val[np]=1;
		while (!a[p][c]&&p) a[p][c]=np,p=fa[p];
		if (!p) fa[np]=1;
		else
		{
			int q=a[p][c];
			if (maxlen[p]+1==maxlen[q]) fa[np]=q;
			else
			{
				int nq=++cnt;maxlen[nq]=maxlen[p]+1;
				memcpy(a[nq],a[q],sizeof(a[q]));
				fa[nq]=fa[q];
				fa[np]=fa[q]=nq;
				while (a[p][c]==q) a[p][c]=nq,p=fa[p];
			}
		}
	}
	void pre()
	{
		for (int i=1;i<=cnt;i++) v[maxlen[i]]++;
		for (int i=1;i<=n;i++) v[i]+=v[i-1];
		for (int i=cnt;i>=1;i--) Q[v[maxlen[i]]--]=i;
		for (int i=cnt;i>=1;i--)
		{
			int u=Q[i];
			if (T) val[fa[u]]+=val[u];
				else val[u]=1;
		}
		val[1]=0;
		for (int i=cnt;i>=1;i--)
		{
			int u=Q[i];
			sum[u]=val[u];
			for (int j=0;j<26;j++) sum[u]+=sum[a[u][j]];
		}
	}
	void dfs(int u,int k)
	{
		if (k<=val[u]) return;
		k-=val[u];
		for (int i=0;i<26;i++)
		if (a[u][i])
		{
			if (k<=sum[a[u][i]])
			{
				putchar('a'+i);
				dfs(a[u][i],k);
				return;
			}
			k-=sum[a[u][i]];
		}
	}
}sam;
int main()
{
	scanf("%s",s+1);
	n=strlen(s+1);
	scanf("%d%d",&T,&K);
	for (int i=1;i<=n;i++)
		sam.extend(s[i]-'a');
	sam.pre();
	if (K>sam.sum[1]) puts("-1");
		else sam.dfs(1,K);
	return 0;
}
