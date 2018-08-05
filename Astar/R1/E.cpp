#include<cstdio>
#include<algorithm>
#include<cstring>
#define mo 1000000007
using namespace std;
const int L=60;
int n,a[10100],f[10100][L+5],g[L+5][10100];
int lowbit(int x) { return x&(-x);}
void add(int x,int y,int z)
{
	for (int i=y;i<=n+1;i+=lowbit(i)) g[x][i]=(g[x][i]+z)%mo;
}
int get(int x,int y)
{
	int ans=0;
	for (int i=y;i>=1;i-=lowbit(i)) ans=(ans+g[x][i])%mo;
	return ans;
}
int main()
{
	int T;
	scanf("%d",&T);
	for (int Case=1;Case<=T;Case++)
	{
		scanf("%d",&n);
		for (int i=1;i<=n;i++) scanf("%d",&a[i]);
		memset(g,0,sizeof(g));
		add(0,1,1);
		for (int i=1;i<=n;i++)
			for (int j=1;j<=min(n,L);j++)
			{
				f[i][j]=get(j-1,a[i]);
				add(j,a[i]+1,f[i][j]);
			}
		printf("Case #%d: ",Case);
		for (int i=1;i<=min(L,n);i++)
			printf("%d%c",get(i,n+1)," \n"[i==n]);
		for (int i=L+1;i<=n;i++) printf("0%c"," \n"[i==n]);
	}
	return 0;
}
