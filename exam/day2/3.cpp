#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
using namespace std;
const int N=1000100;
int n,R,a[N],Rank[N],f[N],A[N],pos[N],cnt;
ll K;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9') { if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9') { x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
inline int lowbit(int x) { return x&(-x);}
void add(int x)
{
	for (int i=x;i<=n;i+=lowbit(i)) f[i]++;
}
int query(int x)
{
	int ans=0;
	for (int i=x;i>=1;i-=lowbit(i)) ans+=f[i];
	return ans;
}
int main()
{
	freopen("sort.in","r",stdin);
	freopen("sort.out","w",stdout);
	scanf("%d%lld",&n,&K);
	ll sum=0;
	for (int i=1;i<=n;i++)
	{
		if (sum+n-i>K) { R=i;break;}
		sum+=n-i;
	}
	for (int i=1;i<=n;i++) a[i]=read();
	R--;
	for (int i=1;i<=n;i++)
	{
		Rank[i]=query(a[i]);
		add(a[i]);
	}
	int num=0;
	for (int i=1;i<=n;i++)
	{
		if (a[i]<=R) { pos[++num]=i;continue;}
		if (Rank[i]<R) A[++cnt]=a[i],pos[++num]=i;
	}
	sort(A+1,A+cnt+1);
	for (int i=num,j=1;j<=cnt;i--,j++) a[pos[i]]=A[j];
	for (int i=1,j=R+2;i<=K-sum;i++,j++)
	{
		if (a[j]<a[R+1]) swap(a[j],a[R+1]);
	}
	for (int i=1;i<=R;i++) printf("%d%c",i," \n"[i==n]);
	for (int i=R+1;i<=n;i++) printf("%d%c",a[i]," \n"[i==n]);
	return 0;
}
