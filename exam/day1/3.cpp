#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=500100;
int n,L[305],l[N],V,A[305][305],a[N][4],match[N],p[105][1010],vis[N],Stack[5],cnt,Ans[N],P[5][N];
char s[305];
void dfs(int t,int s)
{
	if (t<=s&&t!=0)
	{
		l[++cnt]=t;
		for (int i=0;i<t;i++) a[cnt][i]=Stack[i];
	}
	if (t==s) return;
	for (int i=0;i<26;i++)
	{
		Stack[t]=i;
		dfs(t+1,s);
	}
}
bool find(int x)
{
	for (int i=1;i<=cnt;i++)
	if (p[x][i])
	{
		if (vis[i]!=V)
		{
			vis[i]=V;
			if (!match[i]||find(match[i])) { match[i]=x;return 1;}
		}
	}
	return 0;
}
bool Find(int x)
{
	for (int i=1;i<=cnt;i++)
	if (P[x][i])
	{
		if (vis[i]!=V)
		{
			vis[i]=V;
			if (!match[i]||Find(match[i])) { match[i]=x;return 1;}
		}
	}
	return 0;
}
bool check(int len,int o)
{
	cnt=0;
	dfs(0,len);
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=cnt;j++)
		{
			bool flag=0;
			for (int k=0,x=0;k<L[i];k++)
			{
				if (A[i][k]==a[j][x]) x++;
				if (x==l[j]) { flag=1;break;}
			}
			if (flag)
			{
				if (o) p[i][j]=1;
					else P[i][j]=1;
			}else
			{
				if (o) p[i][j]=0;
					else P[i][j]=0;
			}
		}
	}
	V=0;
	for (int i=1;i<=n;i++) vis[i]=0;
	for (int i=1;i<=cnt;i++) match[i]=0;
	for (int i=1;i<=n;i++)
	{
		V++;
		if (o) { if (!find(i)) return 0;}
			else { if (!Find(i)) return 0;}
	}
	for (int i=1;i<=cnt;i++)
		if (match[i]) Ans[match[i]]=i;
	printf("%d\n",len);
	for (int i=1;i<=n;i++)
	{
		for (int j=0;j<l[Ans[i]];j++) printf("%c",'a'+a[Ans[i]][j]);
		puts("");
	}
	return 1;
}
int main()
{
//	freopen("diff.in","r",stdin);
//	freopen("diff.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%s",s);
		L[i]=strlen(s);
		for (int j=0;j<L[i];j++) A[i][j]=s[j]-'a';
	}
	if (n<=4)
	{
		for (int i=1;i<=4;i++)
			if (check(i,0)) return 0;
		puts("-1");
		return 0;
	}
	for (int i=1;i<=2;i++)
	{
		if (check(i,1)) return 0;
	}
	puts("-1");
	return 0;
}
