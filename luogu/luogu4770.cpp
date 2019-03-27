#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
using namespace std;

struct sam
{

	void extend(int c)
	{
		int p=last,np;last=np=++cnt;
		maxlen[np]=maxlen[p]+1;
		while (p&&!a[p][c]) a[p][c]=np,p=fa[p];
		if (!p) fa[np]=1;
		else
		{
			int q=a[p][c];
			if (maxlen[p]==maxlen[p]+1) fa[np]=q;
			else
			{
				int nq=++cnt;
				maxlen[nq]=maxlen[p]+1;
				memcpy(a[nq],a[q],sizeof(a[q]));
				fa[nq]=fa[np]=q;
				fa[q]=p;
				while (p&&a[p][c]==q) a[p][c]=nq,p=fa[p];
			}
		}
	}
	void build(char *S)
	{
		int len=strlen(S);
		root=last=++cnt;
		for (int i=0;i<len;i++) extend(S[i]-'a');
	}
	ll Get()
	{
		ll ans=0;
		for (int i=root;i<=cnt;i++) ans+=maxlen[i]-maxlen[fa[i]];
		return ans;
	}
}SAM[2];
void solve()
{
	int len=strlen(T),id0=SAM[0].root,id1=SAM[1].root,l=0;
	for (int i=0;i<len;i++)
	{
		while (!SAM[0].a[id0][T[i]-'a'])
		{
			id0=SAM[0].fa[id0];
			l=SAM[0].maxlen[id0];
			while (SAM[1].maxlen[SAM[1].fa[id1]]>=l) id1=SAM[1].fa[id1];
		}
		l++;
		id0=SAM[0].a[id0][T[i]-'a'];
		id1=SAM[1].a[id1][T[i]-'a'];
		p[id1]=l;
	}
	for (int i=1;i<=len;i++) num[i]=0;
	for (int i=1;i<=cnt;i++) num[SAM[1].maxlen[i]]++;
	for (int i=1;i<=cnt;i++) num[i]+=num[i-1];
	for (int i=1;i<=cnt;i++) Q[num[SAM[1].maxlen[i]]--]=i;
	for (int i=cnt;i>=1;i--)
	{
		if (
	}
}
int main()
{
	scanf("%s",S);
	scanf("%d",&Q);
	SAM[0].build(S);
	for (int i=0;i<len;i++) 
	while (Q--)
	{
		int l,r;
		scanf("%s%d%d",T,&l,&r);
		SAM[1].build(T);
		sum=0;
		solve();
		printf("%lld\n",SAM[1].Get()-sum);
	}
	return 0;
}
