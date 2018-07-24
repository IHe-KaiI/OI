#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int T,n,tot,cnt,Q[1010],mu[10000010],prime[5000010],p[10000010],num[10000010],f[10000010],ans[10000010];
bool flag[10000010];
void pre()
{
	mu[1]=1;
	for (int i=2;i<=n;i++)
	{
		if (!flag[i]) { prime[++tot]=i;p[i]=i;mu[i]=-1;}
		for (int j=1;j<=tot;j++)
		{
			if (prime[j]*i>n) break;
			flag[prime[j]*i]=1;
			p[prime[j]*i]=prime[j];
			if (i%prime[j]==0) { mu[i*prime[j]]=0;break;}
				else mu[i*prime[j]]=-mu[i];
		}
	}
}
int dfs(int x,int t,int X)
{
	if (t>cnt) { f[x]+=mu[X];return mu[x]*f[x];}
	return dfs(x*num[t],t+1,X)+dfs(x,t+1,X);
}
int main()
{
	scanf("%d",&T);
	for (int i=1;i<=T;i++) { scanf("%d",&Q[i]);n=max(n,Q[i]);}
	pre();
	for (int i=1;i<=n;i++)
	{
		ans[i]=ans[i-1];
		if (mu[i])
		{
			cnt=0;
			for (int j=i;j!=1;j/=p[j]) num[++cnt]=p[j];
			ans[i]+=mu[i]*dfs(1,1,i);
		}
	}
	for (int i=1;i<=T;i++) printf("%d\n",ans[Q[i]]);
	return 0;
}
