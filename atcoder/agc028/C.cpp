#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<set>
#define ll long long
#define mo 1000000007 
using namespace std;
const int N=100010;
int n,a[N],b[N],p[N],X,Y,tot;
struct node {int x,id;}A[N*2];
ll ans=0,Ans=1L<<60;
bool cmp(node a,node b) { return a.x<b.x;}
void Insert(int i)
{
	int j=abs(i);
	p[j]++;
	if (i==j) X++;else Y++;
	if (p[j]==1) tot++;
	ans+=A[i].x;
}
void Del(int i)
{
	int j=abs(i);
	p[j]--;
	if (i==j) X--;else Y--;
	if (p[j]==0) tot--;
	ans-=A[i].x;
}
bool check()
{
	if (tot!=n||X==n||Y==n) return 1;
	return 0;
}
int main()
{
	scanf("%d",&n);
	int cnt=0;
	for (int i=1;i<=n;i++)
	{
		scanf("%d%d",&a[i],&b[i]);
		A[++cnt]=(node){a[i],i};
		A[++cnt]=(node){b[i],-i};
	}
	sort(A+1,A+n+1,cmp);
	for (int i=1;i<=n;i++) Insert(i);
	Del(n);
	Insert(n+1);
	if (check()) { printf("%lld\n",ans);return 0;}
	for (int i=1;i<n;i++)
	{
		Del(i);
		if (check()) Ans=min(Ans,ans);
		Insert(i);
	}
	Insert(n+2);
	Del(n);
	Del(n+1);
	if (check()) Ans=min(Ans,ans);
	printf("%lld\n",ans);
	return 0;
}
