#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
using namespace std;
const int N=200010;
int n,m,K,x[N],y[N],f[N+N];
int get(int x)
{
	if (f[x]==x) return x;else f[x]=get(f[x]);
	return f[x];
}
int main()
{
	scanf("%d%d%d",&n,&m,&K);
	for (int i=1;i<=K;i++) scanf("%d%d",&x[i],&y[i]);
	int ans=0;
	for (int i=1;i<=n+m;i++) f[i]=i;
	for (int i=1;i<=K;i++)
	{
		int X=get(x[i]),Y=get(y[i]+n);
		f[X]=Y;
	}
	for (int i=1;i<=n+m;i++)
		if (get(i)==i) ans++;
	printf("%d\n",ans-1);
	return 0;
}
