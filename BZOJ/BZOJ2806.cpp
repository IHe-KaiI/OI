#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=2200010;
int n,m,last,cnt,maxlen[N],a[N][2],fa[N],Q[N],f[N],Len[N],len;
char s[N];
void extend(int c)
{
	int p=last,np;np=last=++cnt;
	maxlen[np]=maxlen[p]+1;
	while (p&&!a[p][c]) a[p][c]=np,p=fa[p];
	if (!p) fa[np]=1;
	else
	{
		int q=a[p][c];
		if (maxlen[q]==maxlen[p]+1) fa[np]=q;
		else
		{
			int nq=++cnt;
			maxlen[nq]=maxlen[p]+1;
			fa[nq]=fa[q];
			fa[q]=fa[np]=nq;
			memcpy(a[nq],a[q],sizeof(a[q]));
			while (p&&a[p][c]==q) a[p][c]=nq,p=fa[p];
		}
	}
}
void Insert(char *s)
{
	last=1;
	int len=strlen(s);
	for (int i=0;i<len;i++) extend(s[i]-'0');
}
bool check(int x)
{
	int t=1,w=0;
	for (int i=0;i<=len;i++) f[i]=0;
	for (int i=1;i<=len;i++)
	{
		if (i-x>=0)
		{
			int j=i-x;
			while (t<=w&&f[j]-j>=f[Q[w]]-Q[w]) w--;
			Q[++w]=j;
		}
		while (t<=w&&Q[t]<i-Len[i]) t++;
		if (t<=w)
		{
			f[i]=f[Q[t]]+i-Q[t];
		}
		f[i]=max(f[i],f[i-1]);
	}
	return f[len]*10>=len*9;
}
void erfen(int l,int r)
{
	while (l<r)
	{
		int mid=(l+r+1)>>1;
		if (check(mid)) l=mid;
			else r=mid-1;
	}
	printf("%d\n",l);
}
void run()
{
	int id=1,l=0;
	for (int i=0;i<len;i++)
	{
		while (id&&!a[id][s[i]-'0']) id=fa[id],l=maxlen[id];
		l++;
		id=a[id][s[i]-'0'];
		if (!id) id=1,l=0;
		Len[i+1]=l;
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	last=++cnt;
	for (int i=1;i<=m;i++)
	{
		scanf("%s",s);
		Insert(s);
	}
	for (int i=1;i<=n;i++)
	{
		scanf("%s",s);
		len=strlen(s);
		run();
		erfen(0,len);
	}
	return 0;
}
