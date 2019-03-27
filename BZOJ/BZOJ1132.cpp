#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
using namespace std;
const int N=3010;
int n;
struct node{int x,y;}a[N],A[N];
ll cross(node a,node b) { return (ll)a.x*b.y-(ll)a.y*b.x;}
bool cmp(node a,node b) { return cross(a,b)>0;}
bool CMP(node a,node b) { return (a.x==b.x)?a.y<b.y:a.x<b.x;}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d%d",&a[i].x,&a[i].y);
	sort(a+1,a+n+1,CMP);
	ll ans=0;
	for (int i=1;i<=n;i++)
	{
		int cnt=0;
		for (int j=i+1;j<=n;j++)
			A[++cnt]=(node){a[j].x-a[i].x,a[j].y-a[i].y};
		sort(A+1,A+cnt+1,cmp);
		ll sumx=0,sumy=0;
		for (int j=1;j<=cnt;j++)
		{
			ans+=(ll)A[j].x*sumy-(ll)A[j].y*sumx;
			sumx+=A[j].x;
			sumy+=A[j].y;
		}
	}
	ans=abs(ans);
	printf("%lld.%c\n",ans>>1,"05"[ans&1]);
	return 0;
}
