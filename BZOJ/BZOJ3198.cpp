#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define M 2333
#define mo 1000003
#define ll long long
using namespace std;
const int N=100010;
int n,k,a[N][7],C[7][7],tot,cnt,Next[N],head[mo],tree[N],num[N],p[mo];
ll f[7];
int Count(int x)
{
	int ans=0;
	for (;x;x=x&(x-1)) ans++;
	return ans;
}
bool calc_same(int x,int y,int sta)
{
	for (int i=1;i<=6;i++)
		if ((sta&(1<<(i-1)))&&a[x][i]!=a[y][i]) return 0;
	return 1;
}
void add(int x,int y)
{
	tot++;
	Next[tot]=head[x];
	head[x]=tot;
	tree[tot]=y;
	num[tot]=1;
}
int Insert(int x,int now,int sta)
{
	if (p[x]!=cnt) { p[x]=cnt;head[x]=0;}
	for (int i=head[x];i;i=Next[i])
		if (calc_same(tree[i],now,sta)) { num[i]++;return num[i]-1;}
	add(x,now);
	return 0;
}
ll calc(int sta)
{
	cnt++;tot=0;
	ll ans=0;
	for (int i=1;i<=n;i++)
	{
		ll sum=0;
		for (int j=1;j<=6;j++)
			if (sta&(1<<(j-1))) (sum=sum*M%mo+a[i][j])%=mo;
		ans+=Insert(sum,i,sta);
	}
	return ans;
}
int main()
{
	scanf("%d%d",&n,&k);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=6;j++) scanf("%d",&a[i][j]);
	C[0][0]=1;
	for (int i=1;i<=6;i++)
	{
		C[i][0]=1;
		for (int j=1;j<=i;j++) C[i][j]=C[i-1][j]+C[i-1][j-1];
	}
	calc(7);
	for (int i=0;i<=(1<<6)-1;i++) f[Count(i)]+=calc(i);
	ll ans=0;
	for (int i=k;i<=6;i++) ans+=(ll)(((i-k)&1)?-1:1)*C[i][k]*f[i];
	printf("%lld\n",ans);
	return 0;
}
