#include<stdio.h>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=20010,M=1000000;
int n,a[N],num[N],tot,prime[N],ans[3010],L;
void getprime()
{
	for (int i=2;i<=1000;i++)
	{
		bool flag=1;
		for (int j=2;j*j<=i;j++)
			if (i%j==0) { flag=0;break;}
		if (flag) prime[++tot]=i;
	}
}
void Work(int x,int d)
{
	for (int i=1;i<=tot;i++)
	{
		while (x%prime[i]==0) x/=prime[i],num[i]+=d;
		if (x==1) break;
	}
}
void calc(int x,int d)
{
	for (int i=1;i<=x;i++) Work(i,d);
}
void mul(int x)
{
	for (int i=1;i<=L;i++) ans[i]=ans[i]*x;
	for (int i=1;i<=L;i++)
	{
		ans[i+1]+=ans[i]/M;
		ans[i]%=M;
	}
	while (ans[L+1]>0) L++,ans[L+1]+=ans[L]/M,ans[L]%=M;
}
int main()
{
	scanf("%d",&n);
	int m=0,tot=0;
	getprime();
	if (n==1)
	{
		int x;
		scanf("%d",&x);
		if (!x||x==-1) puts("1");
			else puts("0");
		return 0;
	}
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		if (!a[i]) { puts("0");return 0;}
		if (a[i]==-1) m++;
			else a[i]--,tot+=a[i];
	}
	if (tot>n-2) { puts("0");return 0;}
	calc(n-2,1);
	calc(n-2-tot,-1);
	for (int i=1;i<=n;i++) if (a[i]) calc(a[i],-1);
	L=1;ans[1]=1;
	for (int i=1;i<=tot;i++)
	if (num[i]!=0)
	{
		while (num[i]--) mul(prime[i]);
	}
	for (int i=1;i<=n-2-tot;i++) mul(m);
	for (int i=L;i>=1;i--)
	{
		if (i==L) printf("%d",ans[i]);
			else printf("%06d",ans[i]);
	}
	return 0;
}
